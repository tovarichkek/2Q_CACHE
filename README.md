# 2Q_CACHE
Realisation of 2Q cache from vladimirov course

# CACHE
Cache uses 2Q model with two lists, it uses two buffers, provationary buffer with 20% of all size and protected buffer - remaining share. 
Coefficient(20%) can be changed in file 2Q.hpp like constant.
Format of input/output
INPUT: size_cache count_elems [elems]
OUTPUT: hits

# IDEAL
Compare with ideal cache(if we could see the future elements)
Format of input/output
INPUT: size_cache count_elems [elems]
OUTPUT: hits ideal_hits

# TEST
Tests are in tests.txt, if you would change(add or remove some tests) format: cache_size count_elems [elems] hits

# MAKE
Write 
cmake CMakeLists.txt
then for each part of programm you can use make
make all - create executable files main, compare_with_ideal and test
