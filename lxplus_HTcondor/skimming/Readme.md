# How to submit lxplus batch jobs to skim data ntuples located at NCU Tier 3 or Taiwan Tier 2
## Compiling of skimTree

```
setenv SCRAM_ARCH slc6_amd64_gcc530
cmsrel CMSSW_8_0_25
cd CMSSW_8_0_25/src
cmsenv
git init scripts
cd scripts
git remote add origin https://github.com/syuvivida/xtozh_common
git config core.sparsecheckout true
echo "lxplus_batch/skimming/*" >> .git/info/sparse-checkout
git pull --depth=1 origin 80X_analysis
cd lxplus_batch/skimming/
chmod 755 *sh
```
Set the environment variables and some required directories and files
```
source prepare.sh
```

At this point, you should see a file skimTree_C.so in your work directory. If you change something in skimTree.C, remember to compile it again.
```
# compile
root -b -q -e ".L skimTree.C++"
```

## Prepare inputfile that contains a list of NCU ntuples at NCU Tier 3 or Taiwan Tier 2

You can find the full list of input files here: https://github.com/syuvivida/xtozh_common/tree/80X_analysis/2016data


If the files are at NCU Tier 3:
```
gfal-ls root://grid71.phy.ncu.edu.tw:1094//dpm/phy.ncu.edu.tw/home/cms/store/user/syu/SingleMuon/
```
Note, you need to include all the files that are in different subfolders!!
An example input file of ntuples from /JetHT/Run2016B-23Sep2016-v3/MINIAOD is "JetMET_Run2016B"

If the files are at Taiwan Tier 2:
```
gfal-ls root://se01.grid.nchc.org.tw//dpm/grid.nchc.org.tw/home/cms/store/user/syu/SingleMuon
```

To prepare the data root files list, you can use "gfalListDataFile.sh" to make it. 
By giving the keyword of the directory name, it will generates a file which records root file pathes. BUT NOTE, if you have directories from the old jobs under the same dataset name, PLEASE REMEMBER to remove them via "gfal-rm -r xxx"!!
```
./gfalListDataFile.sh JetHT NCUGlobal ncu syu
```

To prepare the MC root files list, you can use "gfalListMCFile.sh" to make it. 
By giving the keyword of the directory name, it will generates a file which records root file pathes. BUT NOTE, if you have directories from the old jobs under the same dataset name, PLEASE REMEMBER to remove them via "gfal-rm -r xxx"!!
```
./gfalListMCFile.sh QCD NCUGlobal ncu syu
```


## Submit the jobs at lxplus

### submit jobs with HTcondor
Before submit the jobs, please check you have run prepare.sh
```
source prepare.sh
```

you will have a grid.proxy at $HOME/private. Then, you can submit jobs if you want to process all input files of a certain dataset at the same time. There are two method to submit the jobs. In the first method, you SHOULD edit the configuration in main.sub and then submit the jobs. In the second method, condor system reads the input file from your submit option so that the file edition is not required. 


```
# I. Change variable 'listFile' in main.sub and run the command
# listFile  = yourDataList
condor_submit main.sub

# II. Run condor_submit with '- append' option
# If you want to run multiple files, use this way
condor_submit main.sub -append "listFile = yourDataList"
```

### Check status of job and other useful commands
Using the following command to check the status of jobs
```
condor_q
condor_q <ClusterID>
```
### Problem handling
If the status of job is "hold" which means something wrong,
using following command to know the reason.
```
condor_q -analyze <ClusterID.jobID>
```
After fixing it, using following command to go on

```
condor_release <ClusterID>   ## release jobs from hold state
```
Or you can remove jobs
```
condor_rm <ClusterID>        ## used to remove specific job
condor_rm -all               ## used to remove all jobs
```
### common troubleshooting
```
-- Failed to fetch ads from: <... : bigbirdxx.cern.ch
SECMAN:2007:Failed to end classad message.
```
If you see this error, wait a while and submit your jobs again. It's better to open a CERN Service Now ticket to inform the IT group.

This is usually due to heavy load, either on a specific schedd host or the central manager. In exceptional cases this might be caused by a centralized outage causing delays to the system.
## The way to submit jobs with other macro

## Useful Links
[CERN Batch Service User Guide](http://batchdocs.web.cern.ch/batchdocs/tutorial/introduction.html)
[HTCondor Manuals](http://research.cs.wisc.edu/htcondor/manual/)
