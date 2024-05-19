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
 * \brief microlibrary algorithms automated tests.
 */

#include <cstddef>
#include <cstdint>
#include <ios>
#include <ostream>
#include <string_view>
#include <type_traits>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/algorithm.h"
#include "microlibrary/result.h"
#include "microlibrary/testing/automated/error.h"

namespace {

using ::microlibrary::Functor_Reports_Errors;
using ::microlibrary::Functor_Reports_Errors_Discard_Functor;
using ::microlibrary::Functor_Reports_Errors_Return_Functor;
using ::microlibrary::Result;
using ::microlibrary::Testing::Automated::Mock_Error;
using ::testing::_;
using ::testing::Each;
using ::testing::InSequence;
using ::testing::MockFunction;
using ::testing::Ref;
using ::testing::Return;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::ValuesIn;

} // namespace

/**
 * \brief microlibrary::for_each() test cases.
 */
std::vector<std::uint_fast8_t> const forEach_TEST_CASES[]{
    {},
    { 0x1C, 0x0C, 0xE6, 0xEC, 0x99 },
};

/**
 * \brief microlibrary::for_each( Iterator, Iterator, Functor ) test fixture.
 */
class forEach : public TestWithParam<std::vector<std::uint_fast8_t>> {
};

/**
 * \brief Verify microlibrary::for_each( Iterator, Iterator, Functor ) works properly.
 */
TEST_P( forEach, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto functor = MockFunction<void( std::uint_fast8_t const & )>{};

    auto const values = GetParam();

    for ( auto const & value : values ) {
        EXPECT_CALL( functor, Call( Ref( value ) ) );
    } // for

    auto const returned_functor = ::microlibrary::for_each(
        values.begin(), values.end(), functor.AsStdFunction() );

    EXPECT_CALL( functor, Call( _ ) );

    returned_functor( 0x04 );
}

INSTANTIATE_TEST_SUITE_P(, forEach, ValuesIn( forEach_TEST_CASES ) );

/**
 * \brief Verify microlibrary::for_each( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors_Return_Functor ) properly handles a functor
 *        error.
 */
TEST( forEachFunctorReportsErrorsReturnFunctorErrorHandling, functorError )
{
    auto functor = MockFunction<Result<void>( std::uint_fast8_t const & )>{};

    auto const error = Mock_Error{ 146 };

    auto const values = std::vector<std::uint_fast8_t>{ 0xB7, 0x87, 0x43, 0x67 };

    EXPECT_CALL( functor, Call( _ ) ).WillOnce( Return( error ) );

    auto const result = ::microlibrary::for_each<Functor_Reports_Errors_Return_Functor>(
        values.begin(), values.end(), functor.AsStdFunction() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief microlibrary::for_each( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors_Return_Functor ) test fixture.
 */
class forEachFunctorReportsErrorsReturnFunctor :
    public TestWithParam<std::vector<std::uint_fast8_t>> {
};

/**
 * \brief Verify microlibrary::for_each( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors_Return_Functor ) works properly.
 */
TEST_P( forEachFunctorReportsErrorsReturnFunctor, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto functor = MockFunction<Result<void>( std::uint_fast8_t const & )>{};

    auto const values = GetParam();

    for ( auto const & value : values ) {
        EXPECT_CALL( functor, Call( Ref( value ) ) ).WillOnce( Return( Result<void>{} ) );
    } // for

    auto const result = ::microlibrary::for_each<Functor_Reports_Errors_Return_Functor>(
        values.begin(), values.end(), functor.AsStdFunction() );

    static_assert( std::is_same_v<decltype( result )::Value, decltype( functor.AsStdFunction() )> );

    ASSERT_FALSE( result.is_error() );

    EXPECT_CALL( functor, Call( _ ) ).WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( result.value()( 0x85 ).is_error() );
}

INSTANTIATE_TEST_SUITE_P(, forEachFunctorReportsErrorsReturnFunctor, ValuesIn( forEach_TEST_CASES ) );

/**
 * \brief Verify microlibrary::for_each( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors_Discard_Functor ) properly handles a
 *        functor error.
 */
TEST( forEachFunctorReportsErrorsDiscardFunctorErrorHandling, functorError )
{
    auto functor = MockFunction<Result<void>( std::uint_fast8_t const & )>{};

    auto const error = Mock_Error{ 146 };

    auto const values = std::vector<std::uint_fast8_t>{ 0xB7, 0x87, 0x43, 0x67 };

    EXPECT_CALL( functor, Call( _ ) ).WillOnce( Return( error ) );

    auto const result = ::microlibrary::for_each<Functor_Reports_Errors_Discard_Functor>(
        values.begin(), values.end(), functor.AsStdFunction() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief microlibrary::for_each( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors_Discard_Functor ) test fixture.
 */
class forEachFunctorReportsErrorsDiscardFunctor :
    public TestWithParam<std::vector<std::uint_fast8_t>> {
};

/**
 * \brief Verify microlibrary::for_each( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors_Discard_Functor ) works properly.
 */
TEST_P( forEachFunctorReportsErrorsDiscardFunctor, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto functor = MockFunction<Result<void>( std::uint_fast8_t const & )>{};

    auto const values = GetParam();

    for ( auto const & value : values ) {
        EXPECT_CALL( functor, Call( Ref( value ) ) ).WillOnce( Return( Result<void>{} ) );
    } // for

    auto const result = ::microlibrary::for_each<Functor_Reports_Errors_Discard_Functor>(
        values.begin(), values.end(), functor.AsStdFunction() );

    static_assert( std::is_same_v<decltype( result )::Value, void> );

    EXPECT_FALSE( result.is_error() );
}

INSTANTIATE_TEST_SUITE_P(, forEachFunctorReportsErrorsDiscardFunctor, ValuesIn( forEach_TEST_CASES ) );

/**
 * \brief microlibrary::fill() test fixture.
 */
class fill : public TestWithParam<std::size_t> {
};

/**
 * \brief Verify microlibrary::fill() works properly.
 */
TEST_P( fill, worksProperly )
{
    auto const size = GetParam();

    auto       container = std::vector<std::uint_fast8_t>( size );
    auto const value     = std::uint_fast8_t{ 0xCB };

    ::microlibrary::fill( container.begin(), container.end(), value );

    EXPECT_THAT( container, Each( value ) );
}

INSTANTIATE_TEST_SUITE_P(, fill, Values<std::size_t>( 0, 5 ) );

/**
 * \brief microlibrary::generate() test cases.
 */
std::vector<std::uint_fast8_t> const generate_TEST_CASES[]{
    {},
    { 0x1C, 0x0C, 0xE6, 0xEC, 0x99 },
};

/**
 * \brief microlibrary::generate( Iterator, Iterator, Functor ) test fixture.
 */
class generate : public TestWithParam<std::vector<std::uint_fast8_t>> {
};

/**
 * \brief Verify microlibrary::generate( Iterator, Iterator, Functor ) works properly.
 */
TEST_P( generate, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto functor = MockFunction<std::uint_fast8_t()>{};

    auto const values = GetParam();

    for ( auto const & value : values ) {
        EXPECT_CALL( functor, Call() ).WillOnce( Return( value ) );
    } // for

    auto container = std::vector<std::uint_fast8_t>( values.size() );

    ::microlibrary::generate( container.begin(), container.end(), functor.AsStdFunction() );

    EXPECT_EQ( container, values );
}

INSTANTIATE_TEST_SUITE_P(, generate, ValuesIn( generate_TEST_CASES ) );

/**
 * \brief Verify microlibrary::generate( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors ) properly handles a functor error.
 */
TEST( generateFunctorReportsErrorsErrorHandling, functorError )
{
    auto functor = MockFunction<Result<std::uint_fast8_t>()>{};

    auto error = Mock_Error{ 146 };

    auto container = std::vector<std::uint_fast8_t>( 5 );

    EXPECT_CALL( functor, Call() ).WillOnce( Return( error ) );

    auto const result = ::microlibrary::generate<Functor_Reports_Errors>(
        container.begin(), container.end(), functor.AsStdFunction() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief microlibrary::generate( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors ) test fixture.
 */
class generateFunctorReportsErrors : public TestWithParam<std::vector<std::uint_fast8_t>> {
};

/**
 * \brief Verify microlibrary::generate( Iterator, Iterator, Functor,
 *        microlibrary::Functor_Reports_Errors ) works properly.
 */
TEST_P( generateFunctorReportsErrors, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto functor = MockFunction<Result<std::uint_fast8_t>()>{};

    auto const values = GetParam();

    for ( auto const & value : values ) {
        EXPECT_CALL( functor, Call() ).WillOnce( Return( value ) );
    } // for

    auto container = std::vector<std::uint_fast8_t>( values.size() );

    EXPECT_FALSE( ::microlibrary::generate<Functor_Reports_Errors>(
                      container.begin(), container.end(), functor.AsStdFunction() )
                      .is_error() );

    EXPECT_EQ( container, values );
}

INSTANTIATE_TEST_SUITE_P(, generateFunctorReportsErrors, ValuesIn( generate_TEST_CASES ) );

/**
 * \brief Verify microlibrary::min() works properly when a is less than b, and a and b are
 *        not adjacent.
 */
TEST( min, worksProperlyALessBNotAdjacent )
{
    auto const a = std::uint_fast8_t{ 28 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::min( a, b ), Ref( a ) );
}

/**
 * \brief Verify microlibrary::min() works properly when a is less than b, and a and b are
 *        adjacent.
 */
TEST( min, worksProperlyALessBAdjacent )
{
    auto const a = std::uint_fast8_t{ 198 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::min( a, b ), Ref( a ) );
}

/**
 * \brief Verify microlibrary::min() works properly when a equals b.
 */
TEST( min, worksProperlyAEqualB )
{
    auto const a = std::uint_fast8_t{ 199 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::min( a, b ), Ref( a ) );
}

/**
 * \brief Verify microlibrary::min() works properly when a is greater than b, and a and b
 *        are adjacent.
 */
TEST( min, worksProperlyAGreaterBAdjacent )
{
    auto const a = std::uint_fast8_t{ 200 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::min( a, b ), Ref( b ) );
}

/**
 * \brief Verify microlibrary::min() works properly when a is greater than b, and a and b
 *        are not adjacent.
 */
TEST( min, worksProperlyAGreaterBNotAdjacent )
{
    auto const a = std::uint_fast8_t{ 232 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::min( a, b ), Ref( b ) );
}

/**
 * \brief Verify microlibrary::max() works properly when a is less than b, and a and b are
 *        not adjacent.
 */
TEST( max, worksProperlyALessBNotAdjacent )
{
    auto const a = std::uint_fast8_t{ 28 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::max( a, b ), Ref( b ) );
}

/**
 * \brief Verify microlibrary::max() works properly when a is less than b, and a and b are
 *        adjacent.
 */
TEST( max, worksProperlyALessBAdjacent )
{
    auto const a = std::uint_fast8_t{ 198 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::max( a, b ), Ref( b ) );
}

/**
 * \brief Verify microlibrary::max() works properly when a equals b.
 */
TEST( max, worksProperlyAEqualB )
{
    auto const a = std::uint_fast8_t{ 199 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::max( a, b ), Ref( a ) );
}

/**
 * \brief Verify microlibrary::max() works properly when a is greater than b, and a and b
 *        are adjacent.
 */
TEST( max, worksProperlyAGreaterBAdjacent )
{
    auto const a = std::uint_fast8_t{ 200 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::max( a, b ), Ref( a ) );
}

/**
 * \brief Verify microlibrary::max() works properly when a is greater than b, and a and b
 *        are not adjacent.
 */
TEST( max, worksProperlyAGreaterBNotAdjacent )
{
    auto const a = std::uint_fast8_t{ 232 };
    auto const b = std::uint_fast8_t{ 199 };

    EXPECT_THAT( ::microlibrary::max( a, b ), Ref( a ) );
}

/**
 * \brief microlibrary::equal() test case.
 */
struct equal_Test_Case {
    /**
     * \brief Range 1.
     */
    std::string_view range_1;

    /**
     * \brief Range 2.
     */
    std::string_view range_2;

    /**
     * \brief range_1 and range_2 are equal.
     */
    bool equal;
};

auto operator<<( std::ostream & stream, equal_Test_Case const & test_case ) -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".range_1 = \"" << test_case.range_1 << '"'
                  << ", "
                  << ".range_2 = \"" << test_case.range_2 << '"'
                  << ", "
                  << ".equal = " << std::boolalpha << test_case.equal
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::equal( Iterator_1, Iterator_1, Iterator_2 ) and
 *        microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Predicate ) test cases.
 */
equal_Test_Case const equal3Iterators_TEST_CASES[]{
    // clang-format off

    {
        "",
        "",
        true },
    {
        "xlC8WWhQqaVcM3",
        "xlC8WWhQqbVcM3",
        false },
    {
        "xlC8WWhQqaVcM3",
        "xlC8WWhQqaVcM3",
        true },

    // clang-format on
};

/**
 * \brief microlibrary::equal( Iterator_1, Iterator_1, Iterator_2 ) test fixture.
 */
class equal3Iterators : public TestWithParam<equal_Test_Case> {
};

/**
 * \brief Verify microlibrary::equal( Iterator_1, Iterator_1, Iterator_2 ) works properly.
 */
TEST_P( equal3Iterators, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ(
        ::microlibrary::equal(
            test_case.range_1.begin(), test_case.range_1.end(), test_case.range_2.begin() ),
        test_case.equal );
}

INSTANTIATE_TEST_SUITE_P(, equal3Iterators, ValuesIn( equal3Iterators_TEST_CASES ) );

/**
 * \brief microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Predicate ) test
 *        fixture.
 */
class equal3IteratorsPredicate : public TestWithParam<equal_Test_Case> {
};

/**
 * \brief Verify microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Predicate )
 *        works properly.
 */
TEST_P( equal3IteratorsPredicate, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ(
        ::microlibrary::equal(
            test_case.range_1.begin(),
            test_case.range_1.end(),
            test_case.range_2.begin(),
            []( auto a, auto b ) { return a == b; } ),
        test_case.equal );
}

INSTANTIATE_TEST_SUITE_P(, equal3IteratorsPredicate, ValuesIn( equal3Iterators_TEST_CASES ) );

/**
 * \brief microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Iterator_2 ) and
 *        microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Iterator_2, Predicate )
 *        test cases.
 */
equal_Test_Case const equal4Iterators_TEST_CASES[]{
    // clang-format off

    {
        "",
        "",
        true },
    {
        "xlC8WWhQqaVcM3",
        "xlC8WWhQqbVcM3fAjJ",
        false },
    {
        "xlC8WWhQqaVcM3",
        "xlC8WWhQqaVcM3fAjJ",
        false },
    {
        "xlC8WWhQqaVcM3",
        "xlC8WWhQqbVcM3",
        false },
    {
        "xlC8WWhQqaVcM3",
        "xlC8WWhQqaVcM3",
        true },

    // clang-format on
};

/**
 * \brief microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Iterator_2 ) test
 *        fixture.
 */
class equal4Iterators : public TestWithParam<equal_Test_Case> {
};

/**
 * \brief Verify microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Iterator_2 )
 *        works properly.
 */
TEST_P( equal4Iterators, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ(
        ::microlibrary::equal(
            test_case.range_1.begin(),
            test_case.range_1.end(),
            test_case.range_2.begin(),
            test_case.range_2.end() ),
        test_case.equal );
}

INSTANTIATE_TEST_SUITE_P(, equal4Iterators, ValuesIn( equal4Iterators_TEST_CASES ) );

/**
 * \brief microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Iterator_2, Predicate )
 *        test fixture.
 */
class equal4IteratorsPredicate : public TestWithParam<equal_Test_Case> {
};

/**
 * \brief Verify microlibrary::equal( Iterator_1, Iterator_1, Iterator_2, Iterator_2,
 *        Predicate ) works properly.
 */
TEST_P( equal4IteratorsPredicate, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ(
        ::microlibrary::equal(
            test_case.range_1.begin(),
            test_case.range_1.end(),
            test_case.range_2.begin(),
            test_case.range_2.end(),
            []( auto a, auto b ) { return a == b; } ),
        test_case.equal );
}

INSTANTIATE_TEST_SUITE_P(, equal4IteratorsPredicate, ValuesIn( equal4Iterators_TEST_CASES ) );
