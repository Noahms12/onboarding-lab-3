#include <cstdint>
#include <bit>
#include <random>

#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>

uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  switch(a) {
    case 0:
      return (0b00 | b >> 6 | c >> 6);
    case 1:
      return (0b01 | c >> 6 | b >> 6);
    case 2:
      return b;
    default:
      return c;
  }
}

struct Mystery2 {
  uint8_t count {0};
  uint16_t out;

  uint16_t reset(uint8_t a, uint8_t b) {
    out = (a << 8) | b;
    count = 0;
    return out;
  }

  uint16_t step(uint8_t a, uint8_t b) {
    count %= 5;
    switch(count++) {
      case 0:
        return out = (a << 8) | (out & 0xFF);
      case 1:
        return out = ((out & 0xFF00) << 8) | b;
      case 2:
        return out = (out & 0xFF) | ((out & 0xFF00) >> 8);
      case 3:
        return out = (out & 0xF)| (out & 0xF0) >> 4 | (out & 0xF00) >> 8 | (out & 0xF000) >> 12;
      default:
        return out = uint16_t(std::popcount(out) & 1;
    }
  }
};

struct Excercise3Sim {
  Mystery2 state;

  uint16_t reset(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in {mystery1(a & 0x3, b & 0xFF, c & 0xFF)};
    uint8_t b_in {mystery1(a >> 2, b >> 8, c >> 8)};
    return state.reset(a_in, b_in);
  }

  uint16_t step(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in {mystery1(a & 0x3, b & 0xFF, c & 0xFF)};
    uint8_t b_in {mystery1(a >> 2, b >> 8, c >> 8)};
    return state.step(a_in, b_in);
  }
};

void step(VExercise3& model) {
  model.clk = 0;
  model.eval();
  model.clk = 1;
  model.eval();
};

TEST_CASE("Test Random") {
  VExercise3 model;
  Excercise3Sim sim;

  std::default_random_engine re {std::random_device {}()};
  std::uniform_int_distribution<uint8_t> rand4 {0, 15};
  std::uniform_int_distribution<uint16_t> rand16;

  model.a = rand4(re);
  model.b = rand16(re);
  model.c = rand16(re);
  model.nReset = 0;
  step(model);

  REQUIRE(model.out == sim.reset(model.a, model.b, model.c));

  model.nReset = 1;

  for(size_t cycles {0}; cycles < 100; ++cycles) {
    model.a = rand4(re);
    model.b = rand16(re);
    model.c = rand16(re);
    step(model);
    REQUIRE(model.out == sim.step(model.a, model.b, model.c));
  }
}
