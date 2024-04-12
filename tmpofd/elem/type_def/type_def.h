//
// created by yinxf on 2024/4/9.
//

#pragma once

#include "tmpofd/refl/traits.h"

#include <filesystem>

namespace tmpofd::elem {

#define OFD_NAMESPACE "ofd:"

using bool_t = bool;

using int_t = int;

using id_t = unsigned int;

using ref_id_t = unsigned int;

using string_t = std::string;

using date_t = string_t;

template<typename T>
using vector_t = std::vector<T>;

using loc_t = std::filesystem::path;

template<typename T, std::enable_if_t<!std::is_same_v<T, loc_t> && !tmpofd::refl::internal::is_st_array_v<T>, int> = 0>
using array_t = vector_t<T>;

template<typename X, typename Y>
struct pos_t {
  X x_;
  Y y_;
};

template<typename X, typename Y, typename W, typename H>
struct box_t {
  X x_;
  Y y_;
  W w_;
  H h_;
};

template<typename T>
struct attribute_t {
  T value_;
};

} // tmpofd::elem
