//
// Created by raph on 1/16/20.
//

#ifndef FINALPROJECTPART2_BESTFIRSTSEARCHER_H
#define FINALPROJECTPART2_BESTFIRSTSEARCHER_H



#include <string>
#include "Searchable.h"
#include "Searcher.h"
#include "SearcherAbstract.h"

template<class T>
class AStarSearcher : public MyPriorityQueue<Solution, T> {

public:
    vector<State<T> *> search(Searchable<T> *searchable) {

       //// this->numOfNodesEvaluated = 0;
        //add initial state to the priory Queue
        State<T> *init = searchable->getInitialState();
        State<T> *goal = searchable->getGoalState();
        this->addOpenList(init);
        vector<State<T> *> closeVec;
        //if there is not any other State in the queue
        while (!this->isEmpty()) {
           //// this->numOfNodesEvaluated++;
            //start with the min state in the queue
            State<T> *minState = this->popOpenList();
            closeVec.insert(minState);
            //if the state is the goal
            if (searchable->isGoalState(minState)) {
                return this->reversePath(minState, init);
            }
            //return the all Neighbors
            vector<State<T> *> statesVecNeighbors = searchable->getAllPossibleStates(minState);
            for (State<T> *s : statesVecNeighbors) {
                if (!containInClose(closeVec, s) && !this->openContains(s)) {
                    //add the Neighbor to the queue
                    this->addOpenList(s);
                } else {
                    if (!containInClose(closeVec, s)) {
                        //if we found shorter path we will replace it
                        this->replacePathIfShorter(s);
                    }
                }
//            } else if (!pqs.isExistVector(successors[i])) {
//                State<T> *item = pqs.find(successors[i]);
//                if (successors[i]->getCost() < item->getCost()) {
//                    pqs.erase(item);
//                    pqs.pushToOpen(successors[i]);
//                } else {
//                    delete (successors[i]);
//                }
//            } else {
//                delete (successors[i]);
//            }
            }
        }
    }
    ~AStarSearcher(){}
};


};
#endif //FINALPROJECTPART2_BESTFIRSTSEARCHER_H
