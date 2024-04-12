//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/refl/traits.h"

namespace tmpofd::refl {

template<typename>
struct class_info;

template<typename T>
struct reflected_info final {
  using class_ = class_info<T>;

  constexpr auto class_name() const noexcept {
    return class_::name();
  }

  template<size_t Idx, typename Function>
  void do_visit_member_variables(Function &&func) {
    auto fields = class_::fields_;
    if constexpr (Idx < tmpofd::refl::internal::detail::list_size_v<
        std::remove_cv_t<std::remove_reference_t<decltype(fields)>>
    >) {
      func(std::get<Idx>(fields));
      do_visit_member_variables<Idx + 1>(std::forward<Function>(func));
    }
  }

  template<typename F>
  void visit_fields(F &&callback) {
    if constexpr (internal::has_fields<class_>) {
      do_visit_member_variables<0>(std::forward<F>(callback));

//      auto _fields = class_::fields_;
//
//      [&callback, &_fields]<std::size_t... i>(std::index_sequence<i...>) {
//        (callback(std::get<i>(_fields)), ...);
//      }(std::make_index_sequence<std::tuple_size_v<decltype(_fields)>>());
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
