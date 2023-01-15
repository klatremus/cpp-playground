//! Src: https://learn.microsoft.com/en-us/cpp/cpp/decltype-cpp?view=msvc-170
// decltype_1.cpp
// compile with: cl /EHsc decltype_1.cpp

#include <iostream>
#include <string>
#include <utility>  // FIXME: ???
#include <iomanip> // FIXME: ???

using namespace std;

template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) ->
//! Note: "Visual Studio 2017 and later: The compiler parses decltype arguments when the templates are declared rather than instantiated. So, if a non-dependent specialization is found in the decltype argument, it won't be deferred to instantiation-time; it's processed immediately and any resulting errors are diagnosed at that time." <-- FIXME: try it out ... ie, when are the bugs provked?
  decltype(forward<T1>(t1) + forward<T2>(t2)) // FIXME: what does 'forward' mean? .... what is the effect of this "decltype" operator?
{
   return forward<T1>(t1) + forward<T2>(t2);
}

class X {
  friend X operator+(const X& x1, const X& x2) // FIXME: what is a "friend" function? <-- same as 'static'?
  {
    return X(x1.m_data + x2.m_data); //! Note: this access is alloed due to the "friedn" attirubte: see "tut-friend.cpp"
  }
  
public:
  X(int data) : m_data(data) {}
  int Dump() const { return m_data;}
private:
  int m_data;
};

int main()
{
   // Integer
   int i = 4;
   cout <<
      "Plus(i, 9) = " <<
      Plus(i, 9) << endl;

   // Floating point
   float dx = 4.0;
   float dy = 9.5;
   cout <<
     setprecision(3) << // FIXME: where is 'setprecision" deifned? what does it do?
      "Plus(dx, dy) = " <<
      Plus(dx, dy) << endl;

   // String
   string hello = "Hello, ";
   string world = "world!";
   cout << Plus(hello, world) << endl;

   // Custom type
   X x1(20);
   X x2(22);
   X x3 = Plus(x1, x2);
   cout <<
      "x3.Dump() = " <<
      x3.Dump() << endl;
}
