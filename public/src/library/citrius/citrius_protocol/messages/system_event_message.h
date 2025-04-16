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


namespace lime::message
{

    #pragma pack(push, 1)
    template <>
    struct message<md::citrius::protocol, md::citrius::message_type_indicator::system_event> :
        citrius_message_header
    {
        static auto constexpr type = message_type_indicator::system_event;
        
        message():message_header(type, sizeof(*this)){}
        static constexpr auto size(){return sizeof(message);}

        big_endian<system_event_indicator> eventIndicator_;
    };
    #pragma pack(pop)

} // namespace lime::message


namespace lime::md::citrius
{
    using system_event_message = message::message<citrius::protocol, message_type_indicator::system_event>;
    static_assert(sizeof(system_event_message) == 4);
}
