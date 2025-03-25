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
    Creation Date:  March 25th, 2025
*/

#pragma once

#include <cstdint>


namespace lime::md::citrius
{

    enum class sro_trade_indicator : std::uint8_t
    {
        undefined               = 0, // reserved
        no_sro_required         = 1,
        average_price           = 2,
        automatic_execution     = 3,
        price_variation         = 4,
        odd_lot                 = 5,
        rule_127                = 6,
        rule_155                = 7,
        market_center_close     = 8,
        prior_reference_price   = 9,
        market_center_open      = 10,
        contingent              = 11,
        cross_trade             = 12,
        stopped_stock           = 13,
        acquisition             = 14,
        bunched                 = 15,
        distribution            = 16,
        reserved                = 17,
        bunched_sold_trade      = 18,
        split_trade             = 19,
        regular_sale            = 20 
    };

} // namespace lime::md::citrius


namespace lime
{
    using citrius_sro_trade_indicator = md::citrius::sro_trade_indicator;
} // namespace lime