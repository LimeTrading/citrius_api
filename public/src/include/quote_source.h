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

    enum class quote_source : std::uint8_t
    {
        undefined                       = 0, // reserved
        opra                            = 1,
        siac                            = 2,
        tvitch                          = 3,
        otc                             = 4,
        citrius                         = 5,
        utp                             = 8,
        edga                            = 9,
        edgx                            = 10,
        bats                            = 11,
        nyse                            = 12,
        nyse_arca                       = 13,
        byx                             = 14,
        psx                             = 15,
        bsx                             = 16,
        nyse_american_open_book_ultra   = 17,
        nyse_open_book_ultra            = 18,
        nyse_american                   = 19,
        iex                             = 20,
    }; // class buy_sell_indicator


    //=========================================================================
    [[maybe_unused]] static std::string to_string
    (
        quote_source type
    )
    {
        using namespace std::string_literals;

        switch (type)
        {
            case quote_source::opra: return "opra"s;
            case quote_source::siac: return "siac"s;
            case quote_source::tvitch: return "tvitch"s;
            case quote_source::otc: return "otc"s;
            case quote_source::citrius: return "citrius"s;
            case quote_source::utp: return "utp"s;
            case quote_source::edga: return "edga"s;
            case quote_source::edgx: return "edgx"s;
            case quote_source::bats: return "bats"s;
            case quote_source::nyse: return "nyse"s;
            case quote_source::nyse_arca: return "nyse_arca"s;
			case quote_source::byx: return "byx"s;
			case quote_source::psx: return "psx"s;
			case quote_source::bsx: return "bsx"s;
			case quote_source::nyse_american_open_book_ultra: return "nyse_american_open_book_ultra"s;
			case quote_source::nyse_open_book_ultra: return "nyse_open_book_ultra"s;
			case quote_source::nyse_american: return "nyse_american"s;
			case quote_source::iex: return "iex"s;
            case quote_source::undefined: return "undefined"s;
            default:
                return "undefined"s;
        };
    }


    //=========================================================================
    [[maybe_unused]] static quote_source & from_string
    (
        std::string_view const value,
        quote_source & destination
    )
    {
        using namespace std::string_literals;

		static auto const opra = "opra"s;
		static auto const siac = "siac"s;
		static auto const tvitch = "tvitch"s;
		static auto const otc = "otc"s;
		static auto const citrius = "citrius"s;
		static auto const utp = "utp"s;
		static auto const edgx = "edgx"s;
		static auto const edga = "edga"s;
		static auto const bats = "bats"s;
		static auto const nyse = "nyse"s;
		static auto const byx = "byx"s;
		static auto const psx = "psx"s;
		static auto const bsx = "psx"s;
		static auto const nyse_american_open_book_ultra = "nyse_american_open_book_ultra"s;
		static auto const nyse_open_book_ultra = "nyse_open_book_ultra"s;
		static auto const nyse_american = "nyse_american"s;
		static auto const nyse_arca = "nyse_arca"s;
		static auto const iex = "iex"s;

        destination = quote_source::undefined;

        auto same = [](auto const & a, auto const & b)
        {
            return ((a.size() == b.size()) && (std::equal(a.begin(), a.end(), b.begin(), [](auto a, auto b){return std::tolower(a) == std::tolower(b);})));
        };

        if (same(trim(value), opra))
            destination = quote_source::opra;
        else if (same(trim(value), siac))
            destination = quote_source::siac;
        else if (same(trim(value), tvitch))
            destination = quote_source::tvitch;
        else if (same(trim(value), utp))
            destination = quote_source::utp;
        else if (same(trim(value), otc))
            destination = quote_source::otc;
        else if (same(trim(value), citrius))
            destination = quote_source::citrius;
        else if (same(trim(value), edga))
            destination = quote_source::edga;
        else if (same(trim(value), edgx))
            destination = quote_source::edgx;
        else if (same(trim(value), bats))
            destination = quote_source::bats;
        else if (same(trim(value), nyse))
            destination = quote_source::nyse;
        else if (same(trim(value), nyse_arca))
            destination = quote_source::nyse_arca;
        else if (same(trim(value), byx))
			destination = quote_source::byx;
        else if (same(trim(value), psx))
			destination = quote_source::psx;
        else if (same(trim(value), bsx))
			destination = quote_source::bsx;
        else if (same(trim(value), nyse_american_open_book_ultra))
			destination = quote_source::nyse_american_open_book_ultra;
        else if (same(trim(value), nyse_open_book_ultra))
			destination = quote_source::nyse_open_book_ultra;
        else if (same(trim(value), nyse_american))
			destination = quote_source::nyse_american;
        else if (same(trim(value), iex))
			destination = quote_source::iex;
        return destination;
    }


    //=========================================================================
    [[maybe_unused]] static void to_json
    (
        configuration::json & destination,
        quote_source const & source
    )
    {
        destination = to_string(source);
    }


    //=========================================================================
    [[maybe_unused]] static void from_json
    (
        configuration::json const & source,
        quote_source & destination
    )
    {
        from_string(source.get<std::string>(), destination);
    }

}
