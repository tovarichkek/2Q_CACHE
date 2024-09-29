#include <unordered_map>
#include "2Q.hpp"
#include "ideal.hpp"


int slow_get_page(int key){
    return key;
    //sleep(0.5);
    //return mapa[key] * 1;
}


int main(){

    int cache_size = 0;
    int count_elems = 0;
    std::cin >> cache_size >> count_elems;
    std::vector<int> keys(count_elems);
    for(int i = 0; i < count_elems; i++){
        std::cin >> keys[i];
    }

    int hits = 0;
    cache_t<int, int> cache(cache_size);
    
    for(int i = 0; i < count_elems; i++){
        hits += cache.lookup_update(keys[i], slow_get_page);
    }
    

    std::cout << "hits : " << hits << std::endl;

    std::cout << "ideal_cache hits: " << ideal_cache_hits(&keys, cache_size) << std::endl;
    


}
