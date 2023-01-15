#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional> //! requried to support: function<int (void)>
#include <assert.h>
#include <memory>
#include <algorithm> //! needed for copy-oeprations such as "copy_if" AND "copy_n"
using namespace std;

/**
   @brief explores the effects of varialbe vility=horiszon for lambeda-fucntions
 **/
void tut_scopeof_lambdaFunctions() {
  vector<int> arr_data = vector<int>(10);
  arr_data[2] = 5;
  //arr_data(2) = 5;
  cout << "arr_data[2]=" << arr_data[2] << endl;
  //cout << "arr_data[2]=" << arr_data(2) << endl;
  //cout << "arr_data=" << string(arr_data) << endl; // ?? why does std::vecotr NOT contin a __str__ funion (as seen for Python classes)?
  //cout << "arr_data=" << [arr_data](){ string result; for(int val : arr_data) {result += "v='" + val;} return result;}() << endl; // TODO: why does this not work (ie, 'val' NOT set)? <-- due to "std::to_string(..)" not beeing called
  cout << "arr_data=" << [arr_data](){ string result; for(int val : arr_data) {result += "v='" + to_string(val) + "', ";} return result;}() << endl; // TODO: why does this not work (ie, 'val' NOT set)?  
  arr_data.push_back(10);

  //auto print_data() = [arr_data](){ string result; for(int val : arr_data) {result += "v='" + to_string(val) + "', ";} return result;} // Eval: why does this not work? <-- (at least) two errors
  //auto print_data = [this]{ string result; for(int val : arr_data) {result += "v='" + to_string(val) + "', ";} return result;}; //! Eval: when to use the "this" (or: "*this") symbol?
  auto print_data = [=]{ string result; for(int val : arr_data) {result += "v='" + to_string(val) + "', ";} return result;};
  //auto print_data = [arr_data]{ string result; for(int val : arr_data) {result += "v='" + to_string(val) + "', ";} return result;};

  
  auto print_vector = [=](auto arr_data) {
			// FIXME: does the above "print_data(..)" uses "arr_data" (local) OR "arr_data" (global)?
			cout << "arr_data=" << print_data() << endl; //! Eval: what is the data which gets pritned out here?
		      };

  //auto arr_new = copy(arr_data); // TODO: why is hts macro/funcion NOT part of the "STD" libarryar?
  //decltype<arr_data> classOf_arr_data; classOf_arr_data arr_new; //! evla: wy does this NOT work?
  //; // = classOf_arr_data();
  decltype(arr_data) arr_new;
  cout << "arr_new.name=" << typeid(arr_new).name() << endl;
  arr_new.push_back(2);

  auto arr_data_renamed = arr_data;
  arr_data = decltype(arr_data)(); //! eval: after this, what gets pirnted out in "print_vector(arr_data)"?  
  print_vector(arr_data);
  print_vector(arr_new);
  //copy(arr_data.begin(), arr_data.end(), arr_new); //! eval: why deos this NOT work?
  copy(arr_data.begin(), arr_data.end(), arr_new.begin());

  { //! Scope: effects of using the "&" operand in lambda-fucnitons    
    //! Src: https://learn.microsoft.com/en-us/cpp/cpp/examples-of-lambda-expressions?view=msvc-170
    { //! SubCase: scalars
      int i = 3;
      int j = 5;

      // The following lambda expression captures i by value and
      // j by reference.
      function<int (void)> f = [i, &j] { return i + j; };

      // Change the values of i and j.
      i = 22;
      j = 44;

      // Call f and print its result.
      cout << f() << endl;
    }
    {
      auto vec_1_raw = vector<int>(20);
      auto vec_1 = make_unique<decltype(vec_1_raw)>(vec_1_raw);
      //! Note: the use of "make_unique(..)" case rpboelsm when pssing, ...eg, to a shred boejct ... due to its deisng [https://stackoverflow.com/questions/39703954/why-am-i-getting-compile-error-use-of-deleted-function-stdunique-ptr/39705668]
    }
    { //! SubCase: 
      //auto vec_1 = make_unique<vector<int>() >;
      std::vector<int> __vector(15);
      /* Copy the vector in a shared pointer */
      auto vec_2 =make_shared<std::vector<int>> (__vector);
      auto vec_1_raw = vector<int>(20);
      auto vec_1 = make_shared<decltype(vec_1_raw)>(vec_1_raw);
      assert(vec_1->size() == vec_1_raw.size());
      // assert(vec_1->data() == vec_1_raw.data());  //! ie, the udnleryign emory-potisn are cosnitn <-- FIXME: why does this no logner hold?
      // auto vec_2 = make_unique<vector<int>() >;
      const int vec_1_oldVal = 5;
      vec_1->at(0) = vec_1_oldVal; //! [https://cplusplus.com/reference/vector/vector/at/]
      assert(vec_1->at(0) == 5);
      //assert(vec_1->at(0) == vec_1_raw[0]); // FIXME: why is this NOT cosntient?
      //*(vec_1)[0] = 5;
      //vec_2->[0] = 0;
      vec_2->at(0) = 0;      

      // The following lambda expression captures i by value and
      // j by reference.
      //auto f = [vec_1, &vec_2] { return vec_1->at(0) + (*vec_2)->at(0); };
      // auto f = [vec_1, &vec_2] { return vec_1->at(0) + vec_2->at(0); };
      function<int (void)> f = [vec_1, &vec_2] { return vec_1->at(0) + vec_2->at(0); };
      //auto f = [vec_1, vec_2] { return vec_1->at(0) + (vec_2)->at(0); };
      //function<int (void)> f = [vec_1] { return  vec_1->at(0); };
      //function<int (void)> f = [move(vec_1)] { return  vec_1->at(0); };
      // //function<int (void)> f = [i, &j] { return i + j; };

      // // Change the values of i and j.
      vec_1->at(0) = 3;
      const int vec_2_newVal = 1;
      vec_2->at(0) = vec_2_newVal;      

      // // Call f and print its result.
      int retVal = f();
      cout << retVal << endl;
      // assert(retVal == 1); // Eval: why does this NOT hold ... due to the glboal pointer having changd

      //!
      //! Step: change the "vec_2" variable ecplti:
      vec_2 = vec_1;
      retVal = f();
      cout << retVal << endl;
      assert(retVal == (vec_2_newVal + vec_1_oldVal)); //! eval: try changing the abmvoe "&vec_2" lambda-sepc to "vec_1": does the results still hold?
    }    

  }
  { //! Task: permtuations of copy-operaitons:
    auto print_results = [](auto vec_result) {
			   cout << "Vec="; for(auto w : vec_result) cout << to_string(w); cout << endl;
			 };
    //! Src: https://www.geeksforgeeks.org/different-methods-copy-c-stl-stdcopy-copy_n-copy_if-copy_backward/
    { //! Task:
      vector<int> vec_1 = {1, 3, 5, 8};
      decltype(vec_1) vec_result_1(6);
      decltype(vec_1) vec_result_2(26);
      decltype(vec_1) vec_result_3(16);
      decltype(vec_1) vec_result_4(16);                  
      //! Copy the data:
      copy(vec_1.begin(), vec_1.begin()+4, vec_result_1.begin());
      //! Print results:
      print_results(vec_result_1);
      //!
      //! Step: ecpltiy add subset
      copy_n(vec_1.begin(), /*cnt=*/3, vec_result_2.begin());
      //! Print results:
      print_results(vec_result_1);
      //!
      //! Step: copy only if elemetns match:
      copy_if(vec_1.begin(), vec_1.end(), vec_result_3.begin(), /*matching-funcion=*/[](const int val){return (val == 0);});
      //!
      //! Step: copy bakwards:
      copy_backward(vec_1.begin(), vec_1.begin() + 2, vec_result_3.begin()+3);
      //!
      //! STep: 
      vector<int>::iterator itr;
      // copy(vec_1.begin(), vec_1.end(), inserter(vec_result_4, itr)); // FIXME: why does thsi trigger a segauflt? <-- next: try findingexamples how how the "std::inserter(..)" is to be correclty used
    }
  }
}

#include <bits/stdc++.h> //! needed for the "for_each" syntax

struct A{
  //! Src: https://stackoverflow.com/questions/58662904/how-to-access-stdshared-ptr-methods
   void method() {}
};

void tut_vector_shared() {
  auto print_vector = [](auto vec) {
			cout << "vec=";
			for_each(vec->begin(), vec->end(), [](auto obj) {cout << to_string(obj) + ", ";});
			cout << endl;
		      };
  vector<int> vec_1 = vector<int>(10);
  print_vector(&vec_1);
  int index = 0;
  for (auto &obj : vec_1) {
    obj = index++;
  }
  
  auto a = make_shared<decltype(vec_1)>();
  //auto b = make_shared<decltype(vec_1)>;
  //print_vector(vec_2);
  //shared_ptr<A> a = make_shared<A>();
  a->begin();
  a->end();  
  for_each(a->begin(), a->end(), [a](auto obj) {cout << to_string(obj) + ", ";});
  print_vector(a);

  // FIXME: get below to work!
  //auto vec_2 = make_shared<decltype(vec_1)>; //! Eval: why does this not work?
  //auto vec_2 = make_shared<decltype(vec_1)>(); //! Eval: how would the below copy-operiton work with this init-call?
  auto vec_2 = make_shared<decltype(vec_1)>(10);
  print_vector(vec_2);
  copy(vec_1.begin(), vec_1.end(), vec_2->begin());
  print_vector(vec_2);  
  //print_vector(vec_2.get());
  //print_vector(vec_2->get());
  //sort(vec_2->begin(), vec_2->end(), [](auto ob1, auto obj2) { return true;});
  //sort(vec_2->begin(), vec_2->end(), [](auto ob1, auto obj2) { return obj1 < obj2;});
  sort(vec_2->begin(), vec_2->end(), [](auto obj1, auto obj2) -> bool { return obj1 < obj2;});
  print_vector(vec_2);  

  const int threshold_search = 3;
  decltype(vec_1) ::iterator iter; //! FIXME: how using "decltype(vec_2)" ... as we then get the smartPointers ?? .... how gtting the inner data-tyep?
  iter = find_if(vec_2->begin(), vec_2->end(), [](auto obj1) {
      return (obj1 < threshold_search);
    });
  cout << "found eleemnt(first)=" << *iter << endl; // FIXME: how to iterate through the below
  cout << "found eleemnt(second)=" << iter[1] << endl;
  //while(iter++ < 5) {;} // FIXME: why does this give the following eerror? 
  //for(int  _val = ; _val < 5; _val++) {
    //double val = *iter;
    /*...*/
    //}

  // while(iter++ < iter->end()) {;} // FIXME: why does this give the following eerror? 
  //for (auto obj : iter) {
  //for (auto p = iter->begin(); p < iter->end(); p++) {
  // for (auto p = vec_2->begin(); p < vec_2->end(); p++) {     cout << "found eleemnt()=" << p << endl;  } // FIXME: why does this not work?
  // FIXME: get bleow to wokr!
//   std::shared_ptr<std::vector<uint8_t> > sp;
// {
//    std::vector<uint8_t> mVector;
//    sp=std::shared_ptr<std::vector<uint8_t> >(&mVector);
// }
// sp->empty();   // dangling reference, as mVector is already destroyed

 
}
#include <numeric> //! needed for "accumulate(..)" and "sum(..)"


int compare_ints(const int val1, const int val2) {
  return (val1 < val2);
}

void tut_vectorOperations() {
  /**
     @remarks exampels we make use of:
     - https://www.geeksforgeeks.org/accumulate-and-partial_sum-in-c-stl-numeric-header/
     - https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/algorithm/accumulate.html
   **/
  { //! apply lgoics on a baisc data-strucutre:
    const int arr_1_size = 10;
    int arr_1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //!
    //! Aspect: get list-subet which mathces cirtiera
    auto arr_found = find_if(arr_1, arr_1 + arr_1_size, [](auto obj1) {return true;});  //! ie, get all <-- eval: correct to use "+ arr_1_size" (or: shodul we use "+ sizeof(int)*arr_1_size")?
    assert(arr_found != nullptr);
    //!
    //! Aspect: get the accumualted sum: (basic)
    auto sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 1);
    cout << "sum_count=" << sum_count << endl;
    //!
    //! Aspect: get the accumaluted sum: / lambda:
    sum_count =  accumulate(arr_1, arr_1 + arr_1_size, -10, [](auto obj1, auto obj2) { //! where "-10" is that arr[0] is evlauated/comapred to
							      //cout << "cmp obj=" << to_string(obj1) << " vs obj2=" << to_string(obj2) << endl;
							    return 1+ obj1*obj2;});
    cout << "sum_count=" << sum_count << endl;
    //!
    //! Aspect: get the accumaluted sum: internal std-funciotns:
    //sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 0, std::minus<int>());
    sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 0, std::minus<decltype(arr_1_size)>());
    cout << "sum_count=" << sum_count << endl;
    sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 0, std::multiplies<decltype(arr_1_size)>());
    cout << "sum_count=" << sum_count << endl;        
    // sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 0, std::minus<decltype(arr_1[0])>()); // FIXME: why does this give the following bug=?Error? cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    //sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 0, std::minus<decltype(*(&arr_1[0]))>());
    //!
    //! Aspect: get the accumaluted sum: use internal function
    sum_count =  accumulate(arr_1, arr_1 + arr_1_size, 0, compare_ints);
    cout << "sum_count=" << sum_count << endl;    
    //!
    //! Aspect: get (??) partial sum: <-- Eval: how does "a parital sum" differs from "accumulate(..)"?
    //decltype(arr_1[0]) arr_partialSum[arr_1_size]; // FIXME: why does this cause the followign bug? error: declaration of ‘arr_partialSum’ as array of references
    //decltype(arr_1_size) arr_partialSum[arr_1_size]; //! Eval: what is the rpoblem with this declearation?
    int b;
    decltype(b) arr_partialSum[arr_1_size] = {}; //! Eval: why the use of "int b" work (while the use of "int arr_1_size" (hint: a const-prefix) works?
    //int arr_partialSum[arr_1_size];
    //
    //partial_sum(arr_1, arr_1 + arr_1_size, arr_partialSum, 2);
    partial_sum(arr_1, arr_1 + arr_1_size, arr_partialSum, [](int obj1, int obj2) {return max(obj1, obj2);});
    //partial_sum(arr_1, arr_1 + arr_1_size, arr_partialSum, [](auto obj1, auto obj2) {return max(obj1, obj2);});
    //!
    //! Aspect: get the accumaluted sum:  
    //!
    //! Aspect:
  }
  { //! Step: hadnlign of stirngs + containers/vector:
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //int sum = std::accumulate(v.begin(), v.end(), 0);
    // int product = std::accumulate(v.begin(), v.end(), 1, multiply);
    std::string sum = std::accumulate(v.begin(), v.end(), std::string(), 
                                        //magic_function
					[](auto v1, auto v2) {
					  //v1 += " ...";
					  v1 += to_string(v2) + ", ";
					  //v1 = to_string(v1) + to_string(v2);
					  return v1;
					}
					);
    
    std::cout << "sum(of ints)=" << sum << endl;
    //!
    //!
    auto dash_fold = [](std::string a, int b) {  //! Src: https://www.educative.io/answers/what-is-the-stdaccumulate-function-in-cpp
		       return a + '-' + std::to_string(b); //! Eval: if we replace "a" by "std::move(a)", would the reuslt change? any other sdie-effects (of using the "std::move")? .... is it nessary (eg, aht are teh compeirla ble to do)?
		       //return std::move(a) + '-' + std::to_string(b); // FIXME: why does this work ... while the below requries the result-boject (Eg, "obj1 += obj2") to be udpated? 
		     };
    std::string s = std::accumulate(
				    //std::next(v.begin()), v.end(),
				    v.begin(), v.end(),
				    std::to_string(v[0]), // start with first element
				    dash_fold
				    );
    
    std::cout << s << endl;    
  }
  { //! STep: a permtaution of aboe, hanling stirngs, and usign std::vector:
    //! Src: https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/algorithm/accumulate.html
    vector<string> arr_1;
    int cnt = 0;    while(cnt++ < 10) { arr_1.push_back(to_string(cnt));}
    //!
    //auto sum_count = accumulate(arr_1.begin(), arr_1.end(), "start: ", [](auto obj1, auto obj2) {return obj1 + obj2;}) //! Eval: whhy does this fail to compile?
    //auto sum_count = accumulate(arr_1.begin(), arr_1.end(), string("start: "), [](auto obj1, auto obj2) {return obj1 + obj2;}) //! Eval: why does the aove NOT give any return-value? <-- hint:  hw large is array?
    //     int cnt = 10;    while(cnt++ < 10) { arr_1.push_back(to_string(cnt));} auto sum_count = accumulate(arr_1.begin(), arr_1.end(), string("start: "), [](auto obj1, auto obj2) {
    auto sum_count = accumulate(arr_1.begin(), arr_1.end(), string(), [](auto obj1, auto obj2) {
									 //return  obj1 + obj2;
									 //return to_string(obj1); // + "yes";
									auto retVal = obj1 + obj2;
									obj1 += obj2 + ",";
									cout << "cmp val=" << obj1 << obj2 << " => retVal=" << retVal << endl;
									return obj1;
								      });
    cout << "sum_count='" << sum_count << "'" << endl; 
    
    //!
    // vector<string> arr_result; partial_sum(arr_1.begin(), arr_1.end(), arr_result.begin(), [](auto obj1, auto obj2) {return obj1+obj2;}); //! eval: why does this program crash?
    vector<string> arr_result(10);
    partial_sum(arr_1.begin(), arr_1.end(), arr_result.begin(), [](auto obj1, auto obj2) {return obj1+obj2;});

    //!
    //! Step: sort the list:
    sort(arr_1.begin(), arr_1.end(), [](auto obj1, auto obj2) {return obj1 < obj2;});
    int cntToAdd  = 10;
    arr_1.resize(cntToAdd + arr_1.size());
    cnt = 0;
    while(cnt++ < cntToAdd) {arr_1.push_back(to_string(cnt));}
    //!
    //! Then ecpltily insert elements at index:
    arr_1.insert(arr_1.end(), /*index=*/100, /*value=*/to_string(-40)); //! ie, insert at an idnex otusiod eht eexpeted range; vlaidte that the systme amanges to handle this [https://cplusplus.com/reference/vector/vector/size/]
    auto str_added = to_string(-40);
    static_assert(is_same<string, decltype(str_added)>::value, "!!\tstr_added NOT a string");
    assert(arr_1[100] == str_added);
    //auto funcRef_valToFind = [=](std::string obj) { //! eval: what happends if we use "[]" instead of "[=]"?
    auto funcRef_valToFind = [=](auto obj) { //! eval: what happends if we use "[]" instead of "[=]"?
			       //cout << "obj.type=" << typeid(obj).name() << endl;
			       static_assert(is_same<string, decltype(str_added)>::value, "!!\tstr_added NOT a string");
			       static_assert(is_same<string, decltype(obj)>::value, "!!\t obj NOT a string");			       
			       //return true;
			       //return obj == obj; //str_added;
			       return str_added == obj; //str_added;
			     };
    assert(funcRef_valToFind(str_added) == true);
    assert(funcRef_valToFind(to_string(40)) == false);
    //!
    //! Step: get the above element
    // auto iter = find_if(arr_1.start(); arr_1.end(), funcRef_valToFind);  //! eval: why does this fial to copmpile?
    auto iter = find_if(arr_1.begin(), arr_1.end(), funcRef_valToFind);
    //assert(iter != nullptr);
    assert(*iter == str_added);
    /*
    */
    //!
    //! Step: get number of maches
    int cnt_found = count_if(arr_1.begin(), arr_1.end(), funcRef_valToFind);
    //assert(cnt_found == 1);
    //!
    //! Step:         
  }
  { //! Step: 
    //! Tempalte: [https://www.educative.io/answers/what-is-the-stdaccumulate-function-in-cpp]
  }
  { //! Step: 
    //! Tempalte: []
  }
  { //! Step: 
    //! Tempalte: []
  }
  { //! Step: 
    //! Tempalte: []
  }  
}

#include <iostream>
#include <vector>
#include <numeric>
#include <string>

int multiply(int x, int y){
    return x*y;
}

std::string magic_function(std::string res, int x) {
    return res += (x > 5) ? "b" : "s";
}


void dummy() {
  //! Src: https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/algorithm/accumulate.html
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  int sum = std::accumulate(v.begin(), v.end(), 0);
  int product = std::accumulate(v.begin(), v.end(), 1, multiply);
  std::string magic = std::accumulate(v.begin(), v.end(), std::string(), 
				      magic_function);
  
  std::cout << sum << '\n'
	    << product << '\n'
	    << magic << '\n';
}


#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
void tut_generate() {
  /**
     @remarks inrpaitons:
     - https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
     - 
   **/
  auto print_vector = [](auto vec) {
			cout << "vec=";
			for_each(vec->begin(), vec->end(), [](auto obj) {cout << to_string(obj) + ", ";});
			cout << endl;
		      };
  auto get_vector = [](auto vec) {
		      string retVal;
		      for_each(vec->begin(), vec->end(), [&retVal](auto obj) {retVal += to_string(obj) + ", ";});
		      return retVal;
		    };  
  {
    //auto val = []() noexcept { throw 5; }();
    auto val = []() noexcept { return 5;  }(); //! "You can use the noexcept exception specification to indicate that the lambda expression doesn't throw any exceptions. " []
    //cout <<
    auto arr_1 = vector<int>();
    //while(auto index++ < 10) {
    int index = 0;
    while(index < 10) {
      //arr_1[index] = index; //! ie, add <-- Eval: what is the effect of this? why?
      //arr_1.insert(arr_1.begin(), index); //! eval: what si teh result of calling this?
      //arr_1.insert(arr_1.end(), index, /*value=*/index); //, index); //! eval: what si teh result of calling this?
      arr_1.insert(arr_1.end(), index); //, index); //! eval: what si teh result of calling this?      
      //arr_1[index] = index; //! ie, add
      index++;
    }
    print_vector(&arr_1);
    int index_next = 0;
    //generate(arr_1.begin(), arr_1.begin() + 5, [&] { return index_next++; }); // FIXME: why does this NOT update teh "arr_1"? <-- hint: what valeus are set?
    //generate(arr_1.begin(), arr_1.begin() + 5, [&] { return -100 + index_next++; }); // FIXME: why does this NOT update teh "arr_1"?
    generate(arr_1.begin(), arr_1.begin() + 5, [&]() mutable { return -10 + index_next++; }); // FIXME: seems like the "mutable" does NOT have any effects here ... why?
    //generate(arr_1.begin(), arr_1.end(), [&] { return index_next++; });
    print_vector(&arr_1);    
    {
      //! Src: https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
      // Sets each element in the vector to the sum of the
      int x = 1;
      int y = -2;
      // previous two elements.
      generate_n(arr_1.begin() + 2,
		 index - 2,
		 [=]() mutable throw() -> int { // lambda is the 3rd parameter
		   // Generate current value.
		   int n = x + y;
		   // Update previous two values.
		   x = y;
		   y = n;
		   return n;
		 });
      //std::print("vector v after call to generate_n() with lambda: ", arr_1);
      cout << "vector v after call to generate_n() with lambda: " << get_vector(&arr_1) << endl;
    }
  }
  {
    // auto answer = [](int n)
    // {
    //     return 32 + n;
    // };

    // constexpr int response = answer(10);

    // //
    //  auto Increment = [](int n)
    // {
    //     return n + 1;
    // };

    // constexpr int(*inc)(int) = Increment;
  }
}

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

void print(const string &str, const vector<string> &vec) {
  cout << str << ":";
  for(const auto &ele  : vec) {
    cout << ele << ", ";
  }
  cout << endl;
}

void tut() {
  { //! Src: https://mjspagna.medium.com/c-stl-std-none-of-98ac7e8ea585
    //list vec_1<int>({2, 7, 17, 29, -29, 0});
    list<int> vec_1({2, 7, 17, 29, -29, 0});
    const bool is_positive_1 = none_of(vec_1.begin(), vec_1.end(), [](const int val) {return val > 0;});
    // FIXME: how to get compilieng for "std::ranges"? <-- error: ‘ranges’ is not a namespace-name
    //const bool is_positive_2 = std::ranges::none_of(vec_1, [](const int val) {return val > 0;});
    // assert(is_positive_1 == is_positive_2);
    // assert(is_positive_1); //! Eval: will this hold (for the inptu-data + fucnion)? why?
    assert(is_positive_1 == false);
    
    const bool someAreNegative = any_of(vec_1.begin(), vec_1.end(), [](auto val) {return val < 0;});
    assert(someAreNegative);
    int cnt_found = 0;
    //auto res =    find_if(vec_1.begin(), vec_1.end(), [&cnt_found](auto val) {const bool is_interesting = ( val < 0); if(is_interesting) {cnt_found++;};}); //! Eval: why does htis fail to compile?
    auto res =    find_if(vec_1.begin(), vec_1.end(), [&cnt_found](auto val) {const bool is_interesting = ( val < 0); if(is_interesting) {cnt_found++;}; return is_interesting;});
    cout << typeid(res).name() << endl;
    assert(cnt_found > 0);
    //for(auto val : res) {     } //! eval: why does this fail?
    //decltype(res) end = res + cnt_found;
    for(int index = 0; index < cnt_found; index++) {
      cout << "index[" + to_string(index) + "]="  << *res << endl; res++; // FIXME: is this a correct=Acceptabe straegy (for travesing an tierator)?
      //cout << "index[" + to_string(index) + "]="  << res->[index] << endl; // FIXME: how to get this to work=compile?
    }

    
  }
  { //! updating entries which match:
    vector<string> vec_1{"love", "high-five", "praising"};
    print("vec_1", vec_1);
    const auto res = find(begin(vec_1), end(vec_1), "high-five"); //! Eval: why can "res" be cosntant ... even though we udpate if (below)?
    //assert(res != nullptr);
    if(res != vec_1.end()) {
      *res = "high there!";
    }
    //!
    //! Step: use a C++17 version (of the above)
    if(const auto res = find(begin(vec_1), end(vec_1), "praising");
       res != end(vec_1)
       ) {
      *res = "praise Jesus";
    }
    print("vec_1 (after updates)=", vec_1);
  }
  { //! Working with diorianries:
    map<string, string> map_1{
			      {"jes", "ja"},
			      {"go", "leve"},
			      {"surprise", "opportunity"},
			      //{"", ""},
    };
    //auto res =
    //map_1.insert("yes", "ja!!!"); //! Eval: why does this not work?
    auto res = map_1.insert({"yes", "ja!!!"});
    auto [key, value] = res;
    cout << "key.type=" << typeid(key).name() << endl;
    cout << "res.value=" << value << endl; //! FIXME: why is the value=1 here??
    //cout << "res=" << key << ":" << value << endl;

    for(const auto &[key, value] : map_1) {
      cout << "res.value=" << value << endl;
    }

    //!
    auto res_2 = map_1.find("go");
    auto [key2, value2] = *res_2; // FIXME: why does this NOT work?
    cout << "res_2.type=" << typeid(*res_2).name()  << "; " << value2 << endl; //! https://cplusplus.com/reference/map/map/find/
    cout << "res.tuple=" << res_2->first << ", " << res_2->second << endl;
    //auto res_2 = find(begin(map_1), end(map_1), "go");
    
    if(auto [iter, is_ok] = map_1.insert({"go", "halleluja"}); is_ok) { //! eval: is this value iserted?
      cout << "insert successed: " << iter->second << endl;
    } else {
      cout << "iter failed" << endl;
    }
    if(auto [iter, is_ok] = map_1.insert({"jess", "halleluja"}); is_ok) { //! eval: is this value iserted?
      cout << "insert successed: " << iter->second << endl;
    } else {
      cout << "iter failed" << endl;
    }    
  }
  { //! Src:
    // namespace ranges = std::ranges;

  }
  { //! Src: 

  }
  { //! Src: 

  }      
  assert(false); // FIXME: complete this ... rewirt eht above 
}

int main() {
  // FIXME: a new exemplfe using:   https://stackoverflow.com/questions/16918231/using-out-of-scope-variables-in-c11-lambda-expressions
  // FIXME: a new exemplfe using: 
  //dummy();
  tut();
  // 
  // FIMXE: incldue the beloiw!
  // tut_generate();
  // tut_vectorOperations();
  // tut_vector_shared();
  //tut_scopeof_lambdaFunctions();
  return 1;
}
// FIXME: update our other exampels with [https://www.geeksforgeeks.org/lambda-expression-in-c/] ... thereafter, update this exmepal!
// FIXME: update our other exampels with [https://www.programiz.com/cpp-programming/lambda-expression] ... thereafter, update this exmepal!
// FIXME: update our other exampels with [https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170] ... thereafter, update this exmepal!
// FIXME: update our other exampels with [https://stackoverflow.com/questions/16918231/using-out-of-scope-variables-in-c11-lambda-expressions] ... thereafter, update this exmepal!
// FIXME: update our other exampels with [] ... thereafter, update this exmepal!
// FIXME: update our other exampels with [] ... thereafter, update this exmepal!
