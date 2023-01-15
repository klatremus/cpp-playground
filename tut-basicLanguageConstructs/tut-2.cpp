/**
@file
@brief introduciton to modenr cpp
@remarks scope:
* Auto type derivation
* Scope for iteration
* Initialization list
* Variable parameter template
@remarks code:
- oekseth-anntoations onto exampels from: [ https://changkun.de/modern-cpp/en-us/02-usability/]
**/

// FIXME: explain each of the belwo concepts ... then udpate our readme-file
// FIXME: get this code to compile 
// FIXME: write your won pemtatuion of this (eg, a new data-structure)
// FIXME: 

#include <iostream>
#define LEN 10

int len_foo() {
    int i = 2;
    return i;
}
constexpr int len_foo_constexpr() {
    return 5;
}

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}


int main_constexpr() {
    char arr_1[10];                      // legal
    char arr_2[LEN];                     // legal

    int len = 10;
    // char arr_3[len];                  // illegal

    const int len_2 = len + 1;
    constexpr int len_2_constexpr = 1 + 2 + 3;
    // char arr_4[len_2];                // illegal, but ok for most of the compilers
    char arr_4[len_2_constexpr];         // legal

    // char arr_5[len_foo()+5];          // illegal
    char arr_6[len_foo_constexpr() + 1]; // legal

    // 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    std::cout << fibonacci(10) << std::endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

int main_iterator() {
    std::vector<int> vec = {1, 2, 3, 4};

    // since c++17, can be simplified by using `auto`
    // FIXME: what is the prupose of the "std::find" operator?
    const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2); // FIXME: does "2" start where to start the search?
    if (itr != vec.end()) {
        *itr = 3;
    }

    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        *itr = 4;
    }

    // should output: 1, 4, 3, 4. can be simplified using `auto`
    for (std::vector<int>::iterator element = vec.begin(); element != vec.end(); 
        ++element)
        std::cout << *element << std::endl;
}


#include <iostream>
#include <vector>

class Foo {
public:
    int value_a;
    int value_b;
    Foo(int a, int b) : value_a(a), value_b(b) {}
};

int main_initLists() {
    // before C++11
    int arr[3] = {1, 2, 3};
    Foo foo(1, 2);
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "arr[0]: " << arr[0] << std::endl;
    std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}

#include <initializer_list>
#include <vector>
#include <iostream>

class MagicFoo {
public:
  /**
To solve this problem, C++11 first binds the concept of the initialization list to the type and calls it std::initializer_list, allowing the constructor or other function to use the initialization list like a parameter, which is the initialization of class objects provides a unified bridge between normal arrays and POD initialization methods, such as:
   **/
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        for (std::initializer_list<int>::iterator it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }
};
int main_initializer_list() {
    // after C++11
  MagicFoo magicFoo = {1, 2, 3, 4, 5}; // FIXME: is this type-checking perofmred on compiletime? <-- FIXME: if "Magicfoo(list)" had more than one argument ... how woudl the system hadnled this? <-- FIXME: try otu the latter: si a compiation-error raised?

    std::cout << "magicFoo: ";
    for (std::vector<int>::iterator it = magicFoo.vec.begin(); 
        it != magicFoo.vec.end(); ++it) 
        std::cout << *it << std::endl;
}


#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> f() {
  /* Structured bindings provide functionality similar to the multiple return values provided in other languages. In the chapter on containers, we will learn that C++11 has added a std::tuple container for constructing a tuple that encloses multiple return values. But the flaw is that C++11/14 does not provide a simple way to get and define the elements in the tuple from the tuple, although we can unpack the tuple using std::tie But we still have to be very clear about how many objects this tuple contains, what type of each object is, very troublesome. */
  return std::make_tuple(1, 2.3, "456"); // FIXME: write an example using this concpet!
}

int main_structruedBindingsn() {
  auto [x, y, z] = f(); // FIXME: try prokoign a compeil-tiem erro here!
  std::cout << x << ", " << y << ", " << z << std::endl;
  return 0;
}


#include <initializer_list>
#include <vector>
#include <iostream>

class MagicFoo_auto {
public:
  std::vector<int> vec;
  MagicFoo_auto(std::initializer_list<int> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
      vec.push_back(*it);
    }
  }
};





int add(auto x, auto y) {
  return x+y;
}

int main_auto() {
  MagicFoo_auto magicFoo = {1, 2, 3, 4, 5};
  std::cout << "magicFoo: ";
  for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
  { //! Some other common usages:

    // FIXME: what is the data-type if "new auto(1.0)" is called (eg, "double" or "float")?

    auto i = 5;              // i as int
    auto arr = new auto(10); // arr as int *

    // Since C++ 20, auto can even be used as function arguments. Consider the following example:

      

    auto i = 5; // type int
    auto j = 6; // type int
    std::cout << add(i, j) << std::endl;

  }
  return 0;
}



template<typename R, typename T, typename U> R add3_ugly(T x, U y) { // FIXME: why do we need to write "typename"? ... are there other 'qualifiers' we an use?
    return x+y;
}
template<typename T, typename U> auto add2(T x, U y) -> decltype(x+y) { // FIXME: what does the "-> " symbol mean? other use-cases (for this)?
    return x + y;
}

// The good news is that from C++14 it is possible to directly derive the return value of a normal function, so the following way becomes legal:

template<typename T, typename U> auto add3(T x, U y){ // FIXME: try to dineify caese where "auto" would NOT workd (ie, where "decltype" woudl be repferable
  return x + y; // FIXME: whne (T, U) are differne clases ... what detmeriens the outomce (of this)?
}

int main_decltype() {
  auto x = 1;
  auto y = 2;
  decltype(x+y) z; // FIXME: how can we use thsi "decltype" concept?

  // You have seen in the previous example that decltype is used to infer the usage of the type. The following example is to determine if the above variables x, y, z are of the same type:
  /**
     Among them, std::is_same<T, U> is used to determine whether the two types T and U are equal. The output is:

     type x == int
     type z == type x
  **/
  if (std::is_same<decltype(x), int>::value)
    std::cout << "type x == int" << std::endl;
  if (std::is_same<decltype(x), float>::value)
    std::cout << "type x == float" << std::endl;
  if (std::is_same<decltype(x), decltype(z)>::value)
    std::cout << "type z == type x" << std::endl;

  /**
     decltype(x+y) add(T x, U y) # fIXME: explain why latter fails to compile! ... what can we dirve form this?

But in fact, this way of writing can not be compiled. This is because x and y have not been defined when the compiler reads decltype(x+y). To solve this problem, C++11 also introduces a trailing return type, which uses the auto keyword to post the return type:
  **/

  // You can check if the type derivation is correct:

  // after c++11
  auto w = add2<int, double>(1, 2.0);
  if (std::is_same<decltype(w), double>::value) {
    std::cout << "w is double: ";
  }
  std::cout << w << std::endl;
  
  // after c++14
  auto q = add3<double, int>(1.0, 2);
  std::cout << "q: " << q << std::endl;


  //  In simple terms, decltype(auto) is mainly used to derive the return type of a forwarding function or package, which does not require us to explicitly specify the parameter expression of decltype. Consider the following example, when we need to wrap the following two functions:

  std::string  lookup1();
  std::string& lookup2();

  // In C++11:

  std::string look_up_a_string_1() {
    return lookup1();
  }
  std::string& look_up_a_string_2() {
    return lookup2();
  }

  // With decltype(auto), we can let the compiler do this annoying parameter forwarding:

  decltype(auto) look_up_a_string_1() { // FIXME: how to utlise the ability of "decltype(auto)" to autmcially map a singuarl=this funciont to both "std::string" AND "std:string&"? <-- are there otehr funciotns hwich this is 'expanded to' (eg, a cpp straegy for intrsoepction, eg, to plto the compelte set of 'allwobale fucniotn-calls resutling from the "decltype(auto)" construct?)? 
    return lookup1();
  }
  decltype(auto) look_up_a_string_2() {
    return lookup2();
}
}
// ----------------------------------
#include <iostream>
#include <utility>
// FIXME: can the below stgrtray of "void reference(int& v)" AND "void reference(int&& v)" be used for system-intrsoepction (eg, to 'map out' the types being used at runt-ime)?
void reference(int& v) {
    std::cout << "lvalue reference" << std::endl;
}
void reference(int&& v) {
  std::cout << "rvalue reference" << std::endl; // FIXME: why is "&&" an "rvalue reference"? <-- due to the (??) 'memory-pointer poining to the memory at the value' (ie, a look-ahead=2 = len("&&")?)?
}
template <typename T> void pass(T&& v) {
  std::cout << "          normal param passing: ";
  reference(v);
  std::cout << "       std::move param passing: ";
  reference(std::move(v));
  std::cout << "    std::forward param passing: ";
  reference(std::forward<T>(v));
  std::cout << "static_cast<T&&> param passing: ";
  reference(static_cast<T&&>(v));
}
void main_forwarding() {
  //! Note: before reding this exmapel, try understanding "tut-std-forward.cpp" and "tut-doubleAmpersand.cpp" and ...
  std::cout << "rvalue pass:" << std::endl;
  pass(1);
  
  std::cout << "lvalue pass:" << std::endl;
  int l = 1;
  pass(l); // FIXME: is this an 'r-value' as the pass(1) argument refers to a variable="l"? ... for "const" data-types, what woudl the data-type be?

  static const int l_static_const = 1;
  pass(l_static_const); // FIXME: is this an 'r-value' as the pass(1) argument refers to a variable="l"? ... for "const" data-types, what woudl the data-type be?
  assert(false); // FIXME: update the desciprtion based on the above resutlls ... which is what we try out
    /**
The outputs are:

rvalue pass:
          normal param passing: lvalue reference <-- FIXME: why is it only an 'rvalue' here?
       std::move param passing: rvalue reference
    std::forward param passing: rvalue reference
static_cast<T&&> param passing: rvalue reference
lvalue pass:
          normal param passing: lvalue reference <-- FIXME: why does "int l = 1" results in an "lvalue"? ... ie, why is the "rvalue" NOT accessed directly?
       std::move param passing: rvalue reference <-- FIXME: 
    std::forward param passing: lvalue reference
static_cast<T&&> param passing: lvalue reference

Regardless of whether the pass parameter is an lvalue or an rvalue, the normal pass argument will forward the argument as an lvalue. So std::move will always accept an lvalue, which forwards the call to reference(int&&) to output the rvalue reference.
     **/
    return 0;
    
}
// ----------------------------------
#include <iostream>

template<typename T> auto print_type_info(const T& t) { // FIXME: a) why is "auto" used as return-value (instead of "T")? 
  if constexpr (std::is_integral<T>::value) { // FIXME: what is "std::is_integral"? ... when does the sysem knows if 'an expression is constexpr'? ... when to sue this cosnturct? <-- where can we use this consurct (in our code)?
        return t + 1;
    } else {
        return t + 0.001;
    }
}



void main_constexpr_if() {
  //! Src: []
    std::cout << print_type_info(5) << std::endl;
    std::cout << print_type_info(3.14) << std::endl;
    
    // FIXME: below: why does the below examples illustrate the "if constexpr" call?
    //     At compile time, the actual code will behave as follows:
    
    //     int print_type_info(const int& t) {
    //     return t + 1;
    //     }
    
    //     double print_type_info(const double& t) {
    //     return t + 0.001;
    //     }

    // int main() {
    //     std::cout << print_type_info(5) << std::endl;
    //     std::cout << print_type_info(3.14) << std::endl;
    // }
}


// ----------------------------------
#include <iostream>
#include <vector>
#include <algorithm>


void main_() { //! Range Based for-loops
  // Finally, C++11 introduces a range-based iterative method, and we can write loops that are as concise as Python, and we can further simplify the previous example:
  //! Src: []
    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4; // FIXME: does this code search for "value=3" ... 
    for (auto element : vec) // FIXME: does the ":" operator always correspodns the "in" operator (in Python)?
        std::cout << element << std::endl; // read only
    for (auto &element : vec) {
        element += 1;                      // writeable
    }
    for (auto element : vec)
        std::cout << element << std::endl; // read only
    // FIXME: valliate that the below code resutls in a compile-error <-- possible to avodi teh compielr failing (for these 'delierate' compile-eror-cases)? .. alternitvley, writ a enw file (with codeexmpels tat sohudl fail) ... then use python to vlaite (taht they fail).
    for (const auto &element : vec) {
        element += 1;                      // writeable
    }
}

// ----------------------------------

void main_templates_external() {
  // C++11 introduces an external template that extends the syntax of the original mandatory compiler to instantiate a template at a specific location, allowing us to explicitly tell the compiler when to instantiate the template:

  template class std::vector<bool>;          // force instantiation
  extern template class std::vector<double>; // should not instantiation in current file

  // FIXME: when to sue the above cosntrucs?
}


// ----------------------------------
template<bool T>  class MagicType_configure_1 {
  bool magic = T;
};

template<typename T, typename U>class MagicType_configure_2 {
public:
  T dark;
  U magic;
};

void main_templates_configureThem() {
  //! Src: []
  // The ">"
  // In the traditional C++ compiler, >> is always treated as a right shift operator. But actually we can easily write the code for the nested template:

  std::vector<std::vector<int>> matrix;
  // This is not compiled under the traditional C++ compiler, and C++11 starts with continuous right angle brackets that become legal and can be compiled successfully. Even the following writing can be compiled by:

  // in main function:
  std::vector<MagicType_configure_1<(1>2)>> magic; // legal, but not recommended <-- FIXME: what is the result of "1>2" (eg, a bit-shift)? ... what is the reuslt of the ">>" operator?

  
  // Type alias templates ...  In traditional C++, typedef can define a new name for the type, but there is no way to define a new name for the template. Because the template is not a type. E.g:
  // template<typename T> typedef MagicType_configure_2<std::vector<T>, std::string> FakeDarkMagic;   // not allowed

  // C++11 uses using to introduce the following form of writing, and at the same time supports the same effect as the traditional typedef:
  typedef int (*process)(void *);
  using NewProcess = int(*)(void *);
  template<typename T>   using TrueDarkMagic = MagicType_2<std::vector<T>, std::string>; // FIXME: does the "using" keyword enalbe typedefs of temeplates?
  //! Then use it:
  TrueDarkMagic<bool> you; // FIXME: an exmapel fot hsi?
  return 1;
}
// --------------

#include <iostream>
template<typename... Ts>  void magic(Ts... args) { // First, we can use sizeof... to calculate the number of arguments: <-- FIXME: where can we sue this 'variadic' combaiton? when is this useful?
    std::cout << sizeof...(args) << std::endl;
}



int main_templates_configureThem_variadic_listBasedOnCompileTime() { //! ie, use 'hard-coded lists' in tempaltes (aka, 'variadic')
  // --------------
  //
  // Variadic templates ... C++'s unique Black Magic. ... now: C++11 ... allowing any number, template parameters of any category, and there is no need to fix the number of parameters when defining. <-- FIXME: how to utlie thsi extended expreisivty? ... how does the latter rleated to Python?

  template<typename... Ts> class Magic;  // The template class Magic object can accept an unrestricted number of typename as a formal parameter of the template, such as the following definition:

  class Magic<int,
	      std::vector<int>,
	      std::map<
		std::string,
		std::vector<int>
		>
	      >
    darkMagic; // note: a template parameter with a number of 0 is also possible: class Magic<> nothing;. <-- FIXME: how to use (in rpatice) thios template-varidci-black-magic concpet?
  template<typename Require, typename... Args> class Magic2; // FIXME: how to use this concpet?

  
  // ... The variable length parameter template can also be directly adjusted to the template function. The printf function in the traditional C, although it can also reach the call of an indefinite number of formal parameters, is not class safe. <-- FIXME: why is "printf(..)" NOT class-safe? when is "printf(..)" unsafe to use? how can we provke such sitaitons (in code-debuging?)?



  // FIXME: how to write a pemtaution of the following funciton: template<typename... Args> void printf(const std::string &str, Args... args);

  // Then we define variable length template parameters, how to unpack the parameters?
  // We can pass any number of arguments to the magic function:
  magic();      // 0
  magic(1);     // 1
  magic(1, ""); // 2
}
// ---------------------------------
#include <iostream>
template<typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}
template<typename T0, typename... T>   void printf2(T0 t0, T... t) { // support for variable parameter template expansion in C++17, so you can write printf in a function:
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...); // FIXME: this pattern seems extmrely smart!! --- how to use it in rpacise?
}

template<typename T, typename... Ts> auto printf3(T value, Ts... args) { // Recursive template functions are standard practice, but the obvious drawback is that you must define a function that terminates recursion. Here is a description of the black magic that is expanded using the initialization list:
  std::cout << value << std::endl;
  //! Note(below): "void" used to avodi compielr-warnings
  //! Note(below): "std::initializer_list<T>" exapnds the "value" <-- ie, "value => [ .. [..] ]": is this a correct obseriovn=asseriotn? <-- FIXME: try it out!
  //! Note(below): the "(), " implies that the lamba-expresison is peormred befure the "std::cout" usage <-- correct?
  (void) std::initializer_list<T>{([&args] { // FIXME: is this black-magic used to ... call the above fucniton?= <-- FIXME: try it out!
				     std::cout << args << std::endl;
				   }(), value)...};
}
#include <iostream>
template<typename ... T> auto sum3(T ... t) { // FIXME: how is "sum3" similar to the above "printf3(..)" call? <-- seems more simliar to "printf1(..)" ... FIXME: why=how is "sum3(..)" terminated (ie, what caseus the requrision to stop?)?
    return (t + ...);
}
// template <typename T, typename U> auto add(T t, U u) {
//     return t+u;
// }


int main_templates_configureThem_variadic_recursive_unpack() { //! ie, unpack lists using compiler-time unpacking (aka, recursion) <-- FIXME: when can this appraoch=method be useufl to apply?
    printf1(1, 2, "123", 1.1);
    //! a vairnat whjih is easier to write=integate=apply
    printf2(1, 2, "123", 1.1);
    //! A black-magic part to ermtine the requcsin:
    printf3(1, 2, "123", 1.1);    
    //! A permtaution oft he above black-magic-stuff:
    std::cout << sum3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}


template <typename T, int BufSize>  class buffer_t { //! where "int BufSize" is a non-type template-paratmer
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
}
  template <auto value> void foo() { //! ie, where the compielr asistes 'with the deriviaont of the type-valeu' <-- FIXME: how=when to use hete "<auto value>" template-paatmer?
    std::cout << value << std::endl;
    return;
  }

int main_templates_configureThem_auto() { //! 
  buffer_t<int, 100> buf; // 100 as template parameter
  //! Use the "<auto value>" tempalte-syntax:
  foo<10>();  // value as int
}



// ----------------------------------

void main_templates_() {
  //! Src: []
}


// ----------------------------------

void main_templates_() {
  //! Src: []
}
// ----------------------------------

void main_objectOriented_delegateConstructs() { // Delegate Constructtor <-- what does this mean?
  //! Src: []
}

// ----------------------------------

void main_objectOriented_() {
  //! Src: []
}


// ----------------------------------

void main_objectOriented_() {
  //! Src: []
}


// ----------------------------------

void main_objectOriented_() {
  //! Src: []
}

// ----------------------------------

void main_() {
  //! Src: []
}


void main_() {
  //! Src: []
}






#include <iostream>
class Base { // "Delegate constructor": allows a constructor to call another constructor in a constructor in the same class, thus simplifying the code:
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // delegate Base() constructor <-- FIXME: idniefy useage of the 'delegate constructor'.
        value2 = value;
    }
};

int main() {
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;
}




#include <iostream>
class Base { //! "Inheritance constructor": ... to avodi redefning the cosnturo muliple times
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // delegate Base() constructor
        value2 = value;
    }
};
class Subclass : public Base {
public:
    using Base::Base; // inheritance constructor <-- FIXME: what does the "using" keyword imply=mean?
};
int main() {
    Subclass s(3);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;
}



struct Base { // "Explicit virtual function overwrite"
  virtual void foo(); // FIXME: if term="virtual" is NOT used, would an error then arise in "SubClass"? <-- try it out!
};
struct SubClass: Base {
    void foo();
};

struct Base {
    virtual void foo(int);
};
struct SubClass: Base {
  // FIXME: what exmaple can we write where we ned both "virtual" AND "override"? <--- FIXME: could we write only "void foo(int) override" (or: does "overroide" always NEED to be joiend=attached to the "virtual" keywrod)?
    virtual void foo(int) override; // legal
    virtual void foo(float) override; // illegal, no virtual function in super class
};


struct Base { // "final": "to prevent the class from being continued to inherit and to terminate the virtual function to continue to be overloaded.":
  virtual void foo() final; //! where "final" is the inverse=oppsite of "override"? ... "final" implies that not any enw fucintos (witht he same name+config) cna be defined (ie, the last=final in the class-heirarcy-tree)?
};
struct SubClass1 final: Base {
}; // legal

struct SubClass2 : SubClass1 {
}; // illegal, SubClass1 has final

struct SubClass3: Base {
    void foo(); // illegal, foo has final
};




class Magic { // "Explicit delete default function": here: "explicit declarations to take or reject functions that come with the compiler. E.g:"
  // Motivaiton: In traditional C++, if the programmer does not provide it, the compiler will default to generating default constructors, copy constructs, assignment operators, and destructors for the object. Besides, C++ also defines operators such as new delete for all classes. This part of the function can be overridden when the programmer needs it.
public:
  Magic() = default; // explicit let compiler use default constructor <-- FIXME: what happedns if the "= default" keywords is NOT used?
  Magic& operator=(const Magic&) = delete; // explicit declare refuse constructor <-- FIXME: what is a "refuse constructor"?
  Magic(int magic_number);
}

#include <iostream>
template<typename T> std::ostream& operator << (typename std::enable_if<
						std::is_enum<T>::value, // FIXME: explore the "is_enum" attribute ... how to use this?
						std::ostream
						>::type& stream, const T& e)
{
  // FIXME: write a epmtatuion of this ... to get the enunm-value <-- nessary? ... what is the type of "new_enum::value3"?
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}


enum class new_enum : unsigned int { // "Strongly typed enumerations": <-- FIXME: can this also be used to inehritt from classes? ... possible to use this to derive the enum-type direlcty? ... how to use this in combion with tempale-aprams + decltype(..) contructs?
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

int main_enums() {
  // FIXME: how to et the int-time of a 'storngly typed enum'?
  if (new_enum::value3 == new_enum::value4) { // true
    std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
  }
  std::cout << new_enum::value3 << std::endl
}





