//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/ofd/doc_info.h"
#include "tmpofd/element/ofd/versions.h"

namespace tmpofd::element {

struct DocBody {
  DocInfo DocInfo;
  ST_Loc DocRoot;
  Versions Versions;
  ST_Loc Signatures;

};

} // tmpofd::element
//
//#include "mirrow/srefl/srefl.hpp"
//#include "mirrow/srefl/srefl_begin.hpp"
//srefl_class(tmpofd::element::DocBody,
//            ctors()
//                fields(
//                    field(&tmpofd::element::DocBody::DocRoot),
//                    field(&tmpofd::element::DocBody::Signatures)
//                )
//)
//#include "mirrow/srefl/srefl_end.hpp"
