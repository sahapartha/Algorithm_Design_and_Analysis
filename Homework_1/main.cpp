//Homework#1 - CS351
//main.cpp
//Author: (Partha Saha)
//         Date:
//         Homework#1, due date Feb. 5, 2020

#include <iostream>
#include <iomanip> //for formatting output
#include <chrono>
#include <unordered_map>
#include <vector>
#include <utility>
using namespace std;
using namespace std::chrono;

int fib_recursion(int n);
int fib_memoize(int n);
int fib_space_optimized(int n);

int algo1(vector<int> & myVec);
int algo2(vector<int> & myVec);
void algo3(vector<int> & myVec, vector<pair<int,int>> & myPair);

int main(int argc, const char * argv[]) {
    //Code for Task1
    int fib1, fib2, fib3;
    vector<int> input_size = {1, 5, 10, 15, 20, };
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double, std::milli> time_span1, time_span2, time_span3, algo1_time1, algo1_time2, algo1_time3, algo2_time1, algo2_time2, algo2_time3,algo3_time1, algo3_time2, algo3_time3;
    vector<pair<int,int>> myPair; //look up Pair-STL


    cout  << left<< setw(12) << setfill(' ') << "n"  ;
    cout  << left<< setw(12) << setfill(' ') << "Recursion";
    cout  << left<< setw(12) << setfill(' ') << "Time";
    cout  << left<< setw(12) << setfill(' ') << "Memoize";
    cout  << left<< setw(12) << setfill(' ') << "Time";
    cout  << left<< setw(12) << setfill(' ') << "Space_Optimized";
    cout  << left<< setw(12) << setfill(' ') << "Time";

    cout << endl;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout << endl;
    
    for (int & x : input_size){
        t1 = high_resolution_clock::now();
        fib1 = fib_recursion(x);
        t2 = high_resolution_clock::now();
        time_span1 = t2-t1;
        t1 = high_resolution_clock::now();
        fib2 = fib_memoize(x);
        t2 = high_resolution_clock::now();
        time_span2 = t2-t1;
        t1 = high_resolution_clock::now();
        fib3 = fib_space_optimized(x);
        t2 = high_resolution_clock::now();
        time_span3 = t2-t1;
        cout  << left<< setw(12) << setfill(' ') << x  ;
        cout  << left<< setw(12) << setfill(' ') <<  fib1  ;
        cout  << left<< setw(12) << setfill(' ') <<  time_span1.count() ;
        cout  << left<< setw(12) << setfill(' ') << fib2 ;
        cout  << left<< setw(12) << setfill(' ') << time_span2.count() ;
        cout  << left<< setw(12) << setfill(' ') << fib3  ;
        cout  << left<< setw(12) << setfill(' ') << time_span3.count() ;
        cout << endl;
    }

    cout << endl << endl;
//    Code for Task2
    vector<int> vec1(10,1);
    vector<int> vec2(500,1);
    vector<int> vec3(10000,1);
    t1 = high_resolution_clock::now();
    algo1(vec1);
    t2 = high_resolution_clock::now();
    algo1_time1 = t2-t1;
    t1 = high_resolution_clock::now();
    algo2(vec1);
    t2 = high_resolution_clock::now();
    algo1_time2 = t2-t1;
    t1 = high_resolution_clock::now();
    algo3(vec1, myPair);
    t2 = high_resolution_clock::now();
    algo1_time3 = t2-t1;
    
    t1 = high_resolution_clock::now();
    algo1(vec2);
    t2 = high_resolution_clock::now();
    algo2_time1 = t2-t1;
    t1 = high_resolution_clock::now();
    algo2(vec2);
    t2 = high_resolution_clock::now();
    algo2_time2 = t2-t1;
    t1 = high_resolution_clock::now();
    algo3(vec2, myPair);
    t2 = high_resolution_clock::now();
    algo2_time3 = t2-t1;
    
    t1 = high_resolution_clock::now();
    algo1(vec3);
    t2 = high_resolution_clock::now();
    algo3_time1= t2-t1;
    t1 = high_resolution_clock::now();
    algo2(vec3);
    t2 = high_resolution_clock::now();
    algo3_time2 = t2-t1;
    t1 = high_resolution_clock::now();
    algo3(vec3, myPair);
    t2 = high_resolution_clock::now();
    algo3_time3 = t2-t1;
    
    cout  << left<< setw(12) << setfill(' ') << "n"  ;
    cout  << left<< setw(12) << setfill(' ') << "Algo1";
    cout  << left<< setw(12) << setfill(' ') << "Algo2";
    cout  << left<< setw(12) << setfill(' ') << "Algo3";
    cout << endl;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout  << left<< setw(12) << setfill('-') << "-"  ;
    cout << endl;
    cout  << left<< setw(12) << setfill(' ') <<  vec1.size() ;
    cout  << left<< setw(12) << setfill(' ') << algo1_time1.count();
    cout  << left<< setw(12) << setfill(' ') << algo1_time2.count();
    cout  << left<< setw(12) << setfill(' ') << algo1_time3.count();
    cout << endl;
    cout  << left<< setw(12) << setfill(' ') <<  vec2.size() ;
    cout  << left<< setw(12) << setfill(' ') << algo2_time1.count();
    cout  << left<< setw(12) << setfill(' ') << algo2_time2.count();
    cout  << left<< setw(12) << setfill(' ') << algo2_time3.count();
    cout << endl;
    cout  << left<< setw(12) << setfill(' ') << vec3.size() ;
    cout  << left<< setw(12) << setfill(' ') << algo3_time1.count();
    cout  << left<< setw(12) << setfill(' ') << algo3_time2.count();
    cout  << left<< setw(12) << setfill(' ') << algo3_time3.count();
    cout << endl << endl;
}


int fib_recursion(int n){
    if(n==1)
    	return 1;
    if (n==2)
    	return 2;
    return fib_recursion(n-1) + fib_recursion(n-2);
}

int fib_space_optimized(int n){
    //complete your code here!
    return 0;
}

int fib_memoize(int n){
	int memoize[100];
	for(int i=1; i<=100; i++){
		memoize[i]= (-1);
	}
    memoize[1] = 0;
	memoize[2] = 1;
	if (memoize[n] != -1)
		return memoize[n];
	else{
		memoize[n] = fib_memoize(n-1) + fib_memoize(n-2);
		return memoize[n];
	}
		
}

int algo1(vector<int> & myVec){
    //complete your code here!
    //cout<<"\nFirst element: " <<myVec.at(0) <<endl;
    return myVec.at(0);
}

int algo2(vector<int> & myVec){
    //complete your code here!
    int sum=0;
    for(int i=0; i<myVec.size(); i++)
      sum= sum+myVec.at(i);
    //cout<<"\nsum: " <<sum <<endl;
    return sum;
}
void algo3(vector<int> & myVec, vector<pair<int,int>> & myPair){
    pair<int,int> aPair;
    //complete your code here!
    for(int i=0; i<myVec.size(); i++){
    	for(int j=0; j<myVec.size(); j++){
    		 //if(i==j){
          aPair.first =myVec.at(i);
          aPair.second = myVec.at(j);
    			myPair.push_back(aPair);
           //}
		}
    		
	}
}



