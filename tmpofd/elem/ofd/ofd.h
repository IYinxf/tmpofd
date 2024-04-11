//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/doc_body.h"

namespace tmpofd::element {

struct OFD {
  attributes_t<string_t> Version;
  attributes_t<string_t> DocType;

  vector_t<DocBody> DocBody;

};

} // tmpofd::elem

using OFD = tmpofd::element::OFD;

#include "tmpofd/util/reflect_begin.h"

REFLECT(
    OFD,
    ATTRIBUTES(
        ATTRIBUTE(&OFD::Version),
        ATTRIBUTE(&OFD::DocType)
    )
)

#include "tmpofd/util/reflect_end.h"
//,
//FIELD(&tmpofd::elem::OFD::DocBody)