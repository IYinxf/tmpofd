//
// Created by Yinxf on 24-4-12.
//

#pragma once

#include "tmpofd/serd/traits.h"
#include "tmpofd/refl/reflection.h"

#include <stdexcept>

namespace tmpofd::serd {

namespace internal {

namespace detail {

template<char... C, typename Itr>
void match(Itr &&itr, Itr &&end) {
  const auto n = static_cast<size_t>(std::distance(itr, end));
  if (n < sizeof...(C)) {
    static constexpr auto error = "Unexpected end of buffer. Expected:";
    throw std::runtime_error(error);
  }

  if ((... || (*itr++ != C))) {
    static constexpr char b[] = {C..., '\0'};
    throw std::runtime_error(std::string("Expected these: ").append(b));
  }
}

template<char c, typename Itr>
void skip_till(Itr &&it, Itr &&end) {
  static_assert(std::contiguous_iterator<std::decay_t<Itr>>);

  while (it < end) {
    if (*it == c)
      return;
    ++it;
  }

  static constexpr char b[] = {c, '\0'};
  std::string error = std::string("Expected: ").append(b);
  throw std::runtime_error(error);
}

template<char c, typename Itr>
auto skip_pass(Itr &&itr, Itr &&end) {
  skip_till<c>(itr, end);

  auto res = itr++ - 1;
  while (*res == ' ') {
    --res;
  }

  return res + 1;
}

template<typename Itr>
void skip_till_greater_or_space(Itr &&itr, Itr &&end) {
  static_assert(std::contiguous_iterator<std::decay_t<Itr>>);

  while (itr < end) {
    switch (*itr) {
      case '>':
      case ' ':return;
    }
    ++itr;
  }

  throw std::runtime_error("Expected: > or space");
}

template<typename Itr>
void skip_spaces_and_newline(Itr &&itr, Itr &&end) {
  while (itr != end && (static_cast<uint8_t>(*itr) < 33)) {
    ++itr;
  }
}

template<
    typename Object,
    std::enable_if_t<
        std::is_same_v<typename Object::type_, tmpofd::elem::bool_t>
            || std::is_same_v<typename Object::type_, tmpofd::elem::int_t>
            || std::is_same_v<typename Object::type_, tmpofd::elem::id_t>
            || std::is_same_v<typename Object::type_, tmpofd::elem::ref_id_t>,
        int
    > = 0
>
void parse_attr_value(std::string_view value, Object &obj) {
//  auto ret = std::from_chars(value.begin(), value.end(), obj);
//  if (std::errc() != ret.ec) {
//    std::string error = std::string("Parse attribute failed: ").append(value);
//    throw std::runtime_error(error);
//  }
}

template<
    typename Object,
    std::enable_if_t<
        std::is_same_v<typename Object::type_, tmpofd::elem::loc_t>
            || std::is_same_v<typename Object::type_, tmpofd::elem::string_t>,
        int
    > = 0
>
void parse_attr_value(std::string_view value, Object &obj) {
  obj = tmpofd::elem::string_t(value);
}

template<
    typename Itr, typename Object,
    std::enable_if_t<tmpofd::refl::internal::is_reflected_v<Object>, int> = 0
>
void parse_attribute(Itr &&itr, Itr &&end, Object &obj) {
  auto reflected = tmpofd::refl::reflect_it(obj);

  while (itr != end) {
    skip_spaces_and_newline(itr, end);
    if (*itr == '>' || *itr == '/') return;

    auto k_begin = itr;
    auto k_end = skip_pass<'='>(itr, end);
    std::string_view key = std::string_view{&*k_begin, static_cast<size_t>(std::distance(k_begin, k_end))};

    skip_spaces_and_newline(itr, end);
    match<'"'>(itr, end);
    auto v_begin = itr;
    auto v_end = skip_pass<'"'>(itr, end);
    std::string_view value = std::string_view{&*v_begin, static_cast<size_t>(std::distance(v_begin, v_end))};

    reflected.visit_fields(
        [&key, &value, &obj](auto &&field) {
          if (key == field.name()) {
            if constexpr (tmpofd::elem::internal::is_attribute_v<decltype(field.invoke(obj))>) {
              parse_attr_value(value, field.invoke(obj));
            }
          }
        }
    );
  }
}

template<
    typename Itr, typename Object,
    std::enable_if_t<tmpofd::refl::internal::is_reflected_v<Object>, int> = 0
>
void parse_element(Itr &&itr, Itr &&end, std::string_view name, Object &obj) { ///TODO: finish this
  parse_attribute(itr, end, obj);

  auto reflected = tmpofd::refl::reflect_it(obj);

  skip_till<'>'>(itr, end);
  ++itr;

  skip_spaces_and_newline(itr, end);
  match<'<'>(itr, end);
  auto start = itr;
  detail::skip_till_greater_or_space(itr, end);
  std::string_view key = std::string_view{&*start, static_cast<size_t>(std::distance(start, itr))};

  reflected.visit_fields(
      [&itr, &end, &key, &obj](auto &&field) {
        if (key == field.name()) {
          if constexpr (tmpofd::elem::internal::is_vector_v<decltype(field.invoke(obj))>) {
            std::remove_cvref_t<decltype(field.invoke(obj)[0])> item{};

            if constexpr (tmpofd::refl::internal::is_reflected_v<decltype(item)>) {
              parse_element(itr, end, key, item);
              field.invoke(obj).emplace_back(item);
            } else {
              auto &member = item;

              field.invoke(obj).emplace_back(item);
            }
          } else {
            if constexpr (tmpofd::refl::internal::is_reflected_v<decltype(field.invoke(obj))>) {
              parse_element(itr, end, key, field.invoke(obj));
            } else {
              auto &member = field.invoke(obj);
            }
          }
        }
      }
  );
}

} // detail

template<
    typename Itr, typename Declaration, typename Object,
    std::enable_if_t<tmpofd::refl::internal::is_reflected_v<Object>, int> = 0
>
void from_xml(Itr &&itr, Itr &&end, Declaration &decl, Object &obj) {
  while (itr != end) {
    detail::skip_spaces_and_newline(itr, end);
    detail::match<'<'>(itr, end);

    auto declaration_start = itr - 1;
    if (*itr == '?') {
      detail::skip_till<'>'>(itr, end);
      ++itr;

      decl.emplace_back(declaration_start, itr);
    } else {
      break;
    }
  }

  auto start = itr;
  detail::skip_till_greater_or_space(itr, end);
  std::string_view key = std::string_view{&*start, static_cast<size_t>(std::distance(start, itr))};
  detail::parse_element(itr, end, key, obj);
}

} // internal

template<
    typename String, typename Declaration, typename Object,
    std::enable_if_t<internal::is_string_container_v<String>, int> = 0
>
void from_xml(const String &str, Declaration &decl, Object &obj) {
  internal::from_xml(std::begin(str), std::end(str), decl, obj);
}

} // tmpofd::serd
