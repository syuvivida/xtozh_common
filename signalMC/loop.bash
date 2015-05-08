#!/bin/bash


iteration=700
lastfile=2000
while [ $iteration -lt $lastfile ]; 
do
  iteration=$(( iteration + 100 ))
  echo $iteration
#  bsub -R "type=SLC6_64" -q 8nh $PWD/runJob.sh $PWD $iteration
  sed -e "s/MASSVZ/M"$iteration"/g" xzh_LO_proc_card.dat > xzh_LO_M${iteration}_proc_card.dat
#  sed -e "s/MASSVZ/"$iteration"/g" xzh_LO_param_card.dat > xzh_LO_M${iteration}_param_card.dat
#  awk -v number=$iteration '{print "sed -e \"s/MASSVZ/"$1"/g\" -e \"s/WVZ/"$2"/g\" -e \"s/MASSVC/"$3"/g\" -e \"s/WVC/"$4"/g\" xzh_LO_param_card.dat > xzh_LO_M"number"_param_card.dat"}' parameter.txt
  cp -p xzh_LO_run_card.dat xzh_LO_M${iteration}_run_card.dat 
#  $PWD/runJob.sh $PWD $iteration
done
