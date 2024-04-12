//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/refl/traits.h"

namespace tmpofd::refl {

template<typename T>
struct class_info;

template<typename T>
struct reflected_info final {
  using class_ = class_info<T>;

  constexpr auto class_name() const noexcept {
    return class_::name();
  }

  template<typename F>
  void visit_fields(F &&callback) {
    if constexpr (internal::has_fields<class_>) {
      std::apply(
          [&callback](auto &&... args) {
            (callback(std::forward<decltype(args)>(args)), ...);
          },
          class_::fields_
      );
    }
  }

};

namespace internal {

template<typename T>
constexpr auto reflect() {
  return reflected_info<std::remove_cvref_t<T>>();
}

}

} // tmpofd::refl
