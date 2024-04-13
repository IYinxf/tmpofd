//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/doc_body.h"

namespace tmpofd::elem {

struct OFD {
  attribute_t<string_t> version_;
  attribute_t<string_t> doc_type_;

  vector_t<DocBody> doc_body_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::OFD, OFD_NAMESPACE"OFD",
    FIELDS(
        FIELD(&tmpofd::elem::OFD::version_, "Version"),
        FIELD(&tmpofd::elem::OFD::doc_type_, "DocType"),
        FIELD(&tmpofd::elem::OFD::doc_body_, OFD_NAMESPACE"DocBody")
    )
)

#include "tmpofd/refl/reflect_end.h"
