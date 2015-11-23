#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=4

userid="syu"
extraFile="extra.txt"

if [ $# -eq $(( EXPECTED_ARGS - 1 )) ]
then
    echo "user ID is set to "$userid
else if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: ./$scriptname ROOTMacroNameWithout.C remote_directory output_directory_prefix userID"
    echo "Example: ./$scriptname muVariable SingleMuon trial khurana"
    echo "extra.txt stores the list of extra header files that must be copied to the work directory"
    exit 1
else
    userid=$4
fi
fi

echo "user id is "$userid
workdir=$PWD
macroprefix=$1
macro=$workdir/${macroprefix}.C
extra=$workdir/$extraFile
topdir=$2
outputdir=${3}_${topdir}

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

cd $outputdir

#print output file name
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
  
  jobdir=job_$iteration
  mkdir $jobdir
  cp -p $macro $jobdir/.
  ### If there are other header files that need to be copied
  if [[ -e $extra ]]; then
      temp_n=0;
      temp_extra=`cat $extra | wc -l`      
      while [ $temp_n -lt $temp_extra ]; 
      do
	  temp_n=$(( temp_n + 1 ))
	  headerfile=$workdir/`head -n $temp_n $extra  | tail -1`
#	  echo "copying "$headerfile
	  cp -p $headerfile  $jobdir/.
      done
  fi
  currentdir=$PWD/$jobdir
# $workdir/runJob.csh $currentdir $macroprefix $inputfile $outputfile
  bsub -q1nh $workdir/runJob.csh $currentdir $macroprefix $inputfile $outputfile
done


cd -



