#include "2Q.hpp"
#include <unordered_map>
#include "ideal.hpp"

static std::unordered_map <int, int> mapa;

int slow_get_page(int key){
    return key;
    //sleep(0.5);
    //return mapa[key] * 1;
}


int main(){
/*
    for(int i = 0; i < 300; i++){
        mapa[i] = std::rand()%100;
    }

    cache_t<int, int> cach(4, 8);
    int b = 0;
    for(int i = 0; i < 300; i++){
        b = std::rand() % 20;
       // std::cout<< F(b)<<std::endl;
        cach.lookup_update(b, slow_get_page);
        cach.print_cache();
    }
*/

    std::vector<int> keys = {1,1,1, 2,3,2,4,5,1};
    std::cout << ideal_cache_hits(&keys, 4) << std::endl;
    


}
