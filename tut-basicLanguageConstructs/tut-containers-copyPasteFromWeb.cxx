//!
//! Src: https://www.bogotobogo.com/cplusplus/C11/C11_initializer_list.php and https://www.bogotobogo.com/cplusplus/C11/C11_std_array_container_class.php and https://www.bogotobogo.com/cplusplus/C11/C11_override_final.php and https://www.bogotobogo.com/cplusplus/C11/C11_lambda_functions_expressions.php and https://www.bogotobogo.com/cplusplus/C11/C11_Uniform_initialization.php and https://www.bogotobogo.com/cplusplus/C11/C11_static_assertion_constructor_delegation.php https://www.bogotobogo.com/cplusplus/C11/C11_constexpr_string_literals.php
#include <iostream>
#include <vector>

class MyNumber
{
public:
  MyNumber(const std::initializer_list<int> &v;) {
    for (auto itm : v) {
      mVec.push_back(itm);
    }
  }

  void print() {
    for (auto itm : mVec) {
      std::cout << itm << " ";
    }
  }
private:
  std::vector<int> mVec;
};



/* arr1.cpp */
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

int main()
{
  {
    MyNumber m = { 1, 2, 3, 4 };
    m.print();  // 1 2 3 4
  }    
  // construction uses aggregate initialization
  std::array<int, 5> i_array1{ {3, 4, 5, 1, 2} };  // double-braces required
  std::array<int, 5> i_array2 = {1, 2, 3, 4, 5};   // except after =
  std::array<std::string, 2> string_array = { {std::string("a"), "b"} };

  std::cout << "Initial i_array1 : ";
  for(auto i: i_array1)
    std::cout << i << ' ';
  // container operations are supported
  std::sort(i_array1.begin(), i_array1.end());

  std::cout << "\nsored i_array1 : ";
  for(auto i: i_array1)
    std::cout << i << ' ';

  std::cout << "\nInitial i_array2 : ";
  for(auto i: i_array2)
    std::cout << i << ' ';

  std::cout << "\nreversed i_array2 : ";
  std::reverse_copy(i_array2.begin(), i_array2.end(),
		    std::ostream_iterator<int>(std::cout, " "));

  // ranged for loop is supported
  std::cout << "\nstring_array : ";
  for(auto& s: string_array)
    std::cout << s << ' ';

  return 0;
}

/* arr2.cpp */
#include <iostream>
using namespace std;

template <typename T, int n>
class myArray
{
public:
  myArray() {a = new T[n];}
  ~myArray() {delete[] a;}
  T& operator[](int i) {return *(a+i);}

private:
  T* a;
};

int main()
{
  myArray<int, 5> arr;

  for(int i = 0; i < 5 ; i++)
    cout << arr[i] << ' ';

  return 0;
}


// C++11
class Base
{
  virtual void f(int);
};

class Derived : public Base
{
  virtual void f(float) override;  // Error
};

// no class can be derived from class A
class A final
{
  virtual void f(int);
};

class B
{
  // no class can override f()
  virtual void f() final; 
};


/* lambda.cpp */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// assign a value to each element of a vector
void assign(int& v)
{
  static int n = 1; v = n++;
}

// print out each element
void print(int v)
{
  cout << v << " ";
}

int main()
{
  vector<int> vec(10);
  // output initial value of each element
  for_each(vec.begin(), vec.end(), print);
  cout << endl;

  // assign a value to each element of a vector
  for_each(vec.begin(), vec.end(), assign);

  // output updated value of each element
  for_each(vec.begin(), vec.end(), print);
  return 0;
}


/* lambda2.cpp */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
  vector<int> vec(10);
  // output initial value of each element
  // for_each(vec.begin(), vec.end(), print); ==>
  for_each(vec.begin(), vec.end(), [](int v) {cout << v << " ";});
  cout << endl;

  // assign a value to each element of a vector
  // for_each(vec.begin(), vec.end(), assign); ==>
  for_each(vec.begin(), vec.end(), [](int& v) {static int n = 1; v = n++;});

  // output updated value of each element
  // for_each(vec.begin(), vec.end(), print); ==>
  for_each(vec.begin(), vec.end(), [](int v) {cout << v << " ";});
  return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

void foo() { std::cout << "foo()\n"; }
void bar() { std::cout << "bar()\n"; }

int main ()
{
  // 1st lambda function
  auto f  = []() {
	      foo();
	      bar();
	    };
  // the lambda function does something here
  f();

  // 2nd lambda function
  std::vector<int> v(5, 99);
  std::for_each(v.begin(), v.end(), [](int i){std::cout << i << "\n";});

  return 0;
}


int main()
{
  // (1)
  std::cout << [](int a, int b){return a*b; }(4, 5) << std::endl; // 20

  // (2)
  auto f = [](int a, int b) { return a*b; };
  std::cout << f(4, 5) << std::endl;  // 20
}


/* lam.cpp */
#include <iostream>
using namespace std;

int main()
{
  /* case #1 - compiler deduces return type */
  cout << [](int n) {return n*n;} (5);
  cout << endl;
  /* case #2 - explicit return type */
  cout << [](int n)->int {return n*n;} (5);

  return 0;
}


#include <iostream>
#include <vector>

class A
{
public:
  int mx;
  double my;
};

class B
{
public:
  B(int x, double y) : mx{ x }, my{ y } {}

  int mx;
  double my;
};

class C
{
public:
  C(int x, double y) : mx{ x }, my{ y } {}
  C(const std::initializer_list<int>& v) {
    mx = *(v.begin());
    my = *(v.begin() + 1);
  }

  int mx;
  double my;
};

int main()
{
  // Aggregate initialization
  A a{ 1, 3.7 };

  // Regular constructor
  B b{ 2, 9.8 };

  // Initializer_list
  C c{ 3, 7 };

  std::cout << a.mx << " " << a.my << std::endl;
  std::cout << b.mx << " " << b.my << std::endl;
  std::cout << c.mx << " " << c.my << std::endl;

  return 0;
}

// C++11
class A
{
  void doSomethingElse() { std::cout << "doSomethingElse()\n"; }
public:
  A() { ... } // FIXME: is this contrust leagal?
  A(int a) : A() { doSomethingElse(); }
};

#include <vector>

int main()
{
  std::vector<int> a, b;
  std::vector<int> v{ 1, 2, 3, 4, 5 };
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    a.push_back(*it);
  for (auto it = v.begin(); it != v.end(); ++it)
    b.push_back(*it);
}


#include <vector>
int main() 
{
  const std::vector<int> v(1);
  auto a = v[0];        // a has type int
  decltype(v[1]) b = 1; // b has type const int&, the return type of
  //   std::vector<int>::operator[](size_type) const
  auto c = 0;           // c has type int
  auto d = c;           // d has type int
  decltype(c) e;        // e has type int, the type of the entity named by c
  decltype((c)) f = c;  // f has type int&, because (c) is an lvalue
  decltype(0) g;        // g has type int, because 0 is an rvalue
}


#include <iostream>
#include <vector>

int main()
{
  std::vector<int> a, b;
  std::vector<int> v{ 1, 2, 3, 4, 5 };

  // C++03
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    a.push_back(*it);

  // C++11
  for (auto it = v.begin(); it != v.end(); ++it)
    b.push_back(*it);

  for (int item : a)
    std::cout << item << " ";  // read only access

  std::cout << std::endl;

  for (auto &item; : b) { // FIXME: is this a vlalid itation?
    item *= 10;
    std::cout << item << " ";  // read only access
  }
}


#include <ranges>
#include <iostream>
 
int main()
{
  //! Src: https://stackoverflow.com/questions/67557877/what-is-the-point-of-c20-ranges
  auto const ints = {0,1,2,3,4,5};
  auto even = [](int i) { return 0 == i % 2; };
  auto square = [](int i) { return i * i; };
 
  // "pipe" syntax of composing the views:
  for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
    std::cout << i << ' ';
  }
 
  std::cout << '\n';
 
  // a traditional "functional" composing syntax:
  for (int i : std::views::transform(std::views::filter(ints, even), square)) {
    std::cout << i << ' ';
  }
}

#include <algorithm>
#include <iostream>
#include <ranges>

int main()
{
  //! Src: https://learn.microsoft.com/en-us/cpp/standard-library/range-adaptors?view=msvc-170
  int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto even = [](const int n) { return n % 2 == 0; };
  auto x = input | std::views::filter(even); // create a view of the even elements from input

  for (int &i : x)
    {
      std::cout << i << ' '; // 0 2 4 6 8 10
    }
  std::cout << '\n'; 

  std::ranges::fill(x, 42); // changes the evens from input[] to 42
  for (int &i : input) // demonstrates that the even elements in the range are modified
    {
      std::cout << i << ' '; // // 42 1 42 3 42 5 42 7 42 9 42
    }
}

template<typename K, typename V> using MapIterator = typename std::map<K,V>::const_iterator; // FIXME: why is this init requreid? ... what does the "using" keyword mean=imply? ... why do we need to define this at compile-time?
template<typename K, typename V> void printMap(const std::map<K,V>& m) {
  //! Src: https://stackoverflow.com/questions/23043936/using-template-iterator-in-c-stdmap
  for (MapIterator<K, V> iter = m.begin(); iter != m.end(); iter++) {
    std::cout << "Key: " << iter->first << " "          << "Values: " << iter->second << std::endl;
  }
}

template <typename Key, typename Value, typename F> void update(std::map<Key, Value>& m, F foo) {
  // FIXME: how to use arg="foo"?
  printMap(m); // FIXME: why is no tempalte-apramters needd to be givne ecllty (to this call)?
  auto input  = "a test";
  auto val = foo(input);
  // MapIterator<Key, Value> iterator = m.find(foo);
  MapIterator<Key, Value> iterator = m.find("c");
  /*
    std::map<Key, Value>::iterator it = m.find('c'); 
    if (it != m.end())
    it->second = 42;
  */
}

// *****************************************************************************
//! Src: https://www.geeksforgeeks.org/lambda-expression-in-c/
// C++ program to demonstrate lambda expression in C++
#include <bits/stdc++.h>
using namespace std;

// Function to print vector
void printVector(vector<int> v)
{
  // lambda expression to print vector
  for_each(v.begin(), v.end(), [](int i)
			       {
				 std::cout << i << " ";
			       });
  cout << endl;
}

int main()
{
  vector<int> v {4, 1, 3, 5, 2, 3, 1, 7};

  printVector(v);

  // below snippet find first number greater than 4
  // find_if searches for an element for which
  // function(third argument) returns true
  vector<int>:: iterator p = find_if(v.begin(), v.end(), [](int i)
							 {
							   return i > 4;
							 });
  cout << "First number greater than 4 is : " << *p << endl;


  // function to sort vector, lambda expression is for sorting in
  // non-increasing order Compiler can make out return type as
  // bool, but shown here just for explanation
  sort(v.begin(), v.end(), [](const int& a, const int& b) -> bool
			   {
			     return a > b;
			   });

  printVector(v);

  // function to count numbers greater than or equal to 5
  int count_5 = count_if(v.begin(), v.end(), [](int a)
					     {
					       return (a >= 5);
					     });
  cout << "The number of elements greater than or equal to 5 is : "
       << count_5 << endl;

  // function for removing duplicate element (after sorting all
  // duplicate comes together)
  p = unique(v.begin(), v.end(), [](int a, int b)
				 {
				   return a == b;
				 });

  // resizing vector to make size equal to total different number
  v.resize(distance(v.begin(), p));
  printVector(v);

  // accumulate function accumulate the container on the basis of
  // function provided as third argument
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int f = accumulate(arr, arr + 10, 1, [](int i, int j)
				       {
					 return i * j;
				       });

  cout << "Factorial of 10 is : " << f << endl;

  //     We can also access function by storing this into variable
  auto square = [](int i)
		{
		  return i * i;
		};

  cout << "Square of 5 is : " << square(5) << endl;
}

// C++ program to demonstrate lambda expression in C++
#include <bits/stdc++.h>
using namespace std;

int main()
{
  vector<int> v1 = {3, 1, 7, 9};
  vector<int> v2 = {10, 2, 7, 16, 9};

  //  access v1 and v2 by reference
  auto pushinto = [&] (int m)
		  {
		    v1.push_back(m);
		    v2.push_back(m);
		  };

  // it pushes 20 in both v1 and v2
  pushinto(20);

  // access v1 by copy
  [v1]()
  {
    for (auto p = v1.begin(); p != v1.end(); p++)
      {
	cout << *p << " ";
      }
  };

  int N = 5;

  // below snippet find first number greater than N
  // [N]  denotes,   can access only N by value
  vector<int>:: iterator p = find_if(v1.begin(), v1.end(), [N](int i)
							   {
							     return i > N;
							   });

  cout << "First number greater than 5 is : " << *p << endl;

  // function to count numbers greater than or equal to N
  // [=] denotes,   can access all variable
  int count_N = count_if(v1.begin(), v1.end(), [=](int a)
					       {
						 return (a >= N);
					       });

  cout << "The number of elements greater than or equal to 5 is : "
       << count_N << endl;

  //
}

// ----------------------------------------
template <typename T> using PointerType = std::conditional_t<std::is_same<T, int>::value, int, double>; //! [https://stackoverflow.com/questions/70570931/initialize-and-deduce-type-of-shared-ptr-returned-by-lambda-in-template-class-c]
template <typename T> auto pointer_cast(T ptr) { //! [https://stackoverflow.com/questions/70570931/initialize-and-deduce-type-of-shared-ptr-returned-by-lambda-in-template-class-c]
    return std::dynamic_pointer_cast<PointerType<T>>(ptr);
}
void tut() {
  /**
     @brief
   **/
  class EventBase {
    int v;
  };
  class EventA : EventBase {
    float m;
  };
  class EventB : EventBase {
    float m;
  };
  
  auto event = new EventA();
  
  auto event_A_B = [&]() -> std::shared_ptr<EventBase> { 
							//! [https://stackoverflow.com/questions/70570931/initialize-and-deduce-type-of-shared-ptr-returned-by-lambda-in-template-class-c]
							if (std::is_same<T, A>::value) {
											return std::dynamic_pointer_cast<EventA>(event);
							}
							else if (std::is_same<T, B>::value) {
											     return std::dynamic_pointer_cast<EventB>(event);
							}
  };
  // auto event_A_B_constExpr = [&] {
  // 			       //! [https://stackoverflow.com/questions/70570931/initialize-and-deduce-type-of-shared-ptr-returned-by-lambda-in-template-class-c]
  // 			       if constexpr (std::is_same_v<T, A>::value) {
  // 				   return std::dynamic_pointer_cast<EventA>(event);
  // 				 }
  // 			       else if constexpr (std::is_same<T, B>::value) {
  // 				   return std::dynamic_pointer_cast<EventB>(event);
  // 				 }
  // 			     };  
  //!
  //!
  //auto obj2_a = event_A_B();
  //auto obj2_b = event_A_B_constExpr();  
}
