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

#include <include/endian.h>
#include <library/message.h>

#include <concepts>
#include <type_traits>


namespace lime::md
{

    //=========================================================================
    enum class sequence_number_increment_policy
    {
        per_message     = 0,        // increment the seq num by the number of messages in the block
        per_packet      = 1,        // increment the seq num by one per packet

        default_policy  = per_message
        // TODO
    };


    //=========================================================================
    template <std::integral T, T N = {}, sequence_number_increment_policy P = sequence_number_increment_policy::default_policy>
    struct sequence_number_traits
    {
        using value_type = T;                       // underlying sequence number fundamental integral type (32 bit, 64 bit etc)
        static auto constexpr initial_value = N;    // the initial value of the sequence number
        static auto constexpr increment_policy = P; // stub at the moment.  this policy will define which, of the few common methods, are used to increment the sequence number 
    };


    //=========================================================================
    template <typename T>
    concept sequence_number_traits_concept = std::is_same_v<T, sequence_number_traits<typename T::value_type, T::initial_value, T::increment_policy>>;


    template <message::protocol_concept T1, sequence_number_traits_concept T2> struct market_feed_traits;


    //=========================================================================
    template <message::protocol_concept T1, sequence_number_traits_concept T2>
    class sequence_number
    {
    public:
        using protocol = T1;
        using traits = T2;
        using value_type = traits::value_type;
        static auto constexpr increment_policy = traits::increment_policy;

        sequence_number() = default;
        sequence_number(sequence_number const &) = default;
        sequence_number & operator = (sequence_number const &) = default;
        sequence_number(sequence_number &&) = default;
        sequence_number & operator = (sequence_number &&) = default;

        sequence_number
        (
            value_type
        );

        value_type get() const;

        sequence_number operator - 
        (
            value_type
        ) const;

        sequence_number operator + 
        (
            value_type
        ) const;

        value_type operator - 
        (
            sequence_number const &
        ) const;

        value_type operator + 
        (
            sequence_number const &
        ) const;

        sequence_number & operator +=
        (
            value_type
        );

        auto operator <=> 
        (
            sequence_number const &
        ) const;

        auto operator != 
        (
            sequence_number const &
        ) const;

    private:

        value_type value_{traits::initial_value};
    };


    //=========================================================================
    template <typename T>
    concept sequence_number_concept = std::is_same_v<T, typename market_feed_traits<typename T::protocol, typename T::traits>::sequence_number>;


    //=========================================================================
    [[maybe_unused]] 
    static inline auto byte_swap
    (
        sequence_number_concept auto source
    ) -> std::decay_t<decltype(source)>
    {
        using lime::byte_swap;
        return {byte_swap(source.get())};
    }

} // namespace lime::md


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
lime::md::sequence_number<T1, T2>::sequence_number
(
    value_type value
):
    value_(value)
{
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::get
(
) const -> value_type
{
    return value_;
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator - 
(
    value_type value
) const -> sequence_number
{
    return {value_ - value};
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator + 
(
    value_type value
) const -> sequence_number
{
    return {value_ + value};
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator += 
(
    value_type value
) -> sequence_number &
{
    value_ += value;
    return *this;
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator - 
(
    sequence_number const & other
) const -> value_type
{
    return (value_ - other.value_);
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator + 
(
    sequence_number const & other
) const -> value_type 
{
    return (value_ + other.value_);
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator <=> 
(
    sequence_number const & other
) const
{
    return (value_ <=> other.value_);
}


//=============================================================================
template <lime::message::protocol_concept T1, lime::md::sequence_number_traits_concept T2>
auto lime::md::sequence_number<T1, T2>::operator != 
(
    sequence_number const & other
) const
{
    return (value_ != other.value_);
}
