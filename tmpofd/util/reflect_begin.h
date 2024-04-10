//
// Created by Yinxf on 2024/4/10.
//

#define REFLECT(type, ...)                                  \
  template<>                                                \
  struct type_info<type> : internal::base_type_info<type> { \
  static constexpr std::string_view name() {                \
    return #type;                                           \
  }                                                         \
  __VA_ARGS__                                               \
};

#define FIELDS(...) inline static constexpr auto fields = std::make_tuple(__VA_ARGS__);

#define FIELD(pointer) field_traits { pointer, #pointer }

#ifdef TMPOFD_REFLECT_BEGIN
#error  "Unfinished reflection, check whether 'reflect_begin.h' and 'reflect_end.h' are paired"
#define TMPOFD_REFLECT_BEGIN
#endif

namespace tmpofd::util {
