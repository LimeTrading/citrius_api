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

#include "./market_feed_socket.h"
#include "./sequence_number.h"

#include <include/non_copyable.h>
#include <include/non_movable.h>
#include <library/message.h>

#include <concepts>
#include <cstdint>
#include <functional>
#include <span>
#include <utility>
#include <string>
#include <memory>


namespace lime::md
{


    //=========================================================================
    template <message::protocol_concept T1, sequence_number_traits_concept T2>
    struct market_feed_traits
    {
        using protocol = T1;
        using sequence_number = lime::md::sequence_number<T1, T2>;
        struct packet_header; // implementation required
    }; // market_feed_traits


    template <typename T>
    concept market_feed_traits_concept = std::is_same_v<T, market_feed_traits<typename T::protocol, typename T::sequence_number::traits>>;

    
    //=========================================================================
    template <typename target_type, market_feed_traits_concept market_feed_traits_type>
    class market_feed :
        public message::receiver<target_type, typename market_feed_traits_type::protocol>
    {
    public:

        using target = target_type; 
        using market_feed_traits = market_feed_traits_type;
        using protocol = typename market_feed_traits::protocol;
        using packet_header = typename market_feed_traits::packet_header;
        using sequence_number = typename market_feed_traits::sequence_number;
        using sequence_number_traits = typename sequence_number::traits;

        using data_error_handler = std::function<void(market_feed const &, std::span<char const>)>;
        using close_handler = std::function<void(market_feed const &)>;
        using sequence_gap_handler = std::function<void(market_feed const &, sequence_number, std::uint64_t)>;

        struct configuration
        {
            static auto constexpr default_receive_buffer_size = ((1 << 20) * 64);
            std::string socketAddress_;
            std::size_t receiveBufferSize_ = default_receive_buffer_size;
        };

        struct event_handlers
        {
            data_error_handler      dataErrorHandler_;
            sequence_gap_handler    sequenceGapHandler_;
            close_handler           closeHandler_;
        };

        market_feed
        (
            event_handlers
        );

        ~market_feed() = default;

        template <network::network_mode N>
        void connect
        (
            network::virtual_network_interface<N> & virtualNetworkInterface,
            std::function<void(std::span<char const>)> callback,
            market_feed_socket::configuration const & config
        )
        {
            socket_.connect(virtualNetworkInterface, callback, config);
        }
        
        void process_packet
        (
            std::span<char const>
        );

        void close();

    private:

        void on_close();

        void on_data_error
        (
            std::span<char const>
        );

        void on_sequence_gap
        (
            sequence_number
        );

        data_error_handler      dataErrorHandler_;
        sequence_gap_handler    sequenceGapHandler_;
        close_handler           closeHandler_;
        sequence_number         currentSequenceNumber_;
        market_feed_socket      socket_;
    };


    template <typename T>
    concept market_feed_concept = std::is_base_of_v<market_feed<typename T::target, typename T::market_feed_traits>, T>;

} // namespace lime::md


#include "./network/market_feed_interface.h"


//=============================================================================
template <typename target_type, lime::md::market_feed_traits_concept market_feed_traits>
lime::md::market_feed<target_type, market_feed_traits>::market_feed
(
    event_handlers eventHandlers
):
    dataErrorHandler_(eventHandlers.dataErrorHandler_),
    sequenceGapHandler_(eventHandlers.sequenceGapHandler_),
    closeHandler_(eventHandlers.closeHandler_),
    socket_({.closeHandler_ = [this](auto const &){this->on_close();}})
{
}


//=============================================================================
template <typename target_type, lime::md::market_feed_traits_concept market_feed_traits>
void lime::md::market_feed<target_type, market_feed_traits>::close
(
)
{
    socket_.close();
}


//=============================================================================
template <typename target_type, lime::md::market_feed_traits_concept market_feed_traits>
void lime::md::market_feed<target_type, market_feed_traits>::on_close
(
)
{
    if (auto closeHandler = std::exchange(closeHandler_, nullptr); closeHandler != nullptr)
        closeHandler(*this);
}


//=============================================================================
template <typename target_type, lime::md::market_feed_traits_concept market_feed_traits>
void lime::md::market_feed<target_type, market_feed_traits>::process_packet
(
    // a packet has arrived from the multicast stream
    std::span<char const> packetData
)
{
    static auto constexpr header_size = sizeof(packet_header);
    if (packetData.size() < header_size)
    {
        on_data_error(packetData);
        return; // insufficient data for the packet header
    }
    auto beg = packetData.data();
    auto const & packetHeader = *reinterpret_cast<packet_header const *>(beg);
    auto sequenceNumber = get_sequence_number(packetHeader);
    if (sequenceNumber != currentSequenceNumber_)
    {
        if (sequenceNumber < currentSequenceNumber_)
            return; // stale packet
        on_sequence_gap(sequenceNumber);
        currentSequenceNumber_ = sequenceNumber;
    }
    if (auto remaining = this->process(get_message_data(packetHeader)); not remaining.empty())
        on_data_error(remaining); // data remaining in packet after parse (alignment bytes perhaps?)
    currentSequenceNumber_ = get_next_sequence_number(currentSequenceNumber_, packetHeader); 
}


//=============================================================================
template <typename target_type, lime::md::market_feed_traits_concept market_feed_traits>
__attribute__ ((noinline))
void lime::md::market_feed<target_type, market_feed_traits>::on_data_error
(
    std::span<char const> data
)
{
    if (dataErrorHandler_)
        dataErrorHandler_(*this, data);
}


//=============================================================================
template <typename target_type, lime::md::market_feed_traits_concept market_feed_traits>
__attribute__ ((noinline))
void lime::md::market_feed<target_type, market_feed_traits>::on_sequence_gap
(
    sequence_number sequenceNumber
)
{
    if (sequenceGapHandler_)
        sequenceGapHandler_(*this, currentSequenceNumber_, sequenceNumber - currentSequenceNumber_);
}
