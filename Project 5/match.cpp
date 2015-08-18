//
//  main.cpp
//  Project 5
//
//  Created by Jahan Cherian on 11/16/14.
//  Copyright (c) 2014 Jahan Cherian. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;     //the defined maximum length of a match rule
const int DOCUMENT_LIMIT = 200;     // the defined maximum length of an entire document


//------------------Start of Function prototypes-------------------

int standardizeRules(int distance[],
                     char word1[][MAX_WORD_LENGTH+1],
                     char word2[][MAX_WORD_LENGTH+1],
                     int nRules);
int determineQuality(const int distance[],
                     const char word1[][MAX_WORD_LENGTH+1],
                     const char word2[][MAX_WORD_LENGTH+1],
                     int nRules,
                     const char document[]);

void printMatchRules(int distance[],
                     char word1[][MAX_WORD_LENGTH+1],
                     char word2[][MAX_WORD_LENGTH+1],
                     int nRules);

void printOtherArray(char revisedMultiDocument[][DOCUMENT_LIMIT+1], int n);

void refreshDocument(char revisedDocument[], int n);

void refreshMultiDocument(char revisedMultiDocument[][DOCUMENT_LIMIT+1], int n);


bool determineMatchRule(int distance,
                        const char word1[],
                        const char word2[],
                        int index,
                        int jump,
                        char revisedMultiDocument[][DOCUMENT_LIMIT +1]);

//------------------End of Function prototypes-------------------

int main() {                            //Test cases within the main function
    const int TEST0_NCRITERIA = 4;
    int test0dist[TEST0_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test0w1[TEST0_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "swag", "nefarious", "have"
    };
    char test0w2[TEST0_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "deranged",    "plot",      "mad"
    };
    
    
    assert(standardizeRules(test0dist, test0w1, test0w2, TEST0_NCRITERIA)==4);
    
    const int TEST2_NCRITERIA = 4;
    int test2dist[TEST2_NCRITERIA] = {
        2,           	4,          	1,           	13
    };
    char test2w1[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefaRIous", "have"
    };
    char test2w2[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "MaD"
    };
    
    assert(standardizeRules(test2dist, test2w1, test2w2, TEST2_NCRITERIA)==3);
    
    const int TEST3_NCRITERIA = 4;
    int test3dist[TEST3_NCRITERIA] = {
        2,           	1,          	1,           	13
    };
    char test3w1[TEST3_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "PLOT", "nefarious", "scientist"
    };
    char test3w2[TEST3_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "NEFARIOUS",    "plot",      "mad"
    };
    
    assert(standardizeRules(test3dist,test3w1,test3w2,TEST3_NCRITERIA) == 2);
    
    const int TEST4_NCRITERIA = 4;
    int test4dist[TEST4_NCRITERIA] = {
        -3,           	4,          	1,           	13
    };
    char test4w1[TEST4_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefari#$us", "have"
    };
    char test4w2[TEST4_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "mad"
    };
    
    assert(standardizeRules(test4dist,test4w1,test4w2,TEST4_NCRITERIA) == 1);
    
    const int TEST5_NCRITERIA = 4;
    int test5dist[TEST5_NCRITERIA] = {
        3,           	4,          	1,           	13
    };
    char test5w1[TEST5_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "",       "half-witted", "nefari#$us", "have"
    };
    char test5w2[TEST5_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      ""
    };
    
    assert(standardizeRules(test5dist,test5w1,test5w2,TEST5_NCRITERIA) == 0);
    
    const int TEST6_NCRITERIA = 4;
    int test6dist[TEST6_NCRITERIA] = {
        12,           	4,          	1,           	13
    };
    char test6w1[TEST6_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefari#$us", "have"
    };
    char test6w2[TEST6_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad", "guy",    "plot",      "mad"
    };
    
    assert(standardizeRules(test6dist,test6w1,test6w2,TEST6_NCRITERIA) == 2);
    
    const int TEST7_NCRITERIA = 4;
    int test7dist[TEST7_NCRITERIA] = {
        123455,           	4,          	1,           	13
    };
    char test7w1[TEST7_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "asdfghjklmnbvcxzqwer", "nefari#$us", "have"
    };
    char test7w2[TEST7_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "chicken"
    };
    
    assert(standardizeRules(test7dist,test7w1,test7w2,TEST7_NCRITERIA) == 3);
    
    const int TEST1_NCRITERIA = 5;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13 ,  3
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have", "deranged"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad", "deranged"
    };
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "**** 2014 ****") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  That plot: NEFARIOUS!") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged robot deranged robot robot") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "Two mad scientists suffer from deranged-robot fever.") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged deranged deranged deranged") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The deranged robot.") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "that is a Very Nefarious:: plot!!") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA       $scientist unle@asheD a deranged robot.") == 2);
    cout << "All tests succeeded" << endl;
 
 
    
}

void printMatchRules(int distance[],
                     char word1[][MAX_WORD_LENGTH+1],
                     char word2[][MAX_WORD_LENGTH+1],
                     int nRules)                         //prints out the match rules and their respective distances, to use during debugging
{
    for(int i = 0; i <= nRules-1; i++)
    {
        cout << distance[i] << " ";
        cout << word1[i] << " ";
        cout << word2[i] << " ";
        cout << endl;
    }
}

void printOtherArray(char revisedMultiDocument[][DOCUMENT_LIMIT+1], int n)      //prints out the revised document in its multi array format, to use during debugging
{
    for (int i = 0; i < n; i++)
    {
        cout <<revisedMultiDocument[i] << endl;
    }
}

void refreshDocument(char revisedDocument[], int n)     //resets the local array of revised document in determineQuality for continual use
{
    for (int i = 0; i < n; i++)
    {
        revisedDocument[i] = '\0';
    }
}

void refreshMultiDocument(char revisedMultiDocument[][DOCUMENT_LIMIT+1], int n)     //resets the local array of revised multi document (the 2-d array of words) in determineQuality for continual use
{
    for(int i = 0; i < n; i++)
    {
        for(int k = 0; k < n; k++)
        {
            revisedMultiDocument[i][k] = '\0';
        }
    }
}

bool determineMatchRule(int distance,
                        const char word1[],
                        const char word2[],
                        int index,
                        int jump,
                        char revisedMultiDocument[][DOCUMENT_LIMIT +1])

//this function used in determineQuality helps figure out which match word matches up with the word in the document with respect to its distance
{
    for (int i = index; i < jump ; i++)     //go through the word list in revisedMultiDocument
    {
        int distanceTracker = distance;
        
        while (distanceTracker > 0)     //if the distance is greater than 0, then compare the word in the array to word1 and the word n distance after to word2 from the document
        {
            if(((i + distanceTracker) < jump) && strcmp(revisedMultiDocument[i],word1) == 0 && strcmp(revisedMultiDocument[i+distanceTracker],word2) == 0)  //the first check makes sure not to check past non valid words - gets rid of undefined behaviour
            {
                return true;
            } else {
                distanceTracker--;
            }
        }
    }
    return false;
}

int standardizeRules(int distance[],
                     char word1[][MAX_WORD_LENGTH+1],
                     char word2[][MAX_WORD_LENGTH+1],
                     int nRules)
{
    if (nRules <= 0)             //if nRules is ever below 0, then return 0
        return 0;
    
    int validRules = nRules;            //sets an integer to the number of rules
    
    
    //---------Stage 1----------
    
    for(int i = 0; i <= nRules-1; i++)     //go through the row of elements in the overall scheme of things
    {
        if(distance[i] <= 0 && (word1[i][0] != '\0' || word2[i][0] != '\0'))
        {
            validRules--;       //if in any case we encounter a negative distance immediately rule out that row
        } else if(word1[i][0] == '\0' || word2[i][0] == '\0')  //if we ever encounter a word which contains no character, make this set invalid and set it to empty
        {
            distance[i] = -1;
            validRules--;
            word1[i][0] = '\0';
            word2[i][0] = '\0';
        }
        else
        {
            for(int k = 0; k < MAX_WORD_LENGTH+1; k++)  //go through the individual characters in the cstring
            {
                if(isupper(word1[i][k]) || isupper(word2[i][k]))        //if any character in either of the words is uppercase, make it lowercase
                {
                    if(k < strlen(word1[i]))                //this checks to make sure that the evaluation of characters does not go beyond the zero byte
                        word1[i][k] = tolower(word1[i][k]);
                    if(k < strlen(word2[i]))
                        word2[i][k] = tolower(word2[i][k]);
                }
                if((!isalpha(word1[i][k]) && word1[i][k] != '\0') || (!isalpha(word2[i][k]) && word2[i][k] != '\0'))  //if we have a non valid character, that is one that is not an alphabet, disregard this cstring pair
                {
                    distance[i] = -1;    //this checks to make sure that we do not evaluate past the zero byte for both of the cstrings
                    validRules--;
                    word1[i][0] = '\0';
                    word2[i][0] = '\0';
                    break;          //the break is here to ensure that if both words contain a non valid character, valid rules only decreases by one
                    
                }
            }
        }
    }
    
    //---------Stage 2----------
    
    for (int j = 0; j <= nRules - 1; j++)    //call this stage 2, after all the words have been evaluated, we loop through the entire array set again
    {
        for (int w = 0; w <= nRules - 1 ; w++)   //this time we only need to go through the rows
        {
            int compare1=-1;
            int compare2=-1;
            if(strlen(word1[j]) && strlen(word2[w]))    //if both word1 and word2 have valid lengths (that is they are not just the zero byte) then we store the comparison
                compare1 = strcmp(word1[j],word2[w]);
            if(strlen(word1[w]) && strlen(word2[j]))
                compare2 = strcmp(word2[j],word1[w]);
            if(strcmp(word1[j],word2[j]) == 0)  //if for the same match rule, we have word1 = word2
                break;
            if(compare1 == 0 && compare2 == 0 && (distance[j] >= distance[w] && distance[j] > 0 && distance[w] > 0))  //if both comparisons are equal, that is to say that if we have repeated sets, then disregard the set with a greater distance and set it to empty
            {
                validRules--;
                word1[w][0]='\0';
                word2[w][0]='\0';
                distance[w] = -1;       //sets the distance value to -1 for later use
            }
        }
    }
    
    //---------Stage 3----------
    
    for (int m = 0; m <= nRules -1; m++) //call this stage 3, where we go through the rows again
    {
        if(distance[m] < 0){        //if we ever have a negative distance, it means that this set should be ignored and replaced by a more valid set later
            word1[m][0]='\0';
            word2[m][0]='\0';
            for (int q = m; q <= nRules -1 ; q++) {     //look for a valid set and make the invalid set the valid set
                if (distance[q] >= 0) {
                    distance[m] = distance[q];      //this set of code basically switches the invalid match rules with the valid rules that are ahead of them
                    strcpy(word1[m],word1[q]);
                    strcpy(word2[m],word2[q]);
                    word1[q][0] = '\0';
                    word2[q][0] = '\0';
                    distance[q] = -1;
                    m++;
                }
            }
        }
    }
    return validRules;          //return the number of match rules that is valid
}


int determineQuality(const int distance[],
                     const char word1[][MAX_WORD_LENGTH+1],
                     const char word2[][MAX_WORD_LENGTH+1],
                     int nRules,
                     const char document[])
{
    char revisedDocument[DOCUMENT_LIMIT+1];                 //create a local array to store a one dimensional representation of the document after its been edited
    
    char revisedMultiDocument[DOCUMENT_LIMIT+1][DOCUMENT_LIMIT+1];      //create a local array to store the individual words of revisedDocument in a 2-d dimensional array
    
    int jump = 0;           //stores the number of jumps in rows in revisedMultiDocument
    
    int count=0;            //count stores the number of indiviual characters in the columns of revisedMultiDocument to the point it hits a space character
    
    int matchedRules = 0;   //stores the overall number of match rules within the overall document
    
    bool lastSpace = false; //determines whether or not during iteration we hit a space character
    
    refreshDocument(revisedDocument, DOCUMENT_LIMIT + 1);       //initialises revised document to just zero bytes
    
    refreshMultiDocument(revisedMultiDocument, DOCUMENT_LIMIT + 1); //initialises revisedMultiDocument to just zero bytes
    
    //---------Stage 1----------
    
    for(int i = 0, j = 0; document[i] != '\0' && j < DOCUMENT_LIMIT + 1; i++, j++)      //stage 1 takes all the relevant characters from the constant document to revisedDocument as a single cstring
    {
        if(isalpha(document[i]) || document[i] == ' ')      //copies only valid alpahbetical characters and spaces
            revisedDocument[j] = document[i];
        else
            j--;
        if(document[i] == '\0')
            break;
    }
    
    for(int k = 0; revisedDocument[k] != '\0'; k++)         //this part of stage 1 converts all the relevant characters that are now in revisedDocument to lowercase
    {
        if(isupper(revisedDocument[k]))
            revisedDocument[k] = tolower(revisedDocument[k]);
    }
    
    //---------Stage 2----------
    
    for (int r = 0; revisedDocument[r] != '\0'; r++)        //stage 2 breaks revisedDocument up into individual words stored in the 2-dimensional revisedMultiDocument array
    {
        if(revisedDocument[r] != ' ')               //if the characters through the revised document isn't a space, then input each character into revisedMultiDocument and increase count
        {
            revisedMultiDocument[jump][count] = revisedDocument[r];
            count++;
            lastSpace = false;
        } else if (revisedDocument[r] == ' ' && lastSpace == true)  //this takes care of having multiple spaces, and that if we do, do nothing
        {
            // ------DO-NOTHING------
            
        } else if (revisedDocument[r] == ' ' && lastSpace == false)     //if we hit a space then make the rest of the row empty, reverse count back to 0 and jump to the next row
        {
            if(revisedMultiDocument[jump][0] != '\0')
            {
                revisedMultiDocument[jump][count] = '\0';
                count = 0;
                jump++;
                lastSpace = true;
            }
        }
    }
    
    int numWords = jump+1;          //because jump starts from 0th row, the exact number of words is actually jump + 1 which we store in numWords
    
    //---------Stage 3----------
    
    for(int m = 0; m <= nRules - 1; m++)     //this for loop goes through the match rules row by row
    {
        for (int n = 0; n < jump; n++)      //this for loop goes through the words in the revisedMultiDocument
        {
            
            if((strcmp(revisedMultiDocument[n],word1[m]) == 0) || strcmp(revisedMultiDocument[n],word2[m]) == 0)    //this checks to see if the word matches with either word1 or word2 from the match rules
            {
                //if the comaprison is correct then increment the number of matched rules by one
                if(determineMatchRule(distance[m], word1[m], word2[m], n, numWords, revisedMultiDocument) || determineMatchRule(distance[m], word2[m], word1[m], n, numWords, revisedMultiDocument))
                {
                    matchedRules++;
                    break;
                }
            }
        }
    }
    
    refreshDocument(revisedDocument, DOCUMENT_LIMIT);           //refresh the revisedDocument to empty for continual use
    refreshMultiDocument(revisedMultiDocument, DOCUMENT_LIMIT); //refresh the revisedMultiDocument to empty for continual use
    return matchedRules;    //return the value of matchedRules
}