//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/type_def/type_def.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::elem {

struct CustomData {
  attribute_t<string_t> Name;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::CustomData, OFD_NAMESPACE"CustomData",
    FIELDS(
        FIELD(&tmpofd::elem::CustomData::Name, "Name")
    )
)

#include "tmpofd/refl/reflect_end.h"
