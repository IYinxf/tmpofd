//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/keywords.h"
#include "tmpofd/elem/ofd/custom_datas.h"

namespace tmpofd::elem {

struct DocInfo {
  string_t DocID;
  string_t Title;
  string_t Author;
  string_t Subject;
  string_t Abstract;
  date_t CreationDate;
  date_t ModDate;
  string_t DocUsage;
  loc_t Cover;
  Keywords Keywords;
  string_t Creator;
  string_t CreatorVersion;
  CustomDatas CustomDatas;

};

} // tmpofd::elem
