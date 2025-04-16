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

#include <include/trim.h>
#include <library/configuration.h>

#include <cstdint>


namespace lime::md
{

    enum class financial_instrument : std::uint8_t
    {
        undefined        = 0,   // reserved
        equities         = 1,
        options          = 2
    };


    //=============================================================================
    [[maybe_unused]] static std::string_view to_string
    (
        financial_instrument source
    )
    {
        using namespace std::string_literals;

        switch (source)
        {
            case financial_instrument::equities:
            {
                static auto constexpr value = "equities";
                return value;
            }
            case financial_instrument::options:
            {
                static auto constexpr value = "options";
                return value;
            }
            default:
            {
                static auto constexpr value = "undefined";
                return value;
            }
        }
    }


    //=========================================================================
    [[maybe_unused]] static void from_string
    (
        std::string_view const value,
        financial_instrument & destination
    )
    {
        using namespace std::string_literals;

        static auto const equities = "equities"s;
        static auto const options = "options"s;
        static auto const undefined = "undefined"s;

        destination = financial_instrument::undefined;
        if (value.compare(equities) == 0)
            destination = financial_instrument::equities;
        if (value.compare(options) == 0)
            destination = financial_instrument::options;
    }


    //=========================================================================
    [[maybe_unused]] static void to_json
    (
        configuration::json & destination,
        financial_instrument const & source
    )
    {
        destination = to_string(source);
    }


    //=========================================================================
    [[maybe_unused]] static void from_json
    (
        configuration::json const & source,
        financial_instrument & destination
    )
    {
        from_string(source.get<std::string>(), destination);
    }

}
