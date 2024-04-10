//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/definitions/definitions.h"
#include "tmpofd/util/relfection.h"

namespace tmpofd::element {

struct Version {
  Attribute<ST_ID> ID{};
  Attribute<int> Index{};
  Attribute<bool> Current{};
  Attribute<ST_Loc> BaseLoc;

};

} // tmpofd::element
