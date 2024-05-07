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

# Description: microlibrary algorithms automated tests CMake rules.

add_executable( test-automated-microlibrary-algorithm )

target_sources( test-automated-microlibrary-algorithm
    PRIVATE main.cc
    )

target_link_libraries( test-automated-microlibrary-algorithm
    PRIVATE gmock
    PRIVATE gmock_main
    PRIVATE gtest
    PRIVATE microlibrary
    )

add_test(
    NAME    test-automated-microlibrary-algorithm
    COMMAND test-automated-microlibrary-algorithm ${MICROLIBRARY_AUTOMATED_TESTS_OPTIONS}
    )
