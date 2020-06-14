#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 3 ]
then
    echo "1 to 3 parameters are required"
    echo "$0 macroName"
    echo "$0 macroName inputFile"
    echo "$0 macroName inputFile outputFile"
    exit 1
fi


if [[ ${1} =~ ".C" ]]
then
    exeMacro=${1}
else
    exeMacro=${1%.h}.C
fi
inputFile=${2}
outputVar=${3}

if [[ ! -f ${exeMacro} ]] || [[ ! -f ${exeMacro%C}h ]];
then
    echo "Cannot find ${exeMacro} and ${exeMacro%C}h"
    exit 2
fi

# set environment variables
SECONDS=0

if [[ -d /cvmfs/cms.cern.ch/  ]]
then 
    source /cvmfs/cms.cern.ch/cmsset_default.sh
    export SCRAM_ARCH=slc7_amd64_gcc530
    export X509_USER_PROXY=/afs/cern.ch/user/s/shuxiao/private/grid.proxy
    echo
    echo "X509_USER_PROXY=$X509_USER_PROXY"
else
    echo "run in local mode"
    echo "use environment setting"
fi
echo

# replace code 
sed -i "/GetListOfFiles/s|^/*|//|g" ${exeMacro%.C}.h
if [[ -z $(eval "grep '\*f = 0' ${exeMacro%.C}.h") ]]; then sed -i "/TFile.*GetListOf.*/i TFile *f = 0; \/\/ Auto generation" ${exeMacro%.C}.h ;fi
sed -i "s/new TFile/TFile::Open/g" ${exeMacro%.C}.h
sed -i "s/dir->GetObject/f->GetObject/g" ${exeMacro%.C}.h
sed -i "/TDirectory/s|^/*|//|g" ${exeMacro%.C}.h
dirprefix=$(eval "grep \"TDirectory\" ${exeMacro%.C}.h | cut -d '\"' -f 2")
if [[ -n ${dirprefix} ]];
then
    dirprefix=${dirprefix##*:/}
    replacetxt=$(eval "grep GetObject ${exeMacro%.C}.h | cut -d '\"' -f2")
    sed -i "/GetObject/s|${replacetxt}|${dirprefix}/${replacetxt}|g" ${exeMacro%.C}.h
fi

# replace input & output
if [[ ${inputFile} =~ ".root" ]]
then
    echo "Replace input file"
    oriinput=$(eval "grep 'TFile::Open.*root' ${exeMacro%.C}.h | grep -v '//.*f ' ")
    oriinput=${oriinput%);*}
    oriinput=${oriinput#*Open(}
    echo "original input file: " ${oriinput}
    echo "new input file: " ${inputFile}
    sed -i "s|${oriinput}|\"${inputFile}\"|g" ${exeMacro%.C}.h
    echo
fi

if [[ ${outputVar} =~ ".root" ]]
then
    echo "Replace output"
    orioutput=$(eval "grep --ignore-case '.*new TFile' ${exeMacro} | grep -v '//.*new.* TFile'") 
    orioutput=$(eval "echo \$orioutput | grep -o \"(.*,\" | cut -d ',' -f 1")
    ## orioutput=${orioutput#}
    orioutput=${orioutput#(}
    echo "original output file: " ${orioutput}
    echo "new output file: " ${outputVar}
    sed -i "s|${orioutput}|\"${outputVar}\"|g" ${exeMacro}
    echo 
fi

# RUNNING

echo "running macro..."
echo "exeMacro=${exeMacro}"
echo 'root -b -q -e "gROOT->Macro(\"${exeMacro}\");gROOT->ProcessLine(\"${exeMacro%.C} t;t.Loop()\")"'
root -b -q -e "gROOT->Macro(\"${exeMacro}\");gROOT->ProcessLine(\"${exeMacro%.C} t;t.Loop()\")"
## root -b -q -e "gROOT->Macro(\"${exeMacro}\");gROOT->ProcessLine(\"${exeMacro%.C} t;t.Loop(\\\"${outputVar}\\\")\")"

duration=$SECONDS
echo
echo -e "RUN TIME: $(($duration / 60)) minutes and $(($duration % 60)) seconds"
echo "Done"

# replace back
sed -i "s|\"${inputFile}\"|${oriinput}|g" ${exeMacro%.C}.h
sed -i "s|\"${outputVar}\"|${orioutput}|g" ${exeMacro}
