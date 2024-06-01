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
 * \brief microlibrary I/O streams interface.
 */

#ifndef MICROLIBRARY_STREAM_H
#define MICROLIBRARY_STREAM_H

namespace microlibrary {

/**
 * \brief Output formatter.
 *
 * \tparam T The type to print.
 *
 * \attention This class must be fully or partially specialized for each type that will
 *            support formatted output.
 */
template<typename T, typename = void>
class Output_Formatter {
  public:
    /**
     * \brief Constructor.
     */
    Output_Formatter() noexcept;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    Output_Formatter( Output_Formatter && source ) noexcept;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    Output_Formatter( Output_Formatter const & original ) noexcept;

    /**
     * \brief Destructor.
     */
    ~Output_Formatter() noexcept;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Output_Formatter && expression ) noexcept -> Output_Formatter &;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Output_Formatter const & expression ) noexcept -> Output_Formatter &;
};

} // namespace microlibrary

#endif // MICROLIBRARY_STREAM_H
