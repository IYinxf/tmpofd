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

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::DocInfo, OFD_NAMESPACE"DocInfo",
    FIELDS(
        FIELD(&tmpofd::elem::DocInfo::DocID, OFD_NAMESPACE"DocID"),
        FIELD(&tmpofd::elem::DocInfo::Title, OFD_NAMESPACE"Title"),
        FIELD(&tmpofd::elem::DocInfo::Author, OFD_NAMESPACE"Author"),
        FIELD(&tmpofd::elem::DocInfo::Subject, OFD_NAMESPACE"Subject"),
        FIELD(&tmpofd::elem::DocInfo::Abstract, OFD_NAMESPACE"Abstract"),
        FIELD(&tmpofd::elem::DocInfo::CreationDate, OFD_NAMESPACE"CreationDate"),
        FIELD(&tmpofd::elem::DocInfo::ModDate, OFD_NAMESPACE"ModDate"),
        FIELD(&tmpofd::elem::DocInfo::DocUsage, OFD_NAMESPACE"DocUsage"),
        FIELD(&tmpofd::elem::DocInfo::Cover, OFD_NAMESPACE"Cover"),
        FIELD(&tmpofd::elem::DocInfo::Keywords, OFD_NAMESPACE"Keywords"),
        FIELD(&tmpofd::elem::DocInfo::Creator, OFD_NAMESPACE"Creator"),
        FIELD(&tmpofd::elem::DocInfo::CreatorVersion, OFD_NAMESPACE"CreatorVersion"),
        FIELD(&tmpofd::elem::DocInfo::CustomDatas, OFD_NAMESPACE"CustomDatas")
    )
)

#include "tmpofd/refl/reflect_end.h"
