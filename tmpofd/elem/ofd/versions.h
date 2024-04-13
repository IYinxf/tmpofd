//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/version.h"

namespace tmpofd::elem {

struct Versions {
  vector_t<Version> Version;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::Versions, OFD_NAMESPACE"Versions",
    FIELDS(
        FIELD(&tmpofd::elem::Versions::Version, OFD_NAMESPACE"Version")
    )
)

#include "tmpofd/refl/reflect_end.h"
