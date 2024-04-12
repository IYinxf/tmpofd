//
// Created by Yinxf on 2024/4/9.
//

#include "ofd_entry.h"

#include "tmpofd/elem/ofd/ofd.h"
#include "tmpofd/serd/serialization.h"
#include "tmpofd/serd/deserialization.h"

namespace tmpofd {
} // tmpofd

int main() {
  tmpofd::elem::OFD ofd{"1.1", "OFD", {{"Doc_0/Document.xml", "Doc_0/Signs/Signatures.xml"}}};

  auto reflected = tmpofd::refl::reflect_it(ofd);
  reflected.class_name();

  auto is_class = std::is_class_v<decltype(ofd)>;

  std::vector<std::string_view> table;
  reflected.visit_fields(
      [&table, &ofd](auto &&field) {
        if constexpr (std::is_array_v<std::remove_cv_t<decltype(field)>>) {
          auto c = field[0];
          auto is_c = std::is_class_v<decltype(c)>;

        }
        auto is = std::is_class_v<decltype(field)>;
        table.emplace_back(field.name());
      }
  );

  return 0;
}
