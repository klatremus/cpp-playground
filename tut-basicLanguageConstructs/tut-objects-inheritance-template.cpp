// FIXME: incldue from "tut-pointers.cxx"
// FIXME: incldue from "tut-containers.cxx"
// FIXME: incldue from ""
// FIXME: incldue from ""
// FIXME: incldue from ""

//! ""
//! ""
//! ""

//! "tut-containers.cxx"
    for (auto itm : mVec) {
      std::cout << itm << " ";
    }
  MyNumber m = { 1, 2, 3, 4 };
  m.print();  // 1 2 3 4
  
  std::array<int, 5> i_array1{ {3, 4, 5, 1, 2} };  // double-braces required
  std::array<std::string, 2> string_array = { {std::string("a"), "b"} };
  std::sort(i_array1.begin(), i_array1.end());
  std::reverse_copy(i_array2.begin(), i_array2.end(),
		    std::ostream_iterator<int>(std::cout, " "));  

  for_each(vec.begin(), vec.end(), print); // FIXME: relate=combine this wih lambda-funciotns!


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
  // Initializer_list
  C c{ 3, 7 };
{
  std::vector<int> a, b;
  std::vector<int> v{ 1, 2, 3, 4, 5 };
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) // FIXME: why is "it" a reference? <-- har to oterhsie iterate?
    a.push_back(*it);
  for (auto it = v.begin(); it != v.end(); ++it)
    b.push_back(*it);
}
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


// requires /std:c++20 or later
#include <ranges>
#include <iostream>
#include <vector>
void print(auto v)
{
    for (auto& x : v)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
{
//! Src: https://learn.microsoft.com/en-us/cpp/standard-library/filter-view-class?view=msvc-170

    std::vector<int> v{0, 1, -2, 3, -4, -5, 6};
    auto myView = std::views::filter(v, [](int i) {return i > 0; }); // FIXME: how can "std::filter" be used=applied in our system? <-- note: problem is that only "c++20 + " support shtis
    print(myView); // outputs 1 3 6

    auto myView2 = v | std::views::filter([](int i) {return i < 3; });
    print(myView2); // outputs 0 1 -2 -4 -5
}

{ //! Ranges: a correpsonnce to the Pyhton "range(..)" syntax:
//! Src: https://learn.microsoft.com/en-us/cpp/standard-library/drop-view-class?view=msvc-170
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    auto newView = std::views::drop(v, 3);
    for (auto e : newView) // outputs 4 5
    {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    auto numbers = std::views::iota(0) | std::views::take(10); // generate a view of 10 integers
    for (auto i : numbers | std::views::drop(5)) // use the '|' syntax to create a drop_view
    {
        std::cout << i << ' '; // outputs 5 6 7 8 9
    }
}


// C++ code to demonstrate the working
// of for_each with Exception
 
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 
// Helper function 1
void printx2(int a)
{
    cout << a * 2 << " ";
    if ( a % 2 == 0)
    {
        throw a;
    }
     
}
 
// Helper function 2
// object type function
struct Class2
{
    void operator() (int a)
    {
        cout << a * 3 << " ";
        if ( a % 2 == 0)
        {
            throw a;
             
        }
    }
} ob1;
 
 
int main()
{
     
    // Initializing array
    int arr[5] = { 1, 5, 2, 4, 3 };
     
    cout << "Using Array" << endl;
     
    // Printing Exception using for_each
    // using function
    try
    {
        for_each(arr, arr + 5, printx2);
    }
    catch(int i)
    {
        cout << "\nThe Exception element is : " << i ;
    }
    cout << endl;
     
    // Printing Exception using for_each
    // using object function
    try
    {
        for_each(arr, arr + 5, ob1);
    }
    catch(int i)
    {
        cout << "\nThe Exception element is : " << i ;
    }
     
    // Initializing vector
    vector<int> arr1 = { 1, 3, 6, 5, 1 };
     
    cout << "\nUsing Vector" << endl;
     
    // Printing Exception using for_each
    // using function
    try
    {
        for_each(arr1.begin(), arr1.end(), printx2);
    }
    catch(int i)
    {
        cout << "\nThe Exception element is : " << i ;
    }
    cout << endl;
     
    // printing Exception using for_each
    // using object function
    try
    {
        for_each(arr1.begin(), arr1.end(), ob1);
    }
    catch(int i)
    {
        cout << "\nThe Exception element is : " << i ;
    }
}

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
 
int main()
{
 
    vector<int> vec{ 1, 2, 3, 4, 5 };
 
    // this increases all the values in the vector by 1;
    for_each(vec.begin(), vec.end(), [](int& a) { a++; });
 
    // this prints all the values in the vector;
    for_each(vec.begin(), vec.end(),
             [](int a) { cout << a << " " << endl; });
 
    return 0;
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


template<typename T, typename U>
struct S{
    T t;
    U u;
};
// deduction guide was needed in C++17
// template<typename T, typename U>
// S(T, U) -> S<T,U>;

S s{1, 2.0};    // S<int, double>
