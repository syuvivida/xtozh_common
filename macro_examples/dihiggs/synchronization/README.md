## How to run the code

```

mkdir Project
cd Project
git init
git remote add -f origin https://github.com/syuvivida/xtozh_common
git config core.sparsecheckout true
echo "macro_examples/dihiggs/synchronization/*" >> .git/info/sparse-checkout
git pull origin 80X_analysis

```