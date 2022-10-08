# MbedTLS fork for usage with IoTeX machinefi SDK

A fork of [mbedTLS](https://github.com/Mbed-TLS/mbedtls) with some changes necessary to support it's use with the IoTeX machinefi SDK.  

## Branches supported by the machinefi SDK

- [machinefi-3.2.1](https://github.com/as-iotex/mbedtls/tree/machinefi-3.2.1) based on [mbedtls tag v3.2.1](https://github.com/Mbed-TLS/mbedtls/tree/v3.2.1).  

## How to sync this repository with the official mbedtls in order to pull the latest updates

The [mbedtls official repository](https://github.com/Mbed-TLS/mbedtls) is added to this fork as the remote **mbedtls-upstream**.  
In order to sync this fork with the mbedtls upstream run the following:  

```bash
# Fetch all new upstream branches
git fetch mbedtls-upstream
# Checkout the branch you want to sync. In this case, the development branch
# Note that in most cases we willl only need to update the development branch, as we base our branches on tags present in the development branch
git checkout development
# Rebase the branch into the upstream
git rebase mbedtls-upstream/master
```

Alternatively, the sync fork button can be used from the Github interface  
![image](https://user-images.githubusercontent.com/82106612/194701583-642e99cd-f7b5-48e6-a6d7-65c46504fad4.png)


## How to support a new version on mbedTLS in the machinefi SDK

All branches that can be used with the machinefi SDK are prefixed by `machinefi`.  Eg: `machinefi-3.2.1`.  
Each of the branches prefixed by `machinefi-` are based on a mbedtls release tag, and contain IoTeX changes on top.  
Eg, for the `machinefi-3.2.1` branch you can see iotex commits at the top of the [commit list](https://github.com/as-iotex/mbedtls/commits/machinefi-3.2.1).  

In order to create a new mchinefi branch, do the following:  

```bash
# Make sure that the repo is synced to upstream, by following the steps mentioned above

# Checkout the tag we want to base on and pull the latest changes, 3.2.0 in this case
git checkout tags/v3.2.0 && git pull

# Create a new branch prefixed by machinefi-
git checkout -b machinefi-3.2.0

# Now we need to apply our changes on top
# The easiest way is by cherry-picking the changes from the machinefi-3.2.1 branch
# By running git log we can see the commmits
git log --oneline 3.2.1

# The ouput of git log will show something like this, where the commits on top of (tag: v3.2.1, tag: mbedtls-3.2.1) are our changes
# a16dee4d9 (origin/iotex-3.2.1, origin/3.2.1, iotex-3.2.1, 3.2.1) add crypto_spe.h
# 79941223b define psa_key_derivation_input_integer()
# e825341a2 Enable MBEDTLS_PSA_CRYPTO_SPM (build for SPM)
# 37383e2d7 rmove x509 and tls target libraries from build
# 2e27d1776 disable build of programs and tests by default and remove -Wall flag
# 869298bff (tag: v3.2.1, tag: mbedtls-3.2.1, origin/master, mbedtls-upstream/master) Add 3.2.1 Changelog

# Assuming we want to apply the same changes to the new branch
# We cherry pick the range of commits between 2e27d1776 and a16dee4d9. Alternatively we can cherry pick one by one
# Ideally this cherry pick will auto merge. If not, we will have to solve any merge conflicts that appear
git cherry-pick 2e27d1776^..a16dee4d9

# If we want to add more changes, we can make them now and commit them

# After we finish adding changes, we push the new branch to origin
git push --set-upstream origin machinefi-3.2.0
```
