#!/bin/bash

if [ $# -gt 0 ]
then
    size=$1
else
    size=3
fi

avgFitC=0
avgGenC=0
avgEvalC=0
avgFitQ=0
avgGenQ=0
avgEvalQ=0

dataFolder='results'

rm ${dataFolder}/multiple_full.log 2> /dev/null

for i in $(seq 1 $size);
do
    ./compare.sh -c -q > ${dataFolder}/multiple_full.tmp

    tmp=$(cat ${dataFolder}/multiple_full.tmp | grep Classical | tr -d '\t' | sed -E "s/Classical: +(.+) +\(.+/\1/")
    avgFitC=$(echo "$avgFitC + $tmp" | bc -l)

    tmp=$(cat ${dataFolder}/multiple_full.tmp | grep Classical | tr -d '\t' | sed -E "s/.+\(gen +([0-9]+)\).*/\1/")
    avgGenC=$(echo "$avgGenC + $tmp" | bc -l)

	tmp=$(cat "$dataFolder"/joinedEval.tmp | cut -d ':' -f 1)
    avgEvalC=$(echo "$avgEvalC + $tmp" | bc -l)


    tmp=$(cat ${dataFolder}/multiple_full.tmp | grep Quantum | tr -d '\t' | sed -E "s/Quantum: +(.+) +\(.+/\1/")
    avgFitQ=$(echo "$avgFitQ + $tmp" | bc -l)

    tmp=$(cat ${dataFolder}/multiple_full.tmp | grep Quantum | tr -d '\t' | sed -E "s/.+\(gen +([0-9]+)\).*/\1/")
    avgGenQ=$(echo "$avgGenQ + $tmp" | bc -l)

	tmp=$(cat ${dataFolder}/joinedEval.tmp | cut -d ':' -f 2)
    avgEvalQ=$(echo "$avgEvalQ + $tmp" | bc -l)


    perc=$(echo "$i * 100 / $size" | bc -l)
    echo "$perc% done"

done


avgFitC=$(echo "$avgFitC / $size" | bc -l)
avgGenC=$(echo "$avgGenC / $size" | bc -l)
avgEvalC=$(echo "$avgEvalC / $size" | bc -l)

avgFitQ=$(echo "$avgFitQ / $size" | bc -l)
avgGenQ=$(echo "$avgGenQ / $size" | bc -l)
avgEvalQ=$(echo "$avgEvalQ / $size" | bc -l)


echo
echo "Classical:"
echo "    Average fitness:     $avgFitC"
echo "    Average generations: $avgGenC"
echo "    Average evaluations: $avgEvalC"
echo "Quantum:"
echo "    Average fitness:     $avgFitQ"
echo "    Average generations: $avgGenQ"
echo "    Average evaluations: $avgEvalQ"
