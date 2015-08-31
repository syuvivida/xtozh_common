#!/bin/bash

cd /afs/cern.ch/work/s/syu/13tev/debug/CMSSW_7_4_7/src

export SCRAM_ARCH=slc6_amd64_gcc491; eval `scramv1 runtime -sh`
cd -

root -q -b xAna_eleID.C++\(\"/data7/syu/13TeV_signalMC/ZprimeToZhToZlephbb\",0\)
root -q -b xAna_eleID.C++\(\"/data7/syu/13TeV_signalMC/ZprimeToZhToZlephbb\",1\)
root -q -b xAna_eleID.C++\(\"/data7/syu/13TeV_signalMC/ZprimeToZhToZlephbb\",2\)
root -q -b xAna_eleID.C++\(\"/data7/syu/13TeV_signalMC/ZprimeToZhToZlephbb\",3\)

root -q -b call_display.C