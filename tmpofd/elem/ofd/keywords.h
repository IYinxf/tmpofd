//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/elem/type_def/type_def.h"
#include "tmpofd/refl/reflection.h"

namespace tmpofd::elem {

struct Keywords {
  vector_t<string_t> Keyword;

};

} // tmpofd::elem

#include "tmpofd/refl/reflect_begin.h"

REFLECT(
    tmpofd::elem::Keywords, OFD_NAMESPACE"Keywords",
    FIELDS(
        FIELD(&tmpofd::elem::Keywords::Keyword, OFD_NAMESPACE"Keyword")
    )
)

#include "tmpofd/refl/reflect_end.h"
