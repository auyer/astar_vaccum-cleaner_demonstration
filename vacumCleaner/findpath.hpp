////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef findpath_hpp
#define findpath_hpp

#include "stlastar.h"
#include <iostream>
//#include <stdio.h>
#include <math.h>
#include <utility>
#include <vector>
#include "globals.hpp"

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

int GetMap( int x, int y );


// Definitions

class MapSearchNode
{
public:
    int x;
    int y;

    MapSearchNode() { x = y = 0; };
    MapSearchNode( int px, int py ) { x=px; y=py; };

    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost( MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );
    pair<int, int> sendNodeInfo();


};

#endif /* findpath_hpp */
