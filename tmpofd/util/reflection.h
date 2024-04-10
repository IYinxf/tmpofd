//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/util/traits.h"

namespace tmpofd::util {

namespace internal {

template<typename T>
struct base_type_info {
  using type_ = T;
};

}

template<typename T>
struct type_info;

template<typename T>
struct reflected_info final {
 public:
  using type_ = type_info<T>;

  constexpr auto name() const noexcept {
    return type_::name();
  }

  template<typename Function>
  void visit_fields(Function &&func) {
    if constexpr (internal::has_fields_v<type_>) {
      std::apply(
          [&func](auto &&... args) {
            (func(std::forward<decltype(args)>(args)), ...);
          },
          type_::fields);
    }
  }

};

template<typename T>
constexpr auto reflect() {
  return reflected_info<std::remove_cvref_t<T>>();
}

} // tmpofd::util
