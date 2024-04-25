# microlibrary
#
# Copyright 2024, Andrew Countryman <apcountryman@gmail.com> and the microlibrary
# contributors
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
# file except in compliance with the License. You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the specific language governing
# permissions and limitations under the License.

# Description: Build (all HILs, development environment target) and test (automated)
#       configuration.

mark_as_advanced( CMAKE_INSTALL_PREFIX )

set( CMAKE_BUILD_TYPE              "Debug" CACHE INTERNAL "" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON      CACHE INTERNAL "" )

set( MICROLIBRARY_HIL                                       "ALL"                     CACHE INTERNAL "" )
set( MICROLIBRARY_TARGET                                    "DEVELOPMENT_ENVIRONMENT" CACHE INTERNAL "" )
set( MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION OFF                       CACHE INTERNAL "" )
set( MICROLIBRARY_BUILD_AUTOMATED_TESTS                     ON                        CACHE INTERNAL "" )
set( MICROLIBRARY_BUILD_INTERACTIVE_TESTS                   OFF                       CACHE INTERNAL "" )
