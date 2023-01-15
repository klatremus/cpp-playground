// requires /std:c++20 or later
//#include <ranges>
#include <iostream>
#include <vector>
#include<iostream>
#include<vector>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;


// assert false .... add support for operators ... explore this ... 

class Entry_Aux {
public:
  friend string getFiendValue_entry2() { return string();}
};

class Entry_Base  {
  //virtual int getValue(int) = 0; //! FIXME: why does usign this result in ..odd.. compiler-bugs?
  virtual int getValue(int) final {return 1;} //! Eval: why is the varaible-paramter-name NOT specified?
  void dummy() {}
  static void staticTest() {;} //! Eval: in contrast to "getFiendValue()" this funcion can be redeifned (in the cflassses inerhtiign from this); why?
  friend string getFiendValue_entry() {return string("a test"); }
  // friend string getFiendValue() {return string("a test");} //! Eval: why does the compilation fail (if this is included)?
};

//template <typename T1, typename T2> auto addValues(T1 val1, T2 val2) -> decltype(T1 + T2) { //! Eval: why does this fail to compiel? <-- tip: ivnstiatte the reutrn-values
template <typename T1, typename T2> auto addValues(T1 val1, T2 val2) -> decltype(forward<T1>(val1) + forward<T2>(val2)) {
  //return val1 + val2;
  return forward<T1>(val1) + forward<T2>(val2); // FIXME: what is the point of using "forward"? <-- does the codee goes faster? a better straety?
}
auto addValues_case2(auto val1, auto val2) -> decltype(val1 + val2) {
  return val1 + val2;
}

// -----------------
//! Src: [https://www.codeproject.com/Articles/118921/C-Properties]

// FIXME: why does the belwo NOT wokr?
// #define PROPERTY(t,n)  __declspec( property 
// 	( put = property__set_##n, get = property__get_##n ) ) t n;\
// 	typedef t property__tmp_type_##n
// #define READONLY_PROPERTY(t,n) __declspec( property (get = property__get_##n) ) t n;\
// 	typedef t property__tmp_type_##n
// #define WRITEONLY_PROPERTY(t,n) __declspec( property (put = property__set_##n) ) t n;\
// 	typedef t property__tmp_type_##n
// #define GET(n) property__tmp_type_##n property__get_##n() 
// #define SET(n) void property__set_##n(const property__tmp_type_##n& value)   
// -------------

class EntryCompany final : Entry_Base {
// private: 
// 	int _x; 
// public:  
// 	__declspec(property(put = property__set_x, get = property__get_x)) int x;
// 	typedef int property__tmp_type_x;

// 	property__tmp_type_x property__get_x()
// 	{
// 		return _x;
// 	}

// 	void property__set_x(const property__tmp_type_x& value)
// 	{
// 		_x = value;
// 	}  

  //  int i;
  //  void putprop(int j) {
  //     i = j;
  //  }

  //  int getprop() {
  //     return i;
  //  }

  // __declspec(property(get = getprop, put = putprop)) int the_prop;
private:
  string val3;
public:
  //friend string getFiendValue() {return val2;} //! eval: why does this NOT compile?
  // static string staticTest(EntryCompany base) {return val3;} //! Eval: why doe this fails to compile?
  static void staticTest() {;}
  friend string getFiendValue_accessInteranls(EntryCompany base) {    return base.val3;} //! eval: 
  friend string getFiendValue() {
    // ::getFiendValue_entry(); //! Eval: why does this NOT compile?
    return string("a test");
    //return getFiendValue_entry() + string("a test"); //! Eval: why is a "friend" funcion unale to access itnernal membes (of a funcion)? <---
  }

  //friend string Entry_Base::getFiendValue_entry();
  // friend string Entry_Aux::getFiendValue_entry2(); // FIXME: whyd eos this NOT compile?
  friend Entry_Aux; // FIXME: does this impliy that "Entry_Aux" can access prviate emmbers in this?
  friend void friendFunc_2(EntryCompany base);
public:
  // no class can override f()
  //int getValue() final {
  string val2 = ""; //! evaluate: how does this object-init work? when to sue this? when NOT reccomended?
  shared_ptr<string> val;
  int getValue()  {
    return 0;
  }
  void operator>>(string &toAdd)  {
    //*val += toAdd; //! Eval: why does this cause a segfault? how to resolve this segaulat?
    val2 += toAdd;
    toAdd = string("-->") + toAdd;
  }
  //bool operator !=(decltype(this) obj_cmp) {
  bool operator !=(EntryCompany obj_cmp) {
    try {
      return true;
    }
    catch(...) {
      ;
    }
    return false;
  }

  int func() {
    try
    {
      ;
    } catch (invalid_argument& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
  }

  // void set_val(string _val) {
  //   val = _va;
  // }
  // string get_val() {
  //   return val;
  // }
  // 	  //__declspec( property (put=set_val, get=get_val) ) data-type property-name; //! [https://www.codeproject.com/Articles/118921/C-Properties]
	  
// private: 
// 	int _x; 
// public:  
//  	PROPERTY(int, x);
//   	GET(x) 
//  	{ 
//  		return _x; 
// 	}
//  	SET(x)
//  	{
//  		_x = value;
//  	}
	  
  static void tut_class() {
    string var = "dfg";
    auto obj_entry = EntryCompany();
    //var >> obj_entry;
    obj_entry >> var; //! eval: if this had been written as a fucniont, how woudl the fucnion then look like?
    obj_entry.operator >>(var);

    auto obj_new = EntryCompany(obj_entry.val);

    auto val = addValues(var, "hei");
    cout << "val=" << val << endl;

    //cout << obj_new.getFiendValue_accessInteranls() << endl;
    //cout << EntryCompany::getFiendValue_accessInteranls() << endl;
    //cout << ::getFiendValue_accessInteranls() << endl;
  }
  EntryCompany() {};
  EntryCompany(shared_ptr<string> &_val) : val(_val) {}
};


// void EntryCompany::friendFunc_2(EntryCompany base) //! eval: why does ths fail to compile?
void friendFunc_2(EntryCompany base) {
  cout << base.val3 << endl; //! ie, access the prviate variables in "base"
}

class EntryPerson : Entry_Base {
  int mx;
  double my;

public:
  EntryPerson(int x, double y) : mx{ x }, my{ y } {}
  EntryPerson(const std::initializer_list<int>& v) {
    mx = *(v.begin());
    my = *(v.begin() + 1);
  }
};


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
// deduction guide was needed in C++17
// template<typename T, typename U>
// S(T, U) -> S<T,U>;



 

// ***************'

// FIXME: include eprmtauion fo the bwlo ---
// Below is the syntax for using
// the nested namespace
namespace Game {
  namespace Graphics {    
    namespace Physics {      
      class ANestedClass {
      };
    }
  }
}



#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

#include <iostream>
#include <map>
#include <string>
using namespace std;


// FIXME: write the blwo color-class
// class Color {
// public:
//   int green(
// }

// void tut_map() {
//   //! Src: https://www.walletfox.com/course/mapwithcustomclasskey.php
// {
//     auto comparator = [](const Color& c1, const Color& c2) -> bool
//     {
//         return c1.red() + c1.green() + c1.blue() <
//                     c2.red() + c2.green() + c2.blue();
//     };

//     std::map<Color, int, decltype(comparator)> myMap(comparator);
//     myMap = {
//               {Color(0, 0, 0), 0},
//               {Color(230, 159, 0), 1},
//               {Color(86, 180, 233), 2},
//               {Color(128, 128, 0), 3}
//     };

//     for (auto& it : myMap)
//         std::cout << it.first << " " << it.second << '\n';
// }

// overload_date.cpp
// compile with: /EHsc
#include <iostream>
using namespace std;

class Date
{
    int mo, da, yr;
public:
    Date(int m, int d, int y)
    {
        mo = m; da = d; yr = y;
    }
    friend ostream& operator<<(ostream& os, const Date& dt);
};

ostream& operator<<(ostream& os, const Date& dt) //! Note: why is "<<" not delcareed with a "Date::" class prefxi?
{
    os << dt.mo << '/' << dt.da << '/' << dt.yr;
    return os;
}

void main_Date()
{
    Date dt(5, 6, 92);
    cout << dt;
}

#include<iostream> 
using namespace std;

void operator<<(ostream& os, int arr[]) {
    for (int i = 0;i < 10;i++) {
        os << arr[i] << " ";
    }
    os << endl; 
}
    
void ostream_oeraptor_main() {
  int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
  cout << arr;
}

// For manipulating the file
// directories

void tut_filePath() {
  const auto filePath {"FileToCopy"};
  // If any filepath exists
  if(filesystem::exists(filePath)) {
    const auto FileSize {
      filesystem::file_size(filePath)
	};
    
    filesystem::path tmpPath {"/tmp"};
    
    // If filepath is available or not
    if(filesystem::space(tmpPath)
       .available > FileSize) {
      
      // Create Directory
      filesystem::create_directory(
				   tmpPath.append("example"));
      
      // Copy File to file path
      filesystem::copy_file(filePath,
			    tmpPath.append("newFile"));
    }
  }
}




//  ... No, if you inherit from a pure virtual class and you want to use this derived class (declare object of that type, not a pointer), you must implement all its pure virtual methods. In the same manner you could ask the following:
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
#include <iostream>
#include <cxxabi.h>
#define quote(x) #x
template <typename foo,typename bar> class one{ };
int main()
{

  { //! Src: https://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object
      one<int,one<double, int> > A;
      int status;
      char * demangled = abi::__cxa_demangle(typeid(A).name(),0,0,&status);
      std::cout << "demangled=" << demangled<<"\t"<< quote(A) <<"\n";
      free(demangled);
  }
  {
    //cout << getFiendValue_accessInteranls() << endl; //! Eval: why does this NOT work?
    // cout << EntryCompany::getFiendValue_accessInteranls(EntryCompany()) << endl; //! eval: why does this NOT work?
    cout << getFiendValue_accessInteranls(EntryCompany()) << endl;
    //cout << EntryCompany::getFiendValue_accessInteranls() << endl;
    EntryCompany::tut_class();
  }
  {
    {
      //EntryJobListing s{1, 2.0};   //! Eval: why are "{ ... }" used (eg, instead of "(1, 2.0)"?
      //EntryJobListing<int, float> s{1, (float)2.0};   //! Eval: why are "{ ... }" used (eg, instead of "(1, 2.0)"?
      EntryJobListing<int, float> s(1, (float)2.0);   //! Eval: why are "{ ... }" used (eg, instead of "(1, 2.0)"? if we instead call "EntryJobListing<int, float> s{1, (float)2.0};", then, what beocmes the result? (tip: what cosntrucotr is called)?
      //EntryJobListing<int, double> s(1, 1.0);

      //EntryJobListing<int, double> s(1, 1.0);
      //EntryJobListing<int, float> s(1, 2.0);   //! Eval: why are "{ ... }" used (eg, instead of "(1, 2.0)"?
    }
    {
      EntryJobListing<float, int> obj(5.0, -1);
      try
	{
	  int arr[5] = { 1, 5, 2, 4, 3 };
	  for_each(arr, arr + 5, obj);
	}
      catch(int i)
	{
	  cout << "\nThe Exception element is : " << i ;
	}
    }
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
  //
  { //! Case: 
    vector<int> vec_1{1, 2, 3};
    decltype(vec_1) vec_2;
    for(auto val : vec_1) {
      vec_1.push_back(val);
    }
    // FIXME: extend above to class-based logics

    //! An alterntive strtegy:
    decltype(vec_1) vec_3;
    for(auto it = vec_1.begin(); it != vec_1.end(); it++) {
      vec_1.push_back(*it);
    }
  }
  //
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
  //
  { //! Case: 

  }
  //
  { //! Case: 

  }
  //
  { //! Case: 

  }    
}



