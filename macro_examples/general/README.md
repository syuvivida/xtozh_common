
How to set style
=====

At the top of your macro
```
#include "setNCUStyle.C"
```

To call it without plotting the grids:
```
setNCUStyle();
```

To call it if you want to enable gridx and gridy
```
setNCUStyle(true);
```

However, there are some styles that can not be set via setNCUStyle. 
For example, the offset of x-axis, y-axis title, additional texts, etc.
To see how to change title offset and add texts like "CMS Preliminary ...",

see https://github.com/syuvivida/xtozh_common/tree/13TeV_CMSSW747/macro_examples/general/additional_style.C

 