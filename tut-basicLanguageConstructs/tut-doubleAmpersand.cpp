/**
   @rmarks
   - mtoviaotn: expalin the susage observed in "tut-std-forward.cpp"
 **/


template<typename A, typename B> auto min(A&& aref, B&& bref) {
  /** 
      Consider the simplest template function- min and max. In C++03 you have to overload for all four combinations of const and non-const manually. In C++0x it's just one overload. Combined with variadic templates, this enables perfect forwarding.
      - Src: [https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11]
   **/
  // for example, if you pass a const std::string& as first argument,
  // then A becomes const std::string& and by extension, "aref" becomes
  // const std::string&, completely maintaining it's type information.
  if (std::forward<A>(aref) < std::forward<B>(bref))
    return std::forward<A>(aref);
  else
    return std::forward<B>(bref);
  // FIXME: write an exampel using this "&&" template
}



void main_intro() {
  //! Src: [https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11]
  /**
     It denotes an rvalue reference. Rvalue references will only bind to temporary objects, unless explicitly generated otherwise. They are used to make objects much more efficient under certain circumstances, and to provide a facility known as perfect forwarding, which greatly simplifies template code.
  **/

  { // PRoblem: In C++03, you can't distinguish between a copy of a non-mutable lvalue and an rvalue.
    
    std::string s;
    std::string another(s);           // calls std::string(const std::string&);
    std::string more(std::string(s)); // calls std::string(const std::string&);
    std::cout << "min::case1=" << min(s, another) << std::endl;
  }
  {  // In C++0x, this is not the case.
    
    std::string s;
    std::string another(s);           // calls std::string(const std::string&);
    std::string more(std::string(s)); // calls std::string(std::string&&);
    std::cout << "min::case2=" << min(s, another) << std::endl;
  }

 // ... in the second case, we know in advance that the object which was passed in to our constructor is immediately due for destruction, and it doesn't have to remain untouched. We can effectively just swap the internal pointers and not perform any copying at all in this scenario, which is substantially more efficient.

  { // Now we consider the other use of rvalue references- perfect forwarding. Consider the question of binding a reference to a reference.
    
    std::string s;
    std::string& ref = s;
    (std::string&)& anotherref = ref; // usually expressed via template <-- FIXME: when is this "&&" relatinoship expressed via tempaltes?
    std::cout << "min::case3=" << min(s, another) << std::endl;
    /*
      C++0x, the resultant type when dealing with rvalue references is critical. An rvalue reference to a type T, where T is a reference type, becomes a reference of type T.
      
    (std::string&)&& ref; // ref is std::string&
    (const std::string&)&& ref; // ref is const std::string&
    (std::string&&)&& ref; // ref is std::string&&
    (const std::string&&)&& ref; // ref is const std::string&&
    */
  }
  {
    /*
The term for T&& when used with type deduction (such as for perfect forwarding) is known colloquially as a forwarding reference. The term "universal reference" was coined by Scott Meyers in this article, but was later changed.

That is because it may be either r-value or l-value.

Examples are:

// template
template<class T> foo(T&& t) { ... }

// auto
auto&& t = ...;

// typedef
typedef ... T;
T&& t = ...;

// decltype
decltype(...)&& t = ...;
    */
    // FIXME: write examples for "&&" using the [typedef, auto, tempalte, decltype] examepls in the above
  }


}
void main_() {
  //! Src: []
}


void main_() {
  //! Src: []
}


void main_() {
  //! Src: []
}

int main() {
  main_intro();
  return 0;
}
