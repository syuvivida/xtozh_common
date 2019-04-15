# HTcondor: submit jobs with general macro
## Introduction
This framework is used to run macro with large number of input files by batch system, HTcondor. This framework is based on two files, main.sub, subMacro.sh and some user preparing files. User should prepare two files, one is the executed macro and the other is the list of inputfile. With proper aruements setting, jobs will be submit and ran successfully.
## Structure
* Offered file
    * main.sub
    * subMacro.sh
* User preparing file
    * executed macro (.so file; .C, .c file)
    * fileList

### main.sub
This file contains all configuration used for HTcondor. For most of cases, user only need to change the setting in user setting area. 

| variable| explaination |
| -------- | -------- |
| listFile    | your fileList name  |
|exeMacro | your executed macro name|
|outputVar | your output file name in exeMacro|
|outputTransfer | transfering name of your outputfile |
Explaination of variables in user setting area.

### subMacro.sh
This file is used to set environment variables in remote machine and run the executed macro.
for most of cases, you don't need to change it!
### executed macro
It is a macro can be executed by ROOT, e.g. .C, .c, .cpp, .cxx file or .so file. For skimming case, executed macro is skimTree.C.

The macro must require 2 input arguements, the first one is input file name and the second one is output file name.
If you need more then 2 arguements in executed file, you have to change the arguements in subMacro.sh and main.sh.
### fileList
the list of full path of input file.
If the files are not on /eos, T2 or T3, you can generate it by following command.
```
ls /your/path/*.root > mylist.txt
```
