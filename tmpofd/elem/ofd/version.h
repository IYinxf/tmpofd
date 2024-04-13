//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/type_def/type_def.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::elem {

struct Version {
  attribute_t<id_t> ID{};
  attribute_t<int_t> Index{};
  attribute_t<bool_t> Current{};
  attribute_t<loc_t> BaseLoc;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::Version, OFD_NAMESPACE"Version",
    FIELDS(
        FIELD(&tmpofd::elem::Version::ID, "ID"),
        FIELD(&tmpofd::elem::Version::Index, "Index"),
        FIELD(&tmpofd::elem::Version::Current, "Current"),
        FIELD(&tmpofd::elem::Version::BaseLoc, "BaseLoc")
    )
)

#include "tmpofd/refl/reflect_end.h"
