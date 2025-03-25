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

#include <library/citrius.h>

#include <atomic>
#include <iostream>
#include <thread>

using namespace lime;


//=============================================================================
class my_message_receiver :
    public citrius_market_feed<my_message_receiver>
{
public:


    my_message_receiver
    (
    ):
        citrius_market_feed<my_message_receiver>(
        {
            .dataErrorHandler_ = [](auto const &, auto data){std::cout << "data error encountered. bytes = " << data.size() << "          \n";},
            .sequenceGapHandler_ = [](auto const &, auto sequenceNumber, auto gapSize){std::cout << "gap encountered [" << sequenceNumber.get() << " -> " << (sequenceNumber.get() + gapSize - 1) << "]         \n";},
            .closeHandler_ = [](auto const &){std::cout << "stream has closed           \n";}
        })
    {
    }

    ~my_message_receiver() = default;

    void operator()(citrius_book_clear_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got book_clear_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_end_multicast_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got end_multicast_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_heart_beat_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got heart_beat_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_end_of_day_summary_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got end_of_day_summary_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_imbalance_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got imbalance_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_option_description_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got option_description_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_order_add_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got order_add_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_order_cancel_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got order_cancel_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_order_delete_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got order_delete_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_order_executed_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got order_executed_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_order_modify_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got order_modify_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_order_replace_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got order_replace_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_price_band_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got price_band_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_sequence_gap_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got sequence_gap_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_short_sale_restriction_status_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got short_sale_restriction_status_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_start_multicast_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got start_multicast_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_start_of_day_summary_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got start_of_day_summary_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_symbol_description_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got symbol_description_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_top_of_book_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got top_of_book_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_trade_cancel_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got trade_cancel_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_trade_message const & message){std::cout << "Trade: " << to_string(message.shares_.get()) << " @ " << to_string(message.price_.get()) << "\n"; update_message_count();}
    void operator()(citrius_trading_session_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got trading_session_message\n"; return true;}(); update_message_count();}
    void operator()(citrius_trading_status_message const &){[[__maybe_unused__]] static bool once = [](){std::cout << "Got trading_status_message\n"; return true;}(); update_message_count();}

private:

    void update_message_count()
    {
        if ((++messageCount_ & 0xfff) == 0)
            std::cout << "Received " << messageCount_ << " messages\r" << std::flush;
    }

    std::atomic<int> messageCount_{0};
};


//=============================================================================
int main 
(
    int, 
    char **
)
{
    //=========================================================================
    // 1: create an efvi based multicast receiver
    lime::md::efvi_market_feed_interface marketFeedInterface;

    //=========================================================================
    // 2: configure the desired number of polling threads and the desired number of packet processing threads.
    // There's no reason one thread could not do both, but it wouldn't lead to the lowest latency to do so.
    // create polling thread(s)
    static auto constexpr num_polling_threads = 1;
    std::vector<std::jthread> pollingThreads(num_polling_threads);
    for (auto & thread : pollingThreads)
        thread = std::move(std::jthread([&](auto stopToken){while (not stopToken.stop_requested()) marketFeedInterface.poll();}));
    // create packet processing thread(s)
    static auto constexpr num_message_processing_threads = 4;
    std::vector<std::jthread> processingThreads(num_message_processing_threads);
    for (auto & thread : processingThreads)
        thread = std::move(std::jthread([&](auto stopToken){while (not stopToken.stop_requested()) marketFeedInterface.receive();}));
    
    //=========================================================================
    // 3: join the desired citrius market feeds
    std::vector<std::unique_ptr<my_message_receiver>> marketFeeds;
    marketFeeds.push_back(std::move(marketFeedInterface.join_multicast<my_message_receiver>("233.87.224.35:25000")));
    marketFeeds.push_back(std::move(marketFeedInterface.join_multicast<my_message_receiver>("233.87.224.35:25001")));

    //=========================================================================
    // 4: let the polling and packet processing threads handle th joined multicasts for ten seconds prior to terminating
    auto end = std::chrono::system_clock::now() + std::chrono::seconds(10);
    while (std::chrono::system_clock::now() < end)
        ;

    //=========================================================================
    // 5: explicitly release the connection (leave the multicast) - we could just let the market feeds close by leaving scope as well
    for (auto & marketFeed : marketFeeds)
        marketFeed->close();

    //=========================================================================
    // 6: shutdown the polling threads
    for (auto & thread : pollingThreads)
    {
        thread.request_stop();
        thread.join();
    }

    // 7: shutdown the packet processing threads
    for (auto & thread : processingThreads)
    {
        thread.request_stop();
        thread.join();
    }

    return 0;
}
