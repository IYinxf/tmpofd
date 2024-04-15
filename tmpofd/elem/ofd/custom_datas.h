//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/ofd/custom_data.h"

namespace tmpofd::elem {

struct CustomDatas {
  vector_t<CustomData> custom_data_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

using namespace tmpofd::elem;
REFLECT(
    CustomDatas, OFD_NAMESPACE"CustomDatas",
    ATTR() CHILD_ELEM(
        FIELD(&CustomDatas::custom_data_, OFD_NAMESPACE"CustomData")
    )
)

#include "tmpofd/refl/reflect_end.h"
