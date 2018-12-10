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
//declare an array of integers that represent the max capacity of each jug
int capacity[3];
std::vector<state> outList;
//functions that handle the 'fill', 'empty', and 'pour' operations for all combination of jugs
state fill(int pos, state v) {
    switch(pos){
    case 1: v.j1 = capacity[0];
            break;
    case 2: v.j2 = capacity[1];
            break;
    case 3: v.j3 = capacity[2];
            break;
    }
    return v;
}

state empty(int pos, state v) {
    switch (pos) {
    case 1: v.j1 = 0;
            break;
    case 2: v.j2 = 0;
            break;
    case 3: v.j3 = 0;
            break;
    }
    return v;
}

state pour(int src, int tgt, state v) {
    /*the pour function is handled such that the source and target jugs are iteratively 
    decreased and increased, respectively, until either the source is empty or the target is full*/
    switch (src) {
    case 1: 
        switch (tgt) {
        case 2: while (v.j1 > 0 && v.j2 < capacity[1]) {
            v.j1 -= 1;
            v.j2 += 1;
        }
            break;
        case 3: while (v.j1 > 0 && v.j3 < capacity[2]) {
            v.j1 -= 1;
            v.j3 += 1;
        };
            break;
        }
        break;
    case 2:
        switch (tgt) {
        case 1: while (v.j2 > 0 && v.j1 < capacity[0]) {
            v.j2 -= 1;
            v.j1 += 1;
        };
            break;
        case 3: while (v.j2 > 0 && v.j3 < capacity[2]) {
            v.j2 -= 1;
            v.j3 += 1;
        };
            break;
        }
        break;
    case 3: 
        switch (tgt) {
        case 1: while (v.j3 > 0 && v.j1 < capacity[0]) {
            v.j3 -= 1;
            v.j1 += 1;
        };
            break;
        case 2: while (v.j3 > 0 && v.j2 < capacity[1]) {
            v.j3 -= 1;
            v.j2 += 1;
        };
            break;
        }
        break;
    }
    return v;
}

/*this function uses a lambda expression to search through the list of saved states,
and return true if the current state has been found (i.e. if the unique combination of the 
three volumes already exists in the list)*/
bool searchValue;
bool searcher(state v) {
    searchValue = false;
    std::for_each(outList.begin(), outList.end(), [v](state x) {
        if (x.j1 == v.j1 && x.j2 == v.j2 && x.j3 == v.j3) {
            
            searchValue = true;
        }
    });
    return searchValue;
}
/*This is the main search algorithm function*/
void dfs() {
    std::stack<state> nodeStack;
    state tmp;
    state v;
    state init = { 0,0,0 };
    nodeStack.push(init);
    while (!nodeStack.empty()) {
        v = nodeStack.top();
        std::cout << "----------------------------------------------------------------\n";
        std::cout << "top of stack: " << v.j1 << " " << v.j2 << " " << v.j3 << "\n";
        std::cout << "Size of stack: " << nodeStack.size() << "\n";
        std::cout << "Size of output list: " << outList.size() << "\n";
        for (auto &i : outList) {

            std::cout << i.j1 << " " << i.j2 << " " << i.j3 << "\n";
        }
        //if statements to generate children, e.g.:
        //if(v.j1 < capacity[0] && fill1(v) not in outList){
        //  tmp = fill1(v);
        //  nodeStack.push(tmp);
        // outList.push_back(tmp);
        //}
        //first, handles the three possible 'fill' children
        if (v.j1 < capacity[0] && searcher(fill(1, v)) == false) {
            tmp = fill(1, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
           // std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3<< "\n";
        }
        else if (v.j2 < capacity[1] && searcher(fill(2, v)) == false) {
            tmp = fill(2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
          //  std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j3 < capacity[2] && searcher(fill(3, v)) == false) {
            tmp = fill(3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
         //   std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        //next, handles the 3 possible 'empty' children
        else if (v.j1 > 0 && searcher(empty(1, v)) == false) {
            tmp = empty(1, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j2 > 0 && searcher(empty(2, v)) == false) {
            tmp = empty(2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j3 > 0 && searcher(empty(3, v)) == false) {
            tmp = empty(3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        //next, handles the 6 possible 'pour' children
        else if (v.j1 > 0 && v.j2 < capacity[1] && searcher(pour(1, 2, v)) == false) {
            tmp = pour(1, 2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j1 > 0 && v.j3 < capacity[2] && searcher(pour(1, 3, v)) == false) {
            tmp = pour(1, 3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j2 > 0 && v.j1 < capacity[0] && searcher(pour(2, 1, v)) == false) {
            tmp = pour(2, 1, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j2 > 0 && v.j3 < capacity[2] && searcher(pour(2, 3, v)) == false) {
            tmp = pour(2, 3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j3 > 0 && v.j1 < capacity[0] && searcher(pour(3, 1, v)) == false) {
            tmp = pour(3, 1, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else if (v.j3 > 0 && v.j2 < capacity[1] && searcher(pour(3, 2, v)) == false) {
            tmp = pour(3, 2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
            std::cout << tmp.j1 << " " << tmp.j2 << " " << tmp.j3 << "\n";
        }
        else {
            nodeStack.pop();
        }

        
    }
};

int main()
{   
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
