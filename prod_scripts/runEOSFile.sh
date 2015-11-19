#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=6

queue=8nm

if [ $# -eq $(( EXPECTED_ARGS - 1 )) ]
then
    echo "batch job queue is set to "$queue
else if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: ./$scriptname ROOTMacroNameWithout.C userid remote_directory string output_directory queue"
    echo "Example: ./$scriptname pseudoMC_onefile syu AbelianZPrime_ZH_lljj_M800-MADGRAPH NCU trial 1nh"
    exit 1
else
    queue=$6
fi
fi

workdir=$PWD
macroprefix=$1
userid=$2
echo "user id is "$userid
macro=$workdir/${macroprefix}.C
topdir=$3
string=$4
outputdir=${5}_${topdir}

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

### Check which files need to be processed

nowdir=`tcsh -c "eos ls /store/user/$userid/$topdir"`
echo $nowdir
newdir="/store/user/$userid/$topdir/$nowdir"
lastdir="/store/user/$userid/$topdir"
string="NCUGlobalTuples"

#find the full path of directories that contain ROOT files
while [[ $nowdir != *"$string"* ]]; 
do
 nowdir=`tcsh -c "eos ls $newdir"`
 lastdir=$newdir
 newdir="$newdir/$nowdir"
 echo $newdir
done

echo "Full path is "$lastdir
cd $outputdir

#print output file name
list=inputFile.txt
rm -rf $list
cmsLs $lastdir | grep -a $string | awk -v my_var=$lastdir '{print "root://eoscms//eos/cms"my_var"/"$1}' >> $list


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



