#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=3

userid="syu"
if [ $# -eq $(( EXPECTED_ARGS - 1 )) ]
then
    echo "user ID is set to "$userid
else if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: ./$scriptname remote_directory string userID"
    echo "Example: ./$scriptname AbelianZPrime_ZH_lljj_M800-MADGRAPH flattuple syu"
    exit 1
else
    userid=$3
fi
fi

echo $1
echo "user id is "$userid
string=$2
topdir=$1

if [[ ! -e $topdir ]]; then
    echo "creating directory "$topdir
    mkdir $topdir
else
    echo "directory "$topdir" exists!"
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
cd $topdir

cmsLs $lastdir | grep -a $string | awk -v my_var=$lastdir '{print "xrdcp root://eoscms//eos/cms"my_var"/"$1" "$1}'  | bash

cd -




