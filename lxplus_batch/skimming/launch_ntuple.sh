#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=1
if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: $scriptname inputTextFile"
    echo "Example: ./$scriptname JetMET_Run2016B.txt"
    exit 1
fi

## vertify proxy ##
inform=$(voms-proxy-info --all | grep -h "VO cms extension information" | wc -l)
if [[ "$inform" -eq "0" ]]; then
    echo "#############################################"
    echo "execute \"voms-proxy-init --voms cms\" ..."
    export X509_USER_PROXY=$HOME/private/grid.proxy
    voms-proxy-init --voms cms
    echo "#############################################"
fi

export PRODHOME=`pwd`
inputfile=$1
rootfileDir="${inputfile%.txt}"
mkdir -p ${rootfileDir}
cp -p runNtuple.sh ${rootfileDir}/.
cp -p run.C ${rootfileDir}/.
cd ${rootfileDir}

iteration=0
lastfile=`cat ../$inputfile | wc -l`
echo "There are "$lastfile" root files"

while [ $iteration -lt $lastfile ]; 
do
  iteration=$(( iteration + 1 ))
  input=(`head -n $iteration ../$inputfile  | tail -1`)
  echo $iteration $input
#bsub -q1nd -R "rusage[mem=12000]" $PWD/runNtuple.sh $PWD $iteration $input
  bsub -q1nh $PWD/runNtuple.sh $PWD $iteration $input 
done
cd -



