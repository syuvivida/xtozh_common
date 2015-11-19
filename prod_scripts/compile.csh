#!/bin/tcsh

cd $1

setenv SCRAM_ARCH slc6_amd64_gcc481; eval `scramv1 runtime -csh`

root -l -b  <<EOF
.L $2.C++("","")
EOF
