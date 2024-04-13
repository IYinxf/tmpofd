//
// Created by Yinxf on 24-4-13.
//

#include "tmpofd/serd/deserialization.h"

#include "catch2/catch_all.hpp"

TEST_CASE("is_string_container_v") {
  using namespace tmpofd::serd::internal;

  CHECK(is_string_container_v<std::string>);
  CHECK(is_string_container_v<std::string_view>);
  CHECK(!is_string_container_v<int>);

  std::string string("string");
  std::string string_view("string_view");
  CHECK(is_string_container_v<decltype(string)>);
  CHECK(is_string_container_v<decltype(string_view)>);

}

struct Test {
  char field_;
};

struct Test1 {
  char field_;
};

#include "tmpofd/refl/reflect_begin.h"
REFLECT(
    Test, "Test",
    FIELDS(
        FIELD(&Test::field_, "field")
    )
)
#include "tmpofd/refl/reflect_end.h"

TEST_CASE("is_reflected_v") {
  Test test{};
  CHECK(tmpofd::refl::internal::is_reflected_v<decltype(test)>);
  Test1 test1{};
  CHECK(!tmpofd::refl::internal::is_reflected_v<decltype(test1)>);
}
