//
// Created by Yinxf on 2024/4/10.
//

#define REFLECT(elem_type, elem_name, ...)                        \
template<>                                                        \
struct element<elem_type> {                                       \
  static constexpr std::string_view name() {                      \
    return elem_name;                                             \
  }                                                               \
  __VA_ARGS__                                                     \
};                                                                \
template<>                                                        \
constexpr auto reflect_it(const elem_type &it) {                  \
  return internal::reflect<std::remove_cvref_t<decltype(it)>>();  \
}

#define ATTR(...) static constexpr inline auto attr_ = std::make_tuple(__VA_ARGS__);

#define CHILD_ELEM(...) static constexpr inline auto child_elem_ = std::make_tuple(__VA_ARGS__);

#define FIELD(pointer, name) field_traits { pointer, name }

#ifdef TMPOFD_REFLECT_BEGIN
#error  "Unfinished reflection, check whether 'reflect_begin.h' and 'reflect_end.h' are paired"
#define TMPOFD_REFLECT_BEGIN
#endif

namespace tmpofd::refl {
