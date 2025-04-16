/*
MIT License

Copyright (c) 2025 Lime Trading

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
    Contributors: MAM
    Creation Date:  April 16th, 2025
*/


#pragma once

#include <include/endian.h>

#include <type_traits>
#include <cstdint>
#include <string_view>


namespace lime::md
{

    class tick_size
    {
    public:

        enum class value_type : std::uint8_t
        {
            // begin enumeration (from zero and monotonically increasing)
            undefined                   = 0,

            penny_always                = 1,
            penny_until_3_then_nickel   = 2,
            nickel_until_3_then_dime    = 3,

            // end enumeration
            num_unique_values
        };

        tick_size() = default;

        tick_size
        (
            value_type
        );

        value_type get() const;

        bool is_valid() const;

        static auto constexpr get_num_unique_values();

    private:

        value_type value_{value_type::undefined};

    }; // class tick_size


    //=========================================================================
    [[maybe_unused]] static std::string const & to_string
    (
        tick_size
    );


    //=========================================================================
    [[maybe_unused]] static inline auto byte_swap
    (
        tick_size tickSize
    ) -> tick_size
    {
        using lime::byte_swap;
        return {byte_swap(tickSize.get())};
    }   

} // namespace lime::md


//=============================================================================
[[maybe_unused]] inline lime::md::tick_size::tick_size
(
    value_type value
):
    value_(value)
{
}


//=============================================================================
[[maybe_unused]] inline auto lime::md::tick_size::get
(
) const -> value_type
{
    return value_;
}


//=============================================================================
[[maybe_unused]] inline bool lime::md::tick_size::is_valid
(
) const
{
    return (value_ < value_type::num_unique_values);
}


//=============================================================================
[[maybe_unused]] inline auto constexpr lime::md::tick_size::get_num_unique_values
(
)
{
    return static_cast<std::underlying_type_t<value_type>>(value_type::num_unique_values);
}


//=============================================================================
[[maybe_unused]] std::string const & lime::md::to_string
(
    tick_size tickSize
)
{
    using namespace std::string_literals;

    switch (tickSize.get())
    {
        case tick_size::value_type::penny_always:
        {
            static auto const value{"penny_always"s};
            return value;
        }
        case tick_size::value_type::penny_until_3_then_nickel:
        {
            static auto const value = "penny_until_3_then_nickel"s;
            return value;
        }
        case tick_size::value_type::nickel_until_3_then_dime:
        {
            static auto const value = "nickel_until_3_then_dime"s;
            return value;
        }
        default:
        {
            static auto const value = "unknown"s;
            return value;
        }
    };
}
