//
// created by yinxf on 2024/4/9.
//

#pragma once

#include <filesystem>

namespace tmpofd::element {

#define OFD_NAMESPACE "ofd:"

using string_t = std::string;

template<typename T>
using vector_t = std::vector<T>;

using date_t = std::string;

namespace detail {

template<typename T>
using array_t = std::vector<T>;

template<typename>
inline constexpr bool is_st_array = false;

template<typename T>
inline constexpr bool is_st_array<array_t<T>> = true;

template<typename T>
inline constexpr bool st_array_v = is_st_array<T>;

}

using loc_t = std::filesystem::path;

template<typename T, std::enable_if_t<!std::is_same_v<T, loc_t> && !detail::st_array_v<T>, int> = 0>
using array_t = detail::array_t<T>;

using id_t = unsigned int;

using ref_id_t = unsigned int;

template<typename X, typename Y>
struct pos_t {
  X x_;
  Y y_;
};

using string_pos_t = pos_t<std::string, std::string>;
using float_pos_t = pos_t<float, float>;

template<typename X, typename Y, typename W, typename H>
struct box_t {
  X x_;
  Y y_;
  W w_;
  H h_;
};

using string_box_t = box_t<std::string, std::string, std::string, std::string>;
using float_box_t = box_t<float, float, float, float>;

template<typename T>
struct attributes_t {
  T value_;
};

} // tmpofd::elem
