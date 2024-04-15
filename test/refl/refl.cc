//
// Created by Yinxf on 24-4-14.
//

#include "tmpofd/refl/reflection.h"
#include "tmpofd/elem/ofd/ofd.h"

#include "catch2/catch_all.hpp"

TEST_CASE("has_reflected_filed_v") {
  namespace tr = tmpofd::refl;
  namespace te = tmpofd::elem;

  CHECK(tr::has_reflected_filed_v<te::OFD>);
  CHECK(!tr::has_reflected_filed_v<te::CustomData>);

}
