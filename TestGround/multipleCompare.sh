#!/bin/bash

if [ $# -gt 0 ]
then
    size=$1
else
    size=3
fi

avgFitC=0
avgGenC=0
avgFitQ=0
avgGenQ=0

rm multiple_full.log 2> /dev/null


for i in $(seq 1 $size);
do
    ./compare.sh -c -q > multiple_full.tmp

    tmp=$(cat multiple_full.tmp | grep Classical | tr -d '\t' | sed -E "s/Classical: +([0-9]+\.*[0-9]*).+/\1/")
    avgFitC=$(echo "$avgFitC + $tmp" | bc)

    tmp=$(cat multiple_full.tmp | grep Classical | tr -d '\t' | sed -E "s/.+\(gen +([0-9]+)\).*/\1/")
    avgGenC=$(echo "$avgGenC + $tmp" | bc)

    tmp=$(cat multiple_full.tmp | grep Quantum | tr -d '\t' | sed -E "s/Quantum: +([0-9]+\.*[0-9]*).+/\1/")
    avgFitQ=$(echo "$avgFitQ + $tmp" | bc)

    tmp=$(cat multiple_full.tmp | grep Quantum | tr -d '\t' | sed -E "s/.+\(gen +([0-9]+)\).*/\1/")
    avgGenQ=$(echo "$avgGenQ + $tmp" | bc)

    perc=$(echo "$i * 100 / $size" | bc)
    echo "$perc% done"
    rm multiple_full.tmp
done

avgFitC=$(echo "$avgFitC / $size" | bc -l)
avgGenC=$(echo "$avgGenC / $size" | bc -l)
avgFitQ=$(echo "$avgFitQ / $size" | bc -l)
avgGenQ=$(echo "$avgGenQ / $size" | bc -l)

echo
echo "Classical:"
echo "    Average fitness:     $avgFitC"
echo "    Average generations: $avgGenC"
echo "Quantum:"
echo "    Average fitness:     $avgFitQ"
echo "    Average generations: $avgGenQ"