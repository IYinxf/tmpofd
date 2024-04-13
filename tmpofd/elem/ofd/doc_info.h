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

REFLECT(
    tmpofd::elem::DocInfo, OFD_NAMESPACE"DocInfo",
    FIELDS(
        FIELD(&tmpofd::elem::DocInfo::doc_id_, OFD_NAMESPACE"DocID"),
        FIELD(&tmpofd::elem::DocInfo::title_, OFD_NAMESPACE"Title"),
        FIELD(&tmpofd::elem::DocInfo::author_, OFD_NAMESPACE"Author"),
        FIELD(&tmpofd::elem::DocInfo::subject_, OFD_NAMESPACE"Subject"),
        FIELD(&tmpofd::elem::DocInfo::abstract_, OFD_NAMESPACE"Abstract"),
        FIELD(&tmpofd::elem::DocInfo::creation_date_, OFD_NAMESPACE"CreationDate"),
        FIELD(&tmpofd::elem::DocInfo::mod_date_, OFD_NAMESPACE"ModDate"),
        FIELD(&tmpofd::elem::DocInfo::doc_usage_, OFD_NAMESPACE"DocUsage"),
        FIELD(&tmpofd::elem::DocInfo::cover_, OFD_NAMESPACE"Cover"),
        FIELD(&tmpofd::elem::DocInfo::keywords_, OFD_NAMESPACE"Keywords"),
        FIELD(&tmpofd::elem::DocInfo::creator_, OFD_NAMESPACE"Creator"),
        FIELD(&tmpofd::elem::DocInfo::creator_version_, OFD_NAMESPACE"CreatorVersion"),
        FIELD(&tmpofd::elem::DocInfo::custom_datas_, OFD_NAMESPACE"CustomDatas")
    )
)

#include "tmpofd/refl/reflect_end.h"
