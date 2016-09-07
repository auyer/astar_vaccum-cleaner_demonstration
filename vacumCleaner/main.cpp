//
//  main.cpp
//  aspiradorPo
//
//  Created by Rafael Auyer on 22/08/16.
//  Copyright © 2016 Rafael Auyer. All rights reserved.
//

#include <iostream>
#include "robo.hpp"
#include <unistd.h>



int main(int argc, const char * argv[]) {

    robo aspirator;
    
    while(true){
        cycle(aspirator);
        usleep(500000);
    }


    return 0;
}
