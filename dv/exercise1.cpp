#include <VExercise1.h>
#include <cstdint>

bool test_op(int op){
  for (uint8_t a = 0; a <= 255; a++){
    for (uint8_t b = 0; b <= 255; b++){
      if(!test_ab(op, a, b)) { return false; }
    }
  }
  return true;
}

bool test_ab(int op, uint8_t a, uint8_t b)){
  VExercise1 model;
  model.a = a;
  model.b = b;
  model.eval();
  switch(op){
  case 0:
    if(model.out != (uint8_t) (model.a ^ model.b)){ return false; }
    break;
  case 1:
    uint8_t shifted = model.a << model.b;
    if(model.out != shifted) { return false; }
    break;
  case 2:
    if (model.b == 0) { return true; } // ignores case when dividing by 0
    else{
      uint8_t correct = uint8_t (model.a % model.b);
      if (model.out != correct) { return false; }
    }
  break;
  case 3:
    uint8_t correct = uint8_t (~(model.a & model.b));
    if (model.out != correct) {return false; }
  break;
  }
  return true;
}

int main() {
  for (int op = 0; op <= 4; op++){
      if (!test_op(op)){
        std::cerr << "Failed test" << std::endl;
      return 1;
      }
      else {
        std::cout << "Passed all tests" << std::endl;
        return 0;
      }
  }
}
