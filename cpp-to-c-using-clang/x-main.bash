#!/bin/bash

#cp test_ctor.cpp tmp.cpp;
#cp test_std_exception.cpp tmp.cpp;
# cp tmp.cpp;
cp test-template.cpp tmp.cpp;

clang -S -emit-llvm -g tmp.cpp
../../build/tools/llvm-cbe/llvm-cbe tmp.ll;
gcc tmp.cbe.c -Wno-discarded-qualifiers;
./a.out ; echo $?; #! ie, where "?" prints the reutnr-value 
#./a.out
