// FIXME: why does this code-chunk NOT work? ... due to changes in the compilers?

//! Src: https://stackoverflow.com/questions/8814705/how-to-check-if-a-function-exists-in-c-c
#include <stdio.h> //! needed for the c-style "printf(..)" funciton

//#pragma weak func

#pragma weak power2
int power2(int x); //  {return 1;}
//int power2(int x) {return 1;}


//void func(int argc, char *argv[]) __attribute__((weak)); // weak declaration must always be present
/* extern void func(int, char **); */
/* void (*function_toCall)(int, char **) = func; */




// optional definition:
/*void func(int argc, char *argv[]) { 
    printf("ENCONTRE LA FUNC\n");
    for(int aa = 0; aa < argc; aa++){
        printf("arg %d = %s \n", aa, argv[aa]);
    }
}*/

int main(int argc, char *argv[]) {
  //if (function_toCall){
  if(power2) {
    // function_toCall(argc, argv);
    power2(2);
  } else {
    printf("function is NOT defined\n");
  }
}
