//
// Created by Chris on 4/4/2018.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "pa3.h"

using namespace std;

//Used to add string to a stack
void Stack::push(string c) {
    stack.push_back(c);
}

//Used to remove a duplicate from a stack
void Stack::pop(string pos) {
    int count=0;
    for(int i = 0; i < stack.size(); i++){
        if(stack[i] == pos)
           count++;
    }
    if(count>1)
        stack.pop_back();
}

//Return size of the stack vector of a Stack object
int Stack::size(){
    return stack.size();
}

//returns the vector of that Stack variable
vector<string> Stack::getStack() {
    return stack;
}

//Runs the beginning of the program
int main() {
    string fileName;
    string line;
    vector<string> input;

    while(true) {
        cout << "Please enter the name of the input file: ";
        cin >> fileName;
        ifstream f(fileName);

        if (f.is_open()) {
            while (getline(f, line)) {
                input.push_back(line);
            }
            break;
        } else
            cout<<"ERROR 404: FILE NOT FOUND"<<endl;
    }
    compute(input);
}

//runs all of the other methods and also takes in a vector to pass into the methods.
void compute(vector<string> parse){
    cout<< "The depth of the nested loop(s) is "<<nested(parse)<<endl;
    keywords(parse);
    identifier(parse);
    constant(parse);
    operators(parse);
    delimiter(parse);
    syntax(parse);
}

//prints the stack by grabbing its vector and printing the elements out
void print(vector<string> a, string b) {
    cout<<b + ": ";
    for (int i = 0; i < a.size(); i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

//checks the file for keywords and adds them to the stack
void keywords(vector<string> parse){
    Stack stk;
    //These variables are used to only record key words once.
    for (int i = 0; i < parse.size(); i++){//iterates through the vector
        string line = parse[i];

        if ( line.find("BEGIN") != string::npos){//If BEGIN is found add it to key.
            stk.push("BEGIN");
            stk.pop("BEGIN");
        }
        if ( line.find("END") != string::npos){//If END is found add it to key.
            stk.push("END");
            stk.pop("END");
        }
        if ( line.find("FOR") != string::npos){//If FOR is found add it to key.
            stk.push("FOR");
            stk.pop("FOR");
        }
    }

    print(stk.getStack(), "Keywords");
}

//checks the file for identifier and adds them to the stack
void identifier(vector<string> parse){
    Stack stk;

    for(int i = 0; i<parse.size(); i++){//iterates through the vector
        string line = parse[i];
        string alph = "abcdefghijklmnopqrstuvwxyz";//used to find the beginning of a identifier.
        for (int j = 0; j < line.length() ;j++){
            string test=line.substr(j,1);//iterates through the string character by character
            if ( alph.find(test) != string::npos){//npos is the value that .find returns if there isn't a match
                int counter = 0;
                for ( int k = j+1; alph.find(line.substr(k,1))!= string::npos; k++){//This records the length of the idenifier by checking the indexes after the first letter is found
                    counter++;
                }

                string check = line.substr(j, 1+counter);//used by the following if statement to see if the found identifier has already been recorded or not
                int verify=0;
                if(stk.size()>0) {
                    for (int k = 0; k < stk.size(); k++) {
                        if (check == stk.getStack()[k]){
                            verify++;
                        }
                    }
                }
                j+=counter;//used to skip to the index where the substring ended
                if ( verify == 0)//if no previous record was found in stk, then record it.
                    stk.push(check);
            }
        }
    }

    print(stk.getStack(), "Identifiers");
}

//checks the file for constants and adds them to the stack
void constant(vector<string> parse){
    Stack stk;
    for (int i = 0; i < parse.size(); i++) {//iterates through the vector
        string line = parse[i];
        string num = "1234567890";//used to see if the character in line is a constant
        for (int j = 0; j < line.length() ;j++){
            string test=line.substr(j,1);//checks each character for num by testing test to see if it is in num
            if ( num.find(test) != string::npos){
                int counter = 0;
                for ( int k = j+1; num.find(line.substr(k,1))!= string::npos; k++){//records the length of the constant
                    counter++;
                }

                string check = line.substr(j, 1+counter);//makes check equal to the constant
                int verify=0;
                if(stk.size()>0) {//if check is already in con then verify won't =0 and the push_back method will not be run
                    for (int k = 0; k < stk.size(); k++) {
                        if (check == stk.getStack()[k]){
                            verify++;
                        }
                    }
                }
                j+=counter;//used to skip to the index where the substring ended
                if ( verify == 0){//if there is no previous occurrence then add it to the stack
                    stk.push(check);
                }
            }
        }
    }
    print(stk.getStack(), "Constants");
}

//checks the file for operators and adds them to the stack
void operators(vector<string> parse){
    Stack stk;

    for (int i = 0; i < parse.size(); i++){//iterates through the vector
        string line = parse[i];

        if ( line.find("+") != string::npos){//first checks to see if the plus is there, then checks to see if it is a ++ or not.
            if (line.substr(line.find("+"),2)!="++") {//Adds if it is not a ++.
                stk.push("+");
                stk.pop("+");
            }
        }
        if ( line.find("-") != string::npos){//checks to see if its a - and if its already been recorded
            stk.push("-");
            stk.pop("-");
        }
        if ( line.find("/") != string::npos){//checks to see if its a / and if its already been recorded
            stk.push("/");
            stk.pop("/");
        }
        if ( line.find("*") != string::npos){//checks to see if its a * and if its already been recorded
            stk.push("*");
            stk.pop("*");
        }
        if ( line.find("++") != string::npos){//checks to see if its a ++ and if its already been recorded
            stk.push("++");
            stk.pop("++");
        }
        if ( line.find("=") != string::npos){//checks to see if its a = and if its already been recorded
            stk.push("=");
            stk.pop("=");
        }
    }
    print(stk.getStack(), "Operators");
}

//checks the file for delimiters and adds them to the stack
void delimiter(vector<string> parse){
    Stack stk;

    for (int i = 0; i < parse.size(); i++){//iterates through the vector
        string line = parse[i];

        if ( line.find(",") != string::npos){//checks to see if its a , and if its already been recorded
            stk.push(",");
            stk.pop(",");
        }

        if ( line.find(";") != string::npos){//checks to see if its a ; and if its already been recorded
            stk.push(";");
            stk.pop(";");
        }
    }
    print(stk.getStack(), "Delimiters");
}

//checks the file for syntax errors and adds them to the stack
void syntax(vector<string> parse){
    Stack stk;
    int bCount=0;
    int eCount=0;
    int fCount=0;

    for (int i = 0; i < parse.size(); i++){//iterates through the vector
        string line = parse[i];
        string capAlph="ABCDEFGHIJKLMNOPQRSTUVWXYZ";//used to cross reference with the character from test

        for (int j = 0; j < line.length() ;j++) {
            string test = line.substr(j, 1);//gets a character in the form of a string going at increments of one index
            int counter = 0;
            if (capAlph.find(test) != string::npos) {//looks to see if test is in capAlph
                for ( int k = j+1; capAlph.find(line.substr(k,1))!= string::npos && k<line.length(); k++){
                    counter++;
                }
                string word = line.substr(j, 1+counter);//records the length of the capital potential keyword and then saves the word in word


                if (word == "FOR"){//USED TO CHECK FOR EXTRA PARENTHESES
                    int balance = 0;
                    int idx = line.find("FOR");
                    for (int r = idx+3; r<line.length(); r++){//used to change balances value for each occurrence of ( and )
                        char para = line[r];
                        if ( para == '('){
                            balance--;
                        }
                        if ( para == ')'){
                            balance++;
                        }
                    }
                    //if balance is not 0 then return which extra parentheses there is.
                    if (balance < 0 ){
                        stk.push("(");
                    }
                    if (balance > 0 ){
                        stk.push(")");
                    }
                    fCount++;
                }

                if(word == "END")//Counts each END occurrence
                    eCount++;
                if(word == "BEGIN")//Counts each BEGIN occurrence
                    bCount++;
                if (word != "BEGIN" && word != "END" && word!="FOR"){//if word is not equal to any of the keywords then add it to err
                    stk.push(word);
                }
                j+=counter;//used to skip to the index where the substring ended
            }
        }
    }
    //The following if statements are used to see if there are any errors within the text dealing with missing ENDs or BEGINs and ENDs
    if(bCount>eCount || fCount>eCount)
        stk.push("END");
    if(fCount>bCount && eCount != fCount)
        stk.push("BEGIN");
    if(stk.getStack().size()==0)
        stk.push("NA");

    print(stk.getStack(),"Syntax Errors");
}

//checks the file to see how many for loops are syntax free and counts towards total nested for loops
int nested(vector<string> parse) {
    Stack stk;
    int nest = 0;
    int hope = 0;

    for (int i = 0; i < parse.size(); i++) {//iterates through the vector
        string line = parse[i];
        string capAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//used to cross reference with the character from test
        int plus = 0;

        for (int j = 0; j < line.length(); j++) {
            string test = line.substr(j, 1);//gets a character in the form of a string going at increments of one index
            int counter = 0;
            if (capAlph.find(test) != string::npos) {//looks to see if test is in capAlph
                for (int k = j + 1; capAlph.find(line.substr(k, 1)) != string::npos && k < line.length(); k++) {
                    counter++;
                }
                string word = line.substr(j, 1 + counter);//records the length of the capital potential keyword and then saves the word in word

                if (word == "FOR") {
                    line = parse[i + 1 + plus];
                    plus++;
                    if (line.find("BEGIN") != string::npos) {
                        line = parse[i + 2];
                        plus++;
                        if (line.find("FOR") != string::npos) {
                            nest++;
                            plus++;
                        }
                    }
                }
            }
        }
    }

    vector<string> testing;
    for (int i = 0 + nest; i < parse.size(); i++) {
        testing.push_back(parse[i]);
    }


    for (int i = 0 + nest; i < parse.size(); i++) {//iterates through the vector
        string line = parse[i];
        string capAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//used to cross reference with the character from test

        for (int j = 0; j < line.length(); j++) {
            string test = line.substr(j, 1);//gets a character in the form of a string going at increments of one index
            int counter = 0;
            if (capAlph.find(test) != string::npos) {//looks to see if test is in capAlph
                for (int k = j + 1; capAlph.find(line.substr(k, 1)) != string::npos && k < line.length(); k++) {
                    counter++;
                }
                string word = line.substr(j, 1 + counter);//records the length of the capital potential keyword and then saves the word in word

                if (word == "FOR") {
                    if (syntaxChecker(testing) && hope == 0)
                        nest++;
                    hope++;
                }
            }
        }
    }
    return nest;
}

//Used to check a FOR loop if it is valid.
bool syntaxChecker(vector<string> parse){
    Stack stk;
    int bCount=0;
    int eCount=0;
    int fCount=0;


    for (int i = 0; i < parse.size(); i++){//iterates through the vector
        string line = parse[i];
        string capAlph="ABCDEFGHIJKLMNOPQRSTUVWXYZ";//used to cross reference with the character from test

        for (int j = 0; j < line.length() ;j++) {
            string test = line.substr(j, 1);//gets a character in the form of a string going at increments of one index
            int counter = 0;
            if (capAlph.find(test) != string::npos) {//looks to see if test is in capAlph
                for ( int k = j+1; capAlph.find(line.substr(k,1))!= string::npos && k<line.length(); k++){
                    counter++;
                }
                string word = line.substr(j, 1+counter);//records the length of the capital potential keyword and then saves the word in word


                if (word == "FOR"){//USED TO CHECK FOR EXTRA PARENTHESES
                    int balance = 0;
                    int idx = line.find("FOR");
                    for (int r = idx+3; r<line.length(); r++){//used to change balances value for each occurrence of ( and )
                        char para = line[r];
                        if ( para == '('){
                            balance--;
                        }
                        if ( para == ')'){
                            balance++;
                        }
                    }
                    //if balance is not 0 then return which extra parentheses there is.
                    if (balance < 0 ){
                        stk.push("(");
                    }
                    if (balance > 0 ){
                        stk.push(")");
                    }
                    fCount++;
                }

                if(word == "END")//Counts each END occurrence
                    eCount++;
                if(word == "BEGIN")//Counts each BEGIN occurrence
                    bCount++;
                if (word != "BEGIN" && word != "END" && word!="FOR"){//if word is not equal to any of the keywords then add it to err
                    stk.push(word);
                }
                j+=counter;//used to skip to the index where the substring ended
            }
        }
    }
    //The following if statements are used to see if there are any errors within the text dealing with missing ENDs or BEGINs and ENDs
    if(bCount>eCount || fCount>eCount)
        stk.push("END");
    if(fCount>bCount && eCount != fCount)
        stk.push("BEGIN");

    if(stk.size()==0)
        return true;
    else
        return false;
}
