//
// Created by raph on 1/19/20.
//

#ifndef FINALPROJECTPART2_DFSSEARCHER_H
#define FINALPROJECTPART2_DFSSEARCHER_H


#include <stack>
#include "SearcherAbstract.h"

using namespace std;

template<class T>

class DFSSearcher : public SearcherAbstract<T> {
private:

    stack<State<T> *> openList;

    int openListSize() {
        return (int) openList.size();
    }

    bool openContains(State<T> *state) {

        return isExist(state);
    }

    State<T> *popOpenList() {
        return pop();
    }

    State<T> *pop() {
        State<T> *firstState = openList.top();
        this->openList.pop();
        return firstState;
    }


    void addOpenList(State<T> *s) {
        openList.push(s);
    }

    bool isExist(State<T> *state1) {
        vector<State<T> *> vecStates;
        State<T> *tempState;
        bool flag = false;
        //pop all the state from the queue and check if the state exist
        while (!openList.empty()) {
            tempState = this->pop();
            if (*tempState == *state1) {
                flag = true;
            } else {
                vecStates.push_back(tempState);
            }
        }
        //return the queue to the first state
        for (const auto &state : vecStates) {
            this->openList.push(state);
        }
        return flag;
    }


public:
    vector<State<T> *> search(Searchable<T> *searchable) {
        //initialize with 0
        this->zeroNumOfNodesEvaluated();
        vector<State<T> *> closeVec;
        //add the initial stat to the stack
        this->addOpenList(searchable->getInitialState());
        //run on the graph until there are no state in the stack
        while (openListSize() > 0) {
            this->addNumOfNodesEvaluated();
            //pop the the father state
            State<T> *minState = this->popOpenList();
            // check if the state already visited
            if (!this->containInClose(closeVec, minState)) {
                closeVec.push_back(minState);
            }
            //check if we arrive to the goal state
            if (searchable->isGoalState(minState)) {
                return this->reversePath(minState, searchable->getInitialState());
            }
            //input the all Neighbors
            vector<State<T> *> statesVecNeighbors = searchable->getAllPossibleState(minState);
            for (State<T> *tempState : statesVecNeighbors) {
                //check if exist in the close vec
                if (!this->containInClose(closeVec, tempState)) {
                    this->addOpenList(tempState);
                }
            }
        }
        vector<State<T> *> emptyVec;
        //there is not path
        return emptyVec;

    }

    ~DFSSearcher() {}


};


#endif //FINALPROJECTPART2_DFSSEARCHER_H
