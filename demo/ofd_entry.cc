//
// Created by Yinxf on 2024/4/9.
//

#include "ofd_entry.h"

#include "tmpofd/elem/ofd/ofd.h"
#include "tmpofd/serd/serialization.h"
#include "tmpofd/serd/deserialization.h"

#include <iostream>

namespace tmpofd {
} // tmpofd

template<typename T>
void test(T &t) {
  auto _reflected_ofd = tmpofd::refl::reflect_it(t);
  std::cout << "class name = " << _reflected_ofd.class_name() << std::endl;

  _reflected_ofd.visit_fields(
      [&t](auto &&field) {
        std::cout << "\tattribute field name = " << field.name() << std::endl;

        if constexpr (tmpofd::elem::internal::is_attribute_v<decltype(field.invoke(t))>) {
          auto &_attr = field.invoke(t);
          std::cout << "\tattribute field name = " << field.name() << std::endl;
          std::cout << "\tattribute field value = " << _attr.value_ << std::endl;
          _attr.value_ = "test";
          std::cout << "\tattribute field value = " << _attr.value_ << std::endl;
        } else if constexpr (tmpofd::elem::internal::is_vector_v<decltype(field.invoke(t))>) {
          std::cout << "container field name = " << field.name() << std::endl;
          for (auto &_i : field.invoke(t)) {
            test(_i);
          }
        } else {
          std::cout << "\t\tfield name = " << field.name() << std::endl;
          auto &member = field.invoke(t);
          std::cout << "\t\tfield value = " << member << std::endl;
          member = "test";
          tmpofd::elem::loc_t value("test1");
          field.invoke(t, value);
          std::cout << "\t\tfield value = " << member << std::endl;
        }
      }
  );

}

int main() {
  tmpofd::elem::OFD _ofd{"1.1", "OFD", {{"Doc_0/Document.xml", "Doc_0/Signs/Signatures.xml"}}};
  test(_ofd);

  return 0;
}
