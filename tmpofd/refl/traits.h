//
// Created by Yinxf on 2024/4/9.
//

#pragma once

#include <type_traits>
#include <string_view>

namespace tmpofd::refl {

template<typename>
void reflect_it();

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

template<typename, typename = void>
struct is_reflected_t : std::false_type {};

template<typename T>
struct is_reflected_t<
    T,
    std::void_t<decltype(tmpofd::refl::reflect_it(std::declval<T>()))>
> : std::true_type {
};

}

template<typename T>
constexpr inline bool has_fields = !detail::is_empty_list_v<std::remove_cvref_t<decltype(T::fields_)>>;

template<typename T>
constexpr inline bool is_reflected_v = detail::is_reflected_t<std::remove_cvref_t<T>>::value;
///TODO: fix this

}

template<typename T>
struct field_traits final {
  constexpr field_traits(T &&pointer, std::string_view name)
      : pointer_(std::forward<T>(pointer)),
        name_(name) {}

  constexpr auto name() const noexcept { return name_; }

  template<typename... Args>
  decltype(auto) invoke(Args &&... args) { return std::invoke(this->pointer_, std::forward<Args>(args)...); }
  /// TODO: fix this

 private:
  T pointer_;
  std::string_view name_;

};

} // tmpofd::refl
