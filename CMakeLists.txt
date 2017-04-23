cmake_minimum_required(VERSION 3.6)
project(QuantumInspiredGeneticAlgorithm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        QuantumRegister.cpp QuantumRegister.h
        Algorithms/QIGA.cpp Algorithms/QIGA.h

        Operators/QuantumRotationGate.cpp Operators/QuantumRotationGate.h
        Operators/MutQuantumInversion.cpp Operators/MutQuantumInversion.h
        Operators/MutQuantumSwap.cpp Operators/MutQuantumSwap.h

        Problems/FunctionMin/FunctionMinEvalOp.cpp Problems/FunctionMin/FunctionMinEvalOp.h
        Problems/Knapsack/KnapsackEvalOp.cpp Problems/Knapsack/KnapsackEvalOp.h

        Problems/NeuralNetwork/NeuralNetwork.cpp Problems/NeuralNetwork/NeuralNetwork.h
        Problems/NeuralNetwork/NNErrorEvalOp.cpp Problems/NeuralNetwork/NNErrorEvalOp.h
        Problems/NeuralNetwork/Algorithms/Backpropagation.cpp Problems/NeuralNetwork/Algorithms/Backpropagation.h
        Problems/NeuralNetwork/Crossovers/CrsNeuronUniform.cpp Problems/NeuralNetwork/Crossovers/CrsNeuronUniform.h
        Problems/NeuralNetwork/Crossovers/CrsLayer.cpp Problems/NeuralNetwork/Crossovers/CrsLayer.h
        Problems/NeuralNetwork/Crossovers/CrsNeuron.cpp Problems/NeuralNetwork/Crossovers/CrsNeuron.h
        Problems/NeuralNetwork/Mutations/MutScaleNeuron.cpp Problems/NeuralNetwork/Mutations/MutScaleNeuron.h
        Problems/NeuralNetwork/Mutations/MutScale.cpp Problems/NeuralNetwork/Mutations/MutScale.h
        Problems/NeuralNetwork/Mutations/MutGauss.cpp Problems/NeuralNetwork/Mutations/MutGauss.h
        Problems/NeuralNetwork/Mutations/MutNeuron.cpp Problems/NeuralNetwork/Mutations/MutNeuron.h
        Problems/NeuralNetwork/Mutations/MutNeuronN.cpp Problems/NeuralNetwork/Mutations/MutNeuronN.h
        Problems/NeuralNetwork/ActivationFunctions/AbstractActivationFunction.cpp Problems/NeuralNetwork/ActivationFunctions/AbstractActivationFunction.h
        Problems/NeuralNetwork/ActivationFunctions/LinearFunction.cpp Problems/NeuralNetwork/ActivationFunctions/LinearFunction.h
        Problems/NeuralNetwork/ActivationFunctions/SigmoidFunction.cpp Problems/NeuralNetwork/ActivationFunctions/SigmoidFunction.h
        Problems/NeuralNetwork/ActivationFunctions/SineFunction.cpp Problems/NeuralNetwork/ActivationFunctions/SineFunction.h
        )

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
