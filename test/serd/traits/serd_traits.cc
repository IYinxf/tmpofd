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
CHILD_ELEM(
        FIELD(&Test::field_, "field")
    )
)
#include "tmpofd/refl/reflect_end.h"

TEST_CASE("reflectable_v") {
  Test test{};
  CHECK(tmpofd::refl::reflectable_v<decltype(test)>);
  Test1 test1{};
  CHECK(!tmpofd::refl::reflectable_v<decltype(test1)>);
}

TEST_CASE("assign_attr") {
  std::string_view v("test");

  tmpofd::elem::attribute_t<tmpofd::elem::loc_t> loc;
  tmpofd::elem::attribute_t<tmpofd::elem::string_t> string;

  tmpofd::serd::internal::detail::assign_attr("loc", v, loc);
  tmpofd::serd::internal::detail::assign_attr("string", v, string);

  CHECK(std::string(v) == loc.value_);
  CHECK(std::string(v) == string.value_);

  tmpofd::elem::attribute_t<tmpofd::elem::id_t> id;
  tmpofd::serd::internal::detail::assign_attr("id", v, id);

  CHECK(std::string(v) == std::to_string(id.value_));

//  tmpofd::elem::attribute_t<float> f;
//  tmpofd::serd::internal::detail::assign_attr(v, f);
}

TEST_CASE("assign_elem") {
  std::string_view v("test");

  tmpofd::elem::loc_t loc;
  tmpofd::elem::string_t string;

  tmpofd::serd::internal::detail::assign_elem("loc", v, loc);
  tmpofd::serd::internal::detail::assign_elem("string", v, string);

  CHECK(std::string(v) == loc);
  CHECK(std::string(v) == string);

  tmpofd::elem::id_t id;
  tmpofd::serd::internal::detail::assign_elem("id", v, id);

  CHECK(std::string(v) == std::to_string(id));

//  float f;
//  tmpofd::serd::internal::detail::assign_elem(v, f);
}
