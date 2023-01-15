// !src: https://stackoverflow.com/questions/7257144/when-to-use-stdforward-to-forward-arguments
/**
@remarks compil:
```bash
#! To build:
# rm -f *.o tut-std-forward
g++ -std=c++2a -Werror -g -ggdb3 -Wall -c -o tut-std-forward.o tut-std-forward.cpp; g++ tut-std-forward.o  -o tut-std-forward; ./tut-std-forward
```
 **/

/** @remarks Idea:
So if we have a const version of an account we should expect when we pass it to our deposit template<> that the const function is called; and this then throws an exception (the idea being this was a locked account!)

If we have a non const account then we should be able to modify the account.
*/
#include <iostream>
#include <string>
#include <sstream> // std::stringstream
#include <algorithm> // std::move
#include <utility>
#include <iostream>
#include <functional>

// FIXME: rewrite this exmapel ... chanign it inot 'our own exmapel' ... get working! <-- suggesiotns for what ussage-exmpel we cna rewrite this into?

template<class T> class BankAccount { // FIXME: why is "class T" used instead of "typename T"?
private:  
  const T no_cash {}; //! and for case where "no_cash = 100", this translates into: "auto no_cash = {10}", where no_cash is std::initializer_list<int> [https://stackoverflow.com/questions/18222926/what-are-the-advantages-of-list-initialization-using-curly-braces]
  T cash {}; // FIXME: what does the "{}" symbol mean?
public:
  BankAccount<T> () {
    std::cout << "default constructor " << to_string() << std::endl;
  }
  BankAccount<T> (T cash) : cash (cash) {
    std::cout << "new cash " << to_string() << std::endl;
  }
  BankAccount<T> (const BankAccount& o) {
    std::cout << "copy cash constructor called for " << o.to_string() << std::endl;
    cash = o.cash;
    std::cout << "copy cash constructor result is  " << to_string() << std::endl;
  }
  // Transfer of funds?
  BankAccount<T> (BankAccount<T>&& o) {
    std::cout << "move cash called for " << o.to_string() << std::endl;
    cash = o.cash;
    o.cash = no_cash;
    std::cout << "move cash result is  " << to_string() << std::endl;
  }
  ~BankAccount<T> () {
    std::cout << "delete account " << to_string() << std::endl;
  }
  void deposit (const T& deposit) {
    cash += deposit;
    std::cout << "deposit cash called " << to_string() << std::endl;
  }
  friend int deposit (int cash, const BankAccount<int> &&account) { // FIXME: what is a 'friend' function? <--- "Friend Class A friend class can access private and protected members of other class in which it is declared as friend. It is sometimes useful to allow a particular class to access private members of other class. For example, a LinkedList class may be allowed to access private members of Node." [https://www.geeksforgeeks.org/friend-class-function-cpp/]
    throw std::string("tried to write to a locked (const) account");
  }
  friend int deposit (int cash, const BankAccount<int> &account) {
    throw std::string("tried to write to a locked (const) account");
  }
  friend int deposit (int cash, BankAccount<int> &account) {
    account.deposit(cash);
    return account.cash;
  }
  friend std::ostream& operator<<(std::ostream &os, const BankAccount<T>& o) { // FIXME: what is "os::stream"?
    os << "$" << std::to_string(o.cash);
    return os;
  }
  std::string to_string (void) const {
    auto address = static_cast<const void*>(this);
    std::stringstream ss; // FIXME: what is "std::stringstream"?
    ss << address;
    return "BankAccount(" + ss.str() + ", cash $" + std::to_string(cash) + ")";
  }
};

template<typename T, typename Account>
int process_deposit(T cash, Account&& b) { // FIXME: what does the "&&" symbol mean?
//int process_deposit(T cash, Account& b) {
//int process_deposit(T cash, Account b) {
  return deposit(cash, std::forward<Account>(b)); // FIXME: does the "foward" fail due to "Accounb&& b" bein declared "const" (in the caller)?
}

int main(int, char**)
{
  try {
    // create account1 and try to deposit into it
    auto account1 = BankAccount<int>(0);
    process_deposit<int>(100, account1);
    std::cout << account1.to_string() << std::endl;
    std::cout << "ok\tSUCCESS: account1 deposit succeeded!" << std::endl;
  } catch (const std::string &e) {
    std::cerr << "!!\t FAILED: account1 deposit failed!: " << e << std::endl;
  }

  try {
    // create locked account2 and try to deposit into it; this should fail
    const auto account2 = BankAccount<int>(0);
    std::cout << "processes account ..." << std::endl;
    process_deposit<int>(100, account2);
    std::cout << "processes account ... to string" << std::endl;
    std::cout << account2.to_string() << std::endl;
    std::cout << "ok\tSUCCESS: account2 deposit succeeded!" << std::endl;
  } catch (const std::string &e) {
    std::cerr << "!!\tFAILED: account2 deposit failed!: " << e << std::endl;
  }

  try {
    // create locked account3 and try to deposit into it; this should fail
    auto account3 = BankAccount<int>(0);
    process_deposit<int>(100, std::move(account3));
    std::cout << account3.to_string() << std::endl;
    std::cout << "ok\tSUCCESS: account3 deposit succeeded!" << std::endl;
  } catch (const std::string &e) {
    std::cerr << "!!\tFAILED: account3 deposit failed!: " << e << std::endl;
  }
}
