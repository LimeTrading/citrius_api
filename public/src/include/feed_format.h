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

    enum class feed_format : std::uint8_t
    {
        undefined                           = 0,    // reserved
        national_consolidated_top_of_book   = 1,
        depth_of_book                       = 2,
        consolidated_top_of_book            = 3,
        top_of_book                         = 4,
        trades                              = 5,
        imbalance                           = 6
    };


    //=============================================================================
    [[maybe_unused]] static std::string_view to_string
    (
        feed_format source
    )
    {
        using namespace std::string_literals;

        switch (source)
        {
            case feed_format::top_of_book:
            {
                static auto constexpr value = "top_of_book";
                return value;
            }
            case feed_format::consolidated_top_of_book:
            {
                static auto constexpr value = "consolidated_top_of_book";
                return value;
            }
            case feed_format::national_consolidated_top_of_book:
            {
                static auto constexpr value = "national_consolidated_top_of_book";
                return value;
            }
            case feed_format::depth_of_book:
            {
                static auto constexpr value = "depth_of_book";
                return value;
            }
            case feed_format::trades:
            {
                static auto constexpr value = "trades";
                return value;
            }
            case feed_format::imbalance:
            {
                static auto constexpr value = "imbalance";
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
    static void from_string
    (
        std::string_view const value,
        feed_format & destination
    )
    {
        using namespace std::string_literals;

        static auto const top_of_book = "top_of_book"s;
        static auto const consolidated_top_of_book = "consolidated_top_of_book"s;
        static auto const national_consolidated_top_of_book = "national_consolidated_top_of_book"s;
        static auto const depth_of_book = "depth_of_book"s;
        static auto const trades = "trades"s;
        static auto const imbalance = "imbalance"s;
        static auto const undefined = "undefined"s;
        
        destination = feed_format::undefined;
        if (value.compare(top_of_book) == 0)
            destination = feed_format::top_of_book;
        if (value.compare(consolidated_top_of_book) == 0)
            destination = feed_format::consolidated_top_of_book;
        if (value.compare(national_consolidated_top_of_book) == 0)
            destination = feed_format::national_consolidated_top_of_book;
        if (value.compare(depth_of_book) == 0)
            destination = feed_format::depth_of_book;  
        if (value.compare(trades) == 0)
            destination = feed_format::trades;   
        if (value.compare(imbalance) == 0)
            destination = feed_format::imbalance;  
        }


    //=========================================================================
    [[maybe_unused]] static void to_json
    (
        configuration::json & destination,
        feed_format const & source
    )
    {
        destination = to_string(source);
    }


    //=========================================================================
    [[maybe_unused]] static void from_json
    (
        configuration::json const & source,
        feed_format & destination
    )
    {
        from_string(source.get<std::string>(), destination);
    }


} // namespace lime::md
