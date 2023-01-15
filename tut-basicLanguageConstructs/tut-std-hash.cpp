/**
@remarks
- compile: 
g++ tut-std-hash.cpp -std=c++17; ./a.out
 **/
#include <string>
#include <map>
#include <iostream>


int main() {
  std::map<std::string, long long int> m {
					  {"a", 1},
					  {"b", 2},
					  {"c", 3}
  };
  for (const auto &obj : m) {
    auto val = std::hash<std::string>{}(obj.first); 
    std::cout << obj.first << ": " << obj.second << " => key="<< val << std::endl; //! [https://stackoverflow.com/questions/26281979/c-loop-through-map]
  }
  //! A permtuation of the above:
  for (auto&& [key, value] : m) { // FIXME: why si the "&&" used here? <-- try usign this concpet when writing a new code-chunk!
    std::cout << key << ": " << value << std::endl; //! [https://stackoverflow.com/questions/26281979/c-loop-through-map]    
  }
}
