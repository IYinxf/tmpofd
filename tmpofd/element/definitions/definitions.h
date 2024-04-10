//
// Created by Yinxf on 2024/4/9.
//

#pragma once

#include <filesystem>

namespace tmpofd::element {

static const std::string _namespace("ofd:");

using String = std::string;

template<typename T>
using Vector = std::vector<T>;

using Date = std::string;

namespace detail {

template<typename T>
using Array = std::vector<T>;

template<typename>
inline constexpr bool is_st_array = false;

template<typename T>
inline constexpr bool is_st_array<Array<T>> = true;

template<typename T>
inline constexpr bool st_array_v = is_st_array<T>;

}

using ST_Loc = std::filesystem::path;

template<typename T, std::enable_if_t<!std::is_same_v<T, ST_Loc> && !detail::st_array_v<T>, int> = 0>
using ST_Array = detail::Array<T>;

using ST_ID = unsigned int;

using ST_RefID = unsigned int;

template<typename X, typename Y>
struct ST_Pos {
  X x;
  Y y;
};

using ST_Pos_s = ST_Pos<std::string, std::string>;
using ST_Pos_f = ST_Pos<float, float>;

template<typename X, typename Y, typename W, typename H>
struct ST_Box {
  X x;
  Y y;
  W w;
  H h;
};

using ST_Box_s = ST_Box<std::string, std::string, std::string, std::string>;
using ST_Box_f = ST_Box<float, float, float, float>;

template<typename T>
struct Attribute {
  T value;
};

} // tmpofd::element
