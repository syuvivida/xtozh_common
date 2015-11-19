#!/bin/tcsh

cd $1

setenv SCRAM_ARCH slc6_amd64_gcc481; eval `scramv1 runtime -csh`

root -q -b ${2}.C++\(\"$3\",\"$4\"\) 

