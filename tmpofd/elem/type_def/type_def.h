//
// created by yinxf on 2024/4/9.
//

#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace tmpofd::elem {

namespace internal {

namespace detail {

template<typename T>
using array_t = std::vector<T>;

template<typename>
constexpr inline bool is_array_t = false;

template<typename T>
constexpr inline bool is_array_t<array_t<T>> = true;

template<typename T>
struct attribute_t {
  using type = T;

  attribute_t &operator=(T &&value) {
    value_ = std::move(value);
    return *this;
  }

  explicit operator T() { return value_; }

  T value_;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const attribute_t<T> &attr) {
  os << attr.value_;
  return os;
}

template<typename>
constexpr inline bool is_attribute_t = false;

template<typename T>
constexpr inline bool is_attribute_t<attribute_t<T>> = true;

template<typename T>
using vector_t = std::vector<T>;

template<typename, typename = void>
constexpr inline bool is_vector_t = false;

template<typename T>
constexpr inline bool is_vector_t<vector_t<T>> = true;

} // detail

template<typename T>
constexpr inline bool is_array_t_v = detail::is_array_t<std::remove_cvref_t<T>>;

} // internal

#define OFD_NAMESPACE "ofd:"

using bool_t = bool;

using int_t = int;

using id_t = unsigned int;

using ref_id_t = unsigned int;

using string_t = std::string;

using date_t = string_t;

using loc_t = std::filesystem::path;

template<typename T, std::enable_if_t<!std::is_same_v<T, loc_t> && !internal::is_array_t_v<T>, int> = 0>
using array_t = internal::detail::array_t<T>;

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
using attribute_t = internal::detail::attribute_t<T>;

template<typename T>
constexpr inline bool is_attribute_t_v = internal::detail::is_attribute_t<std::remove_cvref_t<T>>;

template<typename T>
using vector_t = internal::detail::vector_t<T>;

template<typename T>
constexpr inline bool is_vector_t_v = internal::detail::is_vector_t<std::remove_cvref_t<T>>;

} // tmpofd::elem
