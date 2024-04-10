//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/definitions/definitions.h"
#include "tmpofd/util/reflection.h"

namespace tmpofd::element {

struct Version {
  attributes_t<id_t> ID{};
  attributes_t<int> Index{};
  attributes_t<bool> Current{};
  attributes_t<loc_t> BaseLoc;

};

} // tmpofd::element
