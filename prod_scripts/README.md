How to send lxplus batch jobs to run files on EOS

create a CMSSW area inside your work directory at lxplus
```
cmsrel CMSSW_7_4_12
cd CMSSW_7_4_12/src
```

In this src directory, put your own analysis macros, required header files, and the following scripts
```
git clone git@github.com:syuvivida/xtozh_common.git

cp -p xtozh_common/prod_scripts/* .

chmod 755 *sh

```
Note, your analysis macros must be able to run on one input file at a time.

Then, you need to know the directory name of the EOS files you want to run on, for 
example, if you want to run muVariables.C macro on the files in /store/khurana/SingleMuon,
you could run the follwing command. BTW, it is always a good practice to try your jobs 
locally before you launch them to lxplus batch system.

To  test it locally without submitting jobs, you could edit runEOSFile.sh 
and comment out the line 66 "bsub" and uncomment the line 65 [1].

[1]
https://github.com/syuvivida/xtozh_common/blob/13TeV_CMSSW747/prod_scripts/runEOSFile.sh#L66
https://github.com/syuvivida/xtozh_common/blob/13TeV_CMSSW747/prod_scripts/runEOSFile.sh#L65

Once you are sure that your jobs run over a few files, you could kill your local job and go 
ahead to submit the jobs to the lxplus batch system.

```
./runEOSFile.sh muVariable khurana SingleMuon trial 1nh

```
A directory trial_SingleMuon will be created and if there are 1000 files in the SingleMuon directory, 1000 jobs will be launched in the lxplus batch system.

The output files will be inside the trial_SIngleMuon directory.

You could change the queue according to your need. See this instruction for the available queues at lxplus:

https://twiki.cern.ch/twiki/bin/view/Main/BatchJobs