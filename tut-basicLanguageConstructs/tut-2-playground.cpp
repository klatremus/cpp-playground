/**
   @brief a playground explroign cocnpets from "tut-2.cpp"
 **/
#include "enum_utility.h"

enum class new_enum : unsigned int { // "Strongly typed enumerations": <-- FIXME: can this also be used to inehritt from classes? ... possible to use this to derive the enum-type direlcty? ... how to use this in combion with tempale-aprams + decltype(..) contructs?
				    value1, //! value defualt set to '1': 
				    value2, //! value defualt set to '1': <-- FIXME: why?
				    value3 = 100,
				    value4 = 100,
				    value5 = 5
};

void print_enum(const int value) {
  std::cout << "Value=" << value << std::endl;
}

void main_enums() {
  // FIXME: how to et the int-time of a 'storngly typed enum'?
  if (new_enum::value3 == new_enum::value4) { // true
    std::cout << "new_enum::value3 == new_enum::value4, val=" << new_enum::value4 << std::endl;
    std::cout << "new_enum::value3 == new_enum::value5, val=" << new_enum::value5 << std::endl;
    print_enum(+new_enum::value5);
    print_enum(+new_enum::value2);
  }
  std::cout << new_enum::value3 << std::endl;
  {
    auto obj_cmp = 1;
    std::cout << "is_same=" << (std::is_same<decltype(obj_cmp), int>::value) << std::endl;
  }
}

#include <tuple>

template <typename _Node, typename _Predicate> class Relation_Base {
  virtual _Node get_head() { // override;
    //virtual void foo(int) override; // legal
    return _Node();
  }
};

#include <type_traits>
#include <assert.h>

bool types_are_equal(const auto var1, const auto var2) { // FIXME: how can this fucnity be used?
  return (typeid(var1).hash_code() ==  typeid(var2).hash_code()); //! [https://stackoverflow.com/questions/36577718/same-typeid-name-but-not-stdis-same]
}

template <typename _Node, typename _Predicate> class Relation : Relation_Base<_Node, _Predicate>{
  private:
  _Node head;
  _Predicate predicate;
  _Node tail;
public:
  Relation(_Node _head, _Predicate _predicate, _Node _tail) : head(_head), predicate(_predicate), tail(_tail) {;}
  //std::tuple<_Node, _Predicate, _Node> get_relation() constexpr { // FIXME: correc tusage of the "constexpr"?
  constexpr std::tuple<_Node, _Predicate, _Node> get_relation()  { // FIXME: correc tusage of the "constexpr"?
    return std::make_tuple(head, predicate, tail);
  }
  _Node get_head() final { // FIXME: any modifers to force a 'const head' reutrn-value?
    return head;
  }
  void print_data() {
    std::cout << "(" << head << ", " << predicate << ", " << tail << std::endl;
  }

  std::string to_string() const {
    auto address = static_cast<const void*>(this); // FIXME: why this "const void*" static-cast?    
    std::stringstream ss; // FIXME: what is "std::stringstream"?
    ss << address;
    return "Relation(" + ss.str() + ", (" + std::to_string(head) + ", " + std::to_string(predicate)+ ", " + std::to_string(tail) + ")";
  }
  // FIXME: try getitng the below to work ... how?
  //  bool isEqual(const _Node &obj_cmp) const {
  //    _Node _obj_cmp = 1;
  //    std::cout << "is_same=" << (std::is_same<decltype(obj_cmp), int>::value) << std::endl;
  //    std::cout << "...is_same=" << (std::is_same<decltype(_obj_cmp), int>::value) << std::endl;     

  //    //if (std::is_same<float, int>::value) {
  //    if (std::is_same<obj_cmp, int>::value) {
  //    //if (std::is_same<decltype(obj_cmp), int>::value) {
  //      return (head == obj_cmp);
  //      //if (std::is_same<obj_cmp, int>) {
  //      //return true;
  //    }
  //    //if (std::is_same<obj_cmp, _Node>::value)
  // //   //if (std::is_same<obj_cmp, _Node>::value)
  // //   {
  // //     //if (std::is_same<decltype(obj_cmp), decltype(_Node)>::value) {
  // //     if (std::is_same<obj_cmp, int>::value) {
  // //     //if (std::is_same<decltype(obj_cmp), int>::value) {
  // // 	/**! @brief test only for the ehad-attribute **/
  // // 	// FIXME: add lgocis
  // // 	return (head == obj_cmp.get_head());
  // //     }
  // //   }
  //    // return head.isEqual(obj_cmp); //! ie, a fallback
  //    return false;
  //  }  
  // constexpr
  bool isEqual(const _Node obj_cmp) const {
    std::cout << "is_integral::a: " << std::is_integral<decltype(obj_cmp)>::value << std::endl;
    //if constexpr(std::is_same<decltype(obj_cmp), _Node>::value == false)    {
    if(std::is_same<decltype(obj_cmp), _Node>::value == false)    {
      //if(
      _Node tmp;
      std::cout << "!!\t types differ: " << typeid(obj_cmp).hash_code() << ", " << typeid(tmp).hash_code() << "; name=" << typeid(tmp).name()<< std::endl; // FIXME: why dopes this if-value thos <--- seems odd: uses it wrongly?
	//assert(false); //! as this enver shoudl happend
      assert(typeid(obj_cmp).hash_code() ==  typeid(tmp).hash_code()); // FIXME: hahwo to sue theis type-fiaiton aviely?
      assert(types_are_equal(obj_cmp, tmp));
    }
    //if constexpr(std::is_integral<decltype(obj_cmp)>::value) { 
    if constexpr(std::is_integral<_Node>::value) {
	//! Note: "_Node" == decltype(obj_cmp)
	// Note: if the "constexpr"  test was NOT used, then the result woudl be a compile-time-error
	//if(std::is_integral<decltype(obj_cmp)) {
	return (head == obj_cmp);
      } else {
      return head.isEqual(obj_cmp); //! ie, a fallback
    }
  }
  bool __isEqual(const int obj_cmp) const {
    //std::cout << "is_integral::a: " << std::is_integral<head>::value ) << std::endl;
    std::cout << "is_integral::a: " << std::is_integral<decltype(obj_cmp)>::value << std::endl;
    std::cout << "is_integral::a: " << std::is_integral<decltype(this)>::value << std::endl;
    return (head == obj_cmp);
    //return true;
  }
  bool isEqual(const Relation &obj_cmp) const { //! and if the caller is delcared as "cosnt", while this funciton does NOT have a "const" attirubte, then the following comeril-eror is givne: "error: passing ‘const Relation<int, int>’ as ‘this’ argument discards qualifiers [-fpermissive]"
    // FIXME: add lgocis
    return true; 
  }
  // friend class Data_Arr<Relation>; // FIXME: how to resovle the following cpmiaotn-erorr? --- error: ‘Data_Arr’ is not a class template
  // friend Data_Arr<Relation>; // FIXME: how to resovle the following cpmiaotn-erorr? --- error: ‘Data_Arr’ does not name a type
  template<typename> friend class Data_Arr; //! ie, make all prviae emmes accesislt to the Data_Arr class [https://stackoverflow.com/questions/8967521/class-template-with-template-class-friend-whats-really-going-on-here]
};
  
#include <vector>
#include <initializer_list>

template <typename _Data> class Data_Arr {
//template <typename _Data, _Data obj_emptyData> class Data_Arr {
  //std::vector<int> arr_data;
  _Data obj_emptyData;
  std::vector<_Data> arr_data;
  //Vertex * arr_data; // FIXME: how to chnage this data-type ... to better reflect the belwo types?
public:
  Data_Arr(std::initializer_list<_Data> list, const _Data _obj_emptyData) : obj_emptyData(_obj_emptyData) {
    typename std::initializer_list<_Data>::iterator it; // FIXME: what does the "typename" qualifyer [https://stackoverflow.com/questions/36902840/error-need-typename-before-iterator] do? <-- 
    for (it = list.begin();
	 it != list.end(); ++it)
      arr_data.push_back(*it);
  }


  constexpr  void print_data()  {
    for (const auto &obj : arr_data) {
      obj.print_data();
    }
  }
  //std::tuple<_Node, _Predicate, _Node> get_relation(const _Node &head) constexpr {
  //std::tuple<auto val1, auto val2, auto val3> get_relation(const auto &head) constexpr {
  //constexpr _Data get_relation(const auto &head) {
  _Data get_relation( auto head) {
    // FIXME: below seems worng ... how to resovle this?
    // FIXME: how to merge "_Node, _Predicate, _Node" into vertex? <-- we need to rewirte this: how?
    // FIXME: 
    // FIXME: f
    for(const _Data &obj : arr_data) {
      if(obj.isEqual(head)) {
       	return obj; //.get_relation();
      }
    }
    return obj_emptyData; //_Data_Empty; //! ie, an empty object
  }
};

typedef Relation<int, int> Relation_Integers;

void main_data() {
  // FIXME: 
  auto obj1 = Relation_Integers(1, 2, 3);
  auto obj2 = Relation_Integers(1, 2, 3);
  auto obj3 = Relation_Integers(1, 2, 3);
  //decltype( _Relation
  const auto obj_empty = Relation_Integers(-1, -1, -1);
  //auto obj_data = Data_Arr<Relation_Integers, obj_empty>({obj1, obj2, obj3});
  auto obj_data = Data_Arr<Relation_Integers>({obj1, obj2, obj3}, obj_empty);
  const int head_ = 1;
  auto obj_relation = obj_data.get_relation(/*head=*/head_); //1);
  //auto obj_relation = obj_data.get_relation(/*head=*/1);
  // auto [head, predicate, tail] = obj_relation.get_relation();
  auto [head, predicate, tail] = obj_relation.get_relation();
  std::cout << "head=" << head << std::endl;
}


// FIXME: try underwting + getting the bleow to work

#include <string>
#include <map>
#include <iostream>

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
void main_assignment() {
// Asignment:    Using structured binding, implement the following functions with just one line of function code: <-- FIXME: suggeiosnts for hoiw solving this? ... 
  std::map<std::string, long long int> m {
					  {"a", 1},
					  {"b", 2},
					  {"c", 3}
  };
  update(m, [](std::string key) { //! Note: to udnestnad this, first go to our "tut-std-hash.cpp"
	      return std::hash<std::string>{}(key); //! ie, the hash-key?
	    });
  // FIXME: why si the "[key, value]" called "structured bindings" ("-std=c++17")? ... when to use this?
  for (auto&& [key, value] : m) { // FIXME: why si the "&&" used here? <-- try usign this concpet when writing a new code-chunk!
    std::cout << key << ":" << value << std::endl;
  }
}

int main() {
  main_enums();
  main_data();
  // FIXME: extend this into a rpacila example ... when this workds, the move this into a new file named ""
  main_assignment();
  // FIXME: extend this into a rpacila example ... when this workds, the move this into a new file named ""  
  
  return 1;
}

// FIXME: pre: [https://www.codeproject.com/Articles/453022/The-new-Cplusplus-11-rvalue-reference-and-why-you]
// FIXME: pre: []
// FIXME: pre: []
// ----
// FIXME: add: smart pointers
/**
#include <iostream>
#include <memory>
void foo(std::shared_ptr<int> i) {
    (*i)++;
}
int main() {
    // auto pointer = new int(10); // illegal, no direct assignment
    // Constructed a std::shared_ptr
    auto pointer = std::make_shared<int>(10);
    foo(pointer);
    std::cout << *pointer << std::endl; // 11
    // The shared_ptr will be destructed before leaving the scope
    return 0;
}

std::shared_ptr can get the raw pointer through the get() method and reduce the reference count by reset(). And see the reference count of an object by use_count(). E.g:

auto pointer = std::make_shared<int>(10);
auto pointer2 = pointer; // reference count+1
auto pointer3 = pointer; // reference count+1
int *p = pointer.get();  // no increase of reference count

std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 3
std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

pointer2.reset();
std::cout << "reset pointer2:" << std::endl;

std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 2
std::cout << "pointer2.use_count() = " 
    << pointer2.use_count() << std::endl;                // pointer2 has reset, 0
std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2

pointer3.reset();
std::cout << "reset pointer3:" << std::endl;

std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 1
std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
std::cout << "pointer3.use_count() = " 
    << pointer3.use_count() << std::endl;  


std::unique_ptr is an exclusive smart pointer that prohibits other smart pointers from sharing the same object, thus keeping the code safe:

std::unique_ptr<int> pointer = std::make_unique<int>(10); // make_unique, from C++14
std::unique_ptr<int> pointer2 = pointer; // illegal

    make_unique is not complicated. C++11 does not provide std::make_unique, which can be implemented by itself:

    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique( Args&& ...args ) {
      return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }


#include <iostream>
#include <memory>

struct Foo {
    Foo()      { std::cout << "Foo::Foo" << std::endl;  }
    ~Foo()     { std::cout << "Foo::~Foo" << std::endl; }
    void foo() { std::cout << "Foo::foo" << std::endl;  }
};

void f(const Foo &) {
    std::cout << "f(const Foo&)" << std::endl;
}

int main() {
    std::unique_ptr<Foo> p1(std::make_unique<Foo>());

    // p1 is not empty, prints
    if (p1) p1->foo();
    {
        std::unique_ptr<Foo> p2(std::move(p1));

        // p2 is not empty, prints
        f(*p2);

        // p2 is not empty, prints
        if(p2) p2->foo();

        // p1 is empty, no prints
        if(p1) p1->foo();

        p1 = std::move(p2);

        // p2 is empty, no prints
        if(p2) p2->foo();
        std::cout << "p2 was destroyed" << std::endl;
    }
    // p1 is not empty, prints
    if (p1) p1->foo();

    // Foo instance will be destroyed when leaving the scope
}

f you think about std::shared_ptr carefully, you will still find that there is still a problem that resources cannot be released. Look at the following example:

#include <iostream>
#include <memory>

class A;
class B;

class A {
public:
    std::shared_ptr<B> pointer;
    ~A() {
        std::cout << "A was destroyed" << std::endl;
    }
};
class B {
public:
    std::shared_ptr<A> pointer;
    ~B() {
        std::cout << "B was destroyed" << std::endl;
    }
};
int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;

    return 0;
}

 **/
// ----
// FIXME: add: lamda-funcitons ... diffneert pmetuatiosn (of these) <--- where can these be used? <--- eg, in data-fitlering?
/**
 auto generic = [](auto x, auto y) {
        return x+y;
    };


#include <iostream>
using foo = void(int);  // function pointer
void functional(foo f) {
    f(1);
}
int main() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    functional(f);  // call by function pointer
    f(1);           // call by lambda expression
    return 0;
}

int foo(int a, int b, int c) {
    ;
}
int main() {
    // bind parameter 1, 2 on function foo,
    // and use std::placeholders::_1 as placeholder for the first parameter.
    auto bindFoo = std::bind(foo, std::placeholders::_1, 1,2);
    // when call bindFoo, we only need one param left
    bindFoo(1);

 **/
// FIXME: add: ... forward-operations ... 
// FIXME: add:
// FIXME: add: 

