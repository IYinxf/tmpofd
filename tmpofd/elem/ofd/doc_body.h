//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/doc_info.h"
#include "tmpofd/elem/ofd/versions.h"

namespace tmpofd::element {

struct DocBody {
  DocInfo DocInfo;
  loc_t DocRoot;
  Versions Versions;
  loc_t Signatures;

};

} // tmpofd::elem

using DocBody = tmpofd::element::DocBody;

#include "tmpofd/util/reflect_begin.h"

REFLECT(
    DocBody,
    FIELDS(
        FIELD(&DocBody::DocRoot, OFD_NAMESPACE),
        FIELD(&DocBody::Signatures, OFD_NAMESPACE)
    )
)

#include "tmpofd/util/reflect_end.h"
