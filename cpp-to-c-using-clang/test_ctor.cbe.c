/* Provide Declarations */
#include <stdint.h>
#ifndef __cplusplus
typedef unsigned char bool;
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define  __ATTRIBUTELIST__(x) __attribute__(x)
#else
#define  __ATTRIBUTELIST__(x)  
#endif

#ifdef _MSC_VER  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif



/* Global Declarations */

/* Types Declarations */
struct l_struct_class_OC_Foo;

/* Function definitions */
typedef void l_fptr_2(void);

typedef void l_fptr_3(struct l_struct_class_OC_Foo*, uint32_t);

typedef uint32_t l_fptr_1(void);


/* Types Definitions */
struct l_struct_class_OC_Foo {
  uint32_t field0;
};

/* Function Declarations */
int main(void) __ATTRIBUTELIST__((noinline));
void _ZN3FooC2Ei(struct l_struct_class_OC_Foo*, uint32_t) __ATTRIBUTELIST__((noinline, nothrow)) __ATTRIBUTE_WEAK__;


/* LLVM Intrinsic Builtin Function Bodies */


/* Function Bodies */

int main(void) {
  uint32_t _1;    /* Address-exposed local */
  struct l_struct_class_OC_Foo _2;    /* Address-exposed local */
  uint32_t _3;

  _1 = 0;
#line 8 "/home/klatremus/poset-src/centric/case-fourc/llvm-cbe/test/cpp_tests/test_ctor.cpp"
  ;
  _ZN3FooC2Ei((&_2), 6);
#line 9 "/home/klatremus/poset-src/centric/case-fourc/llvm-cbe/test/cpp_tests/test_ctor.cpp"
  _3 = *((&_2.field0));
  return _3;
}


void _ZN3FooC2Ei(struct l_struct_class_OC_Foo* _4, uint32_t _5) {
  struct l_struct_class_OC_Foo* _6;    /* Address-exposed local */
  uint32_t _7;    /* Address-exposed local */
  struct l_struct_class_OC_Foo* _8;
  uint32_t _9;

  _6 = _4;
#line 0 "/home/klatremus/poset-src/centric/case-fourc/llvm-cbe/test/cpp_tests/test_ctor.cpp"
  ;
  _7 = _5;
#line 3 "/home/klatremus/poset-src/centric/case-fourc/llvm-cbe/test/cpp_tests/test_ctor.cpp"
  ;
  _8 = _6;
  _9 = _7;
  *((&_8->field0)) = _9;
}

