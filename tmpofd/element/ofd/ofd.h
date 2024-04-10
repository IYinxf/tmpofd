//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/ofd/doc_body.h"

namespace tmpofd::element {

struct OFD {
  attributes_t<string_t> Version;
  attributes_t<string_t> DocType;

  vector_t<DocBody> DocBody;

};

} // tmpofd::element

#include "tmpofd/util/reflect_begin.h"

REFLECT(
    tmpofd::element::OFD,
    FIELDS(
        FIELD(&tmpofd::element::OFD::Version),
        FIELD(&tmpofd::element::OFD::DocType)
    )
)

#include "tmpofd/util/reflect_end.h"
//,
//FIELD(&tmpofd::element::OFD::DocBody)