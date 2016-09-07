//
//  robo.cpp
//  aspiradorPo
//
//  Created by Rafael Auyer on 22/08/16.
//  Copyright © 2016 Rafael Auyer. All rights reserved.
//

#include "robo.hpp"
#include "findpath.hpp"
#include <utility>
#include <vector>
#include <algorithm>

//Getters

inline void robo::test(){this->location={5,5};}

inline int robo::getMaxBattery(){return this ->maxBaterry;}

inline bool robo::getInBase(){return this->inBase;};

inline std::pair<int,int> robo::getDestination(){return this->destination;}

inline std::pair<int,int> robo::getLocation(){return this->location;}

inline int robo::missingCharge(){return this->getMaxBattery() - this->battery;}

inline void robo::setPath(std::pair<int, int> node){this->path.push_back(node);}

inline void robo::setLocation(std::pair<int, int> newLocation){this->location.first=newLocation.first; this->location.second=newLocation.second;}
inline void robo::setDistanceToDestination(float distance){this->distanceToDestination=distance;}

inline float robo::getDistance(){return this->distanceToDestination;}

inline void robo::setDestination(std::pair<int, int> dest){this->destination=dest;}
//methods

inline void robo::discharge(){this->battery --;};

float robo::heuristic(pair<int, int> dest){return (fabsf(this->location.first - dest.first) + fabsf(this->location.second - dest.second));}

void robo::baseCharge(){
    this->battery += this->getMaxBattery()*0.125;
    if (this->battery>=this->getMaxBattery()){
        this->battery=this->getMaxBattery()+1;
    }
};

bool robo::move(vector< vector<int> >& map){
    map[this->location.first][this->location.second]=0;
    this->setLocation(this->path.back());
    //this->location = this->path.back();
    this->path.pop_back();
    map[this->location.first][this->location.second]=5;
    if(this->location.first == 0 && this->location.second ==0){
        this->inBase = true;
    }else{
        this->inBase = false;
        this->distanceToDestination= fabsf(this->location.first - this->destination.first) + fabsf(this->location.second - this->destination.second);
    }
    return true;
};



bool robo::camera(const vector< vector<int> >& map){
    for(int x = 0; x<MAP_WIDTH; x++){
        for (int y=0; y<MAP_HEIGHT; y++) {
            if(map[x][y]==1){
                float distance =1.5*fabsf(x - this->location.first) + fabsf(y - this->location.second);
                if(this->distanceToDestination > 1+distance){
                    this->destination.first=x; this->destination.second=y;
                    this->distanceToDestination = distance;
                    return true;
                }
            }
        }
    }
    return false;
}

//constructor
robo::robo(){
    this->inBase=true;
    this->battery=75;
    this->location={0,0};
    this->distanceToDestination=2*MAP_WIDTH*MAP_HEIGHT;
    this->maxBaterry=75;
    for(int x = 0; x<MAP_WIDTH; x++){
        visualMap.push_back({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
    }
    this->visualMap[0][0]=5;
    this->visualMap[3][3]=1;
}


void printState(vector< vector<int> >& visualMap){
    cout <<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    for(int i =0; i< MAP_WIDTH;i++){
        for (int j=0; j<MAP_HEIGHT; j++) {
            cout << visualMap[i][j]<<" ";
        }
        cout <<"\n";
    }
}



void cycle(robo& aspirator){
    printState(aspirator.visualMap);
    if(rand()%100<15){
        int randx = rand()%15, randy = rand()%15;
        if (aspirator.visualMap[randx][randy]!=5) {
            aspirator.visualMap[randx][randy]=1;
        }
        aspirator.visualMap[rand()%14][rand()%14]=1;
    }
    
    
    if (aspirator.getInBase()){
        if(aspirator.missingCharge()<=0){
            aspirator.path.clear();
            aspirator.camera(aspirator.visualMap);
            aStarsearch(aspirator);
            aspirator.move(aspirator.visualMap);
        }else{aspirator.baseCharge();}
        aspirator.discharge();
    }else if ((aspirator.getMaxBattery()-aspirator.missingCharge())<=5+int(aspirator.heuristic({0,0}))){
        aspirator.setDestination({0,0});
        aspirator.path.clear();
        aStarsearch(aspirator);
        aspirator.setDistanceToDestination(0);
        aspirator.move(aspirator.visualMap);
        
    }else{
        if(aspirator.camera(aspirator.visualMap)){
            aspirator.path.clear();
            aStarsearch(aspirator);
        }
        aspirator.move(aspirator.visualMap);
    }
    if (aspirator.getDestination()==aspirator.getLocation()) {
        aspirator.setDistanceToDestination(2*MAP_WIDTH*MAP_HEIGHT);
    }
    printState(aspirator.visualMap);
    //imprime Estado Mapa
};


int aStarsearch(robo& aspirator){
    AStarSearch<MapSearchNode> astarsearch;
    
    unsigned int SearchCount = 0;
    
    const unsigned int NumSearches = 1;
    
    while(SearchCount < NumSearches)
    {
        
        // Create a start state
        MapSearchNode nodeStart;
        nodeStart.x = aspirator.getLocation().first;
        nodeStart.y = aspirator.getLocation().second;
        
        // Define the goal state
        MapSearchNode nodeEnd;
        nodeEnd.x = aspirator.getDestination().first;
        nodeEnd.y = aspirator.getDestination().second;
        
        // Set Start and goal states
        
        astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );
        
        unsigned int SearchState;
        unsigned int SearchSteps = 0;
        
        do
        {
            SearchState = astarsearch.SearchStep();
            
            SearchSteps++;
            
#if DEBUG_LISTS
            
            cout << "Steps:" << SearchSteps << "\n";
            
            int len = 0;
            
            cout << "Open:\n";
            MapSearchNode *p = astarsearch.GetOpenListStart();
            while( p )
            {
                len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                ((MapSearchNode *)p)->sendNodeInfo();
#endif
                p = astarsearch.GetOpenListNext();
                
            }
            
            cout << "Open list has " << len << " nodes\n";
            
            len = 0;
            
            cout << "Closed:\n";
            p = astarsearch.GetClosedListStart();
            while( p )
            {
                len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                p->sendNodeInfo();
#endif
                p = astarsearch.GetClosedListNext();
            }
            
            cout << "Closed list has " << len << " nodes\n";
#endif
            
        }
        while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );
        
        if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
        {
            //cout << "Search found goal state\n";
            
            MapSearchNode *node = astarsearch.GetSolutionStart();
            
#if DISPLAY_SOLUTION
            //cout << "Displaying solution\n";
#endif
            int steps = 0;
            
            aspirator.setPath(node->sendNodeInfo());
            for( ;; )
            {
                node = astarsearch.GetSolutionNext();
                
                if( !node )
                {
                    break;
                }
                //daiashdiuabd
                aspirator.setPath(node->sendNodeInfo());
                steps ++;
                
            };
            
            //cout << "Solution steps " << steps << endl;
            
            // Once you're done with the solution you can free the nodes up
            astarsearch.FreeSolutionNodes();
            
            
        }
        else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
        {
            cout << "Search terminated. Did not find goal state\n";
            
        }
        
        // Display the number of loops the search went through
        //cout << "SearchSteps : " << SearchSteps << "\n";
        
        SearchCount ++;
        
        astarsearch.EnsureMemoryFreed();
        reverse(aspirator.path.begin(), aspirator.path.end());
        aspirator.path.pop_back();
    }
    return 0;
}