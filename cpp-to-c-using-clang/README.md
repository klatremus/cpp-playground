# FourC

# FIXME: mvoe "/home/klatremus/poset-src/centric/case-fourc/wabt/build/tut-2/fixme.txt" to ... 

Evaluate:
- question: [https://stackoverflow.com/questions/56541790/is-it-possible-to-decompile-web-assembly-wasm-files-to-a-specific-programming]:
* C++ and C into webassembly: [https://github.com/emscripten-core/emscripten] w/tutorial at [https://emscripten.org/docs/getting_started/Tutorial.html]
* " webassembly binaries to C": [https://github.com/WebAssembly/wabt/tree/main/wasm2c]
* [https://github.com/WebAssembly/wabt], eg, supporting: "wasm2c: convert a WebAssembly binary file to a C source and header"
* compile code for different machine arhciectures: [https://github.com/avast/retdec]
* []

Downlaoded repos:
- https://github.com/JuliaHubOSS/llvm-cbe.git

## Repo: "llvm-cbe"
Bug:
- problem with "printf(..)", while "putchar(...)" works.

### Example: c-code:
```bash
cd test/selectionsort;
#!
#! Note: the below code is included into "x-main.bash" (our new-added file):
#!/bin/bash
clang -S -emit-llvm -g main.c
../../build/tools/llvm-cbe/llvm-cbe main.ll;
gcc -o main.cbe main.cbe.c -Wno-discarded-qualifiers;
./main.cbe
```

### Example: 
```cpp
//! Src: "test-template.cpp":
template <typename T> T myMax(T x, T y)
{
  return (x > y) ? x : y;
}

int main() {
  //Foo f(6);
  //return f.x;
  return myMax<int>(3, 7);
}
```

Compile:
```bash
cd test/cpp_tests/;
#!
#! Note: the below code is included into "x-main.bash" (our new-added file):
cp test-template.cpp tmp.cpp;
clang -S -emit-llvm -g tmp.cpp
../../build/tools/llvm-cbe/llvm-cbe tmp.ll;
gcc tmp.cbe.c -Wno-discarded-qualifiers;
./a.out ; echo $?; #! ie, where "?" prints the reutnr-value 
#./a.out

```

### Example: 
```bash

```

## Repo: ""
-----------------------
- [x] "tut-2": ge ta 'dirty' compiation to work
----------
- [x] "tut-3":  scope: re-predocue the results from "tut-2".
- [x] "tut-3": docuemtn the difnfrece=mdoaitons (using the "FIXME" tag) ... copy thw rokgin parts to "../workingExample-cFunc"


- [x] "tut-3":
* adds own=multple c-functions ... then ge tthe udpatede ocde to (again) work
* adds own=cpp-functions = tempaltes
* add structs
* add classes
-----------------

# FIXME: problem: "clang++" does NOT parse structs NOR c++ code ... how to resolve?
- [ ] "tut.cxx": add a class to teh funb( 8makign ti seplcity that tit is used) ... does this hlep? <-- yes:
```bash
clang++ tut.cxx -ObjC++ --compile --target=wasm32 --output fac.wasm
wasm2c fac.wasm -o fac.c;
wasm-decompile fac.wasm;
wasm-decompile fac.wasm | grep function; #! reveals: fiv e founds <-- fIXME: where are muliple funciotns for case="a:int):int": why? <-- seems like it is provked byb which cosntrucot used in the cxx-file
gcc  fac.c wasm-rt-impl.c main.c -g; ./a.out 2; #! whic results in many comion-eroirs (though only he expeted)!
```
* note: the "clang++" gives erros if *.h fil(s)a re wrong.. thus, clang acutally evlautes the ehad-erilfe!
- [ ] "": 
- [ ] "": 
- [ ] "": try installing a different tool
```
#! Src: [https://askubuntu.com/questions/891630/how-to-install-the-latest-emscripten-on-ubuntu-using-command-line]
git clone https://github.com/emscripten-core/emsdk.git
d ../../../
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
#! then try it:
emcc;

#
# FIXME: why is theere not any fuciont in the below?
cd /home/klatremus/poset-src/centric/case-fourc/emsdk;
emcc ../wabt/build/tut-3/tut.cxx --no-entry -o tut-emcc.wasm;
# klatremus@klatremus:~/poset-src/centric/case-fourc/emsdk$
wasm-decompile tut-emcc.wasm

#!
#! cd /home/klatremus/poset-src/centric/case-fourc;
# FIXME: why is the below an extmrely ugly code?
emcc -lembind -o quick_example.js wabt/build/tut-3/tut.cxx
#!
#!
emcc -lembind -o quick_example.js tut-emcc.cpp;
#!
#! STart the program in the browser:
# FIXME: why is the below "emrun" neccsary?
emrun --browser firefox tut-emcc-main.html

```
- [ ] "": 
- [ ] "":
- [ ] "": 
- [ ] "":
```
-----------
- [ ] "tut-3": amange to compiel header-files
```bash
#!
# clang++ tut.h tut.cxx -ObjC++ --compile --target=wasm32-unknown-unknown-wasm --optimize=3 #! does NOT work
#
#! SrC: https://stackoverflow.com/questions/23534362/warning-treating-c-header-input-as-c-header-when-in-c-mode-this-behavi
clang++ -x c++-header tut.h; #! works!
clang++ -x c++-header tut.h -ObjC++ --compile --target=wasm32-unknown-unknown-wasm --output fac.wasm;
clang++ -x c++-header tut.h --compile --target=wasm32-unknown-unknown-wasm --output fac.wasm; wasm-decompile fac.wasm; #! result: error: bad magic value


#! Prblem: ehader-file not part (of only the cxx part is adeded)
clang++ tut.cxx -ObjC++ --compile --target=wasm32-unknown-unknown-wasm --output fac.wasm; #! prodcue good results ... though the header-file is NOT included

#!
#! Straegy: merge them ... see if this resolves the pboelm:
echo "" > merged.cxx;
cat tut.h >> merged.cxx; cat tut.cxx >> merged.cxx;
#
clang++ merged.cxx -ObjC++ --compile --target=wasm32-unknown-unknown-wasm --output fac.wasm

```

- [x] "tut-3":
* geht teh above to compiel direclty using a c++-builder (updaitng our "x-build.bash")

- [x] "tut-3":
* explore:
* explore: use of objects/structs: how does the code (and access-methdos) becomes different from "tut-2"?
* explore: effects of itnernal macros
"x-build.bash": write the b uild-sciprt, get working
"":
"": 
- [x] "tut-3":
- [x] "tut-3":
- [x] "tut-3":
- [x] "tut-3":
- [x] "tut-3":
- [x] "":
--------------
- [x] "":
* scope: investigate how accessing c++ template4-constructs
* build-system: errors which are provoked?
* extends: "tut-3" with advanced c++-cosntrucors
- [x] "":
### Example: 
```cpp
//! Src: "test-template.cpp":
template <typename T> T myMax(T x, T y)
{
  return (x > y) ? x : y;
}

int main() {
  //Foo f(6);
  //return f.x;
  return myMax<int>(3, 7);
}
```
- [x] "":
- [x] "":
--------------
- [x] "":
* scope:
* extends: 
```
# FIXME: unalbe to compeil with a "printf(...)". Tried he following:
#!
#! Pre: clang++ --analyze tut.cxx
#! fix: .. why does the below nNOT work?
locate printf | grep -v -P "man|poset|node"; #! to find the path
#! Src: https://stackoverflow.com/questions/42997218/add-library-search-path-to-clang
clang++ tut.cxx  -L/usr/include/ -ObjC++ --compile --target=wasm32-unknown-unknown-wasm --output fac.wasm -v -L/usr/local/lib -l/user/local
# FIXME: whay are hte abov eargumetns flagged as 'input unused [-Wunused-command-line-argument]'?? <-- what apramtes to use
# FIXME: explore the below et of commans
/usr/bin/clang++ --help | less


# FIXME: go through the belwo options <-- what does they tell us?
#! Src: [https://stackoverflow.com/questions/48369566/clang-stdio-h-file-not-found]
clang++ -### tut.cxx

# FIXME: does it help explroignt hte below?
clang tut.cxx --target=wasm32-unknown-unknown-wasm --include-directory =/usr/include/ -nostartfiles -nostdlib -Wl,--no-entry -Wl,--export-all -o test.wasm


``` 
- [x] "":
- [x] "":
- [x] "":
* scope:
- [x] "": 
-----------
gcc api_base.c -c
gcc api_base.c api_main.c;

----------
nm fac.o
----------
gcc -c fac.c;
gcc -c wasm-rt-impl.c;
gcc  fac.c wasm-rt-impl.c main.c -lm;
----------
 paly arodun with the amcors fopr naming ... and relate to: https://stackoverflow.com/questions/62527929/function-declaration-problem-in-multi-file-c-project
