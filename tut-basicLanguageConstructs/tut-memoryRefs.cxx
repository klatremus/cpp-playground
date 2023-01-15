#include <iostream>

// #if __cplusplus >= 201103L
//   template<typename _Category>
//     struct __copy_move<true, false, _Category>
//     // first specialized template argument is whether to move
//     {
//       template<typename _II, typename _OI>
//         static _OI
//         __copy_m(_II __first, _II __last, _OI __result)
//         {
//       for (; __first != __last; ++__result, ++__first)
//         *__result = std::move(*__first); // That may be your line
//       return __result;
//     }
//     };
// #endif


class A {
public:
  int *pointer;
  A():pointer(new int(1)) {
    std::cout << "() => construct: " << pointer << std::endl;
  }
  A(A& a):pointer(new int(*a.pointer)) {
    std::cout << "(A& a): copy: " << pointer << std::endl;
  } // meaningless object copy
  A(A&& a) : // FIXME: is this funcion always called at 'exec-point = give-caller-value-of-object' (ie, as the object is no longer used int he current scope, thus, can savely be mvoed)?
    pointer(a.pointer)
  {
    a.pointer = nullptr;
    std::cout << "(A&& a) move: " << pointer << std::endl;
  }
  ~A(){
    std::cout << "~() destruct: " << pointer << std::endl;
    delete pointer;
  }
};
A return_rvalue(bool test) { //! Note: fucniton used to "avoid compiler optimization"
    A a, b;
    std::cout << "After init: apply if-calsue" << std::endl;
    if(test) return a; // equal to static_cast<A&&>(a);
    else return b;     // equal to static_cast<A&&>(b);
}

#include <type_traits>
int main_basicRefs() {
  //int &a = std::move(1); // illegal, non-const lvalue reference cannot ref rvalue
  {
    // Correct. The type of "01234" is const char [6], so it is an lvalue
    const char (&left)[6] = "01234";

    // Assert success. It is a const char [6] indeed. Note that decltype(expr)
    // yields lvalue reference if expr is an lvalue and neither an unparenthesized
    // id-expression nor an unparenthesized class member access expression.
    static_assert(std::is_same<decltype("01234"), const char(&)[6]>::value, ""); // FIXME: where=how to use this comionat of "static_assert" + "std::is_same" + "decltype< ..., ....>"?

    // Error. "01234" is an lvalue, which cannot be referenced by an rvalue reference
    // const char (&&right)[6] = "01234";
  }
  {
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    std::cout << "end of && example" << std::endl;
  }
  {
    std::string v = "hei";
    const std::string &b = std::move(v); // FIXME: is the "std::move" a basic copy-operaiton? <-- answer: "std::move moves the elements if possible, and copies otherwise. std::copy will always copy." [https://stackoverflow.com/questions/26432990/are-stdmove-and-stdcopy-identical] <-- FIXME: when shoiuld we epclty use the "std::move" operation (eg, instead of a cruder "obj_new = *old_object"?)?
    //const int &b = std::move(1); // legal, const lvalue reference can
    
    std::cout << "input: " << v << std::endl;
    std::cout << "result: " << b << std::endl;
  }
  {
    const char v = 3;
    const int &b = std::move(v);
    //const int &b = std::move(1); // legal, const lvalue reference can
    
    std::cout << "input: " << (int)v << std::endl;
    std::cout << "result: " << b << std::endl;
  }  
  return -0;
}

// --------------------------------------------------------
#include <iostream> // std::cout
#include <utility>  // std::move
#include <vector>   // std::vector
#include <string>   // std::string
#include <assert.h>

#include <iostream>
#include <utility>
void reference(int& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference(int&& v) {
    std::cout << "Rrr-value reference" << std::endl;
}
void reference(std::string& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference(std::string&& v) {
    std::cout << "Rrr-value reference" << std::endl;
}


template <typename T>
void pass(T&& v) {
    std::cout << "          normal param passing: ";
    reference(v);
}

#include <iostream>
#include <utility>
// void reference_2(int& v) {
//     std::cout << "lvalue reference" << std::endl;
// }
// void reference_2(int&& v) {
//     std::cout << "rvalue reference" << std::endl;
// }
template <typename T>
void pass_2(T&& v) {
  // FIXME: for case="l-value" ... is the implcaiotn that there is a "shallow copy"?
    std::cout << "          normal param passing: ";
    reference(v);
    std::cout << "       std::move param passing: ";
    reference(std::move(v)); //! ie, then try making the system 'steal=grab the data' <-- FIXME: seems like "std::move" ALWASY forces an r-value operaiton: correct? <-- FIXME: does "std::mvoe" use the 'enarest' r-valeu, or deudcues the atucal=acomtiv value(s)? how to vinesitgate?
    std::cout << "    std::forward param passing: ";
    reference(std::forward<T>(v)); // FIXME: how to understadn the workdings=applcailbiy of the "std::forward"??
    std::cout << "static_cast<T&&> param passing: ";
    reference(static_cast<T&&>(v));
}

int main_containers() {
  {
    std::string str = "Hello world.";
    std::vector<std::string> v;

    // use push_back(const T&), copy
    v.push_back(str);
    // "str: Hello world."
    std::cout << "str: " << str << std::endl;

    // use push_back(const T&&),
    // no copy the string will be moved to vector,
    // and therefore std::move can reduce copy cost
    v.push_back(std::move(str));
    // str is empty now
    std::cout << "str: " << str << std::endl;
  }
  {
    std::cout << "\n\n # && constructs, part 1"  << std::endl;
    std::cout << "rvalue pass:" << std::endl;
    pass(1); // FIXME: why is this interpted as an l-vlaue (ie, in contract to the cookboook)? <-- changes in the cmperil-spec?

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass(l);
    
    std::cout << "?? string-pass:" << std::endl;
    std::string v = "dfg";
    pass(v);    
  }
 {
    std::cout << "\n\n # && constructs, part 2"  << std::endl;
    std::cout << "\n# rvalue pass:" << std::endl;
    pass_2(66);

    std::cout << "\n# lvalue pass:" << std::endl;
    int l = 66;
    pass_2(l);
    
    return 0;
}


  return +0;
}



// --------------------------------------------------------

int main() {
  main_containers();
  assert(false); // FIXME: remvoe when above is owrking!
  // static_assert(false); // FIXME: can "static_assert" be seen as a macro-pamter (whcih stops the uion tuding the coaiton itself)? if yes, how do they differ?
  main_basicRefs();
  // FIXME: where (in our code) can we use the "std::move(..)" call? conrete applciaotns (of this copying)? <-- when isneritng objects reuqriemenbing heap-memory-allciotni (eg, when isneritng an "std::string object")?
  return 0;
}
