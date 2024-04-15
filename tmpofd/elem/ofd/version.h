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
  attribute_t<bool_t> Current_{false};
  attribute_t<loc_t> BaseLoc_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

using namespace tmpofd::elem;
REFLECT(
    Version, OFD_NAMESPACE"Version",
    ATTR(
        FIELD(&Version::ID_, "ID"),
        FIELD(&Version::Index_, "Index"),
        FIELD(&Version::Current_, "Current"),
        FIELD(&Version::BaseLoc_, "BaseLoc")
    ) CHILD_ELEM()
)

#include "tmpofd/refl/reflect_end.h"
