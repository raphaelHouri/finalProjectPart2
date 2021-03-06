//
// Created by meshi on 16/01/2020.
//
#pragma once

#ifndef FINALPROJECTPART2_MYPRIORITYQUEUE_H
#define FINALPROJECTPART2_MYPRIORITYQUEUE_H


#include <iostream>
#include <queue>
#include "SearcherAbstract.h"

using namespace std;
//6.4 -- object functions
template <class T>
class comp {
public:
    bool operator()(State<T> *stateCmp, State<T>* otherState) {
        return stateCmp->getCost() > otherState->getCost();
    }
};


template <class T>

class MyPriorityQueue: public SearcherAbstract<T>  {
    // Data members of class
protected:
    //// Syntax to create a min heap for priority queue
    //priority_queue <type, vector<type>, loading func for min >>
    priority_queue<State<T> *, vector<State<T> *>, comp<T>> openList;
public:
    int openListSize() {
        return (int) size();
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
    bool openContains(State<T> *state) {
        bool flag=this->isExist(state);
        return  flag;
    }
    State<T>* popOpenList(){
        return pop();
    }

    void addOpenList(State<T> *s){
       // this->evaluateNodes++;
        push(s);
    }

    //------------overload func of queue------------
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

        State<T> *firstState = this->openList.top();
        return firstState;
    }

    //check if the state is empty
    bool isEmpty() {
        if(this->openList.empty()){
            return true;
        }
        return false;
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
        for (const auto &state1 : vecStates) {
            this->push(state1);
        }
        return returnState;
    }


    void replacePathIfShorter(vector<State<T>*> closeVec,State<T> *state) {
        for (const auto &oldState : closeVec) {
            if(oldState == state && (oldState->getCost() >= state->getCost()) ){
                //remove the old state with the long path
                this->erase(oldState);
                //add the sort path
                this->addOpenList(state);
            }

        }
    }


    void erase(State<T> *state1) {
        vector<State<T> *> vecStates;
        State<T> *tempState;
        //pop all the state from the queue and check if the state exist
        while (!isEmpty()) {
            tempState = this->pop();
            if (*tempState == *state1) {
                delete (state1);
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


};

#endif //FINALPROJECTPART2_MYPRIORITYQUEUE_H
