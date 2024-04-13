//
// Created by Yinxf on 24-4-13.
//

#pragma once

#include <type_traits>
#include <string>
#include <string_view>

namespace tmpofd::serd {

namespace internal {

namespace detail {

template<template<typename...> typename T, typename>
struct is_template_of : std::false_type {};

template<template<typename...> typename T, typename... args>
struct is_template_of<T, T<args...>> : std::true_type {};

} // detail

template<typename T>
constexpr inline bool is_string_v = detail::is_template_of<std::basic_string, std::remove_cvref_t<T>>::value;

template<typename T>
constexpr inline bool is_string_view_v = detail::is_template_of<std::basic_string_view, std::remove_cvref_t<T>>::value;

template<typename T>
constexpr inline bool is_string_container_v = is_string_v<T> || is_string_view_v<T>;

} // internal

} // tmpofd::serd
