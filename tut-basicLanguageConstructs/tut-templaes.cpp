/**
   @remarks litterautre:
   * https://dev.to/pratikparvati/introduction-to-c-templates-3d2e
   **/

// FIXME: read the below ... adjsut it ... deirbe its usage


// FIXME: how ae func-tempatles sued?
// FIXME: how to itnrosect=investiate the instance of an titrubte? ... 
// FIXME: possible to set the tange of c++ clases which can be sued?
// FIXME: 




template <typename T> T myMax(T x, T y)
{
  return (x > y) ? x : y;
}

template <typename T> T max(T a, T b)
{
  return (a > b) ? a : b;
}

template <typename RT, typename T1, typename T2> RT max(T1 a, T2 b)
{
  return (a > b) ? a : b;
}

int main()
{
  double x;
  // note that return type cannot be deduced, so must always be specified
  x = max<double, double, int>(23.9, 45);  // double max<double, int>
  x = max<double>(15, 11.5);               // double max<int, double>
  x = max<double>(15.5, 11);               // double max<double, int>

  return EXIT_SUCCESS;
}

template <typename T>
T add(T num1, T num2) {
   return (num1 + num2);
}

int main() {

    int result1;
    double result2;
    // calling with int parameters
    result1 = add<int>(2, 3);
    cout << result1 << endl;

    // calling with double parameters
    result2 = add<double>(2.2, 3.3);
    cout << result2 << endl;

    return 0;
}


//! --------------------
//!
//! Aspect: abbreviated funciont-tempaltes
//! Src:
void f1(auto) { // same as template<class T> void f1(T)
  // FIXME: what to perofmr inside this? ... what is the variable-name?
}
void f2(C1 auto) { // same as template<C1 T> void f2(T), if C1 is a concept
  C1 += 2;
  // FIXME: correct?
}
void f3(C2 auto...) { // same as template<C2... Ts> void f3(Ts...), if C2 is a concep
  C2[0] += 1;
    // FIXME: what to perofmr inside this? ... what is the variable-name?
}
void f4(const C3 auto*, C4 auto&) { // same as template<C3 T, C4 U> void f4(const T*, U&);
  C3[C4.index] += 4;
    // FIXME: what to perofmr inside this? ... what is the variable-name?
}
 
template<class T, C U> void g(T x, U y, C auto z) { // same as template<class T, C U, C W> void g(T x, U y, W z);
  x.obj->value = y.value + z;
  // FIXME: correct?
}

// Abbreviated function templates can be specialized like all function templates.

template<> void f4<int>(const int*, const double&) { // specialization of f4<int, const double>
  // FIXME: wha are the vairlab-enames to call?
}

// ----------
char* p = 0;
 
template<class T> T g(T x = &p) { return x; } // FIXME: is it allwoable to have "&p" as a defautl arugment?
 
template int g<int>(int); // OK even though &p isn’t an int.  <-- FIXME: what is the varialbe-name (in the funciotn)?

/*
## Implicit instantiation

When code refers to a function in context that requires the function definition to exist, or if the existence of the definition affects the semantics of the program (since C++11), and this particular function has not been explicitly instantiated, implicit instantiation occurs. The list of template arguments does not have to be supplied if it can be deduced from context.
Run this code
*/
#include <iostream>
 
template<typename T> void f(T s)
{
    std::cout << s << '\n';
}
 
int main()
{
    f<double>(1); // instantiates and calls f<double>(double)
    f<>('a');     // instantiates and calls f<char>(char)
    f(7);         // instantiates and calls f<int>(int)
    void (*pf)(std::string) = f; // instantiates f<string>(string)
    pf("∇");                     // calls f<string>(string)
}


/**
The existence of a definition of function is considered to affect the semantics of the program if the function is needed for constant evaluation by an expression, even if constant evaluation of the expression is not required or if constant expression evaluation does not use the definition. 
 **/
template<typename T> constexpr int f() { return T::value; }

template<bool B, typename T> void g(decltype(B ? f<T>() : 0));
template<bool B, typename T> void g(...);
 
template<bool B, typename T>
void h(decltype(int{B ? f<T>() : 0}));
template<bool B, typename T>
void h(...);
 
void x()
{
    g<false, int>(0); // OK: B ? f<T>() : 0 is not potentially constant evaluated
    h<false, int>(0); // error: instantiates f<int> even though B evaluates to false
                      // and list-initialization of int from int cannot be narrowing
}

/** Template argument deduction

    In order to instantiate a function template, every template argument must be known, but not every template argument has to be specified. When possible, the compiler will deduce the missing template arguments from the function arguments. This occurs when a function call is attempted and when an address of a function template is taken.  **/

template<typename To, typename From> To convert(From f);
void g(double d) 
{
  //! Note: in the below the type=From is inferred from the argument, while the reutn-value is inferred from the "<>" argument?
    int i = convert<int>(d);    // calls convert<int,double>(double)
    char c = convert<char>(d);  // calls convert<char,double>(double)
    int(*ptr)(float) = convert; // instantiates convert<int, float>(float) <-- FIXME: is "ptr" the name of the new function?
}

// ------------

template<parameter_list> ret_type func_name(argument_list) //! ie, a funciotn-tempalte <-- FIXME: how to use this?
{
  // body of function
}

template <typename T>  
T add(T a, T b)          
{
  return a + b;
}

template <class T>
class MyClass
{
  T a, b;

public:
  MyClass(T first, T second)
  {
    a = first;
    b = second;
  }
  T getMaxval();
};

template <class T>
T MyClass<T>::getMaxval()
{
  return (a > b) ? a : b;
}

int main()
{
  MyClass<int> Obj1(50, 150);
  std::cout << "Maximum of 50 and 150 = " << Obj1.getMaxval() << std::endl;

  MyClass<char> Obj2('A', 'a');
  std::cout << "Maximum of 'A' and 'a' = " << Obj2.getMaxval() << std::endl;

  return 0;
}


template<typename T>
T compare(T l, T r)
{
  return (l > r) ? 1 : 0;
}

template<class T>
class Container
{
public:
  void put(T* p);
  T* get();
  // other members
};

//int size is a non-type parameter
template <class T, int size>
class MyType
{
  T a[size];

public:
  MyType()
  {
    for (int i = 0; i < size; i++)
      a[i] = i;
  }
  T &operator[](int i)
  {

    if (i < 0 || i > size - 1)
      {
	std::cout << "Index value of " << i << " is out-of-bounds.\n";
	exit(1);
      }
    return a[i];
  }
};


template<typename T, size_t n>
void printValues(T (&arr)[n])
{
  for(size_t i = 0; i < n; ++i)
    { 
      std::cout << arr[i] << ' ';
    } 
  std::cout << std::endl;
}

template <class T, size_t N = 10>
struct my_array
{
  T arr[N];
};

int main()
{
  /* Default parameter is ignored, N = 5 */
  my_array<int, 5> a;

  /* Print the length of a.arr: 5 */
  std::cout << sizeof(a.arr) / sizeof(int) << std::endl;

  /* Last parameter is omitted, N = 10 */
  my_array<int> b;

  /* Print the length of a.arr: 10 */
  std::cout << sizeof(b.arr) / sizeof(int) << std::endl;
}

// This template function doesn't give correct result for char *
template <typename T>
T* max(T* a, T* b)
{
  return (*a > *b) ? a : b;
}

// Explicit specialization of max function for const char *
template<>
const char* max(const char* a, const char* b)
{
  return strcmp(a, b) > 0 ? a : b;
}


/**
 * The below template class doesn't give correct result for below piece of code
 * FindMax<const char*> Max
 * const char* str1 = "Good"
 * const char* str2 -= "Bye"
 * const char * res = Max.getMax(str1, str2);
 */
template<typename T>
class FindMax
{
public:
  T getMax(T a, T b)
  {
    return (a > b)? a : b;
  }
};

// Hence, explicitly specialized class defined for const char *
template<>
class FindMax<const char*>
{
public:
  const char* getMax(const char* a, const char* b)
  {
    return (strcmp(a,b) > 0)? a : b;
  }
};

template <class T1, class T2>
class MyClass
{
public:
  MyClass()
  {
    std::cout << "MyClass<T1, T2>::MyClass() --> regular constructor\n";
  }
  T1 _a;
  T2 _b;
};

// Partial specialization class to int as second template parameter
template <class T>
class MyClass<T, int>
{
public:
  MyClass()
  {
    std::cout << "MyClass<T, int>::MyClass() --> partial specializations\n";
  }

  T _a;
  int _b;
};

int main()
{
  MyClass<double, double> a;
  MyClass<double, int> b; // partial specialization
  return 0;
}

/*OUTPUT
  MyClass<T1, T2>::MyClass() --> regular constructor
  MyClass<T, int>::MyClass() --> partial specializations
*/




int main() {
  //Foo f(6);

  max<int>(10, 20);
  max<double>(10.11, 20.22);


  //return f.x;
  return myMax<int>(3, 7);
}


// --------------
//
// FIXME: get the bleow to work
//! Src: https://codereview.stackexchange.com/questions/45549/c-template-range
template<int C, int P, int... N>
struct GetIncreasingRange:
  GetIncreasingRange<C-1, P+1, N..., P>
{};

template<int C, int P, int... N>
struct GetDecreasingRange:
  GetDecreasingRange<C+1, P-1, N..., P>
{};

template<int P, int... N>
struct GetIncreasingRange<0, P, N...>:
  Sizes<N...>
{};

template<int P, int... N>
struct GetDecreasingRange<0, P, N...>:
  Sizes<N...>
{};

template<int S, int E, bool Increasing=(S<E)>
struct Range;

template<int S, int E>
struct Range<S, E, true>:
  GetIncreasingRange<E-S, S>
{};

template<int S, int E>
struct Range<S, E, false>:
  GetDecreasingRange<E-S, S>
{};
static void call()
{
  // FIXME: write a new tut outlining the below
  std::array<int, sizeof...(N)> v { N... };
  // FIXME: hwo does the below work?
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, "\n"));
}


// --------------
//
// FIXME: get the bleow to work
//! Src: https://stackoverflow.com/questions/69081332/how-do-i-declare-a-template-parameter-of-type-range
template <std::ranges::range Range>
requires std::same_as<std::ranges::range_value_t<Range>, int>
auto TransformIt(Range r)
{
  return r | std::views::transform([](int n) { return n * n; });
}

template <class R, class Value>
concept range_over = std::ranges::range<R> && 
	 std::same_as<std::ranges::range_value_t<R>, Value>;

template <range_over<int> Range>
auto TransformIt(Range r)
{
  return r | std::views::transform([](int n) { return n * n; });
}


// --------------
//
// FIXME: get the bleow to work
//! Src:


// --------------
//
// FIXME: get the bleow to work
//! Src:
