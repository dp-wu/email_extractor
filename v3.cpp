/* 
new version is using map instead of multiset.
it should be much faster and space efficient compare to previous two versions (also shorter code, easier to understand).
seems like the prof prefer to have less lines of code in main() func,
personally i prefer that too, but in this case i think it is UNnecessary to do so.
i moved some parts outside anyways just for whoever's sake. -.-
*/

//  email.cpp
//  Created by Yvette Wu on 5/19/20.
//  Copyright © 2020 Yvette Wu. All rights reserved.

//  Description:
//  Write a program named email.cpp that opens and reads
//  a text file and writes another text file.

#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef map<string, string> Map;
const int MAX_LEN = 1000; // maximum length of the email records

struct Emails {
    string formatted;
    string rawForm;
}; // 1-1 mapping for easier access

bool isValidChar(char c) {
    string validChar = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-+";
    if (validChar.find(c) == -1) return false;
    else return true;
} // verify if a char is valid to form an email address

int lineParser (string rawText, Emails ep[]) {
    int p=1, lp=1, rp=1, counter=0; // ind for @, left p, right p
    
    for (p=1; rawText[p+1]; ++p) {
        string ss="@", SS="@";
        if (rawText[p] == '@' && rawText[p-1]!='.' && rawText[p+1]!='.') {
            if (isValidChar(rawText[p-1]) && isValidChar(rawText[p+1])) {
                for (lp=p-1; lp>-1; --lp) {
                    if (!isValidChar(rawText[lp])) break;
                    else {
                        string ls(1, rawText[lp]); //left char
                        string lS(1, toupper(rawText[lp]));
                        ss = ls + ss;
                        SS = lS + SS;
                    }
                } // search for the left part
                for (rp=p+1; rawText[rp]; ++rp) {
                    if (!isValidChar(rawText[rp])) break;
                    else {
                        string rs(1, rawText[rp]);
                        string rS(1, toupper(rawText[rp]));
                        ss = ss + rs;
                        SS = SS + rS;
                    }
                } // search for the left part
                
                ep[counter].rawForm = ss;
                ep[counter].formatted = SS;
                ++counter; // .@. is not a valid format, but +@_ is valid here
            } // found a valid label, concat ss, SS
        }
    }
    return counter;
} // process raw string and return email address if found any

void getFiles(string fList[]) {
    cout << "Enter source file name or press ENTER to use default: ";
    getline(cin, fList[0]); // get target source
    if (fList[0].empty()) fList[0] = "fileContainingEmails.txt";
    cout << "Enter the destination file name or press ENTER to use default: ";
    getline(cin, fList[1]); // get target destination
    if (fList[1].empty()) fList[1] = "copyPasteMyEmails.txt";
} // get dir info


int main() {
    string iof[2];
    getFiles(iof);
    
    fstream f; // open source text file
    f.open(iof[0].c_str(), ios::in); // open txt file
    if (!f.good()) throw "I/O error";
    
    Map emails;
    Map::iterator p;
    while (f.good()) {
        Emails temp[MAX_LEN]; // temporary email array from each line
        int temp_size = 0;
        
        string line;
        getline(f, line); // read line
        temp_size = lineParser(line, temp); // handle current line
        if (temp_size == 0) continue; // if 0 email found continue to next line
        
        for (int i=0; i<temp_size; ++i) {
            if (emails.find(temp[i].formatted) != emails.end()) continue;
            else emails.insert(pair<string, string>(temp[i].formatted, temp[i].rawForm));
        } // insert email into emails, skip duplicates
    }
    f.close();
    
    if (emails.size() == 0) {
        cout << "\nSorry, no email addresses were found in the file " << iof[0] << endl;
        return 0; // if 0 email address found, exit program
    }
    else cout << "\n" << emails.size() << " email addresses were found, and copied to the file " << iof[1] << "\n" << endl;
    
    f.open(iof[1].c_str(), ios::out|ios::trunc); // overwrite if same as input file
    if (!f.good()) throw "I/O error";
    for (p=emails.begin(); p!=emails.end(); ++p) {
        cout << p->second << endl;
        if (p == --emails.end()) f << p->second; // how I become bald
        else f << p->second << "; ";
    } // write extracted info into file
    f.close();
    
    cout << "\nOpen the output file and copy/paste its contents into the" << endl;
    cout << "\"to\", \"cc\", or \"bcc\" field of any email message. " << endl;
    cout << "But it is best to use the \"bcc\" field so that everyone's" << endl;
    cout << "email address does not appear in the messageto protect " << endl;
    cout << "their privacy." << endl; // message
}
