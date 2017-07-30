#!/bin/bash
for file in QCD*to*.txt; do
    launch_ntuple.sh $file
done
