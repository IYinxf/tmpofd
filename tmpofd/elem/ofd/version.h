//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/type_def/type_def.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::elem {

struct Version {
  attribute_t<id_t> ID_{};
  attribute_t<int_t> Index_{};
  attribute_t<bool_t> Current_{};
  attribute_t<loc_t> BaseLoc_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::Version, OFD_NAMESPACE"Version",
    FIELDS(
        FIELD(&tmpofd::elem::Version::ID_, "ID"),
        FIELD(&tmpofd::elem::Version::Index_, "Index"),
        FIELD(&tmpofd::elem::Version::Current_, "Current"),
        FIELD(&tmpofd::elem::Version::BaseLoc_, "BaseLoc")
    )
)

#include "tmpofd/refl/reflect_end.h"
