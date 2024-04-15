//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/type_def/type_def.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::elem {

struct CustomData {
  attribute_t<string_t> name_;
  string_t value_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

using namespace tmpofd::elem;
REFLECT(
    CustomData, OFD_NAMESPACE"CustomData",
    ATTR(
        FIELD(&CustomData::name_, "Name")
    ) CHILD_ELEM(
        FIELD(&CustomData::value_, "Value")
    )
)

#include "tmpofd/refl/reflect_end.h"
