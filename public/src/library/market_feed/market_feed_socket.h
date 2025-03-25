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

#include <concepts>
#include <cstdint>
#include <functional>
#include <span>
#include <memory>
#include <string>


namespace lime::network
{

    enum class network_mode : std::uint32_t;

    template <network_mode>
    class virtual_network_interface;

    class socket_base;
}


namespace lime::md
{

    //=========================================================================
    class market_feed_socket :
        virtual non_copyable,
        virtual non_movable
    {
    public:

        struct configuration
        {
            static auto constexpr default_receive_buffer_size = ((1 << 20) * 64);
            std::string socketAddress_;
            std::size_t receiveBufferSize_ = default_receive_buffer_size;
        };

        using close_handler = std::function<void(market_feed_socket const &)>;

        struct event_handlers
        {
            close_handler closeHandler_;
        };

        market_feed_socket
        (
            event_handlers 
        );

        ~market_feed_socket();

        void close();

        template <network::network_mode N>
        void connect
        (
            network::virtual_network_interface<N> &,
            std::function<void(std::span<char const>)>,
            configuration const &
        );

        std::unique_ptr<network::socket_base>   socketBase_;

        close_handler                           closeHandler_;
    };

} // namespace lime::md
