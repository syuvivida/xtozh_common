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

### ask for gluon fusion only

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M2000.lhe outputFile=2HDMhh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M4500.lhe outputFile=2HDMhh4b_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M2000.lhe outputFile=RShh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_1.lhe,root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_gluon.root


### ask for DY only

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M2000.lhe outputFile=2HDMhh4b_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M4500.lhe outputFile=2HDMhh4b_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M2000.lhe outputFile=RShh4b_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_1.lhe,root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_DY.root



#### apply |eta(H)|<2.5 and |delta eta(H,H)|<1.3

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M2000.lhe outputFile=2HDMhh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M4500.lhe outputFile=2HDMhh4b_M4500_etacut.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M2000.lhe outputFile=RShh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_1.lhe,root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_etacut.root

### ask for gluon fusion only

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_gluon_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M2000.lhe outputFile=2HDMhh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M4500.lhe outputFile=2HDMhh4b_M4500_gluon_etacut.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M2000.lhe outputFile=RShh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_1.lhe,root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_gluon_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_gluon_etacut.root



### ask for DY only

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_DY_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_DY_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M2000.lhe outputFile=2HDMhh4b_M2000_DY_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/2HDM_hh_M4500.lhe outputFile=2HDMhh4b_M4500_DY_etacut.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M2000.lhe outputFile=RShh4b_M2000_DY_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_1.lhe,root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_DY_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_DY_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=True inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/hh4b/LHE/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_DY_etacut.root


#### X->WW->qqll

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Radion_WW_M2000.lhe outputFile=RadionWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Radion_WW_M4500.lhe outputFile=RadionWW_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Zprime_WW_M2000.lhe outputFile=ZprimeWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Zprime_WW_M4500.lhe outputFile=ZprimeWW_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/RS_WW_M2000.lhe outputFile=RSWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/RS_WW_M4500.lhe outputFile=RSWW_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Bulk_WW_M2000.lhe outputFile=BulkWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Bulk_WW_M4500.lhe outputFile=BulkWW_M4500.root


### ask for gluon fusion only

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Radion_WW_M2000.lhe outputFile=RadionWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Radion_WW_M4500.lhe outputFile=RadionWW_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Zprime_WW_M2000.lhe outputFile=ZprimeWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Zprime_WW_M4500.lhe outputFile=ZprimeWW_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/RS_WW_M2000.lhe outputFile=RSWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/RS_WW_M4500.lhe outputFile=RSWW_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Bulk_WW_M2000.lhe outputFile=BulkWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=1 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Bulk_WW_M4500.lhe outputFile=BulkWW_M4500_gluon.root



### ask for DY only

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Radion_WW_M2000.lhe outputFile=RadionWW_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Radion_WW_M4500.lhe outputFile=RadionWW_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Zprime_WW_M2000.lhe outputFile=ZprimeWW_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Zprime_WW_M4500.lhe outputFile=ZprimeWW_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/RS_WW_M2000.lhe outputFile=RSWW_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/RS_WW_M4500.lhe outputFile=RSWW_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Bulk_WW_M2000.lhe outputFile=BulkWW_M2000_DY.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=2 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/Bulk_WW_M4500.lhe outputFile=BulkWW_M4500_DY.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/2HDM_WW_M2000.lhe outputFile=2HDMWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fprod=0 fhh=False inputFiles=root://eoscms//eos/cms//store/group/phys_exotica/exovv/LHE/2HDM_WW_M4500.lhe outputFile=2HDMWW_M4500.root
