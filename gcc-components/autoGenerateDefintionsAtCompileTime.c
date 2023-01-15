/**
   @file 
   @brief exemplfiyt how to cosntruct tionf-names at compiel tiem dynamcially
 **/
#include <stdint.h> //! needed for "uint16_t": "for C, it's in stdint.h, which is introduced in C99" ... For cpp/c++: ""Use uint16_t in cstdint, which is introduced in C++11. Or define your own type."  [https://stackoverflow.com/questions/19106922/keeps-saying-uint16-is-not-declared]
#include <stdio.h> //! needed for the c-style "printf(..)" funciton
// Src: https://stackoverflow.com/questions/60760980/are-compile-time-checks-possible-for-value-parameters-in-c99-or-gcc-clang
#include <stdbool.h> //! to suppore useo of true fand false





#define MAKE_SURE_THIS_IS_FIVE(number)                          \
    do {                                                        \
        extern void this_isnt_five(void) __attribute__((error(  \
                "I asked for five and you gave me " #number))); \
        if ((number) != 5)                                      \
            this_isnt_five();                                   \
    } while (0)

/* #define DEFINE_TABLE_COPY(type)                                              \ */
/*   static inline void type##_table_copy(wasm_rt_##type##_table_t* dest,       \ */
/*                                        const wasm_rt_##type##_table_t* src,  \ */
/*                                        u32 dest_addr, u32 src_addr, u32 n) { \ */
/*     if (UNLIKELY(dest_addr + (uint64_t)n > dest->size))                      \ */
/*       TRAP(OOB);                                                             \ */
/*     if (UNLIKELY(src_addr + (uint64_t)n > src->size))                        \ */
/*       TRAP(OOB);                                                             \ */
/*                                                                              \ */
/*   } */

/*
    memmove(dest->data + dest_addr, src->data + src_addr,                    \
            n * sizeof(wasm_rt_##type##_t));                                 \
*/

#define DEFINE_TABLE_COPY(str_type)                                              \
  static inline void str_type##_table_copy(const int val) {printf("A str_function cal w/number=%d\n", val);}

/* DEFINE_TABLE_COPY(funcref) */
/* DEFINE_TABLE_COPY(externref) */

DEFINE_TABLE_COPY(str)

int main() {
  //!
  //! Pattern:
  str_table_copy(2); //! ie, call the funciotn gnerated by the above "DEFINE_TABLE_COPY"
  
  return 0;
}
  
