
#include <iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move

void lambda_expression_capture() {
  auto arr_int = std::make_unique<int>(1); // FIXME: what does the "make_unique"? ... an URI? 
  // FIXME: what is the effect of the "std::move(..)" in the lambda-fucniton?
  auto add = [v1 = 1, v2 = std::move(arr_int)](int x, int y) -> int { // FIXME: does the "std::move" change the ownership of "pointer = important"?
	       return x+y+v1+(*v2);
	     };
  std::cout << add(3,4) << std::endl;
  std::cout << "arr_int.pointer=" << arr_int.get() << std::endl;
}


using foo = void(int);  // function pointer <-- FIXME: can these be declreaed for any combiantos? <-- if yes, when=how to use these cosntructs?
void functional(foo f) {
    f(1);
}

#include <functional>
#include <iostream>

int _foo(int para) {
    return para;
}


int foo_threeArgs(int a, int b, int c) {
  std::cout << "a=" << a << std::endl;
  return 0;
}

int main_basicPointers() {
  {
    //! https://stackoverflow.com/questions/16918231/using-out-of-scope-variables-in-c11-lambda-expressions
    auto const global = 0;
    
    
    {
      auto const local = 0;
      
      auto lam1 = [](){ return global; }; // global is always seen
      auto lam2 = [&](){ return local; }; // need to capture local
      
      std::cout << lam1() << "\n";
      std::cout << lam2() << "\n";
    }
  }

  {
    lambda_expression_capture();
  }

  {
    auto f = [](int value) {
	       std::cout << value << std::endl;
	     };
    // FIXME: where may we use the belwo strategy ... to use 'im,plcit fucniotns' as fitlering-arguemtns to a diffneret fucniotn?
    functional(f);  // call by function pointer
    f(1);           // call by lambda expression
  }
  {
    // std::function wraps a function that take int paremeter and returns int value
    std::function<int(int)> func = _foo;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int { // FIXME: whow does thid "std::function" cosntruct differes from the abveo ?? <-- FIXME: wht is the effect of removintg the "&" symbol? ... IFMX:E hwat happends if we drop teh "-> init" statement? ... can "-> int" be repalce3d by "-> auto"?
				      return 1+value+important;
				    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
  }
  {
    // bind parameter 1, 2 on function foo,
    // and use std::placeholders::_1 as placeholder for the first parameter.
    // FIXME: what is the input-aprtmer to the "foo(..)" funciotn? <--- when is the "std::placeholders" useful?
    auto bindFoo = std::bind(foo_threeArgs, std::placeholders::_1, 1,2); //! where "1, 2" is now defauylt partmers (eg, (x, y) when updating r, g, b varialbes serpately
    // when call bindFoo, we only need one param left
    bindFoo(10);
    std::cout << "called bindFoo(..)" << std::endl;
  }
  return 0;
}



void main_modernFunctions() {
  //! Src. https://oleksandrkvl.github.io/2021/04/02/cpp-20-overview.html
class S{
  /**
     @remarks [https://stackoverflow.com/questions/43827651/can-a-lambda-capturing-nothing-access-global-variables]
    [a,&b] where a is captured by copy and b is captured by reference.
    [this] captures the current object (*this) by reference
    [&] captures all automatic variables used in the body of the lambda by reference and current object by reference if exists
    [=] captures all automatic variables used in the body of the lambda by copy and current object by reference if exists
    [ ] captures nothing

   **/
    void f(){
        [=]{};          // captures this by reference, deprecated since C++20
        [=, *this]{};   // OK since C++17, captures this by value
    }
    void f2(){
        [=]{};          // captures this by reference, deprecated since C++20
        //[=, this]{};    // OK since C++20, captures this by reference
    }  
};
}



int main() {
  main_modernFunctions();
  
  main_basicPointers();
  return 0;
}
