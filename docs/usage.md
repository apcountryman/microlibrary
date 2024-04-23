# Usage

## Table of Contents

1. [Dependency](#dependency)
    1. [General Configuration Options](#general-configuration-options)
1. [Development](#development)

## Dependency

To use microlibrary as a dependency, use CMake's FetchContent module to add microlibrary
to a CMake build, and link with the `microlibrary` static library.
```cmake
include( FetchContent )
```
```cmake
FetchContent_Declare( microlibrary
    ...
    )
```
```cmake
FetchContent_MakeAvailable( microlibrary )
```
```cmake
target_link_libraries( foo
    microlibrary
    )
```

### General Configuration Options

microlibrary supports the following general configuration options:
- `MICROLIBRARY_HIL` (defaults to an empty string): HIL.
  Must be one of the following strings:
    - `ARM_CORTEX_M0PLUS`: Generic Arm Cortex-M0+ HIL.
    - `MICROCHIP_MEGAAVR`: Microchip megaAVR HIL.
    - `MICROCHIP_MEGAAVR0`: Microchip megaAVR 0-series HIL.
    - `MICROCHIP_SAM_D21DA1`: Microchip SAM D21/DA1 HIL.
    - `ALL`: All officially supported HILs.
      `MICROLIBRARY_TARGET` must be `DEVELOPMENT_ENVIRONMENT` or `NONE`.
    - `CUSTOM`: A HIL that is not officially supported.
- `MICROLIBRARY_TARGET` (defaults to an empty string): Target environment.
  Must be one of the following strings:
    - `DEVELOPMENT_ENVIRONMENT`: Development environment.
    - `HARDWARE`: Hardware.
    - `NONE`: None (used to exclude target specific code from static analysis).
- `MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION` (defaults to `OFF`): Suppress
  human readable error information.
- `MICROLIBRARY_BUILD_AUTOMATED_TESTS` (defaults to `OFF`): Build automated tests.
  `MICROLIBRARY_TARGET` must be `DEVELOPMENT_ENVIRONMENT`.
  `MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION` must be `OFF`.
- `MICROLIBRARY_BUILD_INTERACTIVE_TESTS` (defaults to `OFF`): Build interactive tests.
  `MICROLIBRARY_TARGET` must be `HARDWARE`.

## Development

To install the microlibrary repository's Git hooks, execute the `install.sh` script
located in the `git/hooks` directory.
See the `install.sh` script's help text for usage details.
```shell
./git/hooks/install.sh --help
```

The repository's `pre-commit.sh` hook script is the simplest way to configure, build, and
test microlibrary during development.
See the `pre-commit.sh` script's help text for usage details.
```shell
./git/hooks/pre-commit.sh --help
```

Additional checks, such as static analysis, are performed by the repository's GitHub
Actions CI workflow.
