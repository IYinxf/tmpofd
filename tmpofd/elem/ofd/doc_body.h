//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/doc_info.h"
#include "tmpofd/elem/ofd/versions.h"

namespace tmpofd::elem {

struct DocBody {
  DocInfo DocInfo;
  loc_t DocRoot;
  Versions Versions;
  loc_t Signatures;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::DocBody, OFD_NAMESPACE"DocBody",
    FIELDS(
        FIELD(&tmpofd::elem::DocBody::DocRoot, OFD_NAMESPACE"DocRoot"),
        FIELD(&tmpofd::elem::DocBody::Signatures, OFD_NAMESPACE"Signatures")
    )
)

#include "tmpofd/refl/reflect_end.h"
