For those who need the code, you can download it from github.

https://github.com/juwugit/XtoZh/blob/master/CLs_results/plot_Asymptotic.C

command to download it:
``
wget https://raw.githubusercontent.com/juwugit/XtoZh/master/CLs_results/plot_Asymptotic.C
```

How to use is very simple, you need to provide the output limit trees from combine tool[1], theoretical cross-section with corresponding masspoint in a text file[2] and put them in the same directory as the location of the code.

You need to modify "nxm"[3] and "Xmass"[4] to fulfil your requirements.
About the input argument, you can delete it.

I have 3 kinds of limit tree sources, so that I ask the code to output the 
plots in different names.

You can modify line#93-95, remove the if statement, if you don't need.

Also in line#526-540, you can choose your output file format or remove the outputname.data()
if you don't need it.




[1] https://github.com/juwugit/XtoZh/tree/master/CLs_results/higgsCombine*.root

[2] https://github.com/juwugit/XtoZh/blob/master/CLs_results/xsec_Zhllbb.txt

[3] https://github.com/juwugit/XtoZh/blob/master/CLs_results/plot_Asymptotic.C#L18

[4] https://github.com/juwugit/XtoZh/blob/master/CLs_results/plot_Asymptotic.C#L85
