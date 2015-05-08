import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()


process = cms.Process("dumpLHE")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.dummy = cms.EDAnalyzer("DummyGenAnalyzer",
    histoutputFile= cms.untracked.string(options.outputFile)          
)


process.p = cms.Path(process.dummy)


