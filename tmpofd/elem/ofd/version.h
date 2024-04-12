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
