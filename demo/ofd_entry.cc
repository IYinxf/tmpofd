//
// Created by Yinxf on 2024/4/9.
//

#include "tmpofd/elem/ofd/ofd.h"
#include "tmpofd/serd/serialization.h"
#include "tmpofd/serd/deserialization.h"

#include <iostream>

template<typename, typename = void>
struct is_reflected_t : std::false_type {};

template<typename T>
struct is_reflected_t<
    T, std::void_t<decltype(tmpofd::refl::reflect_it(std::declval<T>()))>
> : std::true_type {
};

template<typename T>
constexpr inline bool is_reflected_v = is_reflected_t<T>::value;

template<typename T>
void test(T &t) {
  auto reflected = tmpofd::refl::reflect_it(t);
  std::cout << "struct = " << reflected.struct_name() << std::endl;

  reflected.visit_fields(
      [&t](auto &&field) {
        if constexpr (tmpofd::elem::internal::is_attribute_v<decltype(field.invoke(t))>) {
          auto &attr = field.invoke(t);
          std::cout << "attribute = " << field.name() << ", value = " << attr << std::endl;
        } else if constexpr (tmpofd::elem::internal::is_vector_v<decltype(field.invoke(t))>) {
          std::cout << "container = " << field.name() << std::endl;
          for (auto &i : field.invoke(t)) {
            if constexpr (is_reflected_v<decltype(i)>) {
              test(i);
            } else {
              std::cout << "value = " << i << std::endl;
            }
          }
        } else {
          if constexpr (is_reflected_v<decltype(field.invoke(t))>) {
            test(field.invoke(t));
          } else {
            auto &member = field.invoke(t);
            std::cout << "field = " << field.name() << ", value = " << member << std::endl;
          }
        }
      }
  );

}

int main() {
  tmpofd::elem::OFD ofd;
  ofd.Version = "Version";
  ofd.DocType = "DocType";
  ofd.DocBody = {
      {
          {
              "DocID",
              "Title",
              "Author",
              "Subject",
              "Abstract",
              "CreationDate",
              "ModDate",
              "DocUsage",
              "Cover",
              {{"Keyword1", "Keyword2"}},
              "Creator",
              "CreatorVersion",
              {{{"CustomData1"}, {"CustomData2"}}}
          },
          "DocRoot",
          {{{1, 1, true, "Version1"}, {2, 2, false, "Version2"}}},
          "Signatures"
      }
  };

  test(ofd);

  return 0;
}
