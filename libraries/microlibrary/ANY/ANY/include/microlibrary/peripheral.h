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
 * \brief microlibrary::Peripheral interface.
 */

#ifndef MICROLIBRARY_PERIPHERAL_H
#define MICROLIBRARY_PERIPHERAL_H

#include <cstdint>

#include "microlibrary/pointer.h"
#include "microlibrary/precondition.h"

/**
 * \brief Peripheral facilities.
 */
namespace microlibrary::Peripheral {

/**
 * \brief Peripheral instance.
 *
 * \tparam T The type of the peripheral instance.
 * \tparam INSTANCE_ADDRESS The address of the peripheral instance.
 */
template<typename T, std::uintptr_t INSTANCE_ADDRESS>
class Instance {
  public:
    /**
     * \brief The type of the peripheral instance.
     */
    using Type = T;

    /**
     * \brief The address of the peripheral instance.
     */
    static constexpr auto ADDRESS = INSTANCE_ADDRESS;

    /**
     * \brief Get a pointer to the peripheral instance.
     *
     * \return A pointer to the peripheral instance.
     */
    static auto pointer() noexcept -> Not_Null<Type *>
    {
        return Not_Null{ BYPASS_PRECONDITION_EXPECTATION_CHECKS, reinterpret_cast<Type *>( ADDRESS ) };
    }

    Instance() = delete;

    Instance( Instance && ) = delete;

    Instance( Instance const & ) = delete;

    ~Instance() = delete;

    auto operator=( Instance && ) = delete;

    auto operator=( Instance const & ) = delete;
};

} // namespace microlibrary::Peripheral

#endif // MICROLIBRARY_PERIPHERAL_H
