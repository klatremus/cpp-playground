// FIXME: get this to work

// stl_release_unique.cpp
// Compile by using: cl /W4 /EHsc stl_release_unique.cpp
#include <iostream>
#include <memory>

struct Sample {
   int content_;
   Sample(int content) : content_(content) {
      std::cout << "Constructing Sample(" << content_ << ")" << std::endl;
   }
   ~Sample() {
      std::cout << "Deleting Sample(" << content_ << ")" << std::endl;
   }
};

void ReleaseUniquePointer() {
//! Src: https://learn.microsoft.com/en-us/cpp/standard-library/unique-ptr-class?view=msvc-170
// FIXME: for what use-cases are we intersted in releaisng a given pointer? ... to tke over tis ownership?
   // Use make_unique function when possible.
   auto up1 = std::make_unique<Sample>(3);
   auto up2 = std::make_unique<Sample>(42);

   auto ptr_moved = std::move(up1); //! ie, grab=move the old pointer
   std::cout << "ptr_moved=" << ptr_moved.get() << std::endl;
   std::cout << "ptr_old=" <<up1.get() << std::endl;   
   // Take over ownership from the unique_ptr up2 by using release
   auto ptr = up2.release(); //! ie, get access to the inner=Raw datat-tyep?
   if (up2) {
      // This statement does not execute, because up2 is empty.
      std::cout << "up2 is not empty." << std::endl;
   }
   // We are now responsible for deletion of ptr.

   // FIXME: why doe sthe bleow compiation fail?
   std::cout << "ptr.type=" << typeid(ptr).name() << std::endl;
   const Sample *ptr_same = ptr;
   //auto ptr_fromPtr = std::make_unique<Sample>(ptr);
   // auto ptr_fromPtr = std::make_unique<int>(ptr);
   auto ptr_fromPtr = std::make_unique<Sample*>(ptr); //! works!

   delete ptr;
   // up1 deletes its stored pointer when it goes out of scope.
}

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
//int main() 

#include <assert.h>
bool types_are_equal(const auto var1, const auto var2) { // FIXME: how can this fucnity be used?
  return (typeid(var1).hash_code() ==  typeid(var2).hash_code()); //! [https://stackoverflow.com/questions/36577718/same-typeid-name-but-not-stdis-same]
}

bool inspectTypes(){
  int head = 2;
  int obj_cmp = 1;
  typedef int _Node;
  if(std::is_same<decltype(obj_cmp), _Node>::value == false)    {
      //if(
      _Node tmp;
      std::cout << "!!\t types differ: " << typeid(obj_cmp).hash_code() << ", " << typeid(tmp).hash_code() << "; name=" << typeid(tmp).name()<< std::endl; // FIXME: why dopes this if-value thos <--- seems odd: uses it wrongly?
	//assert(false); //! as this enver shoudl happend
      // FIXME: how to get the below to work?
      // assert(typeid(obj_cmp).hash_code() ==  typeid(tmp).hash_code()); // FIXME: hahwo to sue theis type-fiaiton aviely?
      assert(types_are_equal(obj_cmp, tmp));
      // static_assert(types_are_equal(obj_cmp, tmp)); // FIXME: dineify usage of the "static_assert(..)" compile-time assert-funciotn
    }
    //if constexpr(is_integral<decltype(obj_cmp)>::value) { 
  if constexpr(std::is_integral<_Node>::value) {// FIXME: what is the dffrence between "is_integral" VS "is_same"?? (eg, subsets?)?
	//! Note: "_Node" == decltype(obj_cmp)
	// Note: if the "constexpr"  test was NOT used, then the result woudl be a compile-time-error
	//if(is_integral<decltype(obj_cmp)) {
      
	return (head == obj_cmp);
      } else {
    return false; //head.isEqual(obj_cmp); //! ie, a fallback
    }
}
#include <vector>
bool inspectTypes2(){
  std::shared_ptr<int> arr_int = std::make_shared<int>();
  auto arr_2 = std::forward<decltype(arr_int)> (arr_int);
  //auto arr_2 = std::forward<int*>(arr_int);
  // auto arr_3 = static_cast< decltype<arr_int> >(arr_int);   // FME: why not working?
  //auto arr_3 = static_cast<std::shared<int> &&>(arr_int); // FIXME: why not working? <--- how to convert wrt. the "make_shared" pointers? .... use a direct-acess?
    std::vector<std::string> v;  
    auto v2 = static_cast<std::vector<std::string> &&>(v);
    return true;
}

void tut_vectors()
 {

   { //! Case: "shared_ptr reset throws segmentation fault":
     //! Src: https://stackoverflow.com/questions/45428001/shared-ptr-reset-throws-segmentation-fault
     A *raw_ptr = new A();
     std::shared_ptr<A> sptr1(raw_ptr);
     std::shared_ptr<A> sptr2 = sptr1;
     sptr1.reset(); // occurs Segmentation Fault here
     //std::cout << sptr1.use_count() << std::endl; // prints 2
     std::cout << "count: "<< sptr1.use_count() 
       // << "value: "<< sptr1->pointer.get()
	       << std::endl
       ; 
     sptr1.reset(); // occurs Segmentation Fault here
   }
   
   // FIXME: get bleow to work!
   //! SrC: https://stackoverflow.com/questions/26734452/how-can-i-create-a-shared-ptr-to-a-stdvector
   std::vector<uint8_t> mVector; //(29);
   /* Copy the vector in a shared pointer */
   // std::shared_ptr<std::vector<uint8_t> > mSharedPtr ( new std::vector<uint8_t>(mVector) );
   
   std::shared_ptr<std::vector<uint8_t> > mSharedPtr ( new std::vector<uint8_t>() ); //! Eval: why deos this inti-procedure work?
   
   std::vector<uint8_t> vector(20);
   /* Copy the vector in a shared pointer */
   auto sharedPtr = std::make_shared<std::vector<uint8_t>> (vector);
   
   //std::shared_ptr<std::vector<uint8_t>> sPtr_1 (&mVector);   // FIXME: why does this cause a segafult?
   std::shared_ptr<std::vector<uint8_t>> sPtr;
   std::cout << "sptr=" << sPtr.get() << std::endl;
   //sPtr.reset(&mVector); // FIXME: why does this cause=throws a sefault?
   //std::cout << "sptr=" << sPtr.get() << std::endl;
   // std::shared_ptr<std::vector<uint8_t>> sPtr (&mVector,[](std::vector<uint8_t>*){}); // FIXME: what is the point=meaning of this?
 }  

int main() {
  tut_vectors();
  inspectTypes();
  inspectTypes2();  
   ReleaseUniquePointer();
{
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;

    return 0;
}
}

