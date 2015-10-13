#!/bin/bash


export SCRAM_ARCH=slc6_amd64_gcc481; eval `scramv1 runtime -sh`

#### X->hh->4b
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M2000.lhe outputFile=2HDMhh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M4500.lhe outputFile=2HDMhh4b_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M2000.lhe outputFile=RShh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_1.lhe,root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500.root

