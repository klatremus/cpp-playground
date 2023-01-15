/**
   @file 
   @brief throw a compile-tiem error if value is outdie the givne range
 **/
#include <stdint.h> //! needed for "uint16_t": "for C, it's in stdint.h, which is introduced in C99" ... For cpp/c++: ""Use uint16_t in cstdint, which is introduced in C++11. Or define your own type."  [https://stackoverflow.com/questions/19106922/keeps-saying-uint16-is-not-declared]
#include <stdio.h> //! needed for the c-style "printf(..)" funciton
// Src: https://stackoverflow.com/questions/60760980/are-compile-time-checks-possible-for-value-parameters-in-c99-or-gcc-clang
#include <stdbool.h> //! to suppore useo of true fand false

/**
   @brief the function used to explore the different "static_assert(...)" permtuations
 **/
void function_real(const uint16_t len) {
  if(len != 0) {} //! used to hdie compiel-tiem warnings
  printf("\t len=%d [%s]:%d\n", len, __FUNCTION__, __LINE__);
}
/*
*/


// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ************************************ Case 1 ***********************************************************************************
#define function_permutation_1(len) ((void)sizeof(char[len > 10 ? -1 : 1]), function_real(len))

// Better:

#define function_permutation_2(len) ((void)sizeof(struct{ int a:len > 10 ? -1 : 1;}), function_real(len))
/*
// OR:
*/


#if false // FIXME: why does the below NOT work? <-- changes in the compilers? 
static inline 
void function_test(const uint16_t len) {
  if (!__builtin_constant_p(len)) {
    extern __attribute__(( __error__ ( "Och no! len couldn't be evaulated at runtime" ) ))
      void compile_time_error(void);
    compile_time_error();
  }
  else
  if (len < 12) {
    //if(false) {
    extern __attribute__(( __error__ ( "Och no! len is too small!" ) ))
      void compile_time_error2(void);
    compile_time_error2();
  }  
  function_real(len);
}
static void case_useFunctionBuiltInConst() {
  //function(12);
  function_test(2);
}
#endif //! #if false

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ********************************************* Case 2 **************************************************************************
// ***********
// Src: https://stackoverflow.com/questions/9229601/what-is-in-c-code <-- https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-g_t_005f_005fbuiltin_005fconstant_005fp-3386 and https://gcc.gnu.org/onlinedocs/gcc-4.8.1/gcc/Function-Attributes.html#index-g_t_0040code_007bflatten_007d-function-attribute-2586



/* Force a compilation error if condition is true, but also produce a
   result (of value 0 and type size_t), so the expression can be used
   e.g. in a structure initializer (or where-ever else comma expressions
   aren't permitted). */
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int:-!!(e); }))
#define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int:-!!(e); }))

// Src:

static void case_negationInStruct() {
  if(BUILD_BUG_ON_ZERO(0))     {   } //! ie, passes
  // if(BUILD_BUG_ON_ZERO(10))     {   } //! ie, fails
  // if(BUILD_BUG_ON_NULL("..."))     {   } //! ie, fails
  if(BUILD_BUG_ON_NULL(NULL))     {   } //! ie, passes
}



/* #define Scale_Value(X)      \ */
/*   (__builtin_constant_p (X) \ */
/*   ? ((X) * SCALE + OFFSET) : Scale (X)) */

/* static const int table[] = { */
/*    __builtin_constant_p (EXPRESSION) ? (EXPRESSION) : -1, */
/* }; */


// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ********************************************* Case 3 **************************************************************************

/*
// OR:
*/

#define func(len) ({_Static_assert(len < 10, "Length exceeds size of input ... ");  function_real(len); })

static void case_useOfStaticAssert() {
  //function(12);
  //func(12); //!  which triggers a comion error
  func(2); //! which workds
}

//#if false
static void case_useMacros() {
  /**
     @remarks
     - the below valeus are ivnestiaged irrespecitv eof the fuino being called (or NOT), thus, to dorp evlauating this fucniotn, add adn "#if false" clase (roudn it)
   **/
  function_permutation_2(2); //! ie, inside the threshold
  const int value_0 = 12;
  function_permutation_1(__builtin_constant_p(value_0)); // FIXME: why does the use of "__builtin_constant_p(..)" NOT trigger a compiel-tiem warning?
  const int value_1 = 12;               //! Note: this does NOT throw an error for "-O0", while is trhown for "-O2"  AND "-O3"
  //function_permutation_1(value_1);
  static const int value_2 = 12;        //! Note: this does NOT throw an error for "-O0", while is trhown for "-O2"  AND "-O3"
  //function_permutation_1(value_2);
#define value_3 12 // FIXME: accoridng to the coding-stard, when is this permtitted=ok to use?
  //function_permutation_1(value_3);
  //function_permutation_1(12);
  //function_permutation_1(value);
}
//#endif // #if false

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ********************************************* Case 4 **************************************************************************
#include <assert.h>
#include <string.h>
static void case_compileTimeEvaluations() { 
  // https://stackoverflow.com/questions/27490858/how-can-you-compare-two-character-strings-statically-at-compile-time
  printf("retVal=%d\n", strcmp("Thing1", "Thing2")); //! retutnrs -1
  assert(strcmp("Thing1", "Thing2") == 0); //! FIXME: in constrast to thje abve assert, thsi first fails at run-time. Thus, other parises (eg, curnelty in sued) which will aslo fail?
}


int main() {
  //!
  //! Pattern:
  case_compileTimeEvaluations();
  //!
  //! Pattern:
  case_useOfStaticAssert();
  //!
  //! Pattern:
  //case_useFunctionBuiltInConst();
  //!
  //! Pattern: use macros:
  //case_useMacros();
  return 0;
}






/* // ****************' */
/* // Note: c++ 2011 --- https://en.cppreference.com/w/cpp/language/constexpr -- <-- not supported by g++-5.5   */
/* //! https://stackoverflow.com/questions/9441348/gcc-compile-time-checking-of-constant-function-inputs */
/* // cpp-compilers : [https://gist.github.com/ax3l/53db9fa8a4f4c21ecc5c4100c0d93c94] */
/*   //  */
/* static_assert(__builtin_choose_expr(__builtin_constant_p(port), \ */
/*                           port<2, 1), "parameter port must be < 2") */

/* or: */

/* #include <stdio.h> */

/* void _uart(int port) { */
/*  printf("port is %d", port); */
/* } */

/* #define uart(port) \ */
/*  static_assert(__builtin_constant_p(port)? port<2: 1, "parameter port must be < 2"); \ */
/*  _uart(port) */

/* int main(void) { */
/*  int x=1; */
/*  uart(x); */
/* } */

// 

