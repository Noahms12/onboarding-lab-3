#include <VExercise4.h>

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Decoder") {
  VExercise4 model;
  model.alpha = 1;
  model.beta = 2;
  model.gamma = 3;
  model.cs = 1;

  for(model.sel = 0; model.sel < 3; model.sel++) {
    model.eval();
    REQUIRE(model.out == (model.sel + 1));
  }

  model.eval();
  REQUIRE(model.out == (model.alpha & (model.beta | model.gamma)));

  model.cs = 0;
  for(model.sel = 0; model.sel < 3; model.sel++) {
    model.eval();
    REQUIRE(model.out == 0);
  }
}
