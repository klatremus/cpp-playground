/**
   @brief explores the use of C++17 folding support
 **/
#include <iostream>
#include <string>
using namespace std;



template <typename ... Args> auto sum(Args ... args) { //! Eval: how can this be used for printing?
  return (args + ...); //! evla: what is the effect of this?
  //return (args + ... + 0);
}

template <typename ...Args> auto all(Args ...args) {
  return (... && args); //! eval: what is the effect of this? where can this expanion be used? if an expression should be rewirten (using this), whow woudl the enw code look like?
}

int main() {
  cout << sum(1, 2, 3) << endl;
  cout << sum(to_string(1), to_string(2), to_string(2))
       << endl;

  cout << "all.1=" << all(true) << endl;
  cout << "all.2=" << all(true, false, true) << endl;  
}
