# Automated Tests

## Table of Contents

1. [Tests](#tests)
1. [Tests Coverage](#tests-coverage)

## Tests

Automated tests can be found in the
[`tests/automated/`](https://github.com/apcountryman/microlibrary/tree/main/tests/automated)
directory.
The location of the automated tests for a particular library feature can be found in the
documentation for the feature.
Not all library features have automated tests.

## Tests Coverage

To generate an automated tests coverage report, build the
`microlibrary-automated-tests-coverage` target.
The automated tests coverage report can then be found in the build directory's
`microlibrary-automated-tests-coverage-report` subdirectory.
The reported coverage will be misleadingly high due to microlibrary's use of conditional
compilation and templates that are not explicitly instantiated.
