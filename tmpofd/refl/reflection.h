//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/refl/traits.h"

namespace tmpofd::refl {

template<typename>
struct struct_info;

template<typename T>
struct reflected final {
  using struct_ = struct_info<T>;

  constexpr auto struct_name() const noexcept {
    return struct_::name();
  }

  template<typename F>
  void visit_fields(F &&callback) {
    if constexpr (internal::has_fields<struct_>) {
      auto fields = struct_::fields_;

      [&callback, &fields]<std::size_t... i>(std::index_sequence<i...>) {
        (callback(std::get<i>(fields)), ...);
      }(std::make_index_sequence<std::tuple_size_v<decltype(fields)>>());
    }
  }

};

namespace internal {

template<typename T>
constexpr auto reflect() {
  return reflected<std::remove_cvref_t<T>>();
}

}

} // tmpofd::refl
