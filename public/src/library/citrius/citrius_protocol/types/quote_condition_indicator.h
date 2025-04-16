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


namespace lime::md::citrius
{

    enum class quote_condition_indicator : std::uint8_t
    {
        nbbo_qualified_flag                                 = 0x80,

        undefined                                           = 0,
        not_applicable                                      = 1,
        news_dissemination                                  = 2,
        trading_range_indication                            = 3,
        order_imbalance                                     = 4,
        luld_trading_pause                                  = 5,
        news_pending                                        = 6,
        resume                                              = 7,
        equipment_changeover                                = 8,
        sub_penny_trading                                   = 9,
        no_open_no_resume                                   = 10,
        luld_price_band                                     = 11,
        mwcb_1_breach                                       = nbbo_qualified_flag | 12,
        mwcb_2_breach                                       = nbbo_qualified_flag | 13,
        mwcb_3_breach                                       = nbbo_qualified_flag | 14,
        republished_luld_price_band                         = 15,
        slow_offer                                          = nbbo_qualified_flag | 16,
        slow_bid                                            = nbbo_qualified_flag | 17,
        closing                                             = 18,
        slow_offer_lrp_or_gap                               = nbbo_qualified_flag | 19,
        slow_bid_lrp_or_gap                                 = nbbo_qualified_flag| 20,
        slow_bid_and_offer                                  = nbbo_qualified_flag | 21,
        closed_market_maker                                 = 22,
        non_firm                                            = 23,
        opening_quote                                       = nbbo_qualified_flag | 24,
        regular                                             = nbbo_qualified_flag | 25,
        slow_bid_and_offer_lrp_or_gap                       = 26,
        slow_bid_and_offer_list                             = nbbo_qualified_flag | 27,
        intraday_auction                                    = 28,
        manual_ask_automated_bid                            = nbbo_qualified_flag | 29,
        manual_bid_automated_ask                            = nbbo_qualified_flag | 30,
        fast_trading                                        = 31,
        manual_bid_and_ask                                  = nbbo_qualified_flag | 32,
        open_quote_automated                                = nbbo_qualified_flag | 33,
        regular_two_sided_open_quote_automated              = nbbo_qualified_flag | 34,
        manual_bid_and_ask_non_firm                         = 35,
        order_influx                                        = 36,
        automated_bid_no_offer_or_automated_offer_no_bid    = nbbo_qualified_flag | 37,
        additional_information_requested                    = 38,
        regulatory_concern                                  = 39,
        merge_effective                                     = 40,
        etf_component_prices_not_available                  = 41,
        corporate_action                                    = 42,
        new_security_offering                               = 43,
        interday_indicative_value_not_available             = 44     
    };

} // namespace lime::md::citrius


namespace lime
{
    using citrius_quote_condition_indicator = md::citrius::quote_condition_indicator;
} // namespace lime