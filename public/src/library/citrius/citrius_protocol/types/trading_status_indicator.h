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

    enum class trading_status_indicator : std::uint8_t
    {
        undefined                           = 0, // reserved
        trading_halted                      = 1,
        trading_paused                      = 2,
        trading                             = 3,
        quotes_only                         = 4,
        unknown                             = 5,
        revoked                             = 6,
        deleted                             = 7,
        security_status_not_applicable      = 8,
        opening_delay                       = 9,
        no_open_no_resume                   = 10,
        price_indication                    = 11,
        trading_range_indication            = 12,
        market_imbalance_buy                = 13,
        market_imbalance_sell               = 14,
        market_on_close_imbalance_buy       = 15,
        market_on_close_imbalance_sell      = 16,
        reserved                            = 17,
        no_market_imbalance                 = 18,
        no_market_on_close_imbalance        = 19  
    };

} // namespace lime::md::citrius


namespace lime
{
    using citrius_trading_status_indicator = md::citrius::trading_status_indicator;
} // namespace lime