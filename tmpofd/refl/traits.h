//
// Created by Yinxf on 2024/4/9.
//

#pragma once

#include <type_traits>
#include <string_view>
#include <functional>

namespace tmpofd::refl {

/**
 * reflect object 'it' to reflected<T>
 */
template<typename T>
constexpr auto reflect_it(T const &it);

namespace internal {

namespace detail {

/**
 * int
 */
template<typename T>
struct basic_type_traits {
  using type = T;
};

/**
 * int FOO::*
 */
template<typename Class, typename T>
struct basic_type_traits<T Class::*> {
  using type = T;
};

/**
 * std::vector<int> FOO::*
 */
template<typename Class, typename T>
struct basic_type_traits<std::vector<T> Class::*> {
  using type = T;
};

template<typename T>
struct is_tuple_empty : std::false_type {};

template<>
struct is_tuple_empty<std::tuple<>> : std::true_type {};

template<typename, typename = void>
struct reflectable : std::false_type {};

template<typename T>
struct reflectable<T, std::void_t<decltype(tmpofd::refl::reflect_it(std::declval<T>()))>> : std::true_type {};

template<typename T>
struct reflectable_in_tuple : reflectable<typename T::type> {};

template<>
struct reflectable_in_tuple<std::tuple<>> : std::false_type {};

template<typename T>
struct reflectable_in_tuple<std::tuple<T>> : reflectable_in_tuple<T> {};

template<typename T, typename... Remains>
struct reflectable_in_tuple<std::tuple<T, Remains...>> {
  static constexpr bool value = reflectable_in_tuple<T>::value || reflectable_in_tuple<std::tuple<Remains...>>::value;
};

} // detail

template<typename T>
using basic_type_traits_t = typename detail::basic_type_traits<T>::type;

template<typename T>
constexpr inline bool is_tuple_empty_v = detail::is_tuple_empty<std::remove_cvref_t<T>>::value;

} // internal

template<typename T>
struct field_traits final {
  using type = internal::basic_type_traits_t<T>;

  constexpr field_traits(T &&pointer, std::string_view name) : pointer_(std::forward<T>(pointer)), name_(name) {}

  constexpr auto name() const noexcept { return name_; }

  template<typename... Args>
  decltype(auto) invoke(Args &&... args) { return std::invoke(this->pointer_, std::forward<Args>(args)...); }

 private:
  T pointer_;
  std::string_view name_;

};

/**
 * it will be 'true' if class T defined reflect_it overload using 'reflect_begin.h' and 'reflect_end.h'
 */
template<typename T>
constexpr inline bool reflectable_v = internal::detail::reflectable<std::remove_cvref_t<T>>::value;

/**
 * check is there a field reflectable in std::tuple
 */
template<typename T>
constexpr inline bool reflectable_in_tuple_v = internal::detail::reflectable_in_tuple<
    std::remove_cvref_t<decltype(T::element::child_elem_)>
>::value;

} // tmpofd::refl
