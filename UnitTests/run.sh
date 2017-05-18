#!/bin/bash
# Unit testing framework
# Created by lirfu on 27.04.17.

# TestFrame - defines the common testing and error reporting methods
# tests/ - holds C++ component tests
# .executables/ - holds generated binaries for tests (prevents compiling unchanged tests)

# From: cmake-build-debug/CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/link.txt
projectLinks="CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/QuantumRegister.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Algorithms/GAIQM.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Operators/QuantumRotationGate.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Operators/MutQuantumInversion.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Operators/MutQuantumSwap.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/FunctionMin/FunctionMinEvalOp.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/Knapsack/KnapsackEvalOp.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/NeuralNetwork.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/NNErrorEvalOp.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Algorithms/Backpropagation.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Crossovers/CrsNeuronUniform.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Crossovers/CrsLayer.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Crossovers/CrsNeuron.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Mutations/MutScaleNeuron.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Mutations/MutScale.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Mutations/MutGauss.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Mutations/MutNeuron.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/Mutations/MutNeuronN.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/ActivationFunctions/AbstractActivationFunction.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/ActivationFunctions/LinearFunction.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/ActivationFunctions/SigmoidFunction.cpp.o CMakeFiles/QuantumInspiredGeneticAlgorithm.dir/Problems/NeuralNetwork/ActivationFunctions/SineFunction.cpp.o "
projectLinks=$(for i in $(echo $projectLinks); do echo $i | sed -Ee 's/(.+)/..\/cmake-build-debug\/\1/g'; done)

rootdir=$(pwd)
tests="$rootdir/tests/"
executables="$rootdir/.executables/"

if [ ! -f "$rootdir/TestFrame.o" -o "$rootdir/TestFrame.h" -nt "$rootdir/TestFrame.o" ] ; then
    echo 'Compiling the TestFrame...'
    rm $rootdir/TestFrame.o 2> /dev/null
    g++ -std=c++11 -lecf -c -o $rootdir/TestFrame.o $rootdir/TestFrame.cpp
fi

echo "Running tests..."
echo

passed=0
testNum=0
for f in $(find $tests/* -type f -printf "%f\n"); do

    filename=$(echo $f | sed -E "s/(.+)(\..+)$/\1/")

    if [ ! -f "$executables$filename.exe" -o "$tests$filename.cpp" -nt "$executables$filename.exe" ]; then
        rm $executables$filename.exe $executables$filename.o 2> /dev/null
        echo "Compiling the $filename..."
        g++ -std=c++11 -Wno-write-strings -lecf -c -o $executables$filename.o $tests$filename.cpp
        g++ -std=c++11 $rootdir/TestFrame.o $executables$filename.o $projectLinks -lecf -o $executables$filename.exe
#        echo "g++ -std=c++11 $rootdir/TestFrame.o $executables$filename.o -lecf -o $executables$filename.exe"
    fi

    if $executables$filename.exe; then
        ((passed++))
        echo -e "\e[32mPASS: $f\e[0m"
    else
        echo -e "\e[31mFAIL: $f\e[0m"
    fi

    ((testNum++))
done

echo
echo "Passed $passed/$testNum"