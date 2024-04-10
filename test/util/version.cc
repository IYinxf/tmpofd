//
// Created by Yinxf on 2024/4/9.
//

#include "tmpofd/base/version.h"

#include "catch2/catch_all.hpp"

TEST_CASE("version") {
  INFO("tmpofd version is " << TMPOFD_VERSION);
  CHECK(true);
}
