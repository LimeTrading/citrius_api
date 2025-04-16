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

#include <include/non_copyable.h>
#include <include/non_movable.h>
#include <library/network.h>

#include <cstdint>
#include <memory>
#include <string>
#include <functional>
#include <span>
#include <chrono>
#include <map>
#include <mutex>



namespace lime::network
{

    enum class network_mode : std::uint32_t;

    template <network_mode>
    class virtual_network_interface;

} // lime::network


namespace lime::md
{

    //=========================================================================
    template <network::network_mode N>
    class market_feed_interface final :
        virtual non_copyable,
        virtual non_movable
    {
    public:

        static auto constexpr default_max_socket_capacity = 256ll;
        static auto constexpr default_max_buffer_heap_capacity = (1ull<< 16);

        struct configuration
        {
            std::string     networkInterfaceName_;
            std::uint64_t   maxSocketCapacity_{default_max_socket_capacity};
            std::uint64_t   maxBufferHeapCapacity_{default_max_buffer_heap_capacity};
        };

        market_feed_interface();

        market_feed_interface
        (
            configuration const &
        );

        ~market_feed_interface();

        void poll();

        void receive();

        bool is_valid() const;

        template <market_feed_concept recipient, typename ... Ts>
        std::unique_ptr<recipient> join_multicast
        (
            std::string,
            Ts && ...
        );

    private:

        void connect
        (
            market_feed_socket *,
            std::string
        );

        std::unique_ptr<network::virtual_network_interface<N>>  virtualNetworkInterface_;

    }; // class market_feed_interface<>


    using efvi_market_feed_interface = market_feed_interface<network::network_mode::kernel_bypass>;
    using kernel_market_feed_interface = market_feed_interface<network::network_mode::kernel>;

} // namespace lime::md


//=============================================================================
template <lime::network::network_mode N>
template <lime::md::market_feed_concept recipient, typename ... Ts>
auto lime::md::market_feed_interface<N>::join_multicast
(
    std::string socketAddress,
    Ts && ... args
) -> std::unique_ptr<recipient>
{
    auto marketFeed = std::make_unique<recipient>(std::forward<Ts>(args) ...);
    marketFeed->connect(*virtualNetworkInterface_, {.socketAddress_ = socketAddress, .receiveBufferSize_ = ((1 << 20) * 64)});
    return marketFeed;
}
