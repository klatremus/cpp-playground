cp tut-1.cxx tmp.cxx
clang++ tmp.cxx -ObjC++ --compile --target=wasm32-unknown-unknown-wasm --optimize=3 --output tmp.wasm;
#!
wasm-decompile tmp.wasm -o tmp.redablePsaudo.c;
#!
#! Step: turn the wasm file to language="c":
wasm2c tmp.wasm -o tmp.c
#
cat tmp.redablePsaudo.c;
#cat tmp.c;

#!
#! Add into a differnet program:
# cp ./wabt/wasm2c/wasm-rt-impl.c ./wabt/wasm2c/wasm-rt-impl.h;
gcc -o fac mainProg.c fac.c wasm-rt-impl.c
