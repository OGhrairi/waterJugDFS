// AICoursework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

//defines a structure to represent the three jugs, j1, j2, j3
struct state {
    int j1;
    int j2;
    int j3;
};

void dfs() {
    std::stack<state> nodeStack;
    std::vector<state> outList;
    state init = { 0,0,0 };
    nodeStack.push(init);
    while (!nodeStack.empty()) {
        state tmp;
        state v = nodeStack.top();
        //if statements to generate children, e.g.:
        //if(v.j1 < capacity[0] && fill1(v) not in outList){
        //  tmp = fill1(v);
        //  nodeStack.push(tmp);
        // outList.push_back(tmp);
        //}
    }
};

int main()
{   
    int capacity[3];
    std::cout << "Input capacities A, B and C\n";
    std::cin >> capacity[0];
    std::cin >> capacity[1];
    std::cin >> capacity[2];
    dfs();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
