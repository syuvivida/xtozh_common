# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: REreco --filein file:/tmp/hbrun/DY_1.root --fileout file:/tmp/hbrun/reRECO.root --mc --eventcontent RECOSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --datatier GEN-SIM-RECO --conditions MCRUN2_72_V1A --step RAW2DIGI,L1Reco,RECO --magField 38T_PostLS1 --python_filename testRERECO.py --no_exec -n 100
import FWCore.ParameterSet.Config as cms

process = cms.Process('RERECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:/data2/syu/testsample/RSGravToZZ_kMpl01_M-4500_Tune4C_13TeV-pythia8_GEN-SIM-RAW_7_2_0.root')
#    fileNames = cms.untracked.vstring('file:/data2/syu/testsample/default_AODSIM.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.19 $'),
    annotation = cms.untracked.string('REreco nevts:100'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionLevel = cms.untracked.int32(4),
    compressionAlgorithm = cms.untracked.string('LZMA'),
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    outputCommands = process.AODSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:AODSIM.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('AODSIM')
    )
)


# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'PHYS14_25_V1', '')


# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)



#lines to customize the seeding:
#process.ancientMuonSeed.deltaPhiSearchWindow = cms.double(0.25)
process.ancientMuonSeed.deltaPhiSearchWindow = cms.double(0.05)
process.ancientMuonSeed.deltaEtaSearchWindow = cms.double(0.2)
process.ancientMuonSeed.deltaEtaCrackSearchWindow = cms.double(0.25)

# End of customisation functions


# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)


CA8jecUnc='START53_V23_Uncertainty_AK7PFchs.txt'
CA8jecLevels = [
    'START53_V23_L1FastJet_AK7PFchs.txt',
    'START53_V23_L2Relative_AK7PFchs.txt',
    'START53_V23_L3Absolute_AK7PFchs.txt'
    ]
AK5jecUnc='START53_V23_Uncertainty_AK5PFchs.txt'
AK5jecLevels = [
    'START53_V23_L1FastJet_AK5PFchs.txt',
    'START53_V23_L2Relative_AK5PFchs.txt',
    'START53_V23_L3Absolute_AK5PFchs.txt'
    ]

process.tree = cms.EDAnalyzer(
    'TreeMaker',
    fillPUweightInfo_ = cms.bool(False),
    fillEventInfo_ = cms.bool(True),
    fillGenInfo_   = cms.bool(True),
    fillRecoMuonInfo_  = cms.bool(True),
    fillMuonInfo_  = cms.bool(False),
    fillElecInfo_  = cms.bool(False),
    fillJetInfo_   = cms.bool(False),
    fillMetInfo_   = cms.bool(False),
    fillTrigInfo_  = cms.bool(False),
    fillPhotInfo_  = cms.bool(False),
    fillTauInfo_   = cms.bool(False),
    genPartLabel=cms.InputTag("genParticles"),
    genJetLabel=cms.InputTag("slimmedGenJets"),
    maxNumGenPar  =  cms.uint32(30),
    patMuons=cms.InputTag("slimmedMuons"),
    recoMuons=cms.InputTag("muons"),
    patElectrons = cms.InputTag("slimmedElectrons"),
    PrunedJets=cms.InputTag("ak8PFJetsCHSPrunedLinks"),
    pvSrc  = cms.InputTag('offlineSlimmedPrimaryVertices'),
    tauLabel_ = cms.untracked.InputTag("slimmedTaus"),
    rhoSrc = cms.InputTag('kt6PFJets','rho'),
    ### CA8Jet
    CA8Jets=cms.InputTag("jetsWithTau"),
    CA8jecPayloadNames = cms.vstring( CA8jecLevels ),
    CA8jecUncName = cms.string(CA8jecUnc),    
    ### AK5Jet
    AK5Jets=cms.InputTag("jetsAK4WithTau"),
    AK5jecPayloadNames = cms.vstring( AK5jecLevels ),
    AK5jecUncName = cms.string(AK5jecUnc),    
    patMetRaw=cms.InputTag("slimmedMETs"),
    patMet = cms.InputTag("slimmedMETs"),
    outFileName=cms.string('outputFileName.root')
    )


process.analysis = cms.Path(process.tree)



process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("default.root")
                                   )




# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.analysis,process.AODSIMoutput_step)
