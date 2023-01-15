#include <list>
//#include <memory>
typedef long long int index_t;
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <iostream>
#include <optional>
#include <assert.h>
using namespace std;
using std::cout;

class URI_TemporaryFromParsing {
  string url;
  string nameOf_entry;
public:
  URI_TemporaryFromParsing() {};
  string get_uri() {return url + nameOf_entry;};
};

class URI
{
private:
  // URI owns the unique_ptr.
  unique_ptr<URI_TemporaryFromParsing> uri_fromParsing;
  // unique_ptr<int[]> arr_dummy;
public:
  shared_ptr<URI> clone() const {
    return make_shared<URI>(new URI(*this));
  }
  // Initialize by using make_unique with ClassFactory default constructor.
  URI()
    : uri_fromParsing(new URI_TemporaryFromParsing())
      // FIXME: why si the belwo NOT wokring?
      // , arr_dummy(5) // FIXME: when suignt hsi <-- mtoviaotn: try: auto p = make_unique<int[]>(5); for (int i = 0; i < 5; ++i) p[i] = i
  {}
  //private:

  URI(const URI &obj) {}; // FIXME: is this used in the "clone(..)" operation? if yes, then data from "uri_fromParsing" is NOT included: correct? ... how sovlignt his issue?
  URI(const URI *obj) {}; // FIXME: where=when is this funcion called? <-- implclty from the "make_shared" "clone(..)" call?
  // void MakeClass()
  // {
  //   factory->DoSomething();
  // }
};


// --------------------------
// 
class NotImplementedError : public std::logic_error
{
public:
  //const string err = "!!\t Funcion Not implemented [" + std::string(__FILE__) + "::" + std::string(__FUNCTION__) + "::" + std::string( __LINE__) + "]";
  //cout << 10;
  //stringstream ss;
  //stringstream string_object_name;
  //string_object_name << 50;
  static string get_errorString() {
    // FIXME: why does the "std::string(10)" OR "std::string(__LINE__)" not work?
    char string_line[100]; // = atoa(__LINE__);
    memset(string_line, '\0', 100);
    sprintf(string_line, "%d", __LINE__);
    const string err = "!!\t Funcion Not implemented [" + std::string(__FILE__) + "::" + std::string(__FUNCTION__) + "::" + string_line; //std::string(10); // << "10"; //std::string(10); // __LINE__) + "]";
    return err;
  }
  NotImplementedError() : std::logic_error(get_errorString()) { };
  //NotImplementedError() : std::logic_error(err) { };
  //NotImplemented() : std::logic_error("!!\t Funcion Not implemented [" << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << "]") { };
};

template<typename T, T threshold_min,  T threshold_max>
class Error_OutOfRange_Base : public std::logic_error
{
private:
  static string get_errorString(const T value) {
    // FIXME: why does the "std::string(10)" OR "std::string(__LINE__)" not work?
    char string_line[100]; // = atoa(__LINE__);
    memset(string_line, '\0', 100);
    sprintf(string_line, "%d", __LINE__);
    const string err = "!!\t Value=\"" + std::to_string(value) + "\" (of type=\"" + typeid(value).name() + "\") out of range, givenFuncion max-range=[" + std::to_string(threshold_min) + ", " + std::to_string(threshold_max) + "] [" + std::string(__FILE__) + "::" + std::string(__FUNCTION__) + "::" + string_line; //std::string(10); // << "10"; //std::string(10); // __LINE__) + "]";
    return err;
  }  
public:
  /**
     @brief raises an erorr if teh cirtiea matches
   **/
  //static Error_OutOfRange_Base raiseIf_criteriaMatches(const T value) {
  static void raiseIf_criteriaMatches(const T value) {
    if( ((index_t)value < threshold_min) || ((index_t)value > threshold_max)  ) {
      //cout << "!!\t\t(outsiode-range)\t...value='" << (int)value << "' ,,," << endl;
      // FIXME: validate that the below trheosw a new error
      const auto obj = Error_OutOfRange_Base(value);
      throw obj;
      //obj.raise_exeception();
    }
  }
  void raise_exeception() throw() {
    throw this;
  }
  Error_OutOfRange_Base(const T value) : std::logic_error(get_errorString(value)) { };
};

class EntryBase {
public:
  virtual ~EntryBase() = default; // make it polymorphic <-- FIXME: what is the point of this?
  virtual URI get_uri() {
    throw NotImplementedError();
  }
};

class EntryCompany : public EntryBase {
  //unique_ptr<URI> uri = ;
  URI uri = URI();
  string nameOf_company = "";
public:
  list<weak_ptr<EntryCompany>> arr_company_related; //! a weak referecne to relaed compines
public:
  bool operator==(const std::shared_ptr<EntryCompany> &obj_cmp) {
    return (obj_cmp->nameOf_company == this->nameOf_company);
  }
  bool operator==(const EntryCompany &obj_cmp) {
    return (obj_cmp.nameOf_company == this->nameOf_company);
  }

  //! @remarks for an example of the "explicit" keyword, see [https://en.cppreference.com/w/cpp/language/explicit]
  bool operator() () const {return true;} //! Eval: what happdns if "explicit" is removed (from the costnuro and/or this funciton?)?  FIXME: when is this called? ... what is the effect?
  
  explicit EntryCompany(string _nameOf_company) : nameOf_company(_nameOf_company) {}  //! Eval: what happends (eg, in our "operator" fucnotns) when the "explicit" keywrord-prop is dropped?
  explicit EntryCompany() {}
  // FIXME: why dos the belwo fail to compile?
  EntryCompany(const EntryCompany &obj) :
    //uri(obj.uri), //! Eval: why does this throw erorr of: error: use of deleted function ‘URI::URI(const URI&)’ ‘URI::URI(const URI&)’ is implicitly deleted because the default definition would be ill-formed: ??
    uri(move(obj.uri)), //! eval: is this safe? any sidefeccts (of this)? <-- eval: why can "move(..)" be used when "EntryCompany" si marked as "const"?
    nameOf_company(obj.nameOf_company) {} 
  // EntryCompany(const EntryCompany &&obj) : uri(obj.uri), nameOf_company(obj.nameOf_company) {} 
  //friend EntryCompany(const EntryCompany &obj) : uri(obj.uri), nameOf_company(obj.nameOf_company) {} 
};


class EntryCompany_Arr {
  //unique_ptr<list<EntryCompany>> arr_company; // FIXME: does this also keep track of refrences=memory inside EntryCompany ??
public:
  list<shared_ptr<EntryCompany>> arr_company; //! [https://stackoverflow.com/questions/33947624/how-to-make-a-list-of-shared-ptr-in-c]
private:
  mutable int cnt_dataAccesses = 0; //! ie, overrids=ignreos any "const" statemnets (in viaralbes, fucntions, etc.) <-- Eval: can "mutable" be seen 'in the same gate=concpet=Cateogry' as prop="friend"?
  //unique_ptr<EntryCompany []> arr_company;
public:
  
  
  void append(const EntryCompany obj_entry) {
    // auto obj_new = make_shared<EntryCompany>(obj_entry); // FIXME: instead use "std::move(..)" OR "std::forward<EntryCompany>(obj_entry)"
    //shared_ptr<EntryCompany> obj_new = new EntryCompany(obj_entry;
    shared_ptr<EntryCompany> obj_new(new EntryCompany(obj_entry));
    //auto obj_new = move(obj_entry);
    arr_company.push_back(obj_new);
    cnt_dataAccesses += 1;
  }
  EntryCompany at_companyName(const string &nameOf_company) const {
    cnt_dataAccesses++;
    for (auto entry : arr_company) {
      //if(entry == nameOf_company) {
      if(*entry == EntryCompany(nameOf_company)) {
	return *entry;
      }
    }
    return EntryCompany(); //! ie, an empty item
  }
  //explicit EntryCompany_Arr(
  static void addDummyData() {
    auto obj_self = EntryCompany_Arr();
    list<shared_ptr<EntryCompany>> arr {
					make_shared<EntryCompany>("1"),
					make_shared<EntryCompany>("2"),
					make_shared<EntryCompany>("3"),
    };
    for(auto obj_entry : arr) {
      obj_self.arr_company.push_back(obj_entry);
      for_each(obj_self.arr_company.begin(), obj_self.arr_company.end(),
	      [&obj_self, &obj_entry](shared_ptr<EntryCompany> obj_shared) {
		weak_ptr<EntryCompany> obj_weak = obj_shared; // make_shared<EntryCompany>(obj_shared);
		obj_entry->arr_company_related.push_back(obj_weak);
	      });
    }
    for(auto obj_entry : arr) {
      cout << "count=" << obj_entry.use_count() << endl;
    }
  }
};
  

 



// // --------------------------------------------
// // --------------------------------------------
// //! Src: https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-weak-ptr-instances?view=msvc-170

// class Controller
// {
// public:
//   int Num;
//   wstring Status;
//   vector<weak_ptr<Controller>> others;
//   explicit Controller(int i) : Num(i), Status(L"On")
//   {
//     wcout << L"Creating Controller" << Num << endl;
//   }

//   ~Controller()
//   {
//     wcout << L"Destroying Controller" << Num << endl;
//   }

//   // Demonstrates how to test whether the
//   // pointed-to memory still exists or not.
//   void CheckStatuses() const
//   {
//     for_each(others.begin(), others.end(), [](weak_ptr<Controller> wp) {
// 	auto p = wp.lock();
// 	if (p)
// 	  {
//             wcout << L"Status of " << p->Num << " = " << p->Status << endl;
// 	  }
// 	else
// 	  {
//             wcout << L"Null object" << endl;
// 	  }
//       });
//   }
// };


// static unique_ptr<EntryCompany_Arr> objGlobal_companyArr(EntryCompany_Arr());
// unique_ptr<EntryCompany_Arr> get_stealGlobal() {  
//   unique_ptr<EntryCompany_Arr> obj_res = move(objGlobal_companyArr);
//   assert(objGlobal_companyArr->get() == 0); //! as we assume this is cleared
//   return obj_res;
// }



// // FIXME: add exampels for "eval" (ie, dynamci evlaution) <-- does this ecits ... ie, run-tiem execution=evaition of code??

int main() {

}
