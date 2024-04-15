//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/type_def/type_def.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::elem {

struct Keywords {
  vector_t<string_t> keyword_;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

using namespace tmpofd::elem;
REFLECT(
    Keywords, OFD_NAMESPACE"Keywords",
    ATTR() CHILD_ELEM(
        FIELD(&Keywords::keyword_, OFD_NAMESPACE"Keyword")
    )
)

#include "tmpofd/refl/reflect_end.h"
