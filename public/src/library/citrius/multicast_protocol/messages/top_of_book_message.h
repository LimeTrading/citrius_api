#pragma once

#include <include/quotation.h>

#include <array>
#include <cstdint>


namespace lime::message
{

    #pragma pack(push, 1)
    template <>
    struct message<md::citrius::protocol, md::citrius::message_type_indicator::top_of_book> :
        citrius_message_header
    {
        static auto constexpr type = message_type_indicator::top_of_book;

        message():message_header(type, sizeof(message) - sizeof(appendages_)){}

        //=====================================================================
        template <quotation_type T>
        struct quote
        {
            static auto constexpr quotation_type = T;
            using price_type = price_quotation<quotation_type, std::uint32_t>;
            using shares_type = shares_quotation<quotation_type, std::uint32_t>;

            quote() = default;
            quote(quote const &) = default;
            quote & operator = (quote const &) = default;
            quote(quote &&) = default;
            quote & operator = (quote &&) = default;

            quote
            (
                participant_indicator participantIndicator,
                std::array<char, 4> mpid,
                shares_type shares,
                price_type price
            ):
                participantIndicator_(participantIndicator),
                mpid_(mpid),
                shares_(shares),
                price_(price)
            {
            }

            big_endian<participant_indicator>   participantIndicator_;
            std::array<char, 4>                 mpid_;
            big_endian<shares_type>             shares_; 
            big_endian<price_type>              price_;
        };


        //=====================================================================
        template <quotation_type T>
        struct nbbo_appendage
        {
            static auto constexpr quotation_type = T;

            quote<quotation_type>       quote_;
            quote_condition_indicator   quoteConditionIndicator_;
        };

        using bid_quote                 = quote<quotation_type::bid>;
        using ask_quote                 = quote<quotation_type::ask>;
        using abstract_bid_appendage    = nbbo_appendage<quotation_type::abstract>;
        using nbbo_bid_appendage        = nbbo_appendage<quotation_type::bid>;
        using nbbo_ask_appendage        = nbbo_appendage<quotation_type::ask>; 


        big_endian<book_id>                     bookId_;
        big_endian<nbbo_indicator>              nbboIndicator_;
        big_endian<bid_quote>                   bid_;
        big_endian<ask_quote>                   ask_;
        big_endian<timestamp>                   exchangeTimeStamp_;
        big_endian<timestamp>                   citriusTimeStamp_;
        big_endian<order_reference_number>      orderReferenceNumber_;
        big_endian<quote_condition_indicator>   quoteConditionIndicator_;
        // struct is dynamically sized. the appendage fields might or might not exist.
        // check nbbo indicator flags and use helper function below.
        std::array<abstract_bid_appendage, 2>   appendages_;
    };
    #pragma pack(pop)

} // namespace lime::message


namespace lime::md::citrius
{
    using top_of_book_message = message::message<protocol, message_type_indicator::top_of_book>;
    static_assert(sizeof(top_of_book_message::nbbo_bid_appendage) == 15);
    static_assert(sizeof(top_of_book_message::nbbo_ask_appendage) == 15);
    static_assert(sizeof(top_of_book_message::abstract_bid_appendage) == 15);
    static_assert(sizeof(top_of_book_message) == 65 +(sizeof(top_of_book_message::abstract_bid_appendage) * 2));

    static auto has_bid_appendage(top_of_book_message const &);
    static auto has_ask_appendage(top_of_book_message const &);
    static auto const * get_bid_appendage(top_of_book_message const &);
    static auto const * get_ask_appendage(top_of_book_message const &);

} // namespace lime::md::citrius


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_bid_appendage
(
    top_of_book_message const & topOfBookMessage
)
{
    return has_bid_appendage(topOfBookMessage.nbboIndicator_);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto lime::md::citrius::has_ask_appendage
(
    top_of_book_message const & topOfBookMessage
)
{
    return has_ask_appendage(topOfBookMessage.nbboIndicator_);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto const * lime::md::citrius::get_bid_appendage
(
    top_of_book_message const & topOfBookMessage
)
{
    auto hasBidAppendage = has_bid_appendage(topOfBookMessage);
    return (hasBidAppendage ? reinterpret_cast<top_of_book_message::nbbo_bid_appendage const *>(&topOfBookMessage.appendages_[0]) : nullptr);
}


//=============================================================================
[[__maybe_unused__]]
static inline auto const * lime::md::citrius::get_ask_appendage
(
    top_of_book_message const & topOfBookMessage
)
{
    auto hasAskAppendage = has_ask_appendage(topOfBookMessage);
    auto hasBidAppendage = has_bid_appendage(topOfBookMessage);
    return (hasAskAppendage ? reinterpret_cast<top_of_book_message::nbbo_ask_appendage const *>(&topOfBookMessage.appendages_[hasBidAppendage]) : nullptr);
}
