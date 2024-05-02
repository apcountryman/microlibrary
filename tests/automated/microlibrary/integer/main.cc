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
 * \brief microlibrary integer utilities automated tests.
 */

#include <bitset>
#include <cstdint>
#include <limits>
#include <ostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/integer.h"

namespace {

using ::microlibrary::highest_bit_set;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

} // namespace

/**
 * \brief microlibrary::highest_bit_set() test case.
 *
 * \tparam Integer The type of unsigned integer the lookup will be performed on.
 */
template<typename Integer>
struct highestBitSet_Test_Case {
    /**
     * \brief The unsigned integer value to perform the lookup on.
     */
    Integer value;

    /**
     * \brief The unsigned integer value's highest bit set.
     */
    std::uint_fast8_t highest_bit_set;
};

template<typename Integer>
auto operator<<( std::ostream & stream, highestBitSet_Test_Case<Integer> const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".value = 0b" << std::bitset<std::numeric_limits<Integer>::digits>{ test_case.value }
                  << ", "
                  << ".highest_bit_set = " << std::dec << static_cast<std::uint_fast16_t>( test_case.highest_bit_set )
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::highest_bit_set() std::uint8_t test fixture.
 */
class highestBitSet8 : public TestWithParam<highestBitSet_Test_Case<std::uint8_t>> {
};

/**
 * \brief Verify microlibrary::highest_bit_set() works properly.
 */
TEST_P( highestBitSet8, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ( highest_bit_set( test_case.value ), test_case.highest_bit_set );
}

/**
 * \brief microlibrary::highest_bit_set() std::uint8_t test cases.
 */
highestBitSet_Test_Case<std::uint8_t> const highestBitSet8_TEST_CASES[]{
    // clang-format off

    { 0b00000001, 0 },
    { 0b00000010, 1 },
    { 0b00000100, 2 },
    { 0b00001000, 3 },
    { 0b00010000, 4 },
    { 0b00100000, 5 },
    { 0b01000000, 6 },
    { 0b10000000, 7 },

    { 0b00000001, 0 },
    { 0b00000011, 1 },
    { 0b00000111, 2 },
    { 0b00001111, 3 },
    { 0b00011111, 4 },
    { 0b00111111, 5 },
    { 0b01111111, 6 },
    { 0b11111111, 7 },

    { 0b00000110, 2 },
    { 0b00001100, 3 },
    { 0b00011101, 4 },
    { 0b00111010, 5 },
    { 0b01010110, 6 },
    { 0b10111000, 7 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, highestBitSet8, ValuesIn( highestBitSet8_TEST_CASES ) );

/**
 * \brief microlibrary::highest_bit_set() std::uint16_t test fixture.
 */
class highestBitSet16 : public TestWithParam<highestBitSet_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify microlibrary::highest_bit_set() works properly.
 */
TEST_P( highestBitSet16, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ( highest_bit_set( test_case.value ), test_case.highest_bit_set );
}

/**
 * \brief microlibrary::highest_bit_set() std::uint16_t test cases.
 */
highestBitSet_Test_Case<std::uint16_t> const highestBitSet16_TEST_CASES[]{
    // clang-format off

    { 0b0000000000000001,  0 },
    { 0b0000000000000010,  1 },
    { 0b0000000000000100,  2 },
    { 0b0000000000001000,  3 },
    { 0b0000000000010000,  4 },
    { 0b0000000000100000,  5 },
    { 0b0000000001000000,  6 },
    { 0b0000000010000000,  7 },
    { 0b0000000100000000,  8 },
    { 0b0000001000000000,  9 },
    { 0b0000010000000000, 10 },
    { 0b0000100000000000, 11 },
    { 0b0001000000000000, 12 },
    { 0b0010000000000000, 13 },
    { 0b0100000000000000, 14 },
    { 0b1000000000000000, 15 },

    { 0b0000000000000001,  0 },
    { 0b0000000000000011,  1 },
    { 0b0000000000000111,  2 },
    { 0b0000000000001111,  3 },
    { 0b0000000000011111,  4 },
    { 0b0000000000111111,  5 },
    { 0b0000000001111111,  6 },
    { 0b0000000011111111,  7 },
    { 0b0000000111111111,  8 },
    { 0b0000001111111111,  9 },
    { 0b0000011111111111, 10 },
    { 0b0000111111111111, 11 },
    { 0b0001111111111111, 12 },
    { 0b0011111111111111, 13 },
    { 0b0111111111111111, 14 },
    { 0b1111111111111111, 15 },

    { 0b0000000000000110,  2 },
    { 0b0000000000001100,  3 },
    { 0b0000000000011101,  4 },
    { 0b0000000000111010,  5 },
    { 0b0000000001010110,  6 },
    { 0b0000000010111000,  7 },
    { 0b0000000111001111,  8 },
    { 0b0000001100001010,  9 },
    { 0b0000011000100010, 10 },
    { 0b0000110000101101, 11 },
    { 0b0001101010101011, 12 },
    { 0b0010000000100010, 13 },
    { 0b0110100010001110, 14 },
    { 0b1010010001100100, 15 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, highestBitSet16, ValuesIn( highestBitSet16_TEST_CASES ) );

/**
 * \brief microlibrary::highest_bit_set() std::uint32_t test fixture.
 */
class highestBitSet32 : public TestWithParam<highestBitSet_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify microlibrary::highest_bit_set() works properly.
 */
TEST_P( highestBitSet32, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_EQ( highest_bit_set( test_case.value ), test_case.highest_bit_set );
}

/**
 * \brief microlibrary::highest_bit_set() std::uint32_t test cases.
 */
highestBitSet_Test_Case<std::uint32_t> const highestBitSet32_TEST_CASES[]{
    // clang-format off

    { 0b00000000000000000000000000000001,  0 },
    { 0b00000000000000000000000000000010,  1 },
    { 0b00000000000000000000000000000100,  2 },
    { 0b00000000000000000000000000001000,  3 },
    { 0b00000000000000000000000000010000,  4 },
    { 0b00000000000000000000000000100000,  5 },
    { 0b00000000000000000000000001000000,  6 },
    { 0b00000000000000000000000010000000,  7 },
    { 0b00000000000000000000000100000000,  8 },
    { 0b00000000000000000000001000000000,  9 },
    { 0b00000000000000000000010000000000, 10 },
    { 0b00000000000000000000100000000000, 11 },
    { 0b00000000000000000001000000000000, 12 },
    { 0b00000000000000000010000000000000, 13 },
    { 0b00000000000000000100000000000000, 14 },
    { 0b00000000000000001000000000000000, 15 },
    { 0b00000000000000010000000000000000, 16 },
    { 0b00000000000000100000000000000000, 17 },
    { 0b00000000000001000000000000000000, 18 },
    { 0b00000000000010000000000000000000, 19 },
    { 0b00000000000100000000000000000000, 20 },
    { 0b00000000001000000000000000000000, 21 },
    { 0b00000000010000000000000000000000, 22 },
    { 0b00000000100000000000000000000000, 23 },
    { 0b00000001000000000000000000000000, 24 },
    { 0b00000010000000000000000000000000, 25 },
    { 0b00000100000000000000000000000000, 26 },
    { 0b00001000000000000000000000000000, 27 },
    { 0b00010000000000000000000000000000, 28 },
    { 0b00100000000000000000000000000000, 29 },
    { 0b01000000000000000000000000000000, 30 },
    { 0b10000000000000000000000000000000, 31 },

    { 0b00000000000000000000000000000001,  0 },
    { 0b00000000000000000000000000000011,  1 },
    { 0b00000000000000000000000000000111,  2 },
    { 0b00000000000000000000000000001111,  3 },
    { 0b00000000000000000000000000011111,  4 },
    { 0b00000000000000000000000000111111,  5 },
    { 0b00000000000000000000000001111111,  6 },
    { 0b00000000000000000000000011111111,  7 },
    { 0b00000000000000000000000111111111,  8 },
    { 0b00000000000000000000001111111111,  9 },
    { 0b00000000000000000000011111111111, 10 },
    { 0b00000000000000000000111111111111, 11 },
    { 0b00000000000000000001111111111111, 12 },
    { 0b00000000000000000011111111111111, 13 },
    { 0b00000000000000000111111111111111, 14 },
    { 0b00000000000000001111111111111111, 15 },
    { 0b00000000000000011111111111111111, 16 },
    { 0b00000000000000111111111111111111, 17 },
    { 0b00000000000001111111111111111111, 18 },
    { 0b00000000000011111111111111111111, 19 },
    { 0b00000000000111111111111111111111, 20 },
    { 0b00000000001111111111111111111111, 21 },
    { 0b00000000011111111111111111111111, 22 },
    { 0b00000000111111111111111111111111, 23 },
    { 0b00000001111111111111111111111111, 24 },
    { 0b00000011111111111111111111111111, 25 },
    { 0b00000111111111111111111111111111, 26 },
    { 0b00001111111111111111111111111111, 27 },
    { 0b00011111111111111111111111111111, 28 },
    { 0b00111111111111111111111111111111, 29 },
    { 0b01111111111111111111111111111111, 30 },
    { 0b11111111111111111111111111111111, 31 },

    { 0b00000000000000000000000000000110,  2 },
    { 0b00000000000000000000000000001100,  3 },
    { 0b00000000000000000000000000011101,  4 },
    { 0b00000000000000000000000000111010,  5 },
    { 0b00000000000000000000000001010110,  6 },
    { 0b00000000000000000000000010111000,  7 },
    { 0b00000000000000000000000111001111,  8 },
    { 0b00000000000000000000001100001010,  9 },
    { 0b00000000000000000000011000100010, 10 },
    { 0b00000000000000000000110000101101, 11 },
    { 0b00000000000000000001101010101011, 12 },
    { 0b00000000000000000010000000100010, 13 },
    { 0b00000000000000000110100010001110, 14 },
    { 0b00000000000000001010010001100100, 15 },
    { 0b00000000000000010111000001011110, 16 },
    { 0b00000000000000111101111011010000, 17 },
    { 0b00000000000001011000100010010011, 18 },
    { 0b00000000000011110011110000011110, 19 },
    { 0b00000000000100111100110101011111, 20 },
    { 0b00000000001110011010101100101011, 21 },
    { 0b00000000010011100011000000010111, 22 },
    { 0b00000000100001101000111111111000, 23 },
    { 0b00000001110111000101110101110110, 24 },
    { 0b00000011010101101001010010100011, 25 },
    { 0b00000101100110001011010011001001, 26 },
    { 0b00001111111011011011010111010101, 27 },
    { 0b00011000000110101110000101010101, 28 },
    { 0b00111100111100011110010111001110, 29 },
    { 0b01101110010000101011010001110110, 30 },
    { 0b10010010100100101000001000111010, 31 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, highestBitSet32, ValuesIn( highestBitSet32_TEST_CASES ) );
