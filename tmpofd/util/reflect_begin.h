//
// Created by Yinxf on 2024/4/10.
//

#define REFLECT(class_name, ...)              \
  template<>                                  \
  struct class_info<class_name> {             \
  static constexpr std::string_view name() {  \
    return #class_name;                       \
  }                                           \
  __VA_ARGS__                                 \
};

#define ATTRIBUTES(...) inline static constexpr auto attributes_ = std::make_tuple(__VA_ARGS__);

#define ATTRIBUTE(pointer) field_traits { pointer, #pointer }

#define FIELDS(...) inline static constexpr auto fields_ = std::make_tuple(__VA_ARGS__);

#define FIELD(pointer, name_space) field_traits { pointer, name_space#pointer }

#ifdef TMPOFD_REFLECT_BEGIN
#error  "Unfinished reflection, check whether 'reflect_begin.h' and 'reflect_end.h' are paired"
#define TMPOFD_REFLECT_BEGIN
#endif

namespace tmpofd::util {
