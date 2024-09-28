#include <stdio.h>
#include <fstream>
#include "2Q.hpp"


const int MAX_INPUT_LEN = 1000;

int slow_get_page(int key){
    return key;
    //sleep(0.5);
    //return mapa[key] * 1;
}

struct Test{
    size_t cache_size;
    size_t count_elems;
    int* keys;
    size_t answer;
};

int unit_test(size_t cache_size, size_t count_elems, int* keys, size_t answer){
    size_t hits = 0;
    cache_t<int> cache(cache_size);

    for (size_t i = 0; i < count_elems; i++){
        if (cache.lookup_update(keys[i], slow_get_page)){
            hits++;
        }
    }
    return hits;
}

bool test(){
    int tests_accepted = 0;
    int test_number = 0;
    int input[MAX_INPUT_LEN] = {0}; 

    std::ifstream inp;
    inp.open("tests.txt");

    Test td = {0, 0, input, 0};
    
    inp >> td.cache_size >> td.count_elems;
    while (!(inp.eof())){
        
        for (int i = 0; i < td.count_elems; i++) 
            inp >> td.keys[i];
        inp >> td.answer;

        test_number++;
        int hits = unit_test(td.cache_size, td.count_elems, td.keys, td.answer);
        std::cout << "Test number " << test_number << ": ";
        if(hits == td.answer){
            std::cout << "Right" << std::endl;
            tests_accepted += 1;

        }
        else{
            std::cout << "WRONG ANSWER" << std::endl;
            std::cout << "CACHE_SIZE: " << td.cache_size << " / COUNT_ELEMS: " << td.count_elems << std::endl;
            std::cout << "KEYS IN TEST: ";
            for(int i = 0; i < td.count_elems; i++){
                std::cout << td.keys[i] << " ";
            }
            std::cout << std::endl << "RIGHT_ANSWER: " << td.answer << " / PROGRAMM ANSWER: " << hits << std::endl << "**********" << std:: endl;
        }
        inp >> td.cache_size >> td.count_elems; //in the end to detect eof
    }
    
    inp.close();
    return tests_accepted == test_number; 
} 

int main() {
    test();
}