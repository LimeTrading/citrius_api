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
    Creation Date:  April 16th, 2025
*/

#pragma once

#include <include/quotation.h>
#include <include/endian.h>

#include "./symbol_name.h"

#include <string_view>
#include <span>
#include <array>
#include <cctype>
#include <cstdint>
#include <span>
#include <type_traits>
#include <chrono>
#include <ctime>


namespace lime::md
{

    #pragma pack(push, 1)
    class osi_name
    {
    public:

        using hash_type = std::uint64_t;
        using price_type = strike_fixed_price<3, std::uint32_t>;
        using symbol_type = std::array<char, 6>;
        enum class option_type : char
        {
            put = 'P',
            call = 'C',
            undefined = '?'
        };

        osi_name() = default;

        osi_name
        (
            std::span<char const>,
            std::uint32_t,
            std::uint32_t,
            std::uint32_t,
            option_type,
            price_type
        );

        osi_name
        (
            std::span<char const>
        );

        osi_name
        (
            symbol_name_concept auto &&
        );

        option_type get_option_type() const;

        price_type const & get_strike_price() const;

        std::span<char const> get_symbol() const;

        std::uint8_t get_year() const;

        std::uint8_t get_month() const;

        std::uint8_t get_day() const;

        bool operator ==
        (
            osi_name const &
        ) const = default;

        bool is_expired() const;

        template <symbol_name_concept T>
        operator T() const;
        
        template <symbol_mapping_concept T>
        operator T() const;

    private:

        symbol_type             symbol_;

        std::uint8_t            year_{0};

        std::uint8_t            month_{0};

        std::uint8_t            day_{0};

        option_type             optionType_{option_type::undefined};

        price_type              strikePrice_;

    }; // class osi_name
    #pragma pack(pop)


    static_assert(sizeof(osi_name) == 14);


    //=========================================================================
    auto inline byte_swap
    (
        // allow osi_names to be used in messages as big_endian or little_endian
        osi_name const & other
    ) -> osi_name
    {
        using lime::byte_swap;
        return osi_name(other.get_symbol(), other.get_year(), other.get_month(),
                other.get_day(), other.get_option_type(), byte_swap(other.get_strike_price()));
    }    


    //=========================================================================
    [[maybe_unused]] static std::string to_string
    (
        osi_name const & osiName
    )
    {
        char result[21 + 1];
        auto cur = result;
        for (auto c : osiName.get_symbol())
        {
            *cur = c;
            cur += (c != ' ');
        }
        auto year = osiName.get_year();
        *cur++ = ('0' + (year / 10));
        *cur++ = ('0' + (year % 10));
        auto month = osiName.get_month();
        *cur++ = ('0' + (month / 10));
        *cur++ = ('0' + (month % 10));
        auto day = osiName.get_day();
        *cur++ = ('0' + (day / 10));
        *cur++ = ('0' + (day % 10));
        auto optionType = osiName.get_option_type();
        *cur++ = static_cast<std::underlying_type_t<decltype(optionType)>>(optionType);
        auto strikePrice = osiName.get_strike_price();
        auto strikePriceAsString = std::to_string(strikePrice.get().get_underlying_value());
        for (auto i = 0ull; i < (8 - strikePriceAsString.size()); ++i)
            *cur++ = '0';
        for (auto c : strikePriceAsString)
            *cur++ = c;
        *cur = '\0';
        return {result, (std::size_t)std::distance(result, cur)};
    }


    //=========================================================================
    [[maybe_unused]] static std::string to_string
    (
        osi_name::option_type type
    )
    {
        using namespace std::string_literals;

        switch (type)
        {
            case osi_name::option_type::put: return "put"s;
            case osi_name::option_type::call: return "call"s;
            case osi_name::option_type::undefined: return "undefined"s;
            default:
                return "undefined"s;
        };
    }

} // namespace lime::md


//=========================================================================
template <>
struct std::hash<lime::md::osi_name>
{
    auto operator()
    (
        auto const & source
    ) const noexcept
    {
        // bits 0-4 -> day
        // bits 5-8 -> month
        // bits 9-15 -> year
        // bit 16 -> type (put/call)
        // bits 17-43 -> price
        std::uint64_t result = source.get_strike_price().get().get_underlying_value();
        result <<= 1;
        result |= (source.get_option_type() == lime::md::osi_name::option_type::put);
        result <<= 7;
        result |= source.get_year();
        result <<= 4;
        result |= source.get_month();
        result <<= 5;
        result |= source.get_day();
        auto symbolHash = std::hash<std::string_view>()({source.get_symbol().data(), source.get_symbol().size()});
        result ^= symbolHash;
        return result;
    }
};


//=============================================================================
inline lime::md::osi_name::osi_name
(
    std::span<char const> name
)
{
    auto begin = name.data();
    auto end = name.data() + name.size();
    while ((begin < end) && (std::isspace(*begin)))
        ++begin;
    while ((end > begin) && (std::isspace(end[-1])))
        --end;
    auto trimmed = std::span(begin, end - begin);

    auto symbol = trimmed.subspan(0, (trimmed.size() > 15) ? trimmed.size() - 15 : 0);
    auto c = std::copy(symbol.begin(), (symbol.size() <= symbol_.size()) ? symbol.end() : symbol.begin() + symbol_.size(), symbol_.begin());
    std::fill(c, symbol_.end(), ' ');

    auto cur = (trimmed.data() + symbol.size());
    year_ = ((*cur++ - '0') * 10);
    year_ += (*cur++ - '0');
    month_ = ((*cur++ - '0') * 10);
    month_ += (*cur++ - '0');
    day_ = ((*cur++ - '0') * 10);
    day_ +=  (*cur++ - '0');
    optionType_ = ((*cur == 'P') ? option_type::put : ((*cur == 'C') ? option_type::call : option_type::undefined));
    ++cur;
    try
    {
        auto price = std::atoi(std::string(cur, 8).c_str());
        strikePrice_ = price_type(price);
    }
    catch (std::exception const & exception)
    {
        std::cerr << "Bad OSI symbol data - dollar/decimal failed conversion from ascii to integer";
    }
}


//=============================================================================
inline lime::md::osi_name::osi_name
(
    symbol_name_concept auto && symbolName
):
    osi_name(std::span(symbolName))
{
}


//=============================================================================
inline lime::md::osi_name::osi_name
(
    std::span<char const> symbol,
    std::uint32_t year,
    std::uint32_t month,
    std::uint32_t day,
    option_type optionType,
    price_type strikePrice
):
    year_(year),
    month_(month),
    day_(day),
    optionType_(optionType),
    strikePrice_(strikePrice)
{
    auto c = std::copy(symbol.begin(), (symbol.size() <= symbol_.size()) ? symbol.end() : symbol.begin() + symbol_.size(), symbol_.begin());
    std::fill(c, symbol_.end(), ' ');
}


//=============================================================================
template <lime::md::symbol_mapping_concept T>
inline lime::md::osi_name::operator T
(
) const
{
    static auto constexpr underlying_symbol_bits = 5;
    static auto constexpr underlying_symbol_hash_mask = ((1 << underlying_symbol_bits) - 1);

    auto hash = std::hash<osi_name>()(*this);
    auto hash2 = std::hash<std::string_view>()({symbol_.data(), symbol_.size()});
    hash <<= underlying_symbol_bits;
    hash |= (hash2 & underlying_symbol_hash_mask);
    return T(hash);
}


//=============================================================================
template <lime::md::symbol_name_concept T>
inline lime::md::osi_name::operator T 
(
) const
{
    return to_string(*this);
}


//=============================================================================
inline bool lime::md::osi_name::is_expired
(
) const
{
    time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tm localTime = *localtime(&tt);

    auto currentYear = (localTime.tm_year % 100);
    auto currentMonth = ((localTime.tm_mon) + 1);
    auto currentDay = (localTime.tm_mday);
    if (currentYear != year_)
        return (year_ < currentYear);
    if (currentMonth != month_)
        return (month_ < currentYear);
    return (day_ < currentDay);
}


//=============================================================================
inline std::uint8_t lime::md::osi_name::get_year
(
) const
{
    return year_;
}


//=============================================================================
inline std::uint8_t lime::md::osi_name::get_month
(
) const
{
    return month_;
}


//=============================================================================
inline std::uint8_t lime::md::osi_name::get_day
(
) const
{
    return day_;
}


//=============================================================================
inline auto lime::md::osi_name::get_option_type
(
) const -> option_type
{
    return optionType_;
}

    
//=============================================================================
inline auto lime::md::osi_name::get_strike_price
(
) const -> price_type const & 
{
    return strikePrice_;
}

    
//=============================================================================
inline auto lime::md::osi_name::get_symbol
(
) const -> std::span<char const>
{
    auto begin = symbol_.data();
    auto end = begin + symbol_.size();
    while ((begin < end) && (std::isspace(*begin) || (*begin == 0)))
        ++begin;
    while ((end > begin) && (std::isspace(end[-1]) || (end[-1] == 0)))
        --end;
    return std::span(begin, end - begin);
}
