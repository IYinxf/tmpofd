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

using namespace tmpofd::elem;
REFLECT(
    OFD, OFD_NAMESPACE"OFD",
    ATTR(
        FIELD(&OFD::version_, "Version"),
        FIELD(&OFD::doc_type_, "DocType")
    ) CHILD_ELEM(
        FIELD(&OFD::doc_body_, OFD_NAMESPACE"DocBody")
    )
)

#include "tmpofd/refl/reflect_end.h"
