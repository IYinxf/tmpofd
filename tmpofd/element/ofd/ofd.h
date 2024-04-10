//
// Created by Yinxf on 2024/4/10.
//

#pragma once

#include "tmpofd/element/ofd/doc_body.h"

namespace tmpofd::element {

struct OFD {
  Attribute<String> Version;
  Attribute<String> DocType;

  Vector<DocBody> DocBody;

};

} // tmpofd::element
//
//#include "mirrow/srefl/srefl_begin.hpp"
//srefl_class(tmpofd::element::OFD,
//            ctors()
//                fields(
//                    field(&tmpofd::element::OFD::Version),
//                    field(&tmpofd::element::OFD::DocType),
//                    field(&tmpofd::element::OFD::DocBody)
//                )
//)
//#include "mirrow/srefl/srefl_end.hpp"
