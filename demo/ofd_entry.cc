//
// Created by Yinxf on 2024/4/9.
//

#include "ofd_entry.h"

#include "tmpofd/elem/ofd/ofd.h"

namespace tmpofd {
} // tmpofd

int main() {
  OFD ofd{"1.1", "OFD", {{"Doc_0/Document.xml", "Doc_0/Signs/Signatures.xml"}}};

  auto reflected = tmpofd::util::reflect<decltype(ofd)>();

  std::vector<std::pair<std::string_view, std::string &>> table;
  reflected.visit_attributes(
      [&table, &ofd](auto &&attribute) {
        table.emplace_back(attribute.name(), attribute.get(ofd).value_);
      }
  );

  table[0].second = "1.8";
  table[1].second = "doc_type";

  return 0;
}
