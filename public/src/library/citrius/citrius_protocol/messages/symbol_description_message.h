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
#include <array>


namespace lime::message
{

    #pragma pack(push, 1)
    template <>
    struct message<md::citrius::protocol, md::citrius::message_type_indicator::symbol_description> :
        citrius_message_header
    {
        static auto constexpr type = message_type_indicator::symbol_description;
        
        message():message_header(type, sizeof(*this)){}
        static constexpr auto size(){return sizeof(message);}

        big_endian<symbol_name>         symbol_;
        big_endian<book_id>             bookId_;
        big_endian<multicast_id>        multicastId_;
        std::array<std::uint8_t, 11>    reserved_;
    };
    #pragma pack(pop)


} // namespace lime::message


namespace lime::md::citrius
{
    using symbol_description_message = message::message<md::citrius::protocol, message_type_indicator::symbol_description>;
    static_assert(sizeof(symbol_description_message) == 62);
}
