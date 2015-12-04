#!/bin/bash

if [ -z $1 ]; then

    echo "Usage: $0 [macro without .C]"
    exit 0

fi


#root -q -b -l $1.C++\(\"/data7/syu/special_study/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/\",\"DYJets_LO.root\"\)

#root -q -b -l $1.C++\(\"/data7/syu/NCUGlobalTuples/Spring15_ReMiniAODSim/9b33d00/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/\",\"DYJets_NLO.root\"\)

#root -q -b -l $1.C++\(\"/data7/syu/NCUGlobalTuples/Spring15_ReMiniAODSim/9b33d00/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/\"\,\"DYJetsToLL_M-50_HT-100to200_13TeV.root\"\)
#root -q -b -l $1.C++\(\"/data7/syu/NCUGlobalTuples/Spring15_ReMiniAODSim/9b33d00/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/\"\,\"DYJetsToLL_M-50_HT-200to400_13TeV.root\"\)
#root -q -b -l $1.C++\(\"/data7/syu/NCUGlobalTuples/Spring15_ReMiniAODSim/9b33d00/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/\"\,\"DYJetsToLL_M-50_HT-400to600_13TeV.root\"\)
#root -q -b -l $1.C++\(\"/data7/syu/NCUGlobalTuples/Spring15_ReMiniAODSim/9b33d00/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/\"\,\"DYJetsToLL_M-50_HT-600toInf_13TeV.root\"\)


root -q -b -l $1.C++\(\"/data7/syu/jet_CMSSW747/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/\"\,\"DYJetsToLL_M-50_HT-100to200_13TeV.root\"\)
root -q -b -l $1.C++\(\"/data7/syu/jet_CMSSW747/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/\"\,\"DYJetsToLL_M-50_HT-200to400_13TeV.root\"\)
root -q -b -l $1.C++\(\"/data7/syu/jet_CMSSW747/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/\"\,\"DYJetsToLL_M-50_HT-400to600_13TeV.root\"\)
root -q -b -l $1.C++\(\"/data7/syu/jet_CMSSW747/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/results/\"\,\"DYJetsToLL_M-50_HT-600toInf_13TeV.root\"\)


exit