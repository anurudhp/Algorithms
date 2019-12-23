cmake_minimum_required(VERSION 3.15)
project(contest)
set(CMAKE_CXX_STANDARD 14)
if (DEBUG_EXEC) # set in 'Debug'
  set(CMAKE_CXX_FLAGS "-std=c++14 -O0 -g -Wall -pedantic -fsanitize=address -fsanitize=undefined")
else () # in 'Run' and 'OJ'
  set(CMAKE_CXX_FLAGS "-std=c++14 -O2 -Wall")
endif()
if (LOCAL_EXEC) # set in 'Debug' and 'Run'
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOCAL_EXEC")
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..) # folder with source
set(srcs a b c d e f g h i j k l problem) # adjust filenames
foreach(F IN LISTS srcs)
    add_executable(${F}.out ${F}.cpp)
endforeach()
