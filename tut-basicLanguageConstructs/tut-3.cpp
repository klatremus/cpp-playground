//! Src: https://changkun.de/modern-cpp/en-us/03-runtime/

// FIXME: make use of the bleow cosnturcts!

#include <iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move

void lambda_expression_capture() {
  auto important = std::make_unique<int>(1); // FIXME: what does the "make_unique"? ... an URI? 
  auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int { // FIXME: does the "std::move" change the ownership of "pointer = important"?
	       return x+y+v1+(*v2);
	     };
  std::cout << add(3,4) << std::endl;
}


#include <iostream>
using foo = void(int);  // function pointer
void functional(foo f) {
    f(1);
}
int main() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    // FIXME: where may we use the belwo strategy ... to use 'im,plcit fucniotns' as fitlering-arguemtns to a diffneret fucniotn?
    functional(f);  // call by function pointer
    f(1);           // call by lambda expression
    return 0;
}



#include <functional>
#include <iostream>

int foo(int para) {
    return para;
}

int main() {
    // std::function wraps a function that take int paremeter and returns int value
    std::function<int(int)> func = foo;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int { // FIXME: whow does thid "std::function" cosntruct differes from the abveo ??
        return 1+value+important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}


int foo(int a, int b, int c) {
    ;
}
int main() {
    // bind parameter 1, 2 on function foo,
    // and use std::placeholders::_1 as placeholder for the first parameter.
  // FIXME: what is the input-aprtmer to the "foo(..)" funciotn? <--- when is the "std::placeholders" useful?
    auto bindFoo = std::bind(foo, std::placeholders::_1, 1,2);
    // when call bindFoo, we only need one param left
    bindFoo(1);
}



// ---------------------

#include <type_traits>

int main() {
    // Correct. The type of "01234" is const char [6], so it is an lvalue
    const char (&left)[6] = "01234";

    // Assert success. It is a const char [6] indeed. Note that decltype(expr)
    // yields lvalue reference if expr is an lvalue and neither an unparenthesized
    // id-expression nor an unparenthesized class member access expression.
    static_assert(std::is_same<decltype("01234"), const char(&)[6]>::value, "");

    // Error. "01234" is an lvalue, which cannot be referenced by an rvalue reference
    // const char (&&right)[6] = "01234";
}

int mian() {
const char*   p    = "01234"; // Correct. "01234" is implicitly converted to const char*
const char*&& pr   = "01234"; // Correct. "01234" is implicitly converted to const char*, which is a prvalue.
// const char*& pl = "01234"; // Error. There is no type const char* lvalue


 std::vector<int> foo() {
    std::vector<int> temp = {1, 2, 3, 4};
    return temp;
}

std::vector<int> v = foo();
}


#include <iostream>
#include <string>

void reference(std::string& str) {
    std::cout << "lvalue" << std::endl;
}
void reference(std::string&& str) {
    std::cout << "rvalue" << std::endl;
}

int main()
{
    std::string  lv1 = "string,";       // lv1 is a lvalue
    // std::string&& r1 = lv1;          // illegal, rvalue can't ref to lvalue
    std::string&& rv1 = std::move(lv1); // legal, std::move can convert lvalue to rvalue
    std::cout << rv1 << std::endl;      // string,

    const std::string& lv2 = lv1 + lv1; // legal, const lvalue reference can
                                        // extend temp variable's lifecycle
    // lv2 += "Test";                   // illegal, const ref can't be modified
    std::cout << lv2 << std::endl;      // string,string,

    std::string&& rv2 = lv1 + lv2;      // legal, rvalue ref extend lifecycle
    rv2 += "string";                    // legal, non-const reference can be modified
    std::cout << rv2 << std::endl;      // string,string,string,string

    reference(rv2);                     // output: lvalue

    return 0;
}


#include <iostream>

int main() {
    // int &a = std::move(1); // illegal, non-const lvalue reference cannot ref rvalue
    const int &b = std::move(1); // legal, const lvalue reference can

    std::cout << b << std::endl;
}

#include <iostream>
class A {
public:
    int *pointer;
    A():pointer(new int(1)) {
        std::cout << "construct" << pointer << std::endl;
    }
    A(A& a):pointer(new int(*a.pointer)) {
        std::cout << "copy" << pointer << std::endl;
    } // meaningless object copy
    A(A&& a):pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "move" << pointer << std::endl;
    }
    ~A(){
        std::cout << "destruct" << pointer << std::endl;
        delete pointer;
    }
};
// avoid compiler optimization
A return_rvalue(bool test) {
    A a,b;
    if(test) return a; // equal to static_cast<A&&>(a);
    else return b;     // equal to static_cast<A&&>(b);
}
int main() {
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    return 0;
}


#include <iostream> // std::cout
#include <utility>  // std::move
#include <vector>   // std::vector
#include <string>   // std::string

int main() {

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

    return 0;
}

#include <iostream>
#include <utility>
void reference(int& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference(int&& v) {
    std::cout << "rvalue reference" << std::endl;
}
template <typename T>
void pass(T&& v) {
    std::cout << "          normal param passing: ";
    reference(v);
}
int main() {
    std::cout << "rvalue pass:" << std::endl;
    pass(1);

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass(l);

    return 0;
}

#include <iostream>
#include <utility>
void reference_2(int& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference_2(int&& v) {
    std::cout << "rvalue reference" << std::endl;
}
template <typename T>
void pass_2(T&& v) {
    std::cout << "          normal param passing: ";
    reference(v);
    std::cout << "       std::move param passing: ";
    reference(std::move(v));
    std::cout << "    std::forward param passing: ";
    reference(std::forward<T>(v));
    std::cout << "static_cast<T&&> param passing: ";
    reference(static_cast<T&&>(v));
}
int main() {
    std::cout << "rvalue pass:" << std::endl;
    pass(1);

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass(l);

    return 0;
}
