#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=5

queue=8nm

if [ $# -eq $(( EXPECTED_ARGS - 1 )) ]
then
    echo "batch job queue is set to "$queue
else if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: ./$scriptname ROOTMacroNameWithout.C userid remote_directory output_directory_prefix queue"
    echo "Example: ./$scriptname muVariable khurana SingleMuon trial 1nh"
    exit 1
else
    queue=$5
fi
fi

workdir=$PWD
macroprefix=$1
userid=$2
echo "user id is "$userid
macro=$workdir/${macroprefix}.C
topdir=$3
outputdir=${4}_${topdir}

if [[ ! -e $macro ]]; then
    echo $macro " does not exist!"
    exit 0;
fi

if [[ ! -e $outputdir ]]; then
    echo "creating directory "$outputdir
    mkdir $outputdir
else
    echo "directory "$outputdir" exists!"
    exit 0;
fi

### Compile the macro first

$workdir/compile.csh $workdir $macroprefix

## move to subdirectory
cd $outputdir


### Check which files need to be processed
list=inputfileslist.txt
rm -rf $list
python $workdir/MakeEOSDirTree.py $topdir $userid


iteration=0
lastfile=`cat $list | wc -l`
echo "There are "$lastfile" input files"
while [ $iteration -lt $lastfile ]; 
do
  iteration=$(( iteration + 1 ))
  inputfile=(`head -n $iteration $list  | tail -1`)
  outputfile=output`echo ${inputfile##*NCUGlobalTuples}`
  currentdir=$PWD/$jobdir
#  $workdir/runShared.csh $currentdir $workdir $macroprefix $inputfile $outputfile
 bsub -q$queue $workdir/runShared.csh $currentdir $workdir $macroprefix $inputfile $outputfile

done


cd -



