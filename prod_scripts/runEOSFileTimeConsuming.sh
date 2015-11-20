#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=5

userid="syu"
extraFile="extra.txt"

if [ $# -eq $(( EXPECTED_ARGS - 1 )) ]
then
    echo "user ID is set to "$userid
else if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: ./$scriptname ROOTMacroNameWithout.C remote_directory string output_directory userID"
    echo "Example: ./$scriptname pseudoMC_onefile AbelianZPrime_ZH_lljj_M800-MADGRAPH NCU trial syu"
    echo "extra.txt stores the list of extra header files that must be copied to the work directory"
    exit 1
else
    userid=$5
fi
fi

echo "user id is "$userid
workdir=$PWD
macroprefix=$1
macro=$workdir/${macroprefix}.C
extra=$workdir/$extraFile
topdir=$2
string=$3
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
/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select ls $lastdir | grep -a $string | awk -v my_var=$lastdir '{print "root://eoscms//eos/cms"my_var"/"$1}' >> $list


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
#  $workdir/runJob.csh $currentdir $macroprefix $inputfile $outputfile
  bsub -q1nh $workdir/runJob.csh $currentdir $macroprefix $inputfile $outputfile
done


cd -



