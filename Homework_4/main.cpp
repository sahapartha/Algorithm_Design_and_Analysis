//Homework#4 - CS351
//main.cpp
//Author: (student's name here)
//         Date:
//         Homework#4, due date May. 10, 2020
//
//  Created by Thitima Srivatanakul on 4/24/20.
//  Copyright © 2020 Thitima Srivatanakul. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <fstream> //filestream
#include <vector>
using namespace std;

long lcs_lengths(string x, string y, long m, long n){
    //Implement code based exactly on this algorithm (from CLRS book)
    //We will discard matrix b though
    
    //let c[0..m, 0..n] be new tables
    //for i = 1 to m
    //   c[i,0] = 0
    //for j = 0 to n
    //   c[0,j] = 0
    //for i = 1 to m
    //   for j = 1 to n
    //       if xi == yj
    //          c[i,j] = c[i-1, j-1] + 1
    //       else if c[i-1, j] >= c[i, j-1]
        //          c[i,j] = c[i-1,j]
        //       else c[i,j] = c[i,j-1]
    //return the length of LCS
    
    //Use this way to initialize the matrix c
    //Do not change this!
    std::vector<std::vector<int>> c;
    c.resize(m+10, std::vector<int>(n+10, 0));
    //e.g. accessing an element in matrix c => c[0][0]
    
    //Implement your code here!!!
    long result;
    c[m][n];
    for(int i = 0; i<=m; i++){
      c[i][0] = 0;
    }
    for(int j= 0; j<=n; j++){
      c[0][j] = 0;
    }
    for (int i=1; i<=m; i++){
      for (int j=1; j<=n; j++){
        if (x[i]==y[j]){
            c[i][j]=c[i-1][j-1] + 1;
        }
        else if (c[i-1][j]>=c[i][j-1]){
           c[i][j]=c[i-1][j];
        }
        else{
          c[i][j]=c[i][j-1];
        }
      }
      
    }
    result=c[m][n];
    return result;
    

    //You can use this for debugging and testing
    //This will output the c matrix in LCS-output.txt
//    std::ofstream ofs("LCS-output.txt");
//        for (int i = 0 ; i<= m ; i++){
//            ofs << endl;
//            for (int j =0; j<=n; j++){
//                ofs << c[i][j] << " ";
//            }
//        }

   // return 0; //change this line

}


int main(int argc, const char * argv[]) {
    long size_str1, size_str2;
    
    //reads file content into string
    std::ifstream dataFile("sequence4.txt"); // replace the file name with other sequences
    std::string string1( (std::istreambuf_iterator<char>(dataFile)),
                        (std::istreambuf_iterator<char>()) );

    std::ifstream dataFile2("coronavirus_genome.txt");
    std::string string2( (std::istreambuf_iterator<char>(dataFile2)),
                        (std::istreambuf_iterator<char>()) );
    
    //remove new line and other white spaces from string
    string1.erase(std::remove(string1.begin(), string1.end(), '\n'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), '\r'), string1.end());
    string1.erase(std::remove(string1.begin(), string1.end(), ' '), string1.end());
    string2.erase(std::remove(string2.begin(), string2.end(), '\n'), string2.end());
    string2.erase(std::remove(string2.begin(), string2.end(), '\r'), string2.end());
    string2.erase(std::remove(string2.begin(), string2.end(), ' '), string2.end());

    
    //Use the following as test cases
    // LCS for "ant" and "atom" is 2
//    string1 = "0ant";
//    string2="0atom";

    // LCS for "pioneer" and "springtime" is 4
//    string1 = "0pioneer";
//    string2="0springtime";
    
    // LCS for "GFSGTGUGFSG" and "ZGFFGUGFFGUEH" is 7
//        string1 = "0GFSGTGUGFSG";
//        string2="0ZGFFGUGFFGUEH";
    
    

    //Also, we'll start counting the string from index 1. Character at index 0 was added as a dummy, so that we can still use the algorithm from the book (starts at index 1).
    //Therefore the total size will be one character more than the actual size of the string
    //If you want to modify string1 and string2 so that you can run tests
    //It needs to be in this format string1 = "0pioneer"; string2="0springtime";
    size_str1 = string1.size()-1;
    size_str2 = string2.size()-1;
    
    //You can access each character of the string with an index, e.g.
//        cout << "Character at the end of the string is: " << string1[size_str1] << endl;
//        cout << "String1 is:" << string1 << endl;
    
    cout << "Length of the first string is: " << size_str1 << endl;
    cout << "Length of the second string is: " << size_str2 << endl;
    cout << "LCS of the first and second string is: ";
    
    cout << lcs_lengths(string1, string2,size_str1,size_str2) << endl;

    return 0;
}
