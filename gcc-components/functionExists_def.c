#include "functionExists_def.h"
extern void function_toCall_inCFile(int argc, char *argv[]) {
  printf("in function of %s:[%s]:%d\n", __FILE__, __FUNCTION__, __LINE__);
}
