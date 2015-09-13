#!/bin/bash


export SCRAM_ARCH=slc6_amd64_gcc481; eval `scramv1 runtime -sh`

#### X->hh->4b
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/RS_hh_M2000.lhe outputFile=RShh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/RS_hh_M4500_1.lhe,file:/home/syu/gridpack/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_gluon.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/RS_hh_M2000.lhe outputFile=RShh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/RS_hh_M4500_1.lhe,file:/home/syu/gridpack/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_gluon.root

#### apply |eta(H)|<2.5 and |delta eta(H,H)|<1.3

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=True inputFiles=file:/home/syu/gridpack/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=True inputFiles=file:/home/syu/gridpack/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_etacut.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=True inputFiles=file:/home/syu/gridpack/RS_hh_M2000.lhe outputFile=RShh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=True inputFiles=file:/home/syu/gridpack/RS_hh_M4500_1.lhe,file:/home/syu/gridpack/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=True inputFiles=file:/home/syu/gridpack/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=True inputFiles=file:/home/syu/gridpack/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=True inputFiles=file:/home/syu/gridpack/Radion_hh_M2000.lhe outputFile=Radionhh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=True inputFiles=file:/home/syu/gridpack/Radion_hh_M4500.lhe outputFile=Radionhh4b_M4500_gluon_etacut.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=True inputFiles=file:/home/syu/gridpack/RS_hh_M2000.lhe outputFile=RShh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=True inputFiles=file:/home/syu/gridpack/RS_hh_M4500_1.lhe,file:/home/syu/gridpack/RS_hh_M4500_2.lhe outputFile=RShh4b_M4500_gluon_etacut.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=True inputFiles=file:/home/syu/gridpack/Bulk_hh_M2000.lhe outputFile=Bulkhh4b_M2000_gluon_etacut.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=True inputFiles=file:/home/syu/gridpack/Bulk_hh_M4500.lhe outputFile=Bulkhh4b_M4500_gluon_etacut.root


#### X->WW->qqll

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Radion_WW_M2000.lhe outputFile=RadionWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Radion_WW_M4500.lhe outputFile=RadionWW_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/RS_WW_M2000.lhe outputFile=RSWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/RS_WW_M4500.lhe outputFile=RSWW_M4500.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Bulk_WW_M2000.lhe outputFile=BulkWW_M2000.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=False fhh=False inputFiles=file:/home/syu/gridpack/Bulk_WW_M4500.lhe outputFile=BulkWW_M4500.root


cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Radion_WW_M2000.lhe outputFile=RadionWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Radion_WW_M4500.lhe outputFile=RadionWW_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/RS_WW_M2000.lhe outputFile=RSWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/RS_WW_M4500.lhe outputFile=RSWW_M4500_gluon.root

cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Bulk_WW_M2000.lhe outputFile=BulkWW_M2000_gluon.root
cmsRun GeneratorInterface/LHEInterface/test/dumpLHE_cfg.py maxEvents=-1 fgf=True fhh=False inputFiles=file:/home/syu/gridpack/Bulk_WW_M4500.lhe outputFile=BulkWW_M4500_gluon.root

