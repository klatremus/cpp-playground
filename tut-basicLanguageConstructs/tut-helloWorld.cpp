
#include <iostream>
 
template<typename T> void f(T s)
{
    std::cout << s << '\n';
}
 
int inmplicitTypes_inFerred_inTemplates() {
    f<double>(1); // instantiates and calls f<double>(double)
    f<>('a');     // instantiates and calls f<char>(char)
    f(7);         // instantiates and calls f<int>(int)
    void (*pf)(std::string) = f; // instantiates f<string>(string) <-- FIXME: for what use-case woudl this 'intation' be rpefarble?
    pf("∇");                     // calls f<string>(string)
}


// FIXME: constexpr VS inline?
template<typename T> constexpr int f() { return T::value; } //! The existence of a definition of function is considered to affect the semantics of the program if the function is needed for constant evaluation by an expression, even if constant evaluation of the expression is not required or if constant expression evaluation does not use the definition. 

template<typename To, typename From> To convert(From f);
void g(double d) 
{
  //! Note: in the below the type=From is inferred from the argument, while the reutn-value is inferred from the "<>" argument?
    int i = convert<int>(d);    // calls convert<int,double>(double)
    char c = convert<char>(d);  // calls convert<char,double>(double)
    int(*ptr)(float) = convert; // instantiates convert<int, float>(float) <-- FIXME: is "ptr" the name of the new function?
}
