//
// Created by Yinxf on 2024/4/10.
//

#define REFLECT(class_t, class_name, ...)                         \
template<>                                                        \
struct class_info<class_t> {                                      \
  static constexpr std::string_view name() {                      \
    return class_name;                                            \
  }                                                               \
  __VA_ARGS__                                                     \
};                                                                \
inline static constexpr auto reflect_it(class_t &it) {            \
  return internal::reflect<std::remove_cvref_t<decltype(it)>>();  \
}

#define FIELDS(...) inline static constexpr auto fields_ = std::make_tuple(__VA_ARGS__);

#define FIELD(pointer, name) field_traits { pointer, name }

#ifdef TMPOFD_REFLECT_BEGIN
#error  "Unfinished reflection, check whether 'reflect_begin.h' and 'reflect_end.h' are paired"
#define TMPOFD_REFLECT_BEGIN
#endif

namespace tmpofd::refl {
