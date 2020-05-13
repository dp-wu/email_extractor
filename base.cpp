//  email.cpp
//  Created by Yvette Wu on 5/6/20.
//  Copyright © 2020 Yvette Wu. All rights reserved.

//  Description:
//  Write a program named email.cpp that opens and reads
//  a text file and writes another text file.

#include <fstream>
#include <iostream>
#include <string>
using namespace std;


struct EMAILS {
    string rawForm;
    string formatted;
}; // 1-1 mapping for easier access

const int MAX_LEN = 1000; // maximum length of the email records

bool isValidChar(char c) {
    string validChar = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-+";
    if (validChar.find(c) == -1) return false;
    else return true;
} // verify if a char is valid to form an email address


int lineParser (string rawText, EMAILS ep[]) {
    int p=1, lp=1, rp=1, counter=0; // ind for @, left p, right p
    
    for (p=1; rawText[p+1]; ++p) {
        //cout << "p = " << p << " rawText[p] = " << rawText[p] << endl;
        string ss="@", SS="@";
        if (rawText[p] == '@' && rawText[p-1]!='.' && rawText[p+1]!='.') {
            if (isValidChar(rawText[p-1]) && isValidChar(rawText[p+1])) {
                // found a valid label, concat ss, SS
                for (lp=p-1; lp>-1; --lp) {
                    // search for the left part
                    if (!isValidChar(rawText[lp])) break;
                    else {
                        string ls(1, rawText[lp]);
                        string lS(1, toupper(rawText[lp]));
                        ss = ls + ss;
                        SS = lS + SS;
                    }
                }
                for (rp=p+1; rawText[rp]; ++rp) {
                    // search for the left part
                    if (!isValidChar(rawText[rp])) break;
                    else {
                        string rs(1, rawText[rp]);
                        string rS(1, toupper(rawText[rp]));
                        ss = ss + rs;
                        SS = SS + rS;
                    }
                }
                //cout <<"counter:  " << counter << endl;
                ep[counter].rawForm = ss;
                //cout << "   ep[counter].rawForm = " << ep[counter].rawForm << endl;
                ep[counter].formatted = SS;
                //cout << "   ep[counter].formatted = " << ep[counter].formatted << endl;
                ++counter; // .@. is not a valid format, but im not sure if +@_ is valid
            }
        }
    }
    return counter;
} // process raw string and return email address if found any

int mergArr(EMAILS *elist, EMAILS *tlist, int eSize, int tSize) {
    for (int i=0; i<tSize; ++i) {
        bool isDup = false; // switch set to false, no duplicate found
        for (int j=0; j<eSize; ++j) {
            if (tlist[i].formatted == elist[j].formatted) {
                isDup = true; // found duplicate from elist
                break;
            }
        }
        if (isDup == true) continue;
        else {
            *(elist+eSize) = tlist[i];
            ++eSize;
        }
    }
    return eSize;
}


int main() {
    ifstream fin; // open source and destination text file
    fin.open("fileContainingEmails.txt");
    if (!fin.good()) throw "I/O error";
    
    EMAILS emails[MAX_LEN];
    int em_size = 0;
    
    while (1) {
        if (!fin.good()) break;
        
        EMAILS temp[MAX_LEN];
        int temp_size = 0;
        
        string line;
        getline(fin, line);
        temp_size = lineParser(line, temp); // handle current line
        
        if (temp_size == 0) continue;
        else em_size = mergArr(emails, temp, em_size, temp_size); // write new infos into email list
    }
    fin.close();
    
    for (int i=0; i<em_size; ++i) cout << emails[i].rawForm << endl;
}
