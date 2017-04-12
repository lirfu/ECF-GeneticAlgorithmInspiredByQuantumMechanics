#!/bin/bash

problemName="NeuralNetwork"

compute=false
display=true
NOTIFY=false

while [[ $# -gt 0 ]]
do
	case "$1" in
	    -c|--compute)
		compute=true
	    ;;
	    -q|--quiet)
		display=false
	    ;;
	    -n|--notify)
		NOTIFY=true
	    ;;
	    -h|--help)
	    	echo "compare - Runs the classical vs. quantum comparison."
	    	echo ""
	    	echo "Usage:"
	    	echo " compare [-flag1 -flag2 ...]"
	    	echo ""
	    	echo "Flags:"
	    	echo " -h, --help       Show this help message."
	    	echo " -c, --compute    Run the programs and generate new log files."
	    	echo " -q, --quiet      Don't display the results in a graph."
	    	echo " -n, --notify     Send a Slack notification via curl on finish (please add the Slack web-hook data to your script before use)."
	    	echo ""
	    	echo "Made by lirfu"
	    	echo -e "\e[0m"
	    	exit 0
	    ;;
	    *)
		echo "Unknown flag $1."
		exit 1
	    ;;
	esac
	shift # Past argument.
done

if $compute
then

    # Remove old logs.
    rm classical_full.log quantum_full.log classicalMin.log classicalMax.log quantumMin.log quantumMax.log joinedMin.tmp joinedMax.tmp 2> /dev/null

    echo "Starting the programs!"

    # Start the threads.
    ../cmake-build-debug/QuantumInspiredGeneticAlgorithm ../Problems/"$problemName"/parametersClassical.txt > classical_full.log &
    class=$!
    ../cmake-build-debug/QuantumInspiredGeneticAlgorithm ../Problems/"$problemName"/parametersQuantum.txt > quantum_full.log &
    quant=$!

    # Print out the PIDs, in case of processor overkill.
#    echo "PID classical: $class"
#    echo "PID quantum:   $quant"

    # Wait for both threads to finish.
    wait

    # Process log files (extract mins).
     egrep "^[[:space:]]+min: +[0-9]+" classical_full.log | sed -E "s/min: ([0-9]+\.*[0-9]*).*/\1/" > classicalMin.log
     egrep "^[[:space:]]+min: +[0-9]+" quantum_full.log | sed -E "s/min: ([0-9]+\.*[0-9]*).*/\1/" > quantumMin.log

     # Process log files (extract max).
     egrep "^[[:space:]]+max: +[0-9]+" classical_full.log | sed -E "s/max: ([0-9]+\.*[0-9]*).*/\1/" > classicalMax.log
     egrep "^[[:space:]]+max: +[0-9]+" quantum_full.log | sed -E "s/max: ([0-9]+\.*[0-9]*).*/\1/" > quantumMax.log

    # Process log files (extract avgs).
     egrep "^[[:space:]]+avg: +[0-9]+" classical_full.log | sed -E "s/avg: ([0-9]+\.*[0-9]*).*/\1/" > classicalAvg.log
     egrep "^[[:space:]]+avg: +[0-9]+" quantum_full.log | sed -E "s/avg: ([0-9]+\.*[0-9]*).*/\1/" > quantumAvg.log

    # Process log files (extract stdevs).
     egrep "^[[:space:]]+stdev: +[0-9]+" classical_full.log | sed -E "s/stdev: ([0-9]+\.*[0-9]*).*/\1/" > classicalStdev.log
     egrep "^[[:space:]]+stdev: +[0-9]+" quantum_full.log | sed -E "s/stdev: ([0-9]+\.*[0-9]*).*/\1/" > quantumStdev.log


    # Join the logs.
    paste -d : classicalMin.log quantumMin.log > joinedMin.tmp
    paste -d : classicalMax.log quantumMax.log > joinedMax.tmp
    paste -d : classicalAvg.log quantumAvg.log > joinedAvg.tmp
    paste -d : classicalStdev.log quantumStdev.log > joinedStdev.tmp

    echo "Finished!"

else
    echo "Displaying pre-generated results."
fi

# Store final fitness values and generations to achieve.
classFit=$(grep "FitnessM" classical_full.log | sed -E "s/<FitnessM.. value=\"([0-9]+\.*[0-9]*).*/\1/")
quantFit=$(grep "FitnessM" quantum_full.log | sed -E "s/<FitnessM.. value=\"([0-9]+\.*[0-9]*).*/\1/")
classGen=$(grep "<Individual" classical_full.log | sed -E "s/<Individual.+gen=\" *([0-9]+\.*[0-9]*).*/\1/")
quantGen=$(grep "<Individual" quantum_full.log | sed -E "s/<Individual.+gen=\" *([0-9]+\.*[0-9]*).*/\1/")

# Print final fitness values and generations.
echo "Classical: $classFit    (gen $classGen)"
echo "Quantum:   $quantFit    (gen $quantGen)"

if $NOTIFY
then
    # Send a Slack notification.
    curl -X POST --data-urlencode 'payload={"channel": "***YOUR_CHANNEL_HERE***", "username": "CGAvsQIGA", "text": "Finished processing the CGA-QIGA comparison.", "icon_emoji": ":ant:", "color": "#00bb44"}' ***YOUR_HOOK_ID***
fi


if $display
then
# Display the fitness comparison graph.
java -jar GeneralGraphPlotter.jar joinedMin.tmp joinedMax.tmp joinedAvg.tmp joinedStdev.tmp &
fi