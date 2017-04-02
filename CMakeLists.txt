cmake_minimum_required(VERSION 3.6)
project(QuantumInspiredGeneticAlgorithm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Algorithms/QIGA.cpp Algorithms/QIGA.h
        QuantumRegister.cpp QuantumRegister.h
        Problems/FunctionMinEvalOp.cpp Problems/FunctionMinEvalOp.h Operators/QuantumRotationGate.cpp Operators/QuantumRotationGate.h Operators/MutQuantumInversion.cpp Operators/MutQuantumInversion.h Operators/MutQuantumInversion.cpp Operators/MutQuantumInversion.h Operators/MutQuantumSwap.cpp Operators/MutQuantumSwap.h Problems/KnapsackEvalOp.cpp Problems/KnapsackEvalOp.h)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(QuantumInspiredGeneticAlgorithm ${SOURCE_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(QuantumInspiredGeneticAlgorithm /home/lirfu/zavrsni/ECF_lib/release/libECF.a)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(QuantumInspiredGeneticAlgorithm /home/lirfu/zavrsni/ECF_lib/release/libECF.a)
endif()
