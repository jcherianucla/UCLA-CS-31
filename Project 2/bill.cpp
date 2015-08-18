//
//  main.cpp
//  Project 2
//
//  Created by Jahan Cherian on 10/15/14.
//  Copyright (c) 2014 Jahan Cherian. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[])
{
    int textAfter = 0;      //Initialises an integer that takes into account the amount of texts after 200 to zero.
    double basePrice = 40;  // The basePrice on which the extra bill gets added onto.
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);      // To set the baseprice to a dollar amount with two decimal points.
    
    cout << "Minutes used: ";   //Takes in the amount of minutes the customer uses.
    int minsUsed;
    cin >> minsUsed;
    
    cout << "Text messages: ";  //Takes in the amount of text messages the customer uses.
    int text;
    cin >> text;
    cin.ignore(10000, '\n');    //Going from integer to string and therefore have to throw out the new line.
    
    cout << "Customer name: ";  //Takes in the customers name.
    string name;
    getline(cin, name);
    
    cout << "Month number (1=Jan, 2=Feb, etc.): ";  //Reads in the Month number.
    int month;
    cin >> month;
    cin.ignore(10000, '\n');
    
    
    cout << "---" << endl;
    
    if (minsUsed > 500){ //This if block is used to increase the base price depending on how many minutes are used passed 500.
        int minsAfter = minsUsed - 500;
        basePrice = basePrice +(0.45 * minsAfter);
    }
    
    if (text > 200 && ((month >= 10 && month <= 12) || (month >=1 && month <=5))){ //The boolean expression check to see if texts exceed 200 and that the months are from october to may.
        textAfter = text - 200;
        basePrice = basePrice + (0.03 * textAfter);
        if (text > 400){    //This is for when the text exceeds 400 then 0.11 cent gets added onto the bill per message.
            textAfter = text - 400;
            basePrice = basePrice + (0.11 * textAfter) - (0.03 * textAfter);
        }
    }
    else if (text > 200 && (month >= 6 && month <= 9)){ //This checks if its between june and september
        textAfter = text - 200;
        basePrice = basePrice + (0.02 * textAfter);
        if (text > 400){
            textAfter = text - 400;
            basePrice = basePrice + (0.11 * textAfter) - (0.02 * textAfter);
        }
    }
    
    if (minsUsed <0) {     //The following statements check to see if there are any errors.
        cout << "The number of minutes used must be nonnegative." << endl;
    }else if (text < 0){
        cout << "The number of text messages must be nonnegative." << endl;
    }else if (name == ""){
        cout << "You must enter a customer name." << endl;
    }else if (month > 12 || month < 1){
        cout << "The month number must be in the range 1 through 12." << endl;
    }
    if(minsUsed >=0 && text >= 0 && name != "" && month >= 1 && month <=12) { //if there are none of the errors listed, then the bill will be shown.
        cout << "The bill for " << name << " is $" << basePrice << endl;
    }
}
    

