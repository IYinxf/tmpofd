//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/doc_info.h"
#include "tmpofd/elem/ofd/versions.h"

namespace tmpofd::elem {

struct DocBody {
  DocInfo doc_info_;
  loc_t doc_root_;
  Versions versions_;
  loc_t signatures_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::DocBody, OFD_NAMESPACE"DocBody",
    FIELDS(
        FIELD(&tmpofd::elem::DocBody::doc_info_, OFD_NAMESPACE"DocInfo"),
        FIELD(&tmpofd::elem::DocBody::doc_root_, OFD_NAMESPACE"DocRoot"),
        FIELD(&tmpofd::elem::DocBody::versions_, OFD_NAMESPACE"Versions"),
        FIELD(&tmpofd::elem::DocBody::signatures_, OFD_NAMESPACE"Signatures")
    )
)

#include "tmpofd/refl/reflect_end.h"
