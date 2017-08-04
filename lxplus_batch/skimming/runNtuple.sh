#!/bin/sh

echo $1
cd /afs/cern.ch/work/s/syu/public/CMSSW_8_0_25/src
export SCRAM_ARCH=slc6_amd64_gcc530; eval `scramv1 runtime -sh`
export X509_USER_PROXY=$HOME/private/grid.proxy
cd $1
root -q -b run.C\($2,\"$3\"\)
rm -rf core*