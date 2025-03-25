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

#include "./financial_instrument.h"
#include "./feed_format.h"

#include <include/endian.h>

#include <cstdint>


namespace lime::md::citrius
{

    #pragma pack(push, 1)
    struct multicast_id
    {
        financial_instrument    financialInstrument_;
        feed_format             feedFormat_;
        std::uint32_t           ipAddress_;
        std::uint16_t           portId_;

        operator std::uint64_t() const{return *reinterpret_cast<std::uint64_t const *>(this);}

        auto operator <=> (multicast_id const &) const = default;
    };
    #pragma pack(pop)

    static_assert(sizeof(multicast_id) == sizeof(std::uint64_t));


    //=========================================================================
    [[maybe_unused]] 
    static inline multicast_id byte_swap
    (
        multicast_id source
    )
    {
        using lime::byte_swap;
        return {byte_swap(source.financialInstrument_), byte_swap(source.feedFormat_), byte_swap(source.ipAddress_), byte_swap(source.portId_)};
    }

} // namespace lime::md::citrius


namespace lime
{
    using citrius_multicast_id = md::citrius::multicast_id;
} // namespace lime