# Project Version

Facilities for getting the microlibrary project version are defined in the
`microlibrary-version` static library's
[`microlibrary/version.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary-version/include/microlibrary/version.h)/[`microlibrary/version.cc.in`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary-version/source/microlibrary/version.cc.in)
header/source file pair.

To get the microlibrary project version, use the `::microlibrary::version()` function.
This function is populated with the output of the following Git command:
```shell
git describe --match=none --always --dirty --broken
```
