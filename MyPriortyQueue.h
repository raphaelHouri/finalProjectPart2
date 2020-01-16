//
// Created by raph on 1/15/20.
//

#ifndef FINALPROJECTPART2_MYPRIORTYQUEUE_H
#define FINALPROJECTPART2_MYPRIORTYQUEUE_H

#include "State.h"
#include <vector>
#include "DataStrucForSearcher.h"
#include <queue>
#include "State.h"
#include "SearcherAbstract.h"

using namespace std;

//6.4 -- object functions
struct comperFuncState {
    template<class T>
    bool operator()(State<T> *stateCmp, State<T> *otherState) const {
        return stateCmp->getCost() > stateCmp->getCost();

    }
};

template <class T, class Solution>
// An abstract class
class MyPriorityQueue:  {
    // Data members of class
protected:
    //// Syntax to create a min heap for priority queue
    //priority_queue <type, vector<type>, loading func for min >>
    priority_queue<State<T> *, vector<State<T> *>, comperFuncState()> openList;
public:


    int openListSize() {
        return (int) size();
    }

    bool openContains(State<T> *state) {

        return  isExist(*state);
    }
    State<T>* popOpenList(){
        return pop();
    }

    void addOpenList(State<T> *s){

        push(s);
    }
    //abstract func
    virtual Solution search(Searchable<T> *searchable) = 0;



    //------------overloud func of queue------------
    //push stat to the queue
    void push(State<T> *state) {
        openList.push(state);
    }

    //get state from the queue, and remove the state
    State<T> *pop() {
        State<T> *firstState = top();
        this->openList.pop();
        return firstState;
    }

    //get the top state
    State<T> *top() {
        State<T> *firstState = top();
        return this->openList.pop();
    }

    //check if the state is empty
    bool isEmpty() {
        return openList().empty();
    }

    //get the size of the queue
    unsigned long size() {
        return openList().size();
    }

    //find iter of the queue if does not find return nullptr
    State<T> *find(State<T> *state) {
        vector<State<T> *> vecStates;
        State<T> *tempState;
        State<T> *returnState = nullptr;

        //remove all the state from the queue and check if the state exist
        while (!isEmpty()) {
            tempState = this->pop();
            vecStates.push_back(tempState);
            if (*tempState == *state) {
                returnState = state;
                break;
            }
        }
        //return the queue to the first state
        for (const auto &state : vecStates) {
            this->push(state);
        }
        return returnState;
    }

    bool containInClose(vector<State<T>*> closeVec,State<T> *s) {
        for (const auto &state : closeVec) {
            if(closeVec == s)
                return true;
        }
        return false;
    }
    bool replacePathIfShorter(vector<State<T>*> closeVec,State<T> *state) {
        for (const auto &oldState : closeVec) {
            if(oldState == state && oldState >= state->getCost() ){
                //remove the old state with the long path
                this->erase(oldState);
                //add the sort path
                this->addOpenList(state);
            }

        }

    }


    void erase(State<T> *state) {
        vector<State<T> *> vecStates;
        State<T> *tempState;
        //pop all the state from the queue and check if the state exist
        while (!isEmpty()) {
            tempState = this->pop();
            if (*tempState == *state) {
                free(state);
                delete (state);
                break;
            } else {
                vecStates.push_back(tempState);
            }
        }
        //return the queue to the first state
        for (const auto &state : vecStates) {
            this->push(state);
        }
    }

    // check if exist
    bool isExist(State<T> *state) {
        State<T> *tempState;
        tempState = this->find(state);
        if (tempState == nullptr) {
            return false;
        }
        return true;
    }


};

#endif //FINALPROJECTPART2_MYPRIORTYQUEUE_H
