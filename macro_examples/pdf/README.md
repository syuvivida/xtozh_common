0) setup environment

```
 cd CMSSW_5_3_20/src
 cmsenv
```

1) Download LHAPDF
   Download LHAPDF from https://lhapdf.hepforge.org/.

 In your work area at lxplus:

 ```  
 wget http://www.hepforge.org/archive/lhapdf/lhapdf-5.8.7.tar.gz
  
 mkdir test_pdf

 mkdir test_pdf/LHAPDF

 setenv LHAPDFDIR $PWD/test_pdf/LHAPDF

 cd test_pdf

 tar xvzf ../lhapdf-5.8.7.tar.gz

 cd lhapdf-5.8.7
 

2) Modify the configuration file configure.ac

```
## NMXSET - max number of concurrent PDF sets
## Normal default number of PDF sets is 5
default_max_num_pdfsets=5
AC_ARG_WITH([max-num-pdfsets],
  [AC_HELP_STRING(--with-max-num-pdfsets,
  [maximum number of PDF sets that can be held concurrently in memory - affects virtual memory overhead (default=5)])],
```

3) Install LHAPDF
 ./configure --prefix=$LHAPDFDIR

 make
 
 make install

```

 [If the build is succesfull, you will find both shared libraries and 
 static library in $LHAPDFDIR/lib.
 Also you will find PDFsets.index in $LHAPDFDIR/share/lhapdf/PDFsets.index
 ]
 
4) Download PDFsets from http://lhapdf.hepforge.org/lhapdf5/pdfsets

```
mkdir  $LHAPDFDIR/share/lhapdf/PDFsets/
 
cd $LHAPDFDIR/share/lhapdf/PDFsets/

wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/cteq6ll.LHpdf
wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/MSTW2008lo68cl.LHgrid
wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/NNPDF21_lo_as_0119_100.LHgrid
wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/CT10.LHgrid
wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/MSTW2008nlo68cl.LHgrid
wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/NNPDF23_nlo_collider_as_0118.LHgrid

wget http://www.hepforge.org/archive/lhapdf/pdfsets/current/cteq66.LHgrid

```

5) Prepare ntuples that include the following information:

```
  Handle<GenEventInfoProduct> pdfInfoHandle;
  if (iEvent.getByLabel("generator", pdfInfoHandle)) {
    if (pdfInfoHandle->pdf()) {

      pdfInfo_.push_back(pdfInfoHandle->pdf()->id.first);
      pdfInfo_.push_back(pdfInfoHandle->pdf()->id.second);
      pdfInfo_.push_back(pdfInfoHandle->pdf()->x.first);
      pdfInfo_.push_back(pdfInfoHandle->pdf()->x.second);
      pdfInfo_.push_back(pdfInfoHandle->pdf()->xPDF.first);
      pdfInfo_.push_back(pdfInfoHandle->pdf()->xPDF.second);
      pdfInfo_.push_back(pdfInfoHandle->pdf()->scalePDF);
    }
  }

```

6) In the directory where you will run macros to perform PDF 
 reweighing, do a soft link to link to the header files:
 
```
 ln -s $LHAPDFDIR/include/LHAPDF .
```


7) Prepare a ROOT macro to use the LHAPDF set to perform PDF reweighing 
 and also use pdfInfo_. Two examples could be found here:

https://github.com/syuvivida/xtozh_common/tree/8TeV_CMSSW520/macro_examples/pdf/runPDF.C

https://github.com/syuvivida/xtozh_common/tree/8TeV_CMSSW520/macro_examples/pdf/myLHAPDF_reweighing.C

 to run this example, cd to your work area
```
 setenv LHAPDFDIR $PWD/test_pdf/LHAPDF
 setenv LHAPATH $LHAPDFDIR/share/lhapdf/PDFsets/
 root -q -b runPDF.C\(\"xxx.root\"\)
``

Note, before calling the macro to reweigh distributions, remember to load 
 the following library:
```
  gROOT->ProcessLine(".L ${LHAPDFDIR}/lib/libLHAPDF.so");
```


8) NOTE!!!
 In most of the MC samples, in the LHAPDF framework, 
 the gluon identifier code is 0, not 21. However, in Sherpa MC, 
 the gluon identifier code is still 22.

 The list of PDFsets need to be either all in LO or all in NLO. 
 You can not mix LO and NLO in the same job.

9) References:
 
 http://arxiv.org/abs/hep-ph/0508110
 http://arxiv.org/abs/hep-ph/0605240