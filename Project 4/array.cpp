//
//  main.cpp
//  Project 4
//
//  Created by Jahan Cherian on 11/8/14.
//  Copyright (c) 2014 Jahan Cherian. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//all the function prototypes

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

void printArray(string list[], int listSize){   //a print array function to be able to check that arrays are correctly manipulated in the debugging process
    for(int i=0;i<listSize;i++){
        cout<<list[i];
    }
    cout<<endl;
}

int main() {        //a main function that goes through each function, the tests may not look thorough, because they are individually constantly changed. Also contains the assert tests from the spec
    // Test appendToAll
    
    string a[5] = { "glenn", "carl", "carol", "rick", "" };
    assert(appendToAll(a, -1, " ") == -1);                                      // negative n
    assert(appendToAll(a, 3, " ") == 3 && a[0] == "glenn " && a[4] == "");      // check before and after
    assert(appendToAll(a, 0, "sup") == 0 && a[3] == "rick");                    // n = 0
    assert(appendToAll(a, 5, "hi") == 5 && a[3] == "rickhi");                   // regular append
    
    // Test lookup
    
    string h[8] = { "glenn", "carl", "carol", "rick", "", "maggie", "daryl", "rick" };
    assert(lookup(h, 7, "maggie") == 5);            // regular
    assert(lookup(h, 7, "carol") == 2);             // regular
    assert(lookup(h, -1, "carol") == -1);           // n < 0
    assert(lookup(h, 2, "carol") == -1);            // not in array
    assert(lookup(h, 0, "carl") == -1);             // n = 0
    
    // Test positionOfMax
    
    assert(positionOfMax(h, 7) == 3);       // regular
    assert(positionOfMax(h, -1) == -1);     // negative n
    assert(positionOfMax(h, 0) == -1);      // n = 0
    assert(positionOfMax(h, 8) == 3);       // multiple of same string
    
    // Test rotateLeft
    
    string b[5] = { "one", "two", "three", "four", "five" };
    assert(rotateLeft(b, -1, 2) == -1);                                         // negative n
    assert(rotateLeft(b, 4, -1) == -1);                                         // negative pos
    assert(rotateLeft(b, 0, 0) == -1 && b[2] == "three" && b[4] == "five");     // n = 0, pos = 0
    assert(rotateLeft(b, 0, 2) == -1 && b[2] == "three" && b[4] == "five");     // pos > n
    assert(rotateLeft(b, 2, 0) == 0 && b[0] == "two" && b[1] == "one");         // regular - first pos
    assert(rotateLeft(b, 2, 2) == -1);                                          // n = pos
    
    b[0] = "one"; b[1] = "two"; b[2] = "three"; b[3] = "four"; b[4] = "five";
    
    assert(rotateLeft(b, 5, 4) == 4 && b[2] == "three" && b[4] == "five");      // regular - last pos
    assert(rotateLeft(b, 5, 2) == 2 && b[2] == "four" && b[4] == "three");      // regular
    
    // Test rotateRight
    
    string c[5] = { "one", "two", "three", "four", "five" };
    assert(rotateRight(c, -1, 2) == -1);                                        // negative n
    assert(rotateRight(c, 4, -1) == -1);                                        // negative pos
    assert(rotateRight(c, 0, 0) == -1 && c[2] == "three" && c[4] == "five");    // n = 0, pos = 0
    assert(rotateRight(c, 0, 2) == -1 && c[2] == "three" && c[4] == "five");    // pos > n
    assert(rotateRight(b, 2, 2) == -1);                                         // n = pos
    assert(rotateRight(c, 5, 0) == 0 && c[2] == "three" && c[4] == "five");     // regular - first pos
    assert(rotateRight(c, 5, 2) == 2 && c[2] == "two" && c[0] == "three");      // regular
    
    c[0] = "one"; c[1] = "two"; c[2] = "three"; c[3] = "four"; c[4] = "five";
    
    assert(rotateRight(c, 5, 4) == 4 && c[2] == "two" && c[0] == "five");       // regular - last pos
    
    
    // Test flip
    
    string d[5] = { "one", "two", "three", "four", "five" };
    assert(flip(d, -1) == -1);                                                          // negative n
    assert(flip(d, 0) == 0 && d[3] == "four");                                          // n = 0
    assert(flip(d, 4) == 4 && d[0] == "four" && d[2] == "two");                         // even n
    
    d[0] = "one"; d[1] = "two"; d[2] = "three"; d[3] = "four"; d[4] = "five";
    
    assert(flip(d, 5) == 5 && d[2] == "three" && d[3] == "two");                        // odd n
    
    
    // Test differ
    
    d[0] = "one"; d[1] = "two"; d[2] = "three"; d[3] = "four"; d[4] = "five";
    string i[6] = { "one", "two", "3", "four", "five", "6" };
    
    assert(differ(d, -1, i, -1) == -1);                                     // negative n1 and n2
    assert(differ(d, -1, i, 5) == -1);                                      // negative n1
    assert(differ(d, 5, i, -1) == -1);                                      // negative n2
    assert(differ(d, 0, i, 5) == 0);                                        // n1 = 0
    assert(differ(d, 5, i, 0) == 0);                                        // n2 = 0
    assert(differ(d, 5, i, 6) == 2 && d[2] == "three" && i[2] == "3");      // regular
    assert(differ(d, 0, i, 0) == 0);                                        // n1 = 0 and n2 = 0
    assert(differ(d, 1, i, 1) == 1);                                        // not found, same value
    assert(differ(d, 1, i, 2) == 1);                                        // not found, n2 greater
    assert(differ(d, 2, i, 1) == 1);                                        // not found, n1 greater
    
    
    // Test subsequence
    
    string j[3] = { "two", "3", "four" };
    
    assert(subsequence(i, -1, j, -1) == -1);                                    // negative n1 and n2
    assert(subsequence(i, -1, j, 3) == -1);                                     // negative n1
    assert(subsequence(i, 5, j, -1) == -1);                                     // negative n2
    assert(subsequence(i, 0, j, 3) == -1);                                      // n1 = 0
    assert(subsequence(i, 3, j, 0) == 0);                                       // n2 = 0
    assert(subsequence(i, 2, j, 3) == 1 && d[2] == "three" && i[2] == "3");     // regular
    assert(subsequence(i, 0, j, 0) == 0);                                       // n1 = 0 and n2 = 0
    assert(subsequence(i, 1, j, 1) == -1);                                      // not found
    assert(subsequence(i, 1, j, 2) == -1);                                      // not found, n2 > n1
    
    
    // Test lookupAny
    
    assert(lookupAny(i, -1, j, -1) == -1);                                      // negative n1 and n2
    assert(lookupAny(i, -1, j, 3) == -1);                                       // negative n1
    assert(lookupAny(i, 5, j, -1) == -1);                                       // negative n2
    assert(lookupAny(i, 0, j, 3) == -1);                                        // n1 = 0
    assert(lookupAny(i, 3, j, 0) == -1);                                        // n2 = 0
    assert(lookupAny(i, 2, j, 3) == 1 && d[2] == "three" && i[2] == "3");       // regular
    assert(lookupAny(i, 0, j, 0) == -1);                                        // n1 = 0 and n2 = 0
    assert(lookupAny(i, 1, j, 1) == -1);                                        // not found
    assert(lookupAny(i, 1, j, 2) == -1);                                        // not found, n2 > n1
    
    
    // Test separate
    
    string m[6] = { "b", "f", "d", "a", "e", "c" };
    
    assert(separate(m, -1, "cat") == -1);                                       // negative n
    assert(separate(m, 0, "cat") == 0);                                         // n = 0
    assert(separate(m, 3, "cat") == 1);                                         // regular, not all values
    m[0] = "b"; m[1] = "f"; m[2] = "d"; m[3] = "a"; m[4] = "e"; m[5] = "c";
    
    assert(separate(m, 6, "dog") == 4);                                         // regular, all values
    m[0] = "b"; m[1] = "f"; m[2] = "d"; m[3] = "a"; m[4] = "e"; m[5] = "c";
    
    assert(separate(m, 6, "cat") == 3);                                         // regular, all values
    m[0] = "b"; m[1] = "f"; m[2] = "d"; m[3] = "a"; m[4] = "e"; m[5] = "c";
    
    assert(separate(m, 4, "z") == 4);                                           // Not separated
    assert(separate(m, 4, "b") == 1);                                           // separator is in array
    
    
    // Extra Tests
    
    string g[4] = { "glenn", "carl", "rick", "maggie" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "glenn?" && g[3] == "maggie?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "rick?" && g[3] == "carl?");
    
    string e[4] = { "carol", "rick", "", "maggie" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(rotateRight(e, 4, 1) == 1 && e[0] == "rick" && e[2] == "");
    
    string f[3] = { "rick", "carol", "tara" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tara" && f[2] == "rick");
    
    assert(separate(h, 7, "daryl") == 3);
    
    cout << "All tests succeeded" << endl;
    
   /* int result;
    int result2;
    int position;
    string test[6] = {"glenn", "carl", "carol", "rick", "maggie", "daryl"};
    result = appendToAll(test, 6, "!!!");
    cout << "Result for Append To all is: " << result << endl;
    printArray(test, 6);
    cout << endl;
    string test2[5] = {"rick", "daryl", "john", "daryl", " "};
    result2 = lookup(test2, 5, "daryl");
    cout << "Result2 for lookup is: "<< result2 << endl;
    position = positionOfMax(test, 3);
    cout << "Position of PositionOf Max is: " << position << endl;
    string characters[8] = { "rosita ", "bob ", "sasha ", "glenn ", "michonne ", "jahan ", "kultar ", "robert "};
    int m = rotateLeft(characters,5, 4);
    cout << "Result for the RotateLeft of characters is: "<< m << endl;
    printArray(characters, 8);
    string characters2[5] = { "rosita ", "bob ", "sasha ", "glenn ", "michonne "};
    int p = rotateRight(characters2, 5, 3);
    cout << "Result for the RotateRight of characters2 is: "<< p << endl;
    printArray(characters2, 5);
    string roles[6] = { "abraham", "tara", "", "daryl", "carol", "tyreese" };
    string group[5] = { "abraham", "tara", "tyreese", "", "maggie" };
    int r = differ(roles, 2, group, 2);
    cout <<"Result for the difference is: "<<  r << endl;
    string names[10] = { "bob", "rick", "beth", "glenn", "bob", "michonne" };
    string set1[10] = { "rick", "bob", "glenn", "rick" };
    int v = lookupAny(names, 6, set1, 4);
    cout << "Result for LookUpAny: " << v << endl;
    string set2[10] = { "daryl", "carol" };
    int w = lookupAny(names, 6, set2, 2);
    cout << w;
    string roles2[6] = { "abraham ", "tara ", " ", "daryl ", "carol ", "tyreese " };
    int q = flip(roles2, -3);
    printArray(roles2, 6);
    cout << q;
    string names0[10] = { "sasha", "rick", "beth", "glenn", "bob", "michonne", "beth","glenn" };
    string names1[10] = { "beth", "glenn" };
    int t = subsequence(names0, 1, names1, 2);
    cout << t<< endl;
    string names2[10] = { "rick" };
    int u = subsequence(names0, 5, names2, 1);
    cout << u << endl;
    string cast[6] = { "maggie", "carl", "daryl", "rick", "michonne", "carol" };
    int x = separate(cast, 6, "glenn");
    printArray(cast, 6);
    cout << x;
    string cast2[4] = { "carol ", "rick ", "michonne ", "daryl " };
    int y = separate(cast2, 4, "daryl ");
    printArray(cast2, 4);
    cout << y;
    
    string h[7] = { "glenn", "carl", "carol", "rick", "", "maggie", "daryl" };
    assert(lookup(h, 7, "maggie") == 5);
    assert(lookup(h, 7, "carol") == 2);
    assert(lookup(h, 2, "carol") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "glenn", "carl", "rick", "maggie" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "glenn?" && g[3] == "maggie?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "rick?" && g[3] == "carl?");
    
    string e[4] = { "carol", "rick", "", "maggie" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(rotateRight(e, 4, 1) == 1 && e[0] == "rick" && e[2] == "");
    
    string f[3] = { "rick", "carol", "tara" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tara" && f[2] == "rick");
    
    assert(separate(h, 7, "daryl") == 3);
    
    cout << "All tests succeeded" << endl;*/
   }

int appendToAll(string a[], int n, string value){   //function to append the value to each string in the array
    if (n >= 0){
    for(int i = 0; i < n; i++){     //run through the array and add on value to the end of each string
        a[i] += value;
    }
        return n;
    }
    return -1;      //if n is less than 0 then always return -1
}

int lookup(const string a[], int n, string target){     //looks up target in the array of string and returns its index
    for(int i = 0; i < n; i++){
        if(a[i] == target){     //when the loop reaches target in the array (if it is there) then it returns the lowest position
            return i;
        }
    }
    return -1;      //if the target is not found or if n is less than 0 then returns -1.
}

int positionOfMax(const string a[], int n){     //finds the position of the largest string by ASCII comparison within the array
    string largest = a[0];      //stores the first string as largest
    string current;
    int maxIndex = 0;       //assumes the largest string is the first string
    if(n<=0){   //if no elements or if n less than 0 then return -1
        return -1;          //if no elements in the array then it returns -1
    }
    for(int i=0;i<n; i++){  //This loop basically checks if the current string is greater than the largest then fix maxIndex to its position and set it as largest
        current = a[i];
        if(current > largest){  //Because the if statement uses > and not >= it will always return the smallest position of the largest
            maxIndex = i;
            largest = current;
        }
        
    }
    return maxIndex;        //returns the index of the largest positioned string
}

int rotateLeft(string a[], int n, int pos){ //rotates the strings in the array such that the strings before that at the defined position are moved to the left of the specific element
    if (pos < 0 || pos >= n || n <=0){       //if an invalid position such as a negative value is given or if there are no elements in the array, return -1
        return -1;
    }
    string extra = a[pos];      //use a storage variable to store the string at a the defined position
    for (int i = 0 ; i < n ; i++){
        if(i == pos){
            for(int k=pos; k<n-1; k++){
                a[k] = a[k+1];      //go through the array again and replace each string at an index with the string at the next index
            }
            a[n-1]=extra;       //the last defined position stores the string at the position from where it was initially moved
            return pos;
        }
    }
    return -1;
}

int rotateRight(string a[], int n, int pos){ //rotates the strings in the array such that the strings before that at the defined position are moved to the right of the specific element
    if (pos < 0 || pos >= n || n <=0){       //if an invalid position such as a negative value is given or if there are no elements in the array, return -1
        return -1;
    }
    string extra = a[pos];      //use a storage variable to store the string at a the defined position
    for (int i = 0 ; i < n ; i++){
        if(i == pos){
            for(int k=pos; k>0; k--){
                a[k] = a[k-1];      //go through the array again and replace each string at an index with the string at the index before it
            }
            a[0]=extra;         //the first defined position stores the string at the position from where it was initially moved
            return pos;
        }
    }
    return -1;
}


int flip(string a[], int n){    //from the beginning to the value n, reverse the order of all the elements in the array
    if(n<0){
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(i == n/2){           //when the iterator reaches half of n (odd or even) break because at this point all the elements are already reversed
            break;
        }
        string extra = a[i];        //storage variable to store the value of the elements being replaced and reversed during each iteration of the loop
        a[i] = a[n-(i+1)];          //reverses each relevant string with its opposite counterpart
        a[n-(i+1)] = extra;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){   //finds the position of the point where the arrays are no longer equal
    int verdict = -1;
    if(n1 >= n2){       //deals with if n1 is bigger than n2
        if(n2 == 0){
            verdict = n2;
        }
    for(int i = 0; i < n2; i++){
        if(a1[i] != a2[i]){     //finds the point where the elements in the arrays are no longer equal
            return i;
        } else {            //otherwise if the strings are equal or one runs out, return the smaller which for this case is n2
            verdict = n2;
            }
        }
    }
    else if (n1 < n2){  //deals with if n2 is bigger than n1
        if(n1 == 0){
            verdict = n1;
        }
    for(int i = 0; i < n1; i++){
        if(a1[i] != a2[i]){     //finds the point where the elements in the arrays are no longer equal
            return i;
        } else {
            verdict = n1;   //otherwise if the strings are equal or one runs out, return the smaller which for this case is n1
            }
        }
    }
    return verdict;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){      //finds a continuous sequence from all of a2 if it appears in a1
    int iPos;
    bool verdict = false;   //use a boolean variable to be able to add extra check conditions
    int startPoint;
    
    for (int i = 0; i < n1; i++){
        if (a1[i] == a2[0]){    //checks if any point in in a1 is the same as the start of a2
            startPoint = i;
            for (int j = 0, iPos = i; j < n2; j++, iPos++){     //goes through a2 and a1 simultaneously where iPos stores the location index of a1
                verdict = true;
                if (a2[j] != a1[iPos]){     //the moment it is not equal then break
                    verdict = false;
                    break;
                }
            }
            if (verdict){           //if the verdict is true then return the smallest position of the start of the continuous sequence in a1
                return startPoint;
            }
        }
    }   if(n2 == 0){        //if there are no elements then it is still technically a subsequence of any array sequence and as such 0 will be returned
        return 0;
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){    //goes through a1 and checks to see if any of the terms in a2 are within a1
    for(int i = 0; i < n1; i++){
            for(int k = 0; k<n2; k++){  //while going through a1 check each term in a1 with all the terms in a2 and then iterate, if there are equal terms then return the smallest position
                if(a1[i] == a2[k]){
                    return i;
                }
            }
    }
    return -1;
}


 int separate(string a[], int n, string separator){        //based on the value of the separator, the function arranges all the strings in order of less than and greater than the separator
     int verdict;
     if(n<0){
         return -1;
     }
     int counter = 0;         //a variable initialised as a counter
     for(int i = 0; i < n; i++){
         if(a[i] > separator){      //checks to see if there is an element greater than the separator
             string extra = a[i];   //stores that specific string in a storage variable
                for(int k=i; k<n-1; k++){       //similar to the rotateLeft function, all those strings that are greater than the separator are moved to the end on the string
                    a[k] = a[k+1];
                }
            a[n-1]=extra;
            i--;           //iterates down to check all the elements even after reversal
            counter++;
            if(counter == n){
                if(a[i-1] > a[i]){          //This takes care of the case if we have an element equal to the separator and makes sure that this element becomes the last element before the elements > than separator come
                    string lastCaseShift = a[i];
                    a[i] = a[i-1];
                    a[i-1] = lastCaseShift;
                }
                verdict = i +1;     //when the counter the reaches the size of n, we return the position of the first element > than the separator
                if(a[i] == separator && a[i-1] != separator){ //however if the element is equal to the separator we return the position of the separator
                    verdict = i;
                }
                if(a[0] > separator){   //if all the elements are greater than the separator then return n
                    verdict = n;
                }
                return verdict;
              }
         }
    }
     return n;
}
