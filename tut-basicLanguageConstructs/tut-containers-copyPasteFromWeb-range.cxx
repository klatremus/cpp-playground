#include <algorithm>
#include <list> 
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <algorithm> //include the algorithm header in your project
#include <vector> //Algorithms work best with stl containers
#include <iostream>
#include <iterator>
void tut() {
  { //! Src: https://mjspagna.medium.com/c-stl-std-none-of-98ac7e8ea585
    std::list<int> l1({12, 9, 2, -3, 65});
    std::list<std::string> l2({"dog", "cat", "bear", "xylophone"});//Iterator none_of, returns true if no value is less than 0
    bool positive = std::none_of(l1.begin()
				 ,l1.end()
				 ,[](int x)->bool
				  {return x<0;});//Ranges none_of, returns true if no value is "fish"
    bool missing = std::ranges::none_of(l2, [](std::string s)->bool // FIXME: can the "std::ranges::none_of"  be used a ssyntatifc-sugra (to aovid eht code-overhead to writing iterators)?
					    {return s=="fish";});//Iterator none_of, returns true if no value is longer than 5
    bool len = std::none_of(l2.begin()
			    ,l2.end()
			    ,[](std::string s)->bool
			     {return s.size()>=5;});  std::cout << "positive: " << positive << '\n';
    std::cout << "missing: " << missing << '\n';
    std::cout << "len: " << len << '\n';
  }
  { //! Src: https://en.cppreference.com/w/cpp/algorithm/ranges/all_any_none_of
    namespace ranges = std::ranges;
    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
     
      if (ranges::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
      }
      if (ranges::none_of(v, std::bind(std::modulus<int>(), std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
      }
       
	auto DivisibleBy = [](int d)
			   {
			     return [d](int m) { return m % d == 0; };
			   };
	 
	  if (ranges::any_of(v, DivisibleBy(7))) {
	    std::cout << "At least one number is divisible by 7\n";
	  }
  }
  { //! Src: https://mjspagna.medium.com/c-stl-std-any-of-b1bc6a56d584
    std::array<int, 5> a1({12, 0, -8, 6, 32});
    std::array<std::string, 3> a2({"dog", "rabbit", "pig"});
  
    //Iterator any_of, returns true if one value is negative
    auto positive = std::any_of(a1.begin()
				,a1.end()
				,[](int x)->bool
				 {return x<0;});  //Ranges any_of, returns true if one value is odd
    auto greater = std::ranges::any_of(a1, [](int x)->bool
                                           {return x%2!=0;});  //Ranges any_of, returns true if one value is "dog"
    auto dog = std::ranges::any_of(a2, [](std::string s)->bool
                                       {return s == "dog";});  std::cout << "positive: " << positive << '\n';
    std::cout << "greater: " << greater << '\n';
    std::cout << "dog: " << dog << '\n';
  }
  
  { //! Src: https://stackoverflow.com/questions/9383788/check-stdstring-whether-contains-any-lowercase-character
    auto res = std::find_if(str.begin(), str.end(), 
			    [](int ch) {
			      return ::isupper( (unsigned char)ch);
			    }
			    ) == str.end();
    assert(false); // FIXME: write a meptmatuion of the above ... which uses the "std::find_if::ranges"
  } 
  { //! Src: https://mjspagna.medium.com/c-stl-overview-of-algorithm-a0d94342253e
    {
      std::vector<int> v1({8,6,9,13,1,2});
      std::vector<int> v2({2,3,4,10,7,4});
  
      std::sort(v1.begin(), v1.end()); //iterator based sort
      std::ranges::sort(v2); //ranged based sort    //Print vector with std::copy and an ostream_iterator<int>
      std::copy(v1.begin(), v1.end()
		,std::ostream_iterator<int>(std::cout, " "));
      std::cout << '\n'  //Print vector with std::ranges::for_each using a lambda
	std::ranges::for_each(v2, [](int i)->void{std::cout << i<< ' ';});
    }
  }
  { //! Src: 

  }
  { //! Src: 

  }
  { //! Src: 

  }      
  assert(false); // FIXME: complete this ... rewirt eht above 
}
