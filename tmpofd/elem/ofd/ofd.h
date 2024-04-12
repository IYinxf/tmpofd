//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/doc_body.h"

namespace tmpofd::elem {

struct OFD {
  attribute_t<string_t> Version;
  attribute_t<string_t> DocType;

  vector_t<DocBody> DocBody;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::OFD, OFD_NAMESPACE"OFD",
    FIELDS(
        FIELD(&tmpofd::elem::OFD::Version, OFD_NAMESPACE"Version"),
        FIELD(&tmpofd::elem::OFD::DocType, OFD_NAMESPACE"DocType"),
        FIELD(&tmpofd::elem::OFD::DocBody, OFD_NAMESPACE"DocBody")
    )
)

#include "tmpofd/refl/reflect_end.h"
