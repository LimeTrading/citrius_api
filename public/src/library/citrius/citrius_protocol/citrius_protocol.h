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

#include "./types/book_id.h"
#include "./types/participant_indicator.h"
#include "./types/buy_sell_indicator.h"
#include "./types/timestamp.h"
#include "./types/volume_update_indicator.h"
#include "./types/trading_status_indicator.h"
#include "./types/trading_session_indicator.h"
#include "./types/trade_through_exemption_indicator.h"
#include "./types/high_low_open_trade_indicator.h"
#include "./types/trade_reference_number.h"
#include "./types/tick_size.h"
#include "./types/system_event_indicator.h"
#include "./types/symbol_name.h"
#include "./types/sro_trade_indicator.h"
#include "./types/short_sale_restriction_indicator.h"
#include "./types/settlement_type_indicator.h"
#include "./types/quote_condition_indicator.h"
#include "./types/nbbo_indicator.h"
#include "./types/multicast_source_identifier.h"
#include "./types/multicast_id.h"
#include "./types/limit_up_limit_down_indicator.h"
#include "./types/gap_origin_indicator.h"
#include "./types/extended_hours_indicator.h"
#include "./types/cross_indicator.h"


#include <library/message.h>
#include <include/endian.h>
#include <include/quotation.h>
#include <include/order_reference_number.h>
#include <include/feed_format.h>
#include <include/financial_instrument.h>

#include <library/market_feed.h>

#include <cstdint>
#include <array>
#include <cstring>
#include <concepts>
#include <type_traits>


//=============================================================================
namespace lime::md::citrius
{

    enum class message_type_indicator : std::uint8_t
    {
        undefined               = 0, // reserved
        option_description      = 3,
        start_multicast         = 5,
        end_multicast           = 6,
        heart_beat              = 7,
        trade                   = 13,
        trade_cancel            = 14,
        imbalance               = 21,
        order_add               = 22,
        order_cancel            = 23,
        order_replace           = 24,
        order_delete            = 25,
        order_executed          = 26,
        symbol_description      = 27,
        top_of_book             = 28, 
        price_band              = 29,
        trading_status          = 30,
        short_sale_restriction_status = 31,
        system_event            = 32,
        trading_session         = 33,
        sequence_gap            = 36,
        book_clear              = 37,
        order_modify            = 38,
        start_of_day_summary     = 99,
        end_of_day_summary       = 100
    };


    using protocol = message::protocol
            <
                message::protocol_traits<"citrius", {2, 4, 'a'}, message_type_indicator>,
                message_type_indicator::option_description,
                message_type_indicator::start_multicast,
                message_type_indicator::end_multicast,
                message_type_indicator::heart_beat,
                message_type_indicator::trade,
                message_type_indicator::trade_cancel,
                message_type_indicator::imbalance,
                message_type_indicator::order_add,
                message_type_indicator::order_cancel,
                message_type_indicator::order_replace,
                message_type_indicator::order_delete,
                message_type_indicator::order_executed,
                message_type_indicator::symbol_description,
                message_type_indicator::top_of_book, 
                message_type_indicator::price_band,
                message_type_indicator::trading_status,
                message_type_indicator::short_sale_restriction_status,
                message_type_indicator::system_event,
                message_type_indicator::trading_session,
                message_type_indicator::sequence_gap,
                message_type_indicator::book_clear,
                message_type_indicator::order_modify,
                message_type_indicator::start_of_day_summary,
                message_type_indicator::end_of_day_summary
            >;

    using sequence_number_traits = lime::md::sequence_number_traits<std::uint64_t>;

    using market_feed_traits =
            lime::md::market_feed_traits
            <
                protocol,
                sequence_number_traits
            >;

    using sequence_number = market_feed_traits::sequence_number;

} // namespace lime::md::citrius


//=============================================================================
namespace lime
{
    // protocol types - derive from this struct to inherit all the citrius protocol's types 
    struct citrius_protocol_types
    {
        using book_id = md::citrius::book_id;
        using participant_indicator = md::citrius::participant_indicator;
        using buy_sell_indicator = md::citrius::buy_sell_indicator;
        using timestamp = md::citrius::timestamp;
        using volume_update_indicator = md::citrius::volume_update_indicator;
        using trading_status_indicator = md::citrius::trading_status_indicator;
        using trading_session_indicator = md::citrius::trading_session_indicator;
        using trade_through_exemption_indicator = md::citrius::trade_through_exemption_indicator;
        using trade_reference_number = md::citrius::trade_reference_number;
        using tick_size = md::citrius::tick_size;
        using system_event_indicator = md::citrius::system_event_indicator;
        using symbol_name = md::citrius::symbol_name;
        using sro_trade_indicator = md::citrius::sro_trade_indicator;
        using short_sale_restriction_indicator = md::citrius::short_sale_restriction_indicator;
        using settlement_type_indicator = md::citrius::settlement_type_indicator;
        using quote_condition_indicator = md::citrius::quote_condition_indicator;
        using order_reference_number = md::order_reference_number<std::uint64_t>;
        using nbbo_indicator = md::citrius::nbbo_indicator;
        using multicast_source_identifier = md::citrius::multicast_source_identifier;
        using multicast_id = md::citrius::multicast_id;
        using limit_up_limit_down_indicator = md::citrius::limit_up_limit_down_indicator;
        using gap_origin_indicator = md::citrius::gap_origin_indicator;
        using financial_instrument = md::financial_instrument;
        using feed_format = md::feed_format;
        using extended_hours_indicator = md::citrius::extended_hours_indicator;
        using high_low_open_trade_indicator = md::citrius::high_low_open_trade_indicator;
        using sequence_number = md::citrius::sequence_number;
        using cross_indicator = md::citrius::cross_indicator;
        using trade_price = lime::trade_price<std::uint32_t>;
        using trade_shares = lime::trade_shares<std::uint32_t>;
        using abstract_price = lime::abstract_price<std::uint32_t>;
        using abstract_shares = lime::abstract_shares<std::uint32_t>;
        using message_type_indicator = md::citrius::message_type_indicator;
    };


    using citrius_protocol = md::citrius::protocol;
    using citrius_sequence_number_traits = md::citrius::sequence_number_traits;
    using citrius_sequence_number = md::citrius::sequence_number;
    using citrius_multicast_source_identifier = md::citrius::multicast_source_identifier;

} // namespace lime


//=============================================================================
namespace lime::md
{

    #pragma pack(push, 1)
    template <>
    struct market_feed_traits<citrius_protocol, citrius_sequence_number_traits>::packet_header
    {
        static auto constexpr multicast_version_number = 4;

        enum class transmission_status : std::uint8_t
        {
            original    = 0,
            retransmit  = 1,
            unsequenced = 2
        };

        big_endian<std::uint8_t>                            version_{multicast_version_number};
        big_endian<std::uint16_t>                           blockSize_;
        big_endian<citrius_multicast_source_identifier>     sourceIdentifier_;
        big_endian<citrius_sequence_number>                 blockSequenceNumber_;
        big_endian<std::uint8_t>                            messagesInBlock_;
        big_endian<citrius::timestamp>                      timeStamp_;
        big_endian<std::uint16_t>                           blockCheckSum_;
        big_endian<transmission_status> mutable             transmissionStatus_{transmission_status::original};
        big_endian<feed_format>                             feedFormat_;
    };
    #pragma pack(pop)

}


//=============================================================================
namespace lime
{
    using citrius_packet_header = md::market_feed_traits<citrius_protocol, citrius_sequence_number_traits>::packet_header;
    static_assert(sizeof(citrius_packet_header) == 28);
}


//=============================================================================
namespace lime::md
{

    [[__maybe_unused__]]
    static inline citrius_sequence_number get_sequence_number
    (
        citrius_packet_header const & packetHeader
    )
    {
        return packetHeader.blockSequenceNumber_;
    }


    [[__maybe_unused__]]
    static inline std::span<char const> get_message_data
    (
        citrius_packet_header const & packetHeader
    )
    {
        auto blockSize = packetHeader.blockSize_.get();
        return std::span(reinterpret_cast<char const *>(&packetHeader) + sizeof(citrius_packet_header), blockSize - sizeof(citrius_packet_header));
    }


    [[__maybe_unused__]]
    static inline citrius_sequence_number get_next_sequence_number
    (
        citrius_sequence_number sequenceNumber,
        citrius_packet_header const & packetHeader
    )
    {
        return sequenceNumber += packetHeader.messagesInBlock_;
    }
    
} // namespace lime::md


//=============================================================================
namespace lime::message
{

    //=========================================================================
    // specialize header which is common for all messages within the protocol
    #pragma pack(push, 1)
    template <>
    struct message_header<citrius_protocol> : citrius_protocol_types
    {
        message_header(message_type_indicator messageTypeIndicator, std::uint16_t size):messageTypeIndicator_(messageTypeIndicator), size_(size){}

        message_type_indicator get_message_indicator() const{return messageTypeIndicator_;}
        std::uint16_t size() const{return size_;}

        big_endian<message_type_indicator>  messageTypeIndicator_;
        big_endian<std::uint16_t>           size_;
    };
    #pragma pack(pop)

} // namespace lime::message


namespace lime
{
    using citrius_message_header = message::message_header<citrius_protocol>;
    static_assert(sizeof(citrius_message_header) == 3);
}


#include "./messages/end_multicast_message.h"
#include "./messages/heart_beat_message.h"
#include "./messages/end_of_day_summary_message.h"
#include "./messages/imbalance_message.h"
#include "./messages/option_description_message.h"
#include "./messages/order_add_message.h"
#include "./messages/order_cancel_message.h"
#include "./messages/order_delete_message.h"
#include "./messages/order_executed_message.h"
#include "./messages/order_modify_message.h"
#include "./messages/order_replace_message.h"
#include "./messages/price_band_message.h"
#include "./messages/sequence_gap_message.h"
#include "./messages/short_sale_restriction_status_message.h"
#include "./messages/start_multicast_message.h"
#include "./messages/start_of_day_summary_message.h"
#include "./messages/symbol_description_message.h"
#include "./messages/top_of_book_message.h"
#include "./messages/trade_cancel_message.h"
#include "./messages/trade_message.h"
#include "./messages/trading_session_message.h"
#include "./messages/trading_status_message.h"
#include "./messages/book_clear_message.h"


namespace lime::md::citrius
{

    template <typename T>
    concept message_concept = std::is_same_v<T, message::message<protocol, T::message_type>>;

    template <typename T>
    using market_feed = lime::md::market_feed<T, market_feed_traits>;

} // namespace lime::md::citrius


namespace lime
{
    // aliases ... for the namespace averse (^:

    template <typename T> using citrius_market_feed = md::citrius::market_feed<T>;

    template <md::citrius::message_type_indicator T> using citrius_message = message::message<md::citrius::protocol, T>;

    template <typename T> concept citrius_message_concept = lime::md::citrius::message_concept<T>;

    using citrius_end_multicast_message = md::citrius::end_multicast_message;
    using citrius_heart_beat_message = md::citrius::heart_beat_message;
    using citrius_end_of_day_summary_message = md::citrius::end_of_day_summary_message;
    using citrius_imbalance_message = md::citrius::imbalance_message;
    using citrius_option_description_message = md::citrius::option_description_message;
    using citrius_order_add_message = md::citrius::order_add_message;
    using citrius_order_cancel_message = md::citrius::order_cancel_message;
    using citrius_order_delete_message = md::citrius::order_delete_message;
    using citrius_order_executed_message = md::citrius::order_executed_message;
    using citrius_order_modify_message = md::citrius::order_modify_message;
    using citrius_order_replace_message = md::citrius::order_replace_message;
    using citrius_price_band_message = md::citrius::price_band_message;
    using citrius_sequence_gap_message = md::citrius::sequence_gap_message;
    using citrius_short_sale_restriction_status_message = md::citrius::short_sale_restriction_status_message;
    using citrius_start_multicast_message = md::citrius::start_multicast_message;
    using citrius_start_of_day_summary_message = md::citrius::start_of_day_summary_message;
    using citrius_symbol_description_message = md::citrius::symbol_description_message;
    using citrius_top_of_book_message = md::citrius::top_of_book_message;
    using citrius_trade_cancel_message = md::citrius::trade_cancel_message;
    using citrius_trade_message = md::citrius::trade_message;
    using citrius_trading_session_message = md::citrius::trading_session_message;
    using citrius_trading_status_message = md::citrius::trading_status_message;
    using citrius_book_clear_message = md::citrius::book_clear_message;
}
