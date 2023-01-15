// Src: https://stackoverflow.com/questions/60760980/are-compile-time-checks-possible-for-value-parameters-in-c99-or-gcc-clang
void function_real(const uint16_t len);

#define function(len) ((void)sizeof(char[len > 32768 ? -1 : 1]), function_real(len))

// Better:

 #define function(len) ((void)sizeof(struct{ int a:len > 32768 ? -1 : 1;}), function_real(len))

// OR:

void function_real(const uint16_t len);

static inline 
void function(const uint16_t len) {
     if (!__builtin_constant_p(len)) {
            extern __attribute__(( __error__ ( "Och no! len couldn't be evaulated at runtime" ) ))
            void compile_time_error(void);
            compile_time_error();
     } else if (len > 32768) {
            extern __attribute__(( __error__ ( "Och no! len is too small!" ) ))
            void compile_time_error2(void);
            compile_time_error2();
     }

     function_real(len);
}

// OR:

#define func(len, buffer)                                           \
({                                                                  \
    _Static_assert(len < 32768, "Length exceeds size of EEPROM");   \
    _func(len, buffer);                                             \
})


bool _func(uint16_t len, const void *buffer)
{ }
