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



bool searchValue;
/*this function uses a lambda expression to search through the list of saved states,
and return true if the current state has been found (i.e. if the unique combination of the
three volumes already exists in the list)*/
bool searcher(state v) {
    searchValue = false;
    std::for_each(outList.begin(), outList.end(), [v](state x) {
        if (x.j1 == v.j1 && x.j2 == v.j2 && x.j3 == v.j3) {
            
            searchValue = true;
        }
    });
    return searchValue;
}

bool goalState;
state goal;

/*This is the main search algorithm function*/
void dfs() {
    std::stack<state> nodeStack;//create the search stack 
    state tmp;
    state v;
    state init = { 0,0,0 };
    nodeStack.push(init);//initialise the stack with the start state
    outList.push_back(init);
    while (!nodeStack.empty()) {//program runs until stack is empty
        v = nodeStack.top(); //current working node
        //if statement to handle if the user wants to reach a certain goal state
        if (goalState == true) {
            if (v.j1 == goal.j1 && v.j2 == goal.j2 && v.j3 == goal.j3) {
                for (auto &i : outList) {
                    std::cout << i.j1 << " " << i.j2 << " " << i.j3 << "\n";
                    //outputs a list of all states from the output list and gives the size of the list
                }
                std::cout << "Size of output list: " << outList.size() << "\n";
                std::cout << "Goal State Reached\n";
                return;
            }
        }

        //beginning of the child node generation. each node can have >= 12 children
        //each of these generators calls the 'searcher' function to check if child is already found
        //first, handles the three possible 'fill' children
        if (v.j1 < capacity[0] && searcher(fill(1, v)) == false) {
            tmp = fill(1, v);//calls the fill function
            nodeStack.push(tmp);//push new node to stack
            outList.push_back(tmp);//add new node to output list
        }
        else if (v.j2 < capacity[1] && searcher(fill(2, v)) == false) {
            tmp = fill(2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j3 < capacity[2] && searcher(fill(3, v)) == false) {
            tmp = fill(3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        //next, handles the 3 possible 'empty' children
        else if (v.j1 > 0 && searcher(empty(1, v)) == false) {
            tmp = empty(1, v);//calls the empty function
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j2 > 0 && searcher(empty(2, v)) == false) {
            tmp = empty(2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j3 > 0 && searcher(empty(3, v)) == false) {
            tmp = empty(3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        //next, handles the 6 possible 'pour' children
        else if (v.j1 > 0 && v.j2 < capacity[1] && searcher(pour(1, 2, v)) == false) {
            tmp = pour(1, 2, v);//calls the pour function with both source and destination
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j1 > 0 && v.j3 < capacity[2] && searcher(pour(1, 3, v)) == false) {
            tmp = pour(1, 3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j2 > 0 && v.j1 < capacity[0] && searcher(pour(2, 1, v)) == false) {
            tmp = pour(2, 1, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j2 > 0 && v.j3 < capacity[2] && searcher(pour(2, 3, v)) == false) {
            tmp = pour(2, 3, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j3 > 0 && v.j1 < capacity[0] && searcher(pour(3, 1, v)) == false) {
            tmp = pour(3, 1, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        else if (v.j3 > 0 && v.j2 < capacity[1] && searcher(pour(3, 2, v)) == false) {
            tmp = pour(3, 2, v);
            nodeStack.push(tmp);
            outList.push_back(tmp);
        }
        /*when none of the above childred are valid, either because 
        the current node has no children, or the children that it does have are already
        present in the output list, the current node is popped from the stack to allow
        the program to move up one level*/
        else {
            nodeStack.pop();
        }
        
    }//outputs a list of all nodes found, and gives the size of the list
    for (auto &i : outList) {

        std::cout << i.j1 << " " << i.j2 << " " << i.j3 << "\n";
        
    }std::cout << "Size of output list: " << outList.size() << "\n";

};

int main()
{   
    char yn;
    goalState = false;
    //allows user to input jug capacities
    std::cout << "Input capacities A, B and C, one at a time\n";
    std::cin >> capacity[0];
    std::cin >> capacity[1];
    std::cin >> capacity[2];
    //allows user to specify an optional goal state at which the program will halt
    std::cout << "Goal State? y/n\n";
    std::cin >> yn;
    if (yn == 'y') {
        std::cout << "Enter Goal State\n";
        std::cin >> goal.j1;
        std::cin >> goal.j2;
        std::cin >> goal.j3;
        goalState = true;
    }
    //calls the main search function
    dfs();
    system("PAUSE");

}