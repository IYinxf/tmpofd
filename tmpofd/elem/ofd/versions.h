//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/version.h"

namespace tmpofd::elem {

struct Versions {
  vector_t<Version> Version_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

using namespace tmpofd::elem;
REFLECT(
    Versions, OFD_NAMESPACE"Versions",
    ATTR() CHILD_ELEM(
        FIELD(&Versions::Version_, OFD_NAMESPACE"Version")
    )
)

#include "tmpofd/refl/reflect_end.h"
