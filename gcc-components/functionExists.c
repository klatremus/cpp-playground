/**
   @file
   @brief test if a function exists   
 **/
// #include <stdint.h> //! needed for "uint16_t": "for C, it's in stdint.h, which is introduced in C99" ... For cpp/c++: ""Use uint16_t in cstdint, which is introduced in C++11. Or define your own type."  [https://stackoverflow.com/questions/19106922/keeps-saying-uint16-is-not-declared]
#include <stdio.h> //! needed for the c-style "printf(..)" funciton
// Src: https://stackoverflow.com/questions/60760980/are-compile-time-checks-possible-for-value-parameters-in-c99-or-gcc-clang
#include <stdbool.h> //! to suppore useo of true fand false

//#include "functionExists_def.h"
//! SrC: https://stackoverflow.com/questions/8814705/how-to-check-if-a-function-exists-in-c-c
void function_toCall(int argc, char *argv[]) __attribute__((weak)); // weak declaration must always be present
//! OR: int function_toCall(int argc, char *argv[]) __attribute__((weak)) = 1; //! [https://stackoverflow.com/questions/274753/how-to-make-weak-linking-work-with-gcc]

#include "functionExists_def.h" //! Note: incldue this to get the "if (function_toCall){" branch to be enteresd

void function_toCall_inCFile(int argc, char *argv[]) {
  printf("in function of %s:[%s]:%d\n", __FILE__, __FUNCTION__, __LINE__); //! 
}

// optional definition:
/*void func(int argc, char *argv[]) { 
    printf("ENCONTRE LA FUNC\n");
    for(int aa = 0; aa < argc; aa++){
        printf("arg %d = %s \n", aa, argv[aa]);
    }
}*/

int main(int argc, char *argv[]) {
    if (function_toCall){ 
        function_toCall(argc, argv); 
    } else {
        printf("function is NOT defined\n");
    }
    if (function_toCall_inCFile){ 
        function_toCall_inCFile(argc, argv); 
    } else {
        printf("function is NOT defined\n");
    }    
}
