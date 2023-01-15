#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

#include <iostream>
#include <map>
#include <string>
using namespace std;


void typeEval_bits() {
  enum Byte : unsigned char {};
  Byte byte{0};
  Byte byte2{255};
  cout << "int(byte)=" << to_integer<int>(byte) << endl;
  Byte byte3{0b1001};
  cout << "int(byte)=" << to_integer<int>(byte3) << endl;  
}

int main() {
  {
    typeEval_bits();
  }
  auto ptr = std::make_shared<int*>();
  std::cout << "ptr.type=" << typeid(ptr).name() << std::endl;
  std::cout << "pointer.use_count() = " << ptr.use_count() << std::endl;   // 2
  auto ptr2 = ptr;
  static_assert(std::is_same<decltype(ptr), decltype(ptr2)>::value, ".. not the same");
  std::cout << "pointer.use_count() = " << ptr.use_count() << std::endl;   // 2
  auto ptr3 = std::forward<decltype(ptr2)>(ptr2); //! Note: observe that thsi does NOT increse the "use_count()" value
  //auto ptr3 = std::forward<decltype(ptr2)>(ptr);  
  static_assert(std::is_same<decltype(ptr), decltype(ptr2)>::value, ".. not the same");  
  std::cout << "pointer.use_count() = " << ptr.use_count() << std::endl;   // 2

  {
    // FIXME: explain the elow ... inlcuding its usage
    std::vector<int> v(1); // int *v;
    auto a = v[0];        // a has type int
    int &var_1 = v[0];
    //int &var_1 = a; //! Eval: what happends if this line is icnldued (and "a = v[0]" (above) remvoed)?
    decltype(v[0]) b = var_1; // b has type const int&, the return type of <-- Eval: why is the "int&" proerpty? what erros would this give (ie, if not used with awareness)?
    std::cout << "b=" << std::to_string(b) << std::endl;
    var_1 = 3;
    // v[0] = 4;
    std::cout << "b=" << std::to_string(b) << std::endl;
    std::cout << "a=" << std::to_string(a) << std::endl;
    std::cout << "v[0]=" << std::to_string(v[0]) << std::endl;  // FIXME: why is "v[0]" not updated?
  
    //   std::vector<int>::operator[](size_type) const
    auto c = 0;           // c has type int
    auto d = c;           // d has type int
    decltype(c) e;        // e has type int, the type of the entity named by c
    decltype((c)) f = c;  // f has type int&, because (c) is an lvalue <-- Eval: 
    decltype(0) g;        // g has type int, because 0 is an rvalue
  }
  {
    int value = 2;
    //if constexpr(std::is_integral<decltype<_value>::value) {
    if constexpr(std::is_integral<decltype(value)>::value) {
	std::cout << "int is an integral type" << std::endl;
      }
  }

  return 0;  
}
