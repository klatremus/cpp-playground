#ifndef functionExists_def_h
#define functionExists_def_h
#include <stdio.h> //! needed for the c-style "printf(..)" funciton
void function_toCall_inCFile(int argc, char *argv[]);
void function_toCall(int argc, char *argv[]) {
  printf("in function of %s:[%s]:%d\n", __FILE__, __FUNCTION__, __LINE__); //! which calls a fucntion defined by the parent (eg, in our "functionExists.c") <-- tODO: is this a safe=good=sound pattern to use?
  function_toCall_inCFile(argc, argv); 
}
#endif //! functionExists_def_h
