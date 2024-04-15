//
// Created by Yinxf on 2024/4/9.
//
#define _CRT_SECURE_NO_WARNINGS
#include "tmpofd/serd/serialization.h"
#include "tmpofd/serd/deserialization.h"

#include <iostream>

std::string readFile(const std::string &filePath, const char *mode) {
  if (filePath.empty() || nullptr == mode) return {};

  FILE * fp = fopen(filePath.c_str(), mode);
  if (nullptr == fp) return {};

  fseek(fp, 0, SEEK_END);
  long len = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::string ret(len, 0);
  if (len != fread(&ret[0], sizeof(char), len, fp)) {
    fclose(fp);
    return {};
  }
  fclose(fp);

  return ret;
}

int main() {
  auto ofd_xml = readFile(R"(E:\System\Desktop\OFD.xml)", "rb");

  tmpofd::elem::OFD ofd;

  std::vector<std::string_view> declaration;
  tmpofd::serd::from_xml(ofd_xml, declaration, ofd);

  return 0;
}
