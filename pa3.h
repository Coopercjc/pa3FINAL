//
// Created by Chris on 4/4/2018.
//

#ifndef PA3_PA3_H
#define PA3_PA3_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main();

void compute(vector<string> parse);
void print(vector<string> a, string b);

void keywords(vector<string> parse);
void identifier(vector<string> parse);
void constant(vector<string> parse);
void operators(vector<string> parse);
void delimiter(vector<string> parse);
void syntax(vector<string> parse);
bool syntaxChecker(vector<string> parse);
int nested(vector<string> parse);


class Stack{
private:
    vector<string> stack;
public:
    void push(string c);
    void pop(string pos);
    int size();
    vector<string> getStack();

};

#endif //PA3_PA3_H
