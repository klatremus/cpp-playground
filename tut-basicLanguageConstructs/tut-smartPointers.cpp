
assert(false); // FIXME: try provoiking memory-bugs ... accessing the raw vlaeus ...e tc.

// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170
void UseSmartPointer()
{
  // Declare a smart pointer on stack and pass it the raw pointer.
  unique_ptr<Song> song2(new Song(L"Nothing on You", L"Bruno Mars"));

  // Use song2...
  wstring s = song2->duration_;
  //...

} // song2 is deleted automatically here.



class LargeObject
{
public:
  void DoSomething(){}
};

void ProcessLargeObject(const LargeObject& lo){}
void SmartPointerDemo()
{    
  // Create the object and pass it to a smart pointer
  std::unique_ptr<LargeObject> pLarge(new LargeObject());

  //Call a method on the object
  pLarge->DoSomething();

  // Pass a reference to a method.
  ProcessLargeObject(*pLarge);

} //pLarge is deleted automatically when function block goes out of scope.

void SmartPointerDemo2()
{
  // Create the object and pass it to a smart pointer
  std::unique_ptr<LargeObject> pLarge(new LargeObject());

  //Call a method on the object
  pLarge->DoSomething();

  // Free the memory before we exit function block.
  pLarge.reset(); // FIXME: what apphends if this is NOT called?

  // Do some other work...

}

void SmartPointerDemo4()
{
  // Create the object and pass it to a smart pointer
  std::unique_ptr<LargeObject> pLarge(new LargeObject());

  //Call a method on the object
  pLarge->DoSomething();

  // Pass raw pointer to a legacy API
  LegacyLargeObjectFunction(pLarge.get());    //! Eval: how can we vodi teh ".get()" from worngly being de-allote(before 'this' is ...)? <-- tip: use "release(..)" or "move(..)"?
}

// FIXME: udnerantd dhte blewo ... explroe the conpets of it
/**
   C++ Standard Library smart pointers

   Use these smart pointers as a first choice for encapsulating pointers to plain old C++ objects (POCO).

   unique_ptr
   Allows exactly one owner of the underlying pointer. Use as the default choice for POCO unless you know for certain that you require a shared_ptr. Can be moved to a new owner, but not copied or shared. Replaces auto_ptr, which is deprecated. Compare to boost::scoped_ptr. unique_ptr is small and efficient; the size is one pointer and it supports rvalue references for fast insertion and retrieval from C++ Standard Library collections. Header file: <memory>. For more information, see How to: Create and Use unique_ptr Instances and unique_ptr Class.

   shared_ptr
   Reference-counted smart pointer. Use when you want to assign one raw pointer to multiple owners, for example, when you return a copy of a pointer from a container but want to keep the original. The raw pointer is not deleted until all shared_ptr owners have gone out of scope or have otherwise given up ownership. The size is two pointers; one for the object and one for the shared control block that contains the reference count. Header file: <memory>. For more information, see How to: Create and Use shared_ptr Instances and shared_ptr Class.

   weak_ptr // FIXME: can we use a "unique_ptr" in combiantion with a "weak_ptr"?
   Special-case smart pointer for use in conjunction with shared_ptr. A weak_ptr provides access to an object that is owned by one or more shared_ptr instances, but does not participate in reference counting. Use when you want to observe an object, but do not require it to remain alive. Required in some cases to break circular references between shared_ptr instances. Header file: <memory>. For more information, see How to: Create and Use weak_ptr Instances and weak_ptr Class.


**/

// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-unique-ptr-instances?view=msvc-170

unique_ptr<Song> SongFactory(const std::wstring& artist, const std::wstring& title)
{
  // Implicit move operation into the variable that stores the result.
  return make_unique<Song>(artist, title);
}

void MakeSongs()
{
  // Create a new unique_ptr with a new object.
  auto song = make_unique<Song>(L"Mr. Children", L"Namonaki Uta");

  // Use the unique_ptr.
  vector<wstring> titles = { song->title };

  // Move raw pointer from one unique_ptr to another.
  unique_ptr<Song> song2 = std::move(song);

  // Obtain unique_ptr from function that returns by value.
  auto song3 = SongFactory(L"Michael Jackson", L"Beat It");
}

void SongVector()
{
  vector<unique_ptr<Song>> songs;
    
  // Create a few new unique_ptr<Song> instances
  // and add them to vector using implicit move semantics.
  songs.push_back(make_unique<Song>(L"B'z", L"Juice")); 
  songs.push_back(make_unique<Song>(L"Namie Amuro", L"Funky Town")); 
  songs.push_back(make_unique<Song>(L"Kome Kome Club", L"Kimi ga Iru Dake de")); 
  songs.push_back(make_unique<Song>(L"Ayumi Hamasaki", L"Poker Face"));

  // Pass by const reference when possible to avoid copying.
  for (const auto& song : songs)
    {
      wcout << L"Artist: " << song->artist << L"   Title: " << song->title << endl; 
    }    
}

class MyClass
{
private:
  // MyClass owns the unique_ptr.
  unique_ptr<ClassFactory> factory;
public:

  // Initialize by using make_unique with ClassFactory default constructor.
  MyClass() : factory (make_unique<ClassFactory>())
  {
  }

  void MakeClass()
  {
    factory->DoSomething();
  }
};

// Create a unique_ptr to an array of 5 integers.
auto p = make_unique<int[]>(5);

// Initialize the array.
for (int i = 0; i < 5; ++i)
  {
    p[i] = i;
    wcout << p[i] << endl;
  }

// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=msvc-170

// FIXME: use the bleow to genrate an image-pointer AND a related name-prefix ... which we later ap+ply operaitosn on ... 

// shared_ptr-examples.cpp
// The following examples assume these declarations:
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct MediaAsset
{
  virtual ~MediaAsset() = default; // make it polymorphic
};

struct Song : public MediaAsset
{
  std::wstring artist;
  std::wstring title;
  Song(const std::wstring& artist_, const std::wstring& title_) :
    artist{ artist_ }, title{ title_ } {}
};

struct Photo : public MediaAsset
{
  std::wstring date;
  std::wstring location;
  std::wstring subject;
  Photo(
        const std::wstring& date_,
        const std::wstring& location_,
        const std::wstring& subject_) :
    date{ date_ }, location{ location_ }, subject{ subject_ } {}
};

using namespace std;

int main()
{
  // The examples go here, in order:
  // Example 1
  // Example 2
  // Example 3
  // Example 4
  // Example 6
}


// Use make_shared function when possible.
auto sp1 = make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

// Ok, but slightly less efficient. 
// Note: Using new expression as constructor argument
// creates no named variable for other code to access.
shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));

// When initialization must be separate from declaration, e.g. class members, 
// initialize with nullptr to make your programming intent explicit.
shared_ptr<Song> sp5(nullptr);
//Equivalent to: shared_ptr<Song> sp5;
//...
sp5 = make_shared<Song>(L"Elton John", L"I'm Still Standing");

//Initialize with copy constructor. Increments ref count.
auto sp3(sp2);

//Initialize via assignment. Increments ref count.
auto sp4 = sp2;

//Initialize with nullptr. sp7 is empty.
shared_ptr<Song> sp7(nullptr);

// Initialize with another shared_ptr. sp1 and sp2
// swap pointers as well as ref counts.
sp1.swap(sp2);  

vector<shared_ptr<Song>> v { // FIXME: why is it OK to iliase a listw without the sue of "="?
  make_shared<Song>(L"Bob Dylan", L"The Times They Are A Changing"),
    make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
    make_shared<Song>(L"Thalía", L"Entre El Mar y Una Estrella")
    };

vector<shared_ptr<Song>> v2;
remove_copy_if(v.begin(), v.end(), back_inserter(v2), [] (shared_ptr<Song> s) 
	       {
		 return s->artist.compare(L"Bob Dylan") == 0;
	       });

for (const auto& s : v2)
  {
    wcout << s->artist << L":" << s->title << endl;
  }

vector<shared_ptr<MediaAsset>> assets {
  make_shared<Song>(L"Himesh Reshammiya", L"Tera Surroor"),
    make_shared<Song>(L"Penaz Masani", L"Tu Dil De De"),
    make_shared<Photo>(L"2011-04-06", L"Redmond, WA", L"Soccer field at Microsoft.")
    };

vector<shared_ptr<MediaAsset>> photos;

copy_if(assets.begin(), assets.end(), back_inserter(photos), [] (shared_ptr<MediaAsset> p) -> bool
	{
	  // Use dynamic_pointer_cast to test whether
	  // element is a shared_ptr<Photo>.
	  shared_ptr<Photo> temp = dynamic_pointer_cast<Photo>(p);
	  return temp.get() != nullptr;
	});

for (const auto&  p : photos)
  {
    // We know that the photos vector contains only 
    // shared_ptr<Photo> objects, so use static_cast.
    wcout << "Photo location: " << (static_pointer_cast<Photo>(p))->location << endl;
  }


// Initialize two separate raw pointers.
// Note that they contain the same values.
auto song1 = new Song(L"Village People", L"YMCA");
auto song2 = new Song(L"Village People", L"YMCA");

// Create two unrelated shared_ptrs.
shared_ptr<Song> p1(song1);    
shared_ptr<Song> p2(song2);

// Unrelated shared_ptrs are never equal.
wcout << "p1 < p2 = " << std::boolalpha << (p1 < p2) << endl;
wcout << "p1 == p2 = " << std::boolalpha <<(p1 == p2) << endl;

// Related shared_ptr instances are always equal.
shared_ptr<Song> p3(p2);
wcout << "p3 == p2 = " << std::boolalpha << (p3 == p2) << endl; 

// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-weak-ptr-instances?view=msvc-170
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Controller
{
public:
  int Num;
  wstring Status;
  vector<weak_ptr<Controller>> others;
  explicit Controller(int i) : Num(i), Status(L"On")
  {
    wcout << L"Creating Controller" << Num << endl;
  }

  ~Controller()
  {
    wcout << L"Destroying Controller" << Num << endl;
  }

  // Demonstrates how to test whether the
  // pointed-to memory still exists or not.
  void CheckStatuses() const
  {
    for_each(others.begin(), others.end(), [](weak_ptr<Controller> wp) {
	auto p = wp.lock();
	if (p)
	  {
            wcout << L"Status of " << p->Num << " = " << p->Status << endl;
	  }
	else
	  {
            wcout << L"Null object" << endl;
	  }
      });
  }
};

void RunTest()
{
  vector<shared_ptr<Controller>> v{
    make_shared<Controller>(0),
      make_shared<Controller>(1),
      make_shared<Controller>(2),
      make_shared<Controller>(3),
      make_shared<Controller>(4),
      };

  // Each controller depends on all others not being deleted.
  // Give each controller a pointer to all the others.
  for (int i = 0; i < v.size(); ++i)
    {
      for_each(v.begin(), v.end(), [&v, i](shared_ptr<Controller> p) {
	  if (p->Num != i)
	    {
	      v[i]->others.push_back(weak_ptr<Controller>(p));
	      wcout << L"push_back to v[" << i << "]: " << p->Num << endl;
	    }
	});
    }

  for_each(v.begin(), v.end(), [](shared_ptr<Controller> &p) {
      wcout << L"use_count = " << p.use_count() << endl;
      p->CheckStatuses();
    });
}

int main()
{
  RunTest();
  wcout << L"Press any key" << endl;
  char ch;
  cin.getline(&ch, 1);
}

 
// --------------------------------------------
// --------------------------------------------
//! Src: https://learn.microsoft.com/en-us/cpp/cpp/static-assert?view=msvc-170
static_assert(sizeof(void *) == 4, "64-bit code generation is not supported."); // FIXME: update our code with this!!!

#include <type_traits>
#include <iosfwd>
namespace std {
  template <class CharT, class Traits = std::char_traits<CharT> >
  class basic_string {
    static_assert(std::is_pod<CharT>::value, // FIXME: write a tempatle-combinion where "PoD" (ie, Plain old Data) is used <--- where? how?
                  "Template argument CharT must be a POD type in class template basic_string");
    // ...
  };
}

struct NonPOD {
  NonPOD(const NonPOD &) {}
  virtual ~NonPOD() {}
};

int main()
{
  std::basic_string<char> bs;
}

// --------------------------------------------
// --------------------------------------------
//! Src:  https://www.geeksforgeeks.org/smart-pointers-cpp/
#include <iostream>
using namespace std;
#include <memory>
 
class Rectangle {
  int length;
  int breadth;
 
public:
  Rectangle(int l, int b){
    length = l;
    breadth = b;
  }
 
  int area(){
    return length * breadth;
  }
};
 
int main(){
 
  unique_ptr<Rectangle> P1(new Rectangle(10, 5));
  cout << P1->area() << endl; // This'll print 50
 
  // unique_ptr<Rectangle> P2(P1);
  unique_ptr<Rectangle> P2;
  P2 = move(P1);
 
  // This'll print 50
  cout << P2->area() << endl; // FIXME: what happedns to "P1"?
 
  // cout<<P1->area()<<endl;
  return 0;
}

#include <iostream>
using namespace std;
#include <memory>
 
class Rectangle {
  int length;
  int breadth;
 
public:
  Rectangle(int l, int b)
  {
    length = l;
    breadth = b;
  }
 
  int area()
  {
    return length * breadth;
  }
};
 
int main()
{
 
  shared_ptr<Rectangle> P1(new Rectangle(10, 5));
  // This'll print 50
  cout << P1->area() << endl;
 
  shared_ptr<Rectangle> P2;
  P2 = P1;
 
  // This'll print 50
  cout << P2->area() << endl;
 
  // This'll now not give an error,
  cout << P1->area() << endl;
 
  // This'll also print 50 now
  // This'll print 2 as Reference Counter is 2
  cout << P1.use_count() << endl;
  return 0;
}



// --------------------------------------------
// --------------------------------------------
//! Src: https://www.geeksforgeeks.org/difference-between-iterators-and-pointers-in-c-c-with-examples/?ref=rp
// C++ program to demonstrate iterators
#include <iostream>
#include <vector>
using namespace std;
int main()
{
  // FIXME: use the bleow to go through a lsit of points ... each stored as bytes ... 
  // Declaring a vector
  vector<int> v = { 1, 2, 3 };
 
  // Declaring an iterator
  vector<int>::iterator i;
 
  int j;
 
  cout << "Without iterators = ";
 
  // Accessing the elements without using iterators
  for (j = 0; j < 3; ++j) {
    cout << v[j] << " ";
  }
 
  cout << "\nWith iterators = ";
 
  // Accessing the elements using iterators
  for (i = v.begin(); i != v.end(); ++i) {
    cout << *i << " ";
  }
 
  // Adding one more element to vector
  v.push_back(4);
 
  cout << "\nWithout iterators = ";
 
  // Accessing the elements without using iterators
  for (j = 0; j < 4; ++j) {
    cout << v[j] << " ";
  }
 
  cout << "\nWith iterators = ";
 
  // Accessing the elements using iterators
  for (i = v.begin(); i != v.end(); ++i) {
    cout << *i << " ";
  }
 
  return 0;
}



 // --------------------------------------------
// --------------------------------------------
//! Src: 





 // --------------------------------------------
// --------------------------------------------
//! Src: 
