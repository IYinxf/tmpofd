//
// Created by Yinxf on 2024/4/9.
//

#include "ofd_entry.h"

#include "tmpofd/element/ofd/ofd.h"

namespace tmpofd {
} // tmpofd

int main() {

  tmpofd::element::OFD ofd{"1.1", "OFD", {{"Doc_0/Document.xml", "Doc_0/Signs/Signatures.xml"}}};

  auto reflected = tmpofd::util::reflect<tmpofd::element::OFD>();

  std::vector<std::pair<std::string_view, std::string&>> table;
  reflected.visit_fields([&table, &ofd](auto &&field) {
    auto &member = std::invoke(field.pointer(), &ofd);

    table.emplace_back(field.name(), member.value_);
  });

  table[0].second = "1.8";
  table[1].second = "doc_type";

  return 0;
}
