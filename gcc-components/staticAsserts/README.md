# Scope: use of "static_assert(..)" for compilers by default NOT supporting "static_assert(..)" constructs

Example files:
- "tut-1.c": a colleciton of strategies for static_assert(..)" explorations

```cpp
//! An example of a cosntruct
// Src: https://stackoverflow.com/questions/9229601/what-is-in-c-code
sizeof(struct { int: -!!(e); }))
```

- "":
- "":
- "":

```bash
gcc tmp.c -O0; ./a.out ;
gcc tmp.c -O2; ./a.out ;
gcc tmp.c -O3; ./a.out ;
```