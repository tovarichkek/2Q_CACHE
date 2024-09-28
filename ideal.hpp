#pragma once
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "2Q.hpp"



//return count of hits in ideal cache
int ideal_cache_hits(std::vector<int>* keys, int ideal_cache_size){ 
    std::vector<int> ideal_cache; //must use_push_back, because key may be equal initialising value
    int hits = 0;

    int j = 0;
    int index = 0;
    while(j < ideal_cache_size && index < (*keys).size()){
        if(std::find(ideal_cache.begin(), ideal_cache.end(), (*keys)[index]) != ideal_cache.end()){
            hits++;
        }
        else{
            ideal_cache.push_back((*keys)[index]);
            j++;
        }
        index++;
    }
 
    std::vector< std::vector<int>::iterator > maps(ideal_cache_size);
    std::vector<int>::iterator it_next_new_el;
    while(index < (*keys).size()){
        if(std::find(ideal_cache.begin(), ideal_cache.end(), (*keys)[index]) != ideal_cache.end()){
            hits++;
        }
        else{
            auto iter = (*keys).begin();
            std::advance(iter, index + 1);
            for(int i = 0; i < ideal_cache_size; i++){
                maps[i] = std::find(iter, (*keys).end(), ideal_cache[i]);
            }
            it_next_new_el = std::find(iter, (*keys).end(), (*keys)[index]);
            auto max_it = std::max_element(maps.begin(), maps.end());
            if(*max_it > it_next_new_el){
                ideal_cache[std::distance(maps.begin(), max_it)] = (*keys)[index];
            }
        } 
        index++;
    }
    return hits;
}