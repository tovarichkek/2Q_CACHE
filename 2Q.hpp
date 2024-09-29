#pragma once
#include <stdlib.h>
#include <list>
#include <unordered_map>
#include <iostream>

//sz_coeff - coefficient for share of probationary cache's size to all cache's size
#define sz_coeff 0.2

template <typename T, typename KeyT = int>
struct cache_t{
    //there are probationary buffer and protected buffer
    size_t sz_prob;
    size_t sz_prot;

    std::list<T> prob_cache; //probationary cache
    std::list<T> prot_cache; //protected cache

    using ListIt = typename std::list<T>::iterator;

    std::unordered_map<KeyT, ListIt> prob_hash;
    std::unordered_map<KeyT, ListIt> prot_hash;

    cache_t(size_t sz_){
        sz_prob = int(sz_ * sz_coeff);
        sz_prot = sz_ - sz_prob;
        if(sz_prob == 0){ //if sz_coeff is too small, set sz_prob = 1, sz_prot = sz_ - sz_prob
            sz_prob = 1;
            sz_prot = sz_ - 1;
        }
    } // ctor with common size buffer
    cache_t(size_t sz_prob_, size_t sz_prot_) : sz_prob(sz_prob_), sz_prot(sz_prot_) {} // ctor with sizes of buffers

    bool full_prob() const{
        return prob_hash.size() >= sz_prob;
    }
    bool full_prot() const{
        return prot_hash.size() >= sz_prot;
    }

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) {

        auto hit = prot_hash.find(key);

        if (hit != prot_hash.end()) { // found
            auto eltit = hit->second;
            if (eltit != prot_cache.begin()){
                prot_cache.splice(prot_cache.begin(), prot_cache, eltit, std::next(eltit));
            }
            return true;
        }

        hit = prob_hash.find(key);
        if (hit != prob_hash.end()) { // found
            if(full_prot()){
                ListIt ll = std::prev(prot_cache.end()); //find key in map for last element of list
                for(auto item : prot_hash){
                    if(item.second == ll){
                        prob_hash[item.first] = item.second;
                        prot_hash.erase(item.first);
                        break;
                    }
                }
                prob_cache.splice(prob_cache.begin(), prot_cache, std::prev(prot_cache.end()), prot_cache.end());
            } 
            auto eltit = hit->second;
            prot_cache.splice(prot_cache.begin(), prob_cache, eltit, std::next(eltit));
            prot_hash[key] = prot_cache.begin();    
            prob_hash.erase(key);
            return true;
        }

        if(full_prob()){
            ListIt ll = std::prev(prob_cache.end());
            for(auto item : prob_hash){
                if(item.second == ll){
                    prob_hash.erase(item.first);
                    break;
                }
            }
            prob_cache.pop_back();
        }
        prob_cache.push_front(slow_get_page(key));
        prob_hash[key] = prob_cache.begin();
        return false;
    }

    //print elems in protected and probationary cache in that moment
    void print_cache(){
        std::cout << "elements in caches: " << std::endl;
        std::cout << "protected cache: ";
        for(ListIt it = prot_cache.begin(); it != prot_cache.end(); ++it){
            std::cout << *it << " ";
        }
        std::cout << " /***/ probationary cache: ";
        for(ListIt it = prob_cache.begin(); it != prob_cache.end(); ++it){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};
