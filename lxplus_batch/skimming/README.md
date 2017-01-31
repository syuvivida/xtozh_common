# How to submit lxplus batch jobs to skim data ntuples located at NCU Tier 3 or Taiwan Tier 2
## Compiling of skimTree
```
setenv SCRAM_ARCH slc6_amd64_gcc530
cmsrel CMSSW_8_0_22
cd CMSSW_8_0_22/src
cmsenv
git init scripts
cd scripts
git remote add origin https://github.com/syuvivida/xtozh_common
git config core.sparsecheckout true
echo "macro_examples/dihiggs/lxplus_batch/skimming/*" >> .git/info/sparse-checkout
git pull --depth=1 origin 80X_analysis
cd macro_examples/dihiggs/lxplus_batch/skimming/
chmod 755 *sh
root -b
.L skimTree.C++
.q
```

At this point, you should see a file skimTree_C.so in your work directory 

## Prepare inputfile that contains a list of NCU ntuples at NCU Tier 3 or Taiwan Tier 2

Open a new lxplus terminal and log back in

```
voms-proxy-init --voms cms
```

If the files are at NCU Tier 3:
```
gfal-ls root://grid71.phy.ncu.edu.tw:1094//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/JetHT/
```
Note, you need to include all the files that are in different subfolders!!
An example input file of ntuples from /JetHT/Run2016B-23Sep2016-v3/MINIAOD is "JetMET_Run2016B"

If the files are at Taiwan Tier 2:
```
gfal-ls root://se01.grid.nchc.org.tw//dpm/grid.nchc.org.tw/home/cms/store/user/syu/JetHT
```

## Submit the jobs at lxplus

```
setenv X509_USER_PROXY $HOME/private/grid.proxy
voms-proxy-init --voms cms
```

Check if you do have a grid.proxy at $HOME/private. Then, you can submit jobs if you want to process all input files of a certain dataset at the same time. If you only want to process part of the input files, change the values of the variables "iteration" and "lastfile" in the script "launch_ntuple.sh"

```
./launch_ntuple.sh JetMET_Run2016B
```
