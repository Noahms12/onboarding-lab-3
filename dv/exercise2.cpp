//
//  Lab3Q2.cpp
//  PDT_Lab3
//
//  Noah Mays-Smith
//  Used https://github.com/rishyak/potential-computing-machine/blob/main/Labs/3/dv/exercise2.cpp
//  For assistance during this section
//

#include <iostream>
#include <cstdint>
#include <bitset>

class LFSR{
public:
    LFSR(uint16_t val = 1) : curr(val), init(val) {}

    // updates curr with new values and
    // returns whether the new digit was
    // 1 or 0
    bool step(bool reset = 0){
        if (!reset){
            bool nextBit = (curr >> 10 & 1) ^
            (curr >> 8 & 1) ^
            (curr >> 3 & 1) ^
            (curr >> 1 & 1);
            curr = curr << 1 | nextBit;
            return (nextBit);
        }
        else{
            curr = ~init;
            return 0;
        }
    }
    uint16_t curr;
    uint16_t init;
};

void step(VExercise2 &model) {
    model.clk = 1;
    model.eval();
    model.clk = 0;
    model.eval();
}

bool test(uint16_t init) {
    bool fail = false;
    VExercise2 model;
    model.init = init;
    model.reset = 1;
    step(model);
    model.reset = 0;

    LFSR lfsr{(uint16_t)~init};

    for (int loop = 0; loop < 100; loop++) {
        if (model.out != lfsr.curr){
            fail = true;
            break;
        }
        else{
            step(model);
            lfsr.step();
        }
    }

    model.reset = 1;
    step(model);
    lfsr.step(1);
    if (model.out != (uint16_t)~init){
        fail = true;
    }
    return !fail;
}
int main() {
    //TEST 1
    std::cout << "Test 1: ";
    test(0) ? std::cout << "pass" : std::cout << "fail";
    endl;
    
    //TEST 2
    std::cout << "Test 2: ";
    test(0Xffff) ? std::cout << "pass" : std::cout << "fail";
    endl;
    
    //TEST 3
    std::cout << "Test 3: ";
    test(1) ? std::cout << "pass" : std::cout << "fail";
    endl;
    
    //TEST 4
    std::cout << "Test 4: ";
    test(0x55) ? std::cout << "pass" : std::cout << "fail";
    endl;
    
    //TEST 5
    std::cout << "Test 5: ";
    test(0xAABB) ? std::cout << "pass" : std::cout << "fail";
    endl;
}
