//
//  main.cpp
//  Project 3
//
//  Created by Jahan Cherian on 10/27/14.
//  Copyright (c) 2014 Jahan Cherian. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;

//*************************************
//  translateNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note translates to if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  translateNote(4, 'A', ' ') returns 'Q'
//            translateNote(4, 'A', '#') returns '%'
//            translateNote(4, 'H', ' ') returns ' '

char translateNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** translateNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}

bool isTuneWellFormed(string tune){ //Function that reurns true if the string is a well formed tune
    bool truth = false;     //truth is the return boolean that the function returns
    int numberOfBeats = 0;      //These are counters that are later used to test whether the string input is well formed or not
    int numberOfNotes = 0;
    int numberOfAccidentalSigns = 0;
    int numberOfOctaves = 0;
    for (int k = 0; k != tune.size(); k++) {    //for loop to loop through the entire string
        if (tune[k] == '/' ) {
            numberOfBeats++;
        }
        if (tune[k] == 'A'|| tune[k] == 'B' || tune[k] == 'C' || tune[k] == 'D' || tune[k] == 'E' || tune[k] == 'F' || tune[k] == 'G') //Checks to make sure it contains only the relevant alphabets that are characterised as notes.
        {
            numberOfNotes++;
            
            if (tune[k+1] == '#' ||tune[k+1] == 'b') { //checks for the two accidental sign cases.
                numberOfAccidentalSigns++;
            }
            if (isdigit(tune [k+1]) || isdigit(tune[k+2])){   //checks to see if the character next to the alphabet or the character two after the alphabet (in the cases of having an accidental sign) are digits.
                numberOfOctaves++;
            }
            if((tune[k+1] == '#' || tune[k+1] == 'b') && isdigit(tune[k+3])){ //checks to make sure there arent any numbers greater than 9 after the letter, if there is an accidental sign and then returns false.
                return false;
            }
            if (isdigit(tune[k+1]) && isdigit(tune[k+2])) { //checks to make sure there arent any numbers greater than 9 after the letter, and then returns false.

                return false;
            }
            if((tune[k+1] == '#' || tune[k+1] == 'b') && (tune[k+2] == '#' || tune[k+2] == 'b') ){//if the tune contains more than one accidental character in a single note, then return false.

                return false;
            }
            if(isdigit(tune[k+1]) &&((tune[k+2] == '#' || tune[k+2] == 'b') && (tune[k+3] == '#' || tune[k+3] == 'b'))){ //if the tune contains more than one accidental character in a single note, then return false.
                return false;
            }
        }
    if (tune[k] == 'a' || tune[k] == 'c' || tune[k] == 'd' || tune[k] == 'e' || tune[k] == 'f' || tune[k] == 'g' || tune[k] == 'h' || tune[k] == 'i' || tune[k] == 'j' || tune[k] == 'k' || tune[k] == 'l' || tune[k] == 'm' || tune[k] == 'n' || tune[k] == 'o' || tune[k] == 'p' || tune[k] == 'q' || tune[k] == 'r' || tune[k] == 's' || tune[k] == 't' || tune[k] == 'u'|| tune[k] == 'v' || tune[k] == 'w' || tune[k] == 'x' || tune[k] == 'y' || tune[k] == 'z' || tune[k] == 'H' || tune[k] == 'I' || tune[k] == 'J'|| tune[k] == 'K' || tune[k] == 'L' || tune[k] == 'M' || tune[k] == 'N' || tune[k] == 'O' || tune[k] == 'P' ||tune[k] == 'Q' || tune[k] == 'R' || tune[k] == 'S' || tune[k] == 'T' || tune[k] == 'U' || tune[k] == 'V' || tune[k] == 'W' || tune[k] == 'X'|| tune[k] == 'Y' || tune[k] == 'Z') {     //Checks to make sure that if any non valid letter is put in, then this function returns false.
            return false;
        }
        if((ispunct(tune[k]) && (tune[k] != '#' && tune[k] != 'b' && tune[k] != '/'))){ //checks to make sure there isnt any random characters such as .?',> in the string.
            return false;
        }
        if(tune[k] == '/' && isdigit(tune[k+1])){ //if the string ever contains a random set of numbers with no associated Note, then immediately return false.
            return false;
        }
        if(tune[k] == ' '){ //if the tune ever contains a space character, return false.
            return false;
        }
        
    }
    if (isdigit(tune[0])) { //if the string starts off with a sequence of numbers, immediately return false.
        return false;
    } else if (tune.empty()){ //if the string is empty, return true.
        return true;
    }else if (numberOfBeats >= 1 && numberOfNotes >= 1 && numberOfOctaves >= 0 && numberOfAccidentalSigns >= 0) { //true for any valid note with any digit and accidental sign
        truth = true;
    }else if (numberOfBeats == tune.size()){ //true for a string of just beats (forward slashes)
        return true;
    }
    if (tune[tune.size()-1] != '/') {   //checks for a beat (forward slash) is always there at the end of the string.
        return false;
    }
    return truth;   //returns the final value of the boolean truth
}

bool isPlayableTune (string tune){  //A boolean function that checks if the tune is playable given that its well formed.
    bool truth = true;
    if (isTuneWellFormed(tune)){
        for (int k = 0; k != tune.size(); k++){ //for loop to loop through the entire string
            if(tune[k] == '0' || tune[k] == '1' || tune[k] == '6' || tune[k] == '7' || tune[k] == '8' || tune[k] == '9'){ //checks to see if there are any non valid digits as octaves, since Button Bass only takes in between 2nd and 5th octaves.
                truth = false;
            }
            if(tune[k] == 'C' && (tune[k+1] == 'b' && tune[k+2] == '2')){ //the single case wherein Cb2 is not playable.
                truth = false;
            }
            //The following 3 if statements basically take in the 3 cases that should work but wouldnt under playable conditions, and thus changes them to their playable counterparts.
            
            if (tune[k] == 'B' && (tune[k+1] == '#' && tune[k+2] == '1') ) {
                tune[k] = 'C';
                tune[k+1]= '2';
                tune[k+2]= ' ';
                truth = true;
            }
            if (tune[k] == 'C' && (tune[k+1] == 'b' && tune[k+2] == '6')) {
                tune[k] = 'B';
                tune[k+1]= '5';
                tune[k+2]= ' ';
                truth = true;
            }
            if (tune[k] == 'C' && tune[k+1] == '6') {
                tune[k] = 'B';
                tune[k+1]= '#';
                tune[k+2] = '5';
                truth = true;
            }
          
        }
    }else if (!isTuneWellFormed(tune)){ //if the tune is not wellformed then simply return false implying it cannot be played under any condition
        truth = false;
    }
    return truth;   //returns the final value of the boolean truth
}


int translateTune(string tune, string& instructions, int& badBeat){
    int translate = 0;
    int numberOfNotes = 0;
  
    if(isPlayableTune(tune)){   //makes sure to first ensure that the string is well formed and playable.
        instructions = "";  //initialises instructions to an empty string
        if(tune[0] == '/'){ //if the tune starts with a beat, then automatically add a space.
            instructions += ' ';
        }
        for (int k = 0; k != tune.size(); k++) { //for loop to loop through the entire string
    
            if (isalpha(tune[k]) && tune[k] != 'b') { //checks to see if the character is a valid alphabet as long as it isnt b which is considered accidental.

                //checks if the note has an accidental sign only and no octave. Example: A#, Bb, F# (Default octave of 4 given)
                if ((tune[k+1] == '#' || tune[k+1] == 'b') && !isdigit(tune[k+2])) {
                    instructions += translateNote(4, tune[k], tune[k+1]);   //calls on translate the note with default octave of 4.
                    numberOfNotes++;
                }
                
                //checks if the note has an accidental sign only and an octave. Example: A#3, Bb5, F#2
                else if ((tune[k+1] == '#' || tune[k+1] == 'b') && isdigit(tune[k+2])) {
                    int num_ch = tune[k+2] - '0'; //for the octave character, this converts the character into its counterpart integer and then uses it in translateNote.
                    instructions += translateNote(num_ch, tune[k], tune[k+1]);
                    numberOfNotes++;
                }
                
                //checks if the note has no accidental sign and only an octave. Example: A3, B5, F2
                else if (isdigit(tune[k+1])) {
                    int num_ch = tune[k+1] - '0';  //for the octave character, this converts the character into its counterpart integer and then uses it in translateNote.
                    instructions += translateNote(num_ch, tune[k], ' ');
                    numberOfNotes++;
                }
                
                //checks if the note has no accidental sign and no octave. Example: A, B, F (Default octave of 4 given)
                else if (!(tune[k+1] == '#' || tune[k+1] == 'b') && !isdigit(tune[k+2])){
                    instructions += translateNote(4, tune[k], ' ');
                    numberOfNotes++;
                }
                
                else {
                    instructions += translateNote(4, tune[k], ' ');
                    numberOfNotes++;
                }
            }
            
            // for the case of having double beats to add a space in between the instruction string
            if (tune[k] == '/' && tune[k+1] == '/') {
                instructions += ' ';
                numberOfNotes =0;
            }
            
            if (tune [k] == '/'){
                numberOfNotes = 0;
            }
            
            //If the string tune contains multiple notes between beats (i.e. is a chord) then add square brackets around the translation for that part.
           if (tune[k+1] == '/' && numberOfNotes > 1){
               instructions =  instructions + ']';
               instructions.insert(instructions.size() - (numberOfNotes + 1), 1,'[');
               numberOfNotes = 0;
            }
        }
        translate = 0;      //return 0 as defined in the spec
    }
    
    //if not well formed then return 1 as defined in the spec
    else if (!isTuneWellFormed(tune)) {
        translate = 1;
    }
    
    //if the tune is well formed but is not playable then it creates a counter for the number of beats and then when it finds an error, it puts the badbeat to the number of beat where it finds the error.
    else if (isTuneWellFormed(tune) && !isPlayableTune(tune)){
        int numberOfBeats = 1;
        for (int k = 0; k != tune.size(); k++) { //for loop to loop through the entire string
            if(tune[k] == '/'){
                numberOfBeats++;
            }
            if (tune[k] == '0' || tune[k] == '1' || tune[k] == '6' || tune[k] == '7' || tune[k] == '8' || tune[k] == '9' || (tune[k] == 'C' && (tune[k+1] == 'b' && tune[k+2] == '2'))) {
                badBeat = numberOfBeats;
                break;
            }
        }
        translate = 2;      //returns 2 as defined in the spec
    }
        return translate;
}

void testTranslate(string tune) //A test function to debug and output the translation of the string/give the position of badbeat and test if well formed and playable.
{
    string instr;
    int badBeat;
    cout<<"Tune: "<<tune<<endl;
    
    int resultNumber = translateTune(tune, instr, badBeat);
    
    switch(resultNumber)
    {
        case 0:
            cout<<"YAY! Tune is Well formed and playable"<<endl;
            cout<<"translation:"<<instr<<endl;
            break;
        case 1:
            cout<<"Sorry! Tune is Not well formed"<<endl;
            break;
        case 2:
            cout<<"Sorry! The Tune is Well formed but not playable"<<endl;
            cout<<"The bad beat is at position: "<<badBeat<<endl;
            break;
        default:
            cout << "Internal program error! We Shouldnt get here!" << endl;
            break;
    }
    
}
int main() {
    for(;;){    //allows for continous running until force stopped, for easier debugging.
    string beat;
    cout << "Enter a beat:";
    getline (cin, beat);
    cout << "Verdict for well formed " << isTuneWellFormed(beat) << endl;   //reconfirmation of whether is well formed (returns 1 for true and 0 for false)
    cout << "Verdict for playable " << isPlayableTune(beat) << endl;    //reconfirmation of whether is playable (returns 1 for true and 0 for false)
    testTranslate(beat);    //actually outputs the test function outcome.
    }
}
