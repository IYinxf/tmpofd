//
// Created by Yinxf on 2024/4/9.
//

#pragma once

#include <type_traits>
#include <string_view>

namespace tmpofd::refl {

namespace internal {

namespace detail {

template<typename>
struct array_t;

template<typename>
inline constexpr bool is_st_array = false;

template<typename T>
inline constexpr bool is_st_array<array_t<T>> = true;

template<typename>
struct attribute_t;

template<typename>
inline constexpr bool is_attribute = false;

template<typename T>
inline constexpr bool is_attribute<attribute_t<T>> = true;

}

template<typename T>
inline constexpr bool is_st_array_v = detail::is_st_array<T>;

template<typename T>
inline constexpr bool is_attribute_v = detail::is_attribute<T>;

}

namespace internal {

namespace detail {

template<typename T>
struct field_type {
  using type_ = T;
};

template<typename>
struct list_size;

template<template<typename...> typename T, typename... Args>
struct list_size<T<Args...>> {
  static constexpr size_t value_ = sizeof...(Args);
};

template<typename T>
constexpr size_t list_size_v = list_size<T>::value_;

template<typename T>
constexpr bool is_empty_list_v = list_size_v<T> == 0;

}

template<typename T>
using field_type_t = typename detail::field_type<T>::type_;

template<typename T>
constexpr bool has_fields = !detail::is_empty_list_v<std::remove_cv_t<decltype(T::fields_)>>;

template<typename T>
struct basic_field_traits {
  using type_ = field_type_t<T>;
};

}

template<typename T>
struct field_traits final : internal::basic_field_traits<T> {
  constexpr field_traits(T &&pointer, std::string_view name)
      : pointer_(std::forward<T>(pointer)),
        name_(name) {}

  constexpr auto name() const noexcept { return name_; }

  template<typename Object>
  constexpr auto &get(Object &&object) const noexcept { return std::invoke(pointer_, std::forward<Object>(object)); }

 private:
  T pointer_;
  std::string_view name_;

};

} // tmpofd::refl
