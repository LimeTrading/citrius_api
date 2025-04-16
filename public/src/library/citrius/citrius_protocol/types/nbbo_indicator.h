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

    enum nbbo_indicator : std::uint8_t
    {
        // flags
        not_included_in_bbo_flag = 0,
        no_nbbo_flag             = 1,
        no_change_nbbo_flag      = 2,
        is_nbbo_flag             = 4,
        has_nbbo_appendage_flag  = 8,

        undefined                   = not_included_in_bbo_flag,
        
        // bid indicators
        no_nbbo_bid                 = (no_nbbo_flag              << 0),
        no_change_nbbo_bid          = (no_change_nbbo_flag       << 0),
        is_nbbo_bid                 = (is_nbbo_flag              << 0),
        has_nbbo_appendage_bid      = (has_nbbo_appendage_flag   << 0),

        // ask indicators
        no_nbbo_ask                 = (no_nbbo_flag              << 4),
        no_change_nbbo_ask          = (no_change_nbbo_flag       << 4),
        is_nbbo_ask                 = (is_nbbo_flag              << 4),
        has_nbbo_appendage_ask      = (has_nbbo_appendage_flag   << 4)
    };

    static auto has_nbbo_update(nbbo_indicator);
    static auto has_bid_appendage(nbbo_indicator);
    static auto has_ask_appendage(nbbo_indicator);
    static auto has_nbbo_bid_update(nbbo_indicator);
    static auto has_nbbo_ask_update(nbbo_indicator);

} // namespace lime::md::citrius


namespace lime
{
    using citrius_nbbo_indicator = md::citrius::nbbo_indicator;
} // namespace lime


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_bid_appendage
(
    nbbo_indicator nbboIndicator
)
{
    static auto constexpr flag = static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::has_nbbo_appendage_bid);
    return ((static_cast<std::underlying_type_t<nbbo_indicator>>(nbboIndicator) & flag) != 0);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_nbbo_bid_update
(
    // returns true if indicates and nbbo bid
    nbbo_indicator nbboIndicator
)
{
    static auto constexpr flags = static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::is_nbbo_bid) |
            static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::has_nbbo_appendage_bid) |
            static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::no_nbbo_bid);
    return ((static_cast<std::underlying_type_t<nbbo_indicator>>(nbboIndicator) & flags) != 0);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_ask_appendage
(
    nbbo_indicator nbboIndicator
)
{
    static auto constexpr flag = static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::has_nbbo_appendage_ask);
    return ((static_cast<std::underlying_type_t<nbbo_indicator>>(nbboIndicator) & flag) != 0);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_nbbo_ask_update
(
    // returns true if indicates and nbbo ask
    nbbo_indicator nbboIndicator
)
{    
    static auto constexpr flags = static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::is_nbbo_ask) |
            static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::has_nbbo_appendage_ask) |
            static_cast<std::underlying_type_t<nbbo_indicator>>(nbbo_indicator::no_nbbo_ask);
    return ((static_cast<std::underlying_type_t<nbbo_indicator>>(nbboIndicator) & flags) != 0);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_nbbo_update
(
    // returns true if flags indicate either the bid or ask (or both) and nbbo
    nbbo_indicator nbboIndicator
)
{
    return (has_nbbo_bid_update(nbboIndicator) || has_nbbo_ask_update(nbboIndicator));
}
