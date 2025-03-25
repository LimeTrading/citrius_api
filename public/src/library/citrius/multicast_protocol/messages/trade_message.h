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
    struct message<md::citrius::protocol, md::citrius::message_type_indicator::trade> :
        citrius_message_header
    {
        static auto constexpr type = message_type_indicator::trade;
        
        message():message_header(type, sizeof(*this)){}
        static constexpr auto size(){return sizeof(message);}

        big_endian<book_id>                             bookId_;
        big_endian<participant_indicator>               participantIndicator_;
        big_endian<trade_shares>                        shares_;
        big_endian<trade_price>                         price_;
        big_endian<timestamp>                           exchangeTimeStamp_;
        big_endian<timestamp>                           citriusTimeStamp_;
        big_endian<trade_reference_number>              tradeReferenceNumber_;
        big_endian<settlement_type_indicator>           settlementIndicator_;
        big_endian<trade_through_exemption_indicator>   tradeThroughExemptionIndicator_;
        big_endian<extended_hours_indicator>            extendedHoursIndicator_;
        big_endian<sro_trade_indicator>                 sroTradeIndicator_;
        big_endian<std::uint8_t>                        feedSpecificTradeProperties_;
        big_endian<volume_update_indicator>             volumeUpdateIndicator_;
        std::array<std::uint8_t, 3>                     reserved_;
        big_endian<high_low_open_trade_indicator>       highLowOpenIndicator_;
    };
    #pragma pack(pop)

} // namespace lime::message


namespace lime::md::citrius
{
    using trade_message = message::message<protocol, message_type_indicator::trade>;
    static_assert(sizeof(trade_message) == 55);
}
