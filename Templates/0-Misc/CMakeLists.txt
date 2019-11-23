cmake_minimum_required(VERSION 3.15)
project(contest)

set(CMAKE_CXX_STANDARD 14) # needed?
set(CMAKE_CXX_FLAGS "-O0 -g -std=c++14 -Wall -fsanitize=address -fsanitize=undefined -DLOCAL_EXEC -I/home/anurudh/Documents/coding/CP/platforms/.includes")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..) # basically folder with source code
set(srcs a b c d e f g h i j k l problem) # adjust names as necessary
foreach(F IN LISTS srcs)
    add_executable(${F}.out ${F}.cpp)
endforeach()
cmake_minimum_required(VERSION 3.15)
project(contest)

set(CMAKE_CXX_STANDARD 14) # needed?
set(CMAKE_CXX_FLAGS "-O0 -g -std=c++14 -Wall -fsanitize=address -fsanitize=undefined -DLOCAL_EXEC -I/home/anurudh/Documents/coding/CP/platforms/.includes")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..) # basically folder with source code
set(srcs a b c d e f g h i j k l problem) # adjust names as necessary
foreach(F IN LISTS srcs)
    add_executable(${F}.out ${F}.cpp)
endforeach()
