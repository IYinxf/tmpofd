//
// Created by Yinxf on 2024/4/9.
//

#pragma once

#include <type_traits>

namespace tmpofd::util {

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
constexpr size_t list_size_v = detail::list_size<T>::value_;

template<typename T>
constexpr bool is_list_empty_v = list_size_v<T> == 0;

}

template<typename T>
using field_type_t = typename detail::field_type<T>::type_;

template<typename T>
constexpr bool has_attributes = !detail::is_list_empty_v<std::remove_cv_t<decltype(T::attributes_)>>;

template<typename T>
constexpr bool has_fields = !detail::is_list_empty_v<std::remove_cv_t<decltype(T::fields_)>>;

template<typename T>
struct basic_field_traits {
  using type_ = field_type_t<T>;
};

inline constexpr void strip_name(std::string_view &name) {
  if (auto i = name.find_last_of(':'); i != std::string_view::npos) {
    name = name.substr(i + 1, name.length());
  }
}

}

template<typename T>
struct field_traits final : internal::basic_field_traits<T> {
  constexpr field_traits(T &&pointer, std::string_view name)
      : pointer_(std::forward<T>(pointer)),
        name_(name) { internal::strip_name(name_); }

  constexpr auto name() const noexcept { return name_; }

  template<typename Object>
  constexpr auto &get(Object &&object) const noexcept { return std::invoke(pointer_, std::forward<Object>(object)); }

 private:
  T pointer_;
  std::string_view name_;

};

} // tmpofd::util
