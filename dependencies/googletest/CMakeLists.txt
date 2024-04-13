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

# Description: GoogleTest dependency CMake rules.

if( NOT MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )
    return()
endif( NOT MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )

option( MICROLIBRARY_USE_PARENT_PROJECT_GOOGLETEST
    "microlibrary: Use parent project GoogleTest."
    ON
    )

if( NOT MICROLIBRARY_USE_PARENT_PROJECT_GOOGLETEST )
    set( BUILD_GMOCK   ON  CACHE INTERNAL "" )
    set( INSTALL_GTEST OFF CACHE INTERNAL "" )

    set( gtest_force_shared_crt      OFF CACHE INTERNAL "" )
    set( gtest_build_tests           OFF CACHE INTERNAL "" )
    set( gtest_build_samples         OFF CACHE INTERNAL "" )
    set( gtest_disable_pthreads      OFF CACHE INTERNAL "" )
    set( gtest_hide_internal_symbols OFF CACHE INTERNAL "" )

    set( gmock_build_tests OFF CACHE INTERNAL "" )
endif( NOT MICROLIBRARY_USE_PARENT_PROJECT_GOOGLETEST )

if( NOT MICROLIBRARY_USE_PARENT_PROJECT_GOOGLETEST )
    add_subdirectory( googletest )
endif( NOT MICROLIBRARY_USE_PARENT_PROJECT_GOOGLETEST )
