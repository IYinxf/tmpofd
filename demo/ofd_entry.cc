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
  auto reflected_ofd = tmpofd::refl::reflect_it(t);
  std::cout << "struct name = " << reflected_ofd.struct_name() << std::endl;

  auto b = is_reflected_v<decltype(t)>;

  reflected_ofd.visit_fields(
      [&t](auto &&field) {
        if constexpr (tmpofd::elem::internal::is_attribute_v<decltype(field.invoke(t))>) {
          auto &attr = field.invoke(t);
          std::cout << "\tattribute field name = " << field.name() << std::endl;
          std::cout << "\tattribute field value = " << attr.value_ << std::endl;
          attr.value_ = "test";
          std::cout << "\tattribute field value = " << attr.value_ << std::endl;
        } else if constexpr (tmpofd::elem::internal::is_vector_v<decltype(field.invoke(t))>) {
          std::cout << "\t\tcontainer field name = " << field.name() << std::endl;
          for (auto &i : field.invoke(t)) {
            test(i);
          }
        } else {
          std::cout << "\t\tfield name = " << field.name() << std::endl;
          auto &member = field.invoke(t);
          std::cout << "\t\tfield value = " << member << std::endl;
          member = "test";
          tmpofd::elem::loc_t value("test1");
          std::cout << "\t\tfield value = " << member << std::endl;
        }
      }
  );

}

int main() {
  tmpofd::elem::OFD ofd{"1.1", "OFD", {{"Doc_0/Document.xml", "Doc_0/Signs/Signatures.xml"}}};
  auto b = is_reflected_v<decltype(ofd)>;

  test(ofd);

  return 0;
}
