//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/ofd/keywords.h"
#include "tmpofd/element/ofd/custom_datas.h"

namespace tmpofd::element {

struct DocInfo {
  String DocID;
  String Title;
  String Author;
  String Subject;
  String Abstract;
  Date CreationDate;
  Date ModDate;
  String DocUsage;
  ST_Loc Cover;
  Keywords Keywords;
  String Creator;
  String CreatorVersion;
  CustomDatas CustomDatas;

};

} // tmpofd::element
