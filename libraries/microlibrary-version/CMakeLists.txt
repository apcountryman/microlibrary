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

# Description: microlibrary-version static library CMake rules.

add_library( microlibrary-version STATIC )

target_include_directories( microlibrary-version
    PUBLIC include
    )

configure_file(
    source/microlibrary/version.cc.in
    source/microlibrary/version.cc
    @ONLY
    )

target_sources( microlibrary-version
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/source/microlibrary/version.cc"
    )

target_link_libraries( microlibrary-version
    PUBLIC microlibrary
    )
