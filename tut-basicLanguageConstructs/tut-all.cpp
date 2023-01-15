// ----------------------------------
#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <iostream>
#include <memory>  // std::make_unique
#include <utility> // std::move
#include <iostream>
#include <string>
#include <iostream>
#include <set>
#include <vector>
using namespace std;



template <typename ... Args> auto sum(Args ... args) { //! Eval: how can this be used for printing?
  return (args + ...); //! evla: what is the effect of this?
  //return (args + ... + 0);
}

template <typename ...Args> auto all(Args ...args) {
  return (... && args); //! eval: what is the effect of this? where can this expanion be used? if an expression should be rewirten (using this), whow woudl the enw code look like?
}

int main() {
  cout << sum(1, 2, 3) << endl;
  cout << sum(to_string(1), to_string(2), to_string(2))
       << endl;

  cout << "all.1=" << all(true) << endl;
  cout << "all.2=" << all(true, false, true) << endl;  
}



void lambda_expression_capture() {
  auto important = std::make_unique<int>(1); // FIXME: what does the "make_unique"? ... an URI? 
  auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int { // FIXME: does the "std::move" change the ownership of "pointer = important"?
	       return x+y+v1+(*v2);
	     };
  std::cout << add(3,4) << std::endl;
}



template<typename T> auto print_type_info(const T& t) { // FIXME: a) why is "auto" used as return-value (instead of "T")? 
  if constexpr (std::is_integral<T>::value) { // FIXME: what is "std::is_integral"? ... when does the sysem knows if 'an expression is constexpr'? ... when to sue this cosnturct? <-- where can we use this consurct (in our code)?
        return t + 1;
    } else {
        return t + 0.001;
    }
}

#include <iostream>
template<typename ... T> auto sum3(T ... t) { // FIXME: how is "sum3" similar to the above "printf3(..)" call? <-- seems more simliar to "printf1(..)" ... FIXME: why=how is "sum3(..)" terminated (ie, what caseus the requrision to stop?)?
    return (t + ...);
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

template<typename A, typename B> auto min(A&& aref, B&& bref) {
  /** 
      Consider the simplest template function- min and max. In C++03 you have to overload for all four combinations of const and non-const manually. In C++0x it's just one overload. Combined with variadic templates, this enables perfect forwarding.
      - Src: [https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11]
   **/
  // for example, if you pass a const std::string& as first argument,
  // then A becomes const std::string& and by extension, "aref" becomes
  // const std::string&, completely maintaining it's type information.
  if (std::forward<A>(aref) < std::forward<B>(bref))
    return std::forward<A>(aref);
  else
    return std::forward<B>(bref);
  // FIXME: write an exampel using this "&&" template
}



enum class new_enum : unsigned int { // "Strongly typed enumerations": <-- FIXME: can this also be used to inehritt from classes? ... possible to use this to derive the enum-type direlcty? ... how to use this in combion with tempale-aprams + decltype(..) contructs?
    value1,
    value2,
    value3 = 100,
    value4 = 100
};





int main() {
  std::map<std::string, long long int> m {
					  {"a", 1},
					  {"b", 2},
					  {"c", 3}
  };
  for (const auto &obj : m) {
    auto val = std::hash<std::string>{}(obj.first); 
    std::cout << obj.first << ": " << obj.second << " => key="<< val << std::endl; //! [https://stackoverflow.com/questions/26281979/c-loop-through-map]
  }
  //! A permtuation of the above:
  for (auto&& [key, value] : m) { // FIXME: why si the "&&" used here? <-- try usign this concpet when writing a new code-chunk!
    std::cout << key << ": " << value << std::endl; //! [https://stackoverflow.com/questions/26281979/c-loop-through-map]    
  }
}


// ------------------------------------
//
// Step: integrate the use of the "explciti" keyword:
//! Src: https://www.geeksforgeeks.org/use-of-explicit-keyword-in-cpp/
//!
/**
//! Src: https://www.geeksforgeeks.org/use-of-explicit-keyword-in-cpp/
//! An example of where the lack of "explicit" cause problems:
// C++ program to illustrate default
// constructor without 'explicit'
// keyword
#include <iostream>
using namespace std;
 
class Complex {
private:
    double real;
    double imag;
 
public:
   
    // Parameterized constructor
    Complex(double r = 0.0,
            double i = 0.0) : real(r),
                              imag(i)
    {
    }
 
    // A method to compare two
    // Complex numbers
    bool operator == (Complex rhs)
    {
        return (real == rhs.real &&
                imag == rhs.imag);
    }
};
 
// Driver Code
int main()
{
    // a Complex object
    Complex com1(3.0, 0.0);
 
    if (com1 == 3.0) //! Eval: is this comparison valid? if yes, why?
        cout << "Same";
    else
        cout << "Not Same";
    return 0;
}
**/

// C++ program to illustrate
// default constructor with
// 'explicit' keyword
// #include <iostream>
// using namespace std;


// --------------------------
// 
class NotImplementedError : public std::logic_error
{
public:
  //const string err = "!!\t Funcion Not implemented [" + std::string(__FILE__) + "::" + std::string(__FUNCTION__) + "::" + std::string( __LINE__) + "]";
  //cout << 10;
  //stringstream ss;
  //stringstream string_object_name;
  //string_object_name << 50;
  static string get_errorString() {
    // FIXME: why does the "std::string(10)" OR "std::string(__LINE__)" not work?
    char string_line[100]; // = atoa(__LINE__);
    memset(string_line, '\0', 100);
    sprintf(string_line, "%d", __LINE__);
    const string err = "!!\t Funcion Not implemented [" + std::string(__FILE__) + "::" + std::string(__FUNCTION__) + "::" + string_line; //std::string(10); // << "10"; //std::string(10); // __LINE__) + "]";
    return err;
  }
  NotImplementedError() : std::logic_error(get_errorString()) { };
  //NotImplementedError() : std::logic_error(err) { };
  //NotImplemented() : std::logic_error("!!\t Funcion Not implemented [" << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << "]") { };
};

template<typename T, T threshold_min,  T threshold_max>
class Error_OutOfRange_Base : public std::logic_error
{
private:
  static string get_errorString(const T value) {
    // FIXME: why does the "std::string(10)" OR "std::string(__LINE__)" not work?
    char string_line[100]; // = atoa(__LINE__);
    memset(string_line, '\0', 100);
    sprintf(string_line, "%d", __LINE__);
    const string err = "!!\t Value=\"" + std::to_string(value) + "\" (of type=\"" + typeid(value).name() + "\") out of range, givenFuncion max-range=[" + std::to_string(threshold_min) + ", " + std::to_string(threshold_max) + "] [" + std::string(__FILE__) + "::" + std::string(__FUNCTION__) + "::" + string_line; //std::string(10); // << "10"; //std::string(10); // __LINE__) + "]";
    return err;
  }  
public:
  /**
     @brief raises an erorr if teh cirtiea matches
   **/
  //static Error_OutOfRange_Base raiseIf_criteriaMatches(const T value) {
  static void raiseIf_criteriaMatches(const T value) {
    if( ((index_t)value < threshold_min) || ((index_t)value > threshold_max)  ) {
      //cout << "!!\t\t(outsiode-range)\t...value='" << (int)value << "' ,,," << endl;
      // FIXME: validate that the below trheosw a new error
      const auto obj = Error_OutOfRange_Base(value);
      throw obj;
      //obj.raise_exeception();
    }
  }
  void raise_exeception() throw() {
    throw this;
  }
  Error_OutOfRange_Base(const T value) : std::logic_error(get_errorString(value)) { };
};
typedef Error_OutOfRange_Base<uchar, 0, 255> Error_OutOfRange_RGB;
typedef Error_OutOfRange_Base<uchar, 0, 1> Error_OutOfRange_Binary;


template <typename _Node> class EntryBase {
  virtual void print_data() const {
    throw NotImplementedError();
  }
  //virtual string to_string() = 0; // FIXME: why does this cause an error?
  virtual string to_string() { //= 0;//   { // FIXME: why does "const" cause here a bug?
     throw NotImplementedError();
   }

  // FIXME: how cosntrucintg virual fucnitons for the belwo?
  virtual _Node get_head() const  {
  // virtual _Node get_head() const {
     throw NotImplementedError();
   }
  virtual bool isEqual(const _Node obj_cmp)const {
    throw NotImplementedError();
  }
  // FIXME: can we add the bleow to this? ... what is the feffect of this?
  template<typename> friend class Data_Row; //! ie, make all prviae emmes accesislt to the Data_Row class [https://stackoverflow.com/questions/8967521/class-template-with-template-class-friend-whats-really-going-on-here]  
};

class A
{
    int x;
          public:
             
    A()
    {
        x=10;
    }
    friend class B;    //friend class
};
 
class B
{
    public:
        void display(A &t)
        {
            cout<<endl<<"The value of x="<<t.x;
        }   
};
 
main()
{
    A _a;
    B _b;
    _b.display(_a);
    return 0;
}

class Base {
public:
    virtual void display() final  {
        cout << "from base" << endl;
    }
};
class Child : public Base {
public:
    void display() {
        cout << "from child" << endl;
    }
};
int main() {
    Base *b = new Child();
    b->display();
    cin.get();
    return 0;
}

class _Base final {
public:
    void displayBase()   {
        cout << "from base" << endl;
    }
};
class _Child : public _Base {
public:
    void displayChild() {
        cout << "from child" << endl;
    }
};


#include<iostream>
using namespace std;
  
class base {
public:
    virtual void print()
    {
        cout << "print base class\n";
    }
  
    void show()
    {
        cout << "show base class\n";
    }
};
  
class derived : public base {
public:
    void print()
    {
        cout << "print derived class\n";
    }
  
    void show()
    {
        cout << "show derived class\n";
    }
};
  
int main()
{
    base *bptr;
    derived d;
    bptr = &d; //! Eval: why is this binidnig valid? would it still be valid if we wrote "base obj = d;"?
  
    // Virtual function, binded at runtime
    bptr->print();
  
    // Non-virtual function, binded at compile time
    bptr->show();
    
    return 0;
}



int main()
{
    A a1 = 1;      // OK: copy-initialization selects A::A(int)
    A a2(2);       // OK: direct-initialization selects A::A(int)
    A a3 {4, 5};   // OK: direct-list-initialization selects A::A(int, int)
    A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
    A a5 = (A)1;   // OK: explicit cast performs static_cast
    if (a1) { }    // OK: A::operator bool()
    bool na1 = a1; // OK: copy-initialization selects A::operator bool()
    bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization
 
//  B b1 = 1;      // error: copy-initialization does not consider B::B(int)
    B b2(2);       // OK: direct-initialization selects B::B(int)
    B b3 {4, 5};   // OK: direct-list-initialization selects B::B(int, int)
//  B b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int, int)
    B b5 = (B)1;   // OK: explicit cast performs static_cast
}





    std::vector<int> vec = {1, 2, 3, 4};
    if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) *itr = 4; // FIXME: does this code search for "value=3" ... 
    for (auto element : vec) // FIXME: does the ":" operator always correspodns the "in" operator (in Python)?
        std::cout << element << std::endl; // read only
    for (auto &element : vec) {
        element += 1;                      // writeable
    }


// --------------------------
// 
//! For-loops:
//! Src: https://www.cppstories.com/2022/improve-loops-cpp2b/
// std::ssize() from C++20:
for (int i = ssize(vec) - 1; i >= 0; --i)
    std::cout << i << ": " << vec[i] << '\n';

// For the forward loop, we can write:
for (int i = 0; i < ssize(vec); ++i)
    std::cout << i << ": " << vec[i] << '\n';

// Alternatively there are also safe comparison functions like: cmp_less(), also from C++20:
for (int i = 0; std::cmp_less(i, vec.size()); ++i)
    std::cout << i << ": " << vec[i] << '\n';

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


int main_enums() {
  // FIXME: how to et the int-time of a 'storngly typed enum'?
  if (new_enum::value3 == new_enum::value4) { // true
    std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
  }
  std::cout << new_enum::value3 << std::endl
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

#include <vector>
#include <algorithm>
#include <iostream>
 
struct Sum
{
    void operator()(int n) { sum += n; }
    int sum{0};
};
 
int main()
{
    std::vector<int> nums{3, 4, 2, 8, 15, 267};
 
    auto print = [](const int& n) { std::cout << " " << n; };
 
    std::cout << "before:";
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';
 
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
 
    // calls Sum::operator() for each number
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());
 
    std::cout << "after: ";
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';
    std::cout << "sum: " << s.sum << '\n';
}

//! "tut-functions.cxx"
    std::function<int(int)> func2 = [&](int value) -> int { ... }
using foo = void(int);  // function pointer <-- FIXME: can these be declreaed for any combiantos? <-- if yes, when=how to use these cosntructs?
    std::function<int(int)> func = _foo;
    auto bindFoo = std::bind(foo_threeArgs, std::placeholders::_1, 1,2); //! where "1, 2" is now defauylt partmers (eg, (x, y) when updating r, g, b varialbes serpately


template<typename T, typename U> class EntryJobListing : Entry_Base {
  T t;
  U u;
public:
  int getValue() {
    // FIXME: validate that the blewo logics works!
    //int getValue() final {
    //constexpr if(is_integral<T>::value) {
    if constexpr(is_integral<T>::value) {
	return 0;
      }  else {
      return T::get_value();
    }
  }

  void operator() (T a)
  {
    cout << a * 3 << " ";
    if ( (int)a % 2 == 0)
      {
	throw a; //! FIXME: what is the pros+cosnts of using a "throw" as an tlatnvie reutnr-valeu?
             
      }
  }
public:
  //EntryJobListing(U x, T y) {} // : t{ x }, u{ y } {}
  EntryJobListing(T x, U y) : t{ x }, u{ y } {}
  EntryJobListing(const std::initializer_list<int>& v) {
    t = *(v.begin());
    u = *(v.begin() + 1);
  }  
};

class A
{
public:
  virtual void foo()=0;
  virtual void hello()=0;
};

class B: public A
{
public:
  void myFoo();
  void hello() { std::cout << "Hello!"; }
};


// ----------------
class Sum {
public:
  void operator()(int n) { sum += n; }
  int sum{0}; //! Eval: how can this initlaision be utlised (eg, for writing mroe efevitve, and fault-torleant, code)?
};


int _dummyFoo_int(const int para) {return para;}
int foo_threeArgs(int a, int b, int c) {
  std::cout << "a=" << a << std::endl;
  return 0;
}

  {
    std::vector<int> nums{3, 4, 2, 8, 15, 267};
 
    auto print = [](const int& n) { std::cout << " " << n; };
 
    std::cout << "before:";
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';
 
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
 
    // calls Sum::operator() for each number
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());
 
    std::cout << "after: ";
    std::for_each(nums.cbegin(), nums.cend(), print);
    std::cout << '\n';
    std::cout << "sum: " << s.sum << '\n';
  }

  { //! Case: 
    //! "tut-functions.cxx"
    // std::function<int(int)> func2 = [&](int value) -> int { ... };
    using foo = void(int);  // function pointer <-- FIXME: can these be declreaed for any combiantos? <-- if yes, when=how to use these cosntructs?

    std::function<int(int)> func = _dummyFoo_int;
    auto bindFoo = std::bind(foo_threeArgs, std::placeholders::_1, 1,2); //! where "1, 2" is now defauylt partmers (eg, (x, y) when updating r, g, b varialbes serpately
    // when call bindFoo, we only need one param left
    bindFoo(10);
    std::cout << "called bindFoo(..)" << std::endl;
  }




void printReverse(auto cont) {
    for (auto it = rbegin(cont); it != rend(cont); ++it)
        std::cout << std::distance(rbegin(cont), it) << ": " << *it << '\n';
}

int main() {
    std::vector vec { 1, 2, 3, 4, 5};
    printReverse(vec);

    std::set<std::string> names { "one", "two", "three", "four" };
    printReverse(names);
}

int main() {
    std::vector vec { 1, 2, 3, 4, 5};
    for (int i = 0; const auto& elem : vec)
        std::cout << i++ << ": " << elem << '\n';
}

template<typename T>
class reverse {
private:
  T& iterable_;
public:
  explicit reverse(T& iterable) : iterable_{iterable} {}
  auto begin() const { return std::rbegin(iterable_); }
  auto end() const { return std::rend(iterable_); }
};

int main() {
    std::vector vec { 1, 2, 3, 4, 5};
    for (int i = 0; const auto& elem : reverse(vec))
        std::cout << i++ << ": " << elem << '\n';
}

/*
//! Repo: https://github.com/PeterSommerlad/ReverseAdapter
using ::adapter::reversed;
for(auto const &i : reversed({0,1,2,3,4,5})) {
    std::cout << i << '\n';
*/

#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector vec { 1, 2, 3, 4, 5};
    for (int i = 0; const auto& elem : vec | std::views::reverse)
        std::cout << i++ << ": " << elem << '\n';
}

for (int i = 0; const auto& elem : std::ranges::reverse_view(vec))
    std::cout << i++ << ": " << elem << '\n';

template <typename T>
void printReverse(const T& cont) {
    std::ranges::copy(cont | std::views::reverse, 
        std::ostream_iterator<typename T::value_type>( std::cout,"\n" ) );
}

/*
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <ranges>
#include <numeric>

void printReverse(auto cont) {
    std::ranges::for_each(
        std::views::zip(std::ranges::iota_view{0, ssize(cont)}, cont) | std::views::reverse, 
        [](const auto&elem) {
        std::cout << std::get<0>(elem) << ' '
                  << std::get<1>(elem) << '\n';
        }
    );
}

int main() {
    std::vector vec { 1, 2, 3, 4, 5};
    printReverse(vec);

    std::set<std::string> names { "one", "two", "three", "four" };
    printReverse(names);
}

void printReverse(auto cont) {
    std::ranges::for_each(cont | std::views::reverse, 
        [i=0](const auto& elem) mutable {
            std::cout << i++ << ' ' << elem << '\n';
        }
    );
}

*/

// --------------------------
//

// --------------------------
// 
//! Src: [https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170]
#include <algorithm>
#include <cmath>

void abssort(float* x, unsigned n) {
  std::sort(x, x + n,
	    // Lambda expression begins
	    [](float a, float b) { // FIXME: what does the "[]" mean? an indication that 'here starts a lambda-expresion'?  <-- "An empty capture clause, [ ], indicates that the body of the lambda expression accesses no variables in the enclosing scope."  [https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170] <-- FIXME: how to use=utlize this aritfact=obserivont=proeprty?
	      return (std::abs(a) < std::abs(b));
	      } // end of lambda expression
	    );  
}

void fillVector(vector<int>& v)
{
    // A local static variable.
    static int nextValue = 1;

    // The lambda expression that appears in the following call to
    // the generate function modifies and uses the local static
    // variable nextValue.
    generate(v.begin(), v.end(), [] { return nextValue++; });
    //WARNING: this isn't thread-safe and is shown for illustration only
}

int main()
{
    // The number of elements in the vector.
    const int elementCount = 9;

    // Create a vector object with each element set to 1.
    vector<int> v(elementCount, 1);

    // These variables hold the previous two elements of the vector.
    int x = 1;
    int y = 1;

    // Sets each element in the vector to the sum of the
    // previous two elements.
    generate_n(v.begin() + 2,
        elementCount - 2,
        [=]() mutable throw() -> int { // lambda is the 3rd parameter <-- FIXME: why is a "throw()" funcion used inide a ldmbda-funciton?
        // Generate current value.
        int n = x + y;
        // Update previous two values.
        x = y;
        y = n;
        return n;
    });
    print("vector v after call to generate_n() with lambda: ", v);

    // Print the local variables x and y.
    // The values of x and y hold their initial values because
    // they are captured by value.
    cout << "x: " << x << " y: " << y << endl;

    // Fill the vector with a sequence of numbers
    fillVector(v);
    print("vector v after 1st call to fillVector(): ", v);
    // Fill the vector with the next sequence of numbers
    fillVector(v);
    print("vector v after 2nd call to fillVector(): ", v);
}

// If a lambda is implicitly or explicitly constexpr, conversion to a function pointer produces a constexpr function: 
auto Increment = [](int n)
{
  return n + 1;
};

constexpr int(*inc)(int) = Increment; // FIXME: explroe this construct <-- where to use this?

// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/lambda-expression-syntax?view=msvc-170
assert(false); // FIXME: mold below into mthe above ...
//

void tut_forEach_lambda() {
  // This example passes a lambda to the for_each function. The lambda prints a result that states whether each element in a vector object is even or odd.
   // Create a vector object that contains 9 elements.
   vector<int> v;
   for (int i = 1; i < 10; ++i) {
      v.push_back(i);
   }

   // Count the number of even numbers in the vector by
   // using the for_each function and a lambda.
   int evenCount = 0;
   for_each(v.begin(), v.end(), [&evenCount] (int n) { // FIXME: write etnvie code ecploring for_each lamdbda eprmtautions ... 
      cout << n;
      if (n % 2 == 0) {
         cout << " is even " << endl;
         ++evenCount;
      } else {
         cout << " is odd " << endl;
      }
   });

   // Print the count of even numbers to the console.
   cout << "There are " << evenCount
        << " even numbers in the vector." << endl;
}

// even_functor.cpp
// compile with: /EHsc
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class FunctorClass
{
public:
    // The required constructor for this example.
    explicit FunctorClass(int& evenCount)
        : m_evenCount(evenCount) { }

    // The function-call operator prints whether the number is
    // even or odd. If the number is even, this method updates
    // the counter.
    void operator()(int n) const {
        cout << n;

        if (n % 2 == 0) {
            cout << " is even " << endl;
            ++m_evenCount;
        } else {
            cout << " is odd " << endl;
        }
    }

private:
    // Default assignment operator to silence warning C4512.
  FunctorClass& operator=(const FunctorClass&); // FIXME: in the "for_each(..)" loop, how is this "=" operator used?

    int& m_evenCount; // the number of even variables in the vector.
};

void tut_forEach_lambda_useFunctionClass() {
{
    // Create a vector object that contains 9 elements.
    vector<int> v;
    for (int i = 1; i < 10; ++i) {
        v.push_back(i);
    }

    // Count the number of even numbers in the vector by
    // using the for_each function and a function object.
    int evenCount = 0;
    for_each(v.begin(), v.end(), FunctorClass(evenCount));

    // Print the count of even numbers to the console.
    cout << "There are " << evenCount
        << " even numbers in the vector." << endl;
 }

// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/type-conversions-and-type-safety-modern-cpp?source=recommendations&view=msvc-170
 void tut_catinging() {
   // FIXME: make use of the below casting-examples in our project ... eg, when converting from "const  uchar* => " uchar*"? ...
   const char* str = "hello";
   int i = static_cast<int>(str);//error C2440: 'static_cast' : cannot
   // convert from 'const char *' to 'int'
   int j = (int)str; // C-style cast. Did the programmer really intend
   // to do this?
   int k = reinterpret_cast<int>(str);// Programming intent is clear. // FIXME: what does a "reinterpret_cast" do?
                                   // However, it is not 64-bit safe.


   Base* b = new Base();

// Run-time check to determine whether b is actually a Derived*
Derived* d3 = dynamic_cast<Derived*>(b);

 void Func(double& d) { ... }
void ConstCast()
{
   const double pi = 3.14;
   Func(const_cast<double&>(pi)); //No error.
}
 }
// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/enumerations-cpp?source=recommendations&view=msvc-170
namespace ScopedEnumConversions
{
    enum class Suit { Diamonds, Hearts, Clubs, Spades };

    void AttemptConversions()
    {
        Suit hand;
        hand = Clubs; // error C2065: 'Clubs' : undeclared identifier
        hand = Suit::Clubs; //Correct.
        int account_num = 135692;
        hand = account_num; // error C2440: '=' : cannot convert from 'int' to 'Suit'
        hand = static_cast<Suit>(account_num); // OK, but probably a bug!!!

        account_num = Suit::Hearts; // error C2440: '=' : cannot convert from 'Suit' to 'int'
       account_num = static_cast<int>(Suit::Hearts); // OK <-- FIXME: makse use of this enum=>int casting!
    }
}

int main()
{
    using namespace std;

    // Create a list of integers with a few initial elements.
    list<int> numbers;
    numbers.push_back(13);
    numbers.push_back(17);
    numbers.push_back(42);
    numbers.push_back(46);
    numbers.push_back(99);

    // FIXME: how can we use the below iteators? .... use it to search for values? ... if yesm, hwt valeus are meanigful to searhc for?
    
    // Use the find_if function and a lambda expression to find the
    // first even number in the list.
    const list<int>::const_iterator result =
        find_if(numbers.begin(), numbers.end(),[](int n) { return (n % 2) == 0; });

    // Print the result.
    if (result != numbers.end()) {
        cout << "The first even number in the list is " << *result << "." << endl;
    } else {
        cout << "The list contains no even numbers." << endl;
    }
}



//! Src: https://www.geeksforgeeks.org/friend-class-function-cpp/
#include<iostream>
using namespace std;
 


// --------------------------
// 
//! SrC: https://stackoverflow.com/questions/8824587/what-is-the-purpose-of-the-final-keyword-in-c11-for-functions

// FIXME: tget this to compile

struct A {
    virtual int foo(); // #1 <-- note: if we changes "virtual" => "final" then a comiaon-error is raised at "struct B : A"
};
struct B : A {
    int foo();
};


/*    if you make a virtual method in base class as final, it cannot be overridden in the derived class. It will show a compilation error: */


/*    If we make a class as final, it cannot be inherited by its child classes: */


// --------------------------
// 
//! Src: https://www.geeksforgeeks.org/virtual-function-cpp/
/**
A virtual function is a member function which is declared within a base class and is re-defined (overridden) by a derived class. When you refer to a derived class object using a pointer or a reference to the base class, you can call a virtual function for that object and execute the derived class’s version of the function. 
**/

// CPP program to illustrate
// concept of Virtual Functions
  

// --------------------------
// 
static void call()
{
  // FIXME: write a new tut outlining the below
  std::array<int, sizeof...(N)> v { N... };
  // FIXME: hwo does the below work?
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, "\n"));
}

// --------------------------
// 
//! Src: https://www.geeksforgeeks.org/variadic-function-templates-c/?ref=rp
// C++ program to demonstrate working of
// Variadic function Template
#include <iostream>
using namespace std;
 
// To handle base case of below recursive
// Variadic function Template
void print()
{
    cout << "I am empty function and "
            "I am called at last.\n";
}
 
// Variadic function Template that takes
// variable number of arguments and prints
// all of them.
template <typename T, typename... Types>
void print(T var1, Types... var2)
{
    cout << var1 << endl;
 
    print(var2...);
}
 
// Driver code
int main()
{
    print(1, 2, 3.14,
          "Pass me any "
          "number of arguments",
          "I will print\n");
 
    return 0;
}


// --------------------------
// 


// --------------------------
// 


// --------------------------
// 

