//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/keywords.h"
#include "tmpofd/elem/ofd/custom_datas.h"

namespace tmpofd::elem {

struct DocInfo {
  string_t doc_id_;
  string_t title_;
  string_t author_;
  string_t subject_;
  string_t abstract_;
  date_t creation_date_;
  date_t mod_date_;
  string_t doc_usage_;
  loc_t cover_;
  Keywords keywords_;
  string_t creator_;
  string_t creator_version_;
  CustomDatas custom_datas_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

using namespace tmpofd::elem;
REFLECT(
    DocInfo, OFD_NAMESPACE"DocInfo",
    ATTR() CHILD_ELEM(
        FIELD(&DocInfo::doc_id_, OFD_NAMESPACE"DocID"),
        FIELD(&DocInfo::title_, OFD_NAMESPACE"Title"),
        FIELD(&DocInfo::author_, OFD_NAMESPACE"Author"),
        FIELD(&DocInfo::subject_, OFD_NAMESPACE"Subject"),
        FIELD(&DocInfo::abstract_, OFD_NAMESPACE"Abstract"),
        FIELD(&DocInfo::creation_date_, OFD_NAMESPACE"CreationDate"),
        FIELD(&DocInfo::mod_date_, OFD_NAMESPACE"ModDate"),
        FIELD(&DocInfo::doc_usage_, OFD_NAMESPACE"DocUsage"),
        FIELD(&DocInfo::cover_, OFD_NAMESPACE"Cover"),
        FIELD(&DocInfo::keywords_, OFD_NAMESPACE"Keywords"),
        FIELD(&DocInfo::creator_, OFD_NAMESPACE"Creator"),
        FIELD(&DocInfo::creator_version_, OFD_NAMESPACE"CreatorVersion"),
        FIELD(&DocInfo::custom_datas_, OFD_NAMESPACE"CustomDatas")
    )
)

#include "tmpofd/refl/reflect_end.h"
