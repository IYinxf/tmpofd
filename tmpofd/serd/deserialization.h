//
// Created by Yinxf on 24-4-12.
//

#pragma once

#include "tmpofd/serd/traits.h"
#include "tmpofd/elem/ofd/ofd.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::serd {

namespace te = tmpofd::elem;
namespace tr = tmpofd::refl;

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

template<typename Itr>
void match_close_tag(Itr &&itr, Itr &&end, std::string_view name) {
  if (itr == end || (*itr++) != '/') {
    throw std::runtime_error("unclosed tag: " + std::string(name));
  }

  size_t size = name.size();
  if (static_cast<size_t>(std::distance(itr, end)) <= size || std::string_view{&*itr, size} != name) {
    throw std::runtime_error("unclosed tag: " + std::string(name));
  }

  itr += size;
}

template<typename Itr>
void skip_spaces_and_newline(Itr &&itr, Itr &&end) {
  while (itr != end && (static_cast<uint8_t>(*itr) < 33)) {
    ++itr;
  }
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

  throw std::runtime_error("Expected: '>' or ' '.");
}

template<typename Itr>
bool skip_till_name(Itr &&itr, Itr &&end) {
  skip_spaces_and_newline(itr, end);

  match<'<'>(itr, end);
  if ('/' == *itr) return false;

  return true;
}

template<char C, typename Itr>
void skip_till(Itr &&itr, Itr &&end) {
  static_assert(std::contiguous_iterator<std::decay_t<Itr>>);

  while (itr < end) {
    if (*itr == C)
      return;
    ++itr;
  }

  static constexpr char b[] = {C, '\0'};
  std::string error = std::string("Expected: ").append(b);
  throw std::runtime_error(error);
}

template<char C, typename Itr>
auto skip_pass(Itr &&itr, Itr &&end) {
  skip_till<C>(itr, end);

  auto res = itr++ - 1;
  while (*res == ' ') {
    --res;
  }

  return res + 1;
}

//std::enable_if_t<
//    std::is_same_v<typename Attr::type_, te::bool_t>
//        || std::is_same_v<typename Attr::type_, te::int_t>
//        || std::is_same_v<typename Attr::type_, te::id_t>
//        || std::is_same_v<typename Attr::type_, te::ref_id_t>,
//    int
//> = 0
template<
    typename Attr,
    std::enable_if_t<
        !std::is_same_v<typename Attr::type, te::loc_t> && !std::is_same_v<typename Attr::type, te::string_t>,
        int
    > = 0
>
void assign_attr(std::string_view name, std::string_view value, Attr &attr) {
/// TODO:: finish this

//  auto ret = std::from_chars(value.data(), value.data() + value.size(), attr);
//
//  if (std::errc() != ret.ec) {
//    auto error = std::string("Parse attribute failed: ").append(name);
//    throw std::runtime_error(error);
//  }
}

template<
    typename Attr,
    std::enable_if_t<
        std::is_same_v<typename Attr::type, te::loc_t> || std::is_same_v<typename Attr::type, te::string_t>,
        int
    > = 0
>
void assign_attr(std::string_view name, std::string_view value, Attr &attr) {
  (void) name;

  attr = te::string_t(value);
}

template<
    typename Itr, typename Attr,
    std::enable_if_t<tr::reflectable_v<Attr>, int> = 0
>
void parse_attribute(Itr &&itr, Itr &&end, Attr &attr) {
  auto reflected = tr::reflect_it(attr);

  while (itr != end) {
    skip_spaces_and_newline(itr, end);
    if ('>' == *itr || '/' == *itr) return;

    auto an_begin = itr;
    auto an_end = skip_pass<'='>(itr, end);
    auto attr_name = std::string_view{&*an_begin, static_cast<size_t>(std::distance(an_begin, an_end))};

    skip_spaces_and_newline(itr, end);
    match<'"'>(itr, end);
    auto av_begin = itr;
    auto av_end = skip_pass<'"'>(itr, end);
    auto attr_value = std::string_view{&*av_begin, static_cast<size_t>(std::distance(av_begin, av_end))};

    reflected.visit_attr(
        [&attr_name, &attr_value, &attr](auto &&field) {
          if (attr_name == field.name()) {
            assign_attr(attr_name, attr_value, field.invoke(attr));
          }
        }
    );
  }
}

template<
    typename Elem,
    std::enable_if_t<!std::is_same_v<Elem, te::loc_t> && !std::is_same_v<Elem, te::string_t>, int> = 0
>
void assign_elem(std::string_view name, std::string_view value, Elem &elem) {
/// TODO:: finish this
}

template<
    typename Elem,
    std::enable_if_t<
        std::is_same_v<Elem, te::loc_t> || std::is_same_v<Elem, te::date_t> || std::is_same_v<Elem, te::string_t>,
        int
    > = 0
>
void assign_elem(std::string_view name, std::string_view value, Elem &elem) {
  (void) name;

  elem = te::string_t(value);
}

template<typename Itr, typename Elem>
void parse_element_no_child(Itr &&itr, Itr &&end, std::string_view elem_name, Elem &elem) {
  skip_till<'>'>(itr, end);
  ++itr;
  skip_spaces_and_newline(itr, end);

  auto ev_begin = itr;
  auto ev_end = skip_pass<'<'>(itr, end);
  auto elem_value = std::string_view{&*ev_begin, static_cast<size_t>(std::distance(ev_begin, ev_end))};

  assign_elem(elem_name, elem_value, elem);
}

template<typename Itr, typename Elem, std::enable_if_t<!tr::reflectable_v<Elem>, int> = 0>
void parse_element(Itr &&itr, Itr &&end, std::string_view elem_name, Elem &elem) {
  parse_element_no_child(itr, end, elem_name, elem);
}

template<typename Itr, typename Elem, std::enable_if_t<tr::reflectable_v<Elem>, int> = 0>
void parse_element(Itr &&itr, Itr &&end, std::string_view elem_name, Elem &elem) {
  auto reflected = tr::reflect_it(elem);
  if (elem_name != reflected.elem_name()) return;

  parse_attribute(itr, end, elem);

  if (!tr::reflectable_in_tuple_v<decltype(tr::reflect_it(std::declval<Elem>()))>) {
    parse_element_no_child(itr, end, elem_name, elem);
    return;
  }

  while (itr != end) {
    skip_till<'>'>(itr, end);
    ++itr;

    if (!skip_till_name(itr, end)) return;

    auto cen_begin = itr;
    skip_till_greater_or_space(itr, end);
    auto child_elem_name = std::string_view{&*cen_begin, static_cast<size_t>(std::distance(cen_begin, itr))};

    reflected.visit_child_elem(
        [&itr, &end, &child_elem_name, &elem](auto &&field) {
          if (child_elem_name == field.name()) {
            if constexpr (te::is_vector_t_v<decltype(field.invoke(elem))>) {
              parse_element(itr, end, child_elem_name, field.invoke(elem).emplace_back());
            } else {
              parse_element(itr, end, child_elem_name, field.invoke(elem));
            }

            match_close_tag(itr, end, child_elem_name);
          }
        }
    );
  }
}

} // detail

template<typename Itr, typename Decl, typename Elem, std::enable_if_t<tr::reflectable_v<Elem>, int> = 0>
void from_xml(Itr &&itr, Itr &&end, Decl &decl, Elem &elem) {
  while (itr != end) {
    detail::skip_spaces_and_newline(itr, end);
    detail::match<'<'>(itr, end);

    auto decl_begin = itr - 1;
    if ('?' == *itr) {
      detail::skip_till<'>'>(itr, end);
      ++itr;

      decl.emplace_back(decl_begin, itr);
    } else {
      break;
    }
  }

  auto en_begin = itr;
  detail::skip_till_greater_or_space(itr, end);
  auto elem_name = std::string_view{&*en_begin, static_cast<size_t>(std::distance(en_begin, itr))};

  detail::parse_element(itr, end, elem_name, elem);
  detail::match_close_tag(itr, end, elem_name);
}

} // internal

template<typename Str, typename Decl, typename Elem, std::enable_if_t<internal::is_string_container_v<Str>, int> = 0>
void from_xml(const Str &str, Decl &decl, Elem &elem) {
  internal::from_xml(std::begin(str), std::end(str), decl, elem);
}

} // tmpofd::serd
