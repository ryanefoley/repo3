//
//  File.cpp
//  Pathfinder
//
//  Created by Ryan Foley on 10/21/12.
//  Copyright (c) 2012 Stanford. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <time.h>

int main() {

    time_t start = time(NULL);
    
    int i = 0;
    for (int n=0; n < 100000000; n++) {
        i = n;
    }
        
    time_t end = time(NULL);
    
    std::cout<<end - start<<end;
}