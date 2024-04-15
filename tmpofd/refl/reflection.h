//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/refl/traits.h"

namespace tmpofd::refl {

/**
 * a class info container for ofd document object
 */
template<typename>
struct element;

/**
 * accessor for class info
 */
template<typename T>
struct reflected final {
  using element = element<T>;

  constexpr auto elem_name() const noexcept {
    return element::name();
  }

  template<typename CB>
  void visit_attr(CB &&cb) {
    if constexpr (!internal::is_tuple_empty_v<decltype(element::attr_)>) {
      auto attr = element::attr_;

      [&cb, &attr]<std::size_t... i>(std::index_sequence<i...>) {
        (cb(std::get<i>(attr)), ...);
      }(std::make_index_sequence<std::tuple_size_v<decltype(attr)>>());
    }
  }

  template<typename CB>
  void visit_child_elem(CB &&cb) {
    if constexpr (!internal::is_tuple_empty_v<decltype(element::child_elem_)>) {
      auto child_elem = element::child_elem_;

      [&cb, &child_elem]<std::size_t... i>(std::index_sequence<i...>) {
        (cb(std::get<i>(child_elem)), ...);
      }(std::make_index_sequence<std::tuple_size_v<decltype(child_elem)>>());
    }
  }

};

namespace internal {

template<typename T>
constexpr auto reflect() {
  return reflected<std::remove_cvref_t<T>>();
}

} // internal

} // tmpofd::refl
