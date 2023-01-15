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

struct S { void f(int i); };
void S::f(int i) {
    [&, i]{};      // OK <-- FIXME: what does the "&" operator imply? <-- 'capture value by erence? <-- FIXME: can there be more than one vialbe?
    [&, &i]{};     // ERROR: i preceded by & when & is the default
    [=, this]{};   // ERROR: this when = is the default
    [=, *this]{ }; // OK: captures this by value. See below.
    [i, i]{};      // ERROR: i repeated
}

template<class... Args> // FIXME: what cocnrte applicaiton to use this 'variadic tempalte' case?
void f(Args... args) {
    auto x = [args...] { return g(args...); };
    x();
}

pNums = make_unique<vector<int>>(nums);
//...
auto a = [ptr = move(pNums)]() // FIXME: what is the effect of the "move(<ptr>)" command?
{
  // use ptr
};

//auto y = [] (int first, int second)
auto y = [] (auto first, auto second) //! which exmeplfies 'auto' + return-value
{
    return first + second;
};

//! Src:
//! Src:
//! Src:

// throw_lambda_expression.cpp
// compile with: /W4 /EHsc
int main() // C4297 expected
{
  []() noexcept { throw 5; }(); // FIXME: what is the effect of this "noexcept" call?
}


// captures_lambda_expression.cpp
// compile with: /W4 /EHsc
#include <iostream>
using namespace std;

int main()
{
   int m = 0;
   int n = 0;
   // FIXME: explroe the below! <-- does "[&, n]" always aimpleis that "n is captured by value?" <-- if yes, use "&&"! to cpature 'by refrence'?
   [&, n] (int a) mutable { m = ++n + a; }(4); // FIXME: what is the effect=purpose of keyword="mutable"? <--- " The mutable keyword is used so that the body of the lambda expression can modify its copies of the external variables ..., which the lambda expression captures by value."
   cout << m << endl << n << endl;
}

//

assert(false); // FIXME: merge the blewo with the above ... get to work!


// compile with: /W4 /EHsc
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename C> void print(const string& s, const C& c) {
    cout << s;
    for (const auto& e : c) {
        cout << e << " ";
    }
    cout << endl;
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


assert(false); // FIXME: mold below into mthe above ...
int y = 32;
auto answer = [y]() constexpr
{
  int x = 10;
  return y + x;
};

constexpr int Increment(int n)
{
  return [n] { return n + 1; }();
}

// A lambda is implicitly constexpr if its result satisfies the requirements of a constexpr function:
auto answer = [](int n)
{
  return 32 + n;
};

constexpr int response = answer(10);

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

enum class byte : unsigned char { };

enum class E : int { };
E e1{ 0 };
E e2 = E{ 0 };

struct X
{
    E e{ 0 };
    X() : e{ 0 } { }
};

E* p = new E{ 0 };

void f(E e) {};

int main()
{
  // FIXME: how can we use the bleow in our image-vasting-straegy?
    f(E{ 0 });
    byte i{ 42 };
    byte j = byte{ 42 };

    // unsigned char c = j; // C2440: 'initializing': cannot convert from 'byte' to 'unsigned char'
    return 0;
}

 
 // --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/examples-of-lambda-expressions?view=msvc-170
// declaring_lambda_expressions1.cpp
// compile with: /EHsc /W4
#include <functional>
#include <iostream>
int main()
{
  // FIXME: in the bleow .... try using the blewo for implity point-conveiosn ... eg, wrt. RGB-converiosn ... to islateo the scope?  
    using namespace std;
    {
      
      // Assign the lambda expression that adds two numbers to an auto variable.
      auto f1 = [](int x, int y) { return x + y; };
      
      cout << f1(2, 3) << endl;
      
      // Assign the same lambda expression to a function object.
      function<int(int, int)> f2 = [](int x, int y) { return x + y; };

      cout << f2(3, 4) << endl;
    }
    {

      int i = 3;
      int j = 5;
      
      // The following lambda expression captures i by value and
      // j by reference.
      function<int (void)> f = [i, &j] { return i + j; };      // FIXME: run this .... correct to assume that "i=3, j=44" (as "j" is taken by refrence, ie, ?? by the callers context?)? <-- yes!!!!
      
      // Change the values of i and j.
      i = 22;
      j = 44;
      
      // Call f and print its result.
      cout << f() << endl;
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

 
 // --------------------------------------------
// --------------------------------------------
//! Src:

 // --------------------------------------------
// --------------------------------------------
//! Src: 
