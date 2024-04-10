//
// Created by Yinxf on 2024/4/9.
//

#include "ofd_entry.h"

#include "tmpofd/element/ofd/ofd.h"
#include "mirrow/srefl/reflect.hpp"

namespace tmpofd {
} // tmpofd

int main() {

  std::string DocInfo("DocInfo");

  DocInfo[0] = std::tolower(DocInfo[0], std::locale());

  tmpofd::element::OFD ofd {
    "1.1", "OFD"
  };//, {{"Doc_0/Document.xml", "Doc_0/Signs/Signatures.xml"}}

  auto reflect = mirrow::srefl::reflect<decltype(ofd)>();

  std::vector<std::pair<std::string_view, std::string_view>> table;
  reflect.visit_member_variables([&table, &ofd](auto&& field) {
    auto& member = field.invoke(&ofd);

    table.emplace_back(field.name(), member.value);
  });

  return 0;
}
