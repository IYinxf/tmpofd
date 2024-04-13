//
// Created by Yinxf on 2024/4/9.
//

#pragma once

#include <type_traits>
#include <string_view>
#include <functional>

namespace tmpofd::refl {

namespace internal {

namespace detail {

template<typename>
struct list_size_t;

template<template<typename...> typename T, typename... Args>
struct list_size_t<T<Args...>> {
  constexpr static size_t value_ = sizeof...(Args);
};

template<typename T>
constexpr size_t list_size_v = list_size_t<T>::value_;

template<typename T>
constexpr inline bool is_empty_list_v = list_size_v<T> == 0;

}

template<typename T>
constexpr inline bool has_fields = !detail::is_empty_list_v<std::remove_cvref_t<decltype(T::fields_)>>;

}

template<typename T>
struct field_traits final {
  constexpr field_traits(T &&pointer, std::string_view name)
      : pointer_(std::forward<T>(pointer)),
        name_(name) {}

  constexpr auto name() const noexcept { return name_; }

  template<typename... Args>
  decltype(auto) invoke(Args &&... args) { return std::invoke(this->pointer_, std::forward<Args>(args)...); }

 private:
  T pointer_;
  std::string_view name_;

};

} // tmpofd::refl
