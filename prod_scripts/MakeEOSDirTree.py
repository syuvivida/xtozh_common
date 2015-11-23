#! /usr/bin/env python
import sys
import os
print sys.argv





if len(sys.argv) < 2 :
    print "insufficient options provided"
    print "proper usage "
    print "----------------------------------------------"
    print "python MakeEOSDirTree.py dir_in_eos_to_be_listed user_name_of_eos_holder "
    print "----------------------------------------------"
    print "e.g. python MakeEOSDirTree.py SingleMuon khurana"
    print "----------------------------------------------"
    exit (1)


## default values
samplename='SingleMuon'
username='khurana'

## need 3 parameters

if len(sys.argv) == 3 :
    samplename=sys.argv[1]
    username=sys.argv[2]


eospath='/store/user/'+username+'/'

eos='/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select ls '
fullsamplename=eospath+'/'+samplename



def listdirs(path):
    shellcommand=eos+path
    os.system(shellcommand+' >& dirlist.txt')
    dirlist=open('dirlist.txt','r')
    dirs=[]
    for line in dirlist:
        dirs.append(line.rstrip())
        
    dirlist.close()
    os.system('rm dirlist.txt')
    return dirs


def isFileOrDir(name):
    if 'NCUGlobal' in name : 
        return 'file'
    else :
        return 'dir'
    

inputFileList=open('inputfileslist.txt','w')


def ListFiles(fullsamplename_):
    #print ('-------------------',fullsamplename_)
    dirs=[]
    if isinstance(fullsamplename_,str) :
        dirs=listdirs(fullsamplename_)
    
    if isinstance(fullsamplename_,list) :
        dirs=fullsamplename_
    newdirs=[]
    for dirname in dirs:
        name=fullsamplename_+'/'+dirname
        #print ('name ',name)
        status=isFileOrDir(name)
        #print status
        if status=='file' :
            #if name.count('NCUGlobal')==1:
            towrite =  name+'\n'
            towrite = towrite.replace('/store', 'root://eoscms//eos//cms/store')
            inputFileList.write(towrite)
            #print 'written in file'
        elif status=='dir' :
            newdirlist=listdirs(name)
            #print ('newdirlist',newdirlist)
            for newdir_ in newdirlist:
                #print ('new dir', name+'/'+newdir_)
                #print ('new dir', newdir_)
                #newdirs.append(name+'/'+newdir_)
                if isFileOrDir(newdir_) == 'file' :
                    towrite_ = name+'/'+newdir_+'\n'
                    towrite_ = towrite_.replace('/store', 'root://eoscms//eos//cms/store')
                    inputFileList.write(towrite_)
                elif isFileOrDir(newdir_)== 'dir' :
                    ListFiles(name+'/'+newdir_)
                
            print '**********************'
        else :
            return 0
    return 0
newlistPath=ListFiles(fullsamplename)
print newlistPath



