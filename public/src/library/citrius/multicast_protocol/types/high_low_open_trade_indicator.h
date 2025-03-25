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

    enum class high_low_open_trade_indicator : std::uint8_t
    {
        none_flag       = 0x00,
        low_flag        = 0x01,
        high_flag       = 0x02,
        open_flag       = 0x04,
        last_flag       = 0x08,

        // consolidated 
        consolidated_none   = none_flag,
        consolidated_low    = low_flag,
        consolidated_high   = high_flag,
        consolidated_last   = last_flag,

        // market participant
        participant_none    = (none_flag << 4),
        participant_low     = (low_flag << 4),
        participant_high    = (high_flag << 4),
        participant_open    = (open_flag << 4),
        participant_last    = (last_flag << 4)
    };

} // namespace lime::md::citrius


namespace lime
{
    using citrius_high_low_open_trade_indicator = md::citrius::high_low_open_trade_indicator;
} // namespace lime