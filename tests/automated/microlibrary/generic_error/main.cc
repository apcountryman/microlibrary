/**
 * microlibrary
 *
 * Copyright 2024, Andrew Countryman <apcountryman@gmail.com> and the microlibrary
 * contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * \file
 * \brief microlibrary::Generic_Error automated tests.
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/error.h"

namespace {

using ::microlibrary::Error_Code;
using ::microlibrary::Error_ID;
using ::microlibrary::Generic_Error;
using ::microlibrary::Generic_Error_Category;

} // namespace

/**
 * \brief Verify microlibrary::make_error_code( microlibrary::Generic_Error ) works
 *        properly.
 */
TEST( makeErrorCode, worksProperly )
{
    auto const id = Error_ID{ 226 };

    auto const error = Error_Code{ static_cast<Generic_Error>( id ) };

    EXPECT_EQ( &error.category(), &Generic_Error_Category::instance() );
    EXPECT_EQ( error.id(), id );
}
