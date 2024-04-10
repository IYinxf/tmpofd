//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/ofd/doc_info.h"
#include "tmpofd/element/ofd/versions.h"

namespace tmpofd::element {

struct DocBody {
  DocInfo DocInfo;
  loc_t DocRoot;
  Versions Versions;
  loc_t Signatures;

};

} // tmpofd::element

#include "tmpofd/util/reflect_begin.h"

REFLECT(
    tmpofd::element::DocBody,
    FIELDS(
        FIELD(&tmpofd::element::DocBody::DocRoot),
        FIELD(&tmpofd::element::DocBody::Signatures)
    )
)

#include "tmpofd/util/reflect_end.h"
