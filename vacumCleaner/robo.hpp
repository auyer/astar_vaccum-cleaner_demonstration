//
//  robo.hpp
//  aspiradorPo
//
//  Created by Rafael Auyer on 22/08/16.
//  Copyright © 2016 Rafael Auyer. All rights reserved.
//

#ifndef robo_hpp
#define robo_hpp
#include "findpath.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include "globals.hpp"

typedef vector< vector<int> > Matrix;

class robo {
public:
    inline void test();
    vector<std::pair<int, int> > path ;
    
    vector< vector<int> > visualMap;
    
    //Getters
    
    inline int getMaxBattery();
    
    inline bool getInBase();
    
    inline std::pair<int,int> getDestination();
    
    inline std::pair<int,int> getLocation();
    
    inline float getDistance();
    
    inline int missingCharge();
    
    inline void setPath(std::pair<int, int> node);
    
    inline void setLocation(std::pair<int, int>);
    
    inline void setDistanceToDestination(float distance);
    
    inline void setDestination(std::pair<int, int> dest);
    //methods
    
    float heuristic(pair<int, int>);
    
    
    inline void discharge();
    
    void baseCharge();
    
    bool move(vector< vector<int> >& map);
    
    bool camera(const vector< vector<int> >& map);
    //return true if New node is found
    
    //constructor
    robo();
    
private:
    
    int maxBaterry;
    
    int battery;
    
    float distanceToDestination;
    
    bool inBase;
    
    std::pair<int, int> destination;
    
    std::pair<int, int> location;
};

void cycle(robo&);

int aStarsearch(robo&);
#endif /* robo_hpp */