#!/bin/bash

input_file="input.txt"
time_in=`cat $input_file| head -n 1| grep -o '[0-9]*'| tr '\n' ' '`
distance_in=`cat $input_file| tail -n 1| grep -o '[0-9]*'| tr '\n' ' '`

time=($time_in)
dist=($distance_in)

# Part 1

result=1
for (( i=0; i<${#time[@]}; i++ )) ; {
  curr_time=${time[$i]}
  curr_dist=${dist[$i]}

  echo "Counting: $curr_time $curr_dist"

  ways=0
  for (( n=0; n<$curr_time; n++ )) ; {
    d=$(( ($curr_time - $n)*n ))

    if [ $d -gt $curr_dist ]; then
      ways=$(( $ways + 1 ))
    fi
  }

  result=$(( $result*$ways ))
}

echo "Result: $result"
echo ""

# Part 2
# Could be done with binary search but i wont implement it in bash xd

time=`echo $time_in| sed 's/ //g'`
dist=`echo $distance_in| sed 's/ //g'`

echo "Time: $time"
echo "Dist: $dist"

fails=0
for (( n=0; n<$time; n++ )) ; {
  d=$(( ($time - $n)*n ))

  if [ $d -le $dist ]; then
    fails=$(( $fails + 1 ))
  else
    break
  fi
}

result=$(( $time - (2*$fails) + 1 ))

echo "Result: $result"
