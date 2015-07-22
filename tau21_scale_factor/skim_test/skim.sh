#!/bin/bash

#echo -e "Hello World! \a \n"

iteration=0
lastfile=`find ./flattuple_* -type f | wc -l`


while [ $iteration -lt $lastfile ];
do
	iteration=$(( iteration + 1 ))
#	echo -e "Hello World! \a \n"
    	file=`find ./flattuple_* -type f | head -n $iteration  | tail -1 | cut -c 3- `
	echo $file

#       root -b -l <<EOF

#$file

#EOF

root -b -l <<EOF

.L skimTree1.C++
skimTree1 b("$file")
b.Loop()
.q

EOF

mv *filtered.root filtered_files/ 

done

#file1=`find ./flattuple_* -type f | head -n 2  | tail -1 | cut -c 3- `
#echo $file1

#root -b -l <<EOF
#.L skimTree1.C++
#skimTree1 b("$file1")
#b.Loop()
#.q
#EOF



#root -b -l <<EOF
#.L skimTree1.C++
#skimTree1 b("flattuple_3169.root")
#b.Loop()
#.q
#EOF



#root -l 
#.q


