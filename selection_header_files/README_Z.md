
First download the header files in your work directory
```
curl https://raw.githubusercontent.com/syuvivida/xtozh_common/13TeV_CMSSW747/selection_header_files/isPassZee.h -o isPassZee.h

curl https://raw.githubusercontent.com/syuvivida/xtozh_common/13TeV_CMSSW747/selection_header_files/isPassZmumu.h -o isPassZmumu.h
```

Then, at the top of your analysis macro:

```
#include "isPassZee.h"

#include "isPassZmumu.h"
```

Within your event loop in the macro, for the electron:
```
vector<int> zee;
if(! isPassZee(data,zee))continue;

int leadingEleIndex = zee[0];
int subLeadingEleIndex = zee[1];

```

for the muon:

```
vector<int> zmm;
if(! isPassZmumu(data,zmm))continue;

int leadingMuoIndex = zmm[0];
int subLeadingMuoIndex = zmm[1];

```