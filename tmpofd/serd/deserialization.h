//
// Created by Yinxf on 24-4-12.
//

#pragma once

#include "tmpofd/refl/reflection.h"

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

}

template<typename T>
constexpr inline bool is_string_v = detail::is_template_of<std::basic_string, std::remove_cvref_t<T>>::value;

template<typename T>
constexpr inline bool is_string_view_v = detail::is_template_of<std::basic_string_view, std::remove_cvref_t<T>>::value;

template<typename T>
constexpr inline bool is_string_container_v = is_string_v<T> || is_string_view_v<T>;

}

template<
    typename Itr, typename End, typename Declaration, typename Object,
    std::enable_if_t<tmpofd::refl::internal::is_reflected_v<Object>, int> = 0
>
void from_xml(Itr &&itr, End &&end, Declaration &decl, Object &obj) {

}

template<
    typename String, typename Declaration, typename Object,
    std::enable_if_t<internal::is_string_container_v<String>, int> = 0
>
void from_xml(const String &str, Declaration &decl, Object &obj) {
  from_xml(std::begin(str), std::end(str), decl, obj);
}

} // tmpofd::serd
