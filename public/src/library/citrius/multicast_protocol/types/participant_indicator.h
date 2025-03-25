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

    enum class participant_indicator : std::uint8_t
    {
        undefined                                   = 0, // reserved
        unknown                                     = 1,
        nyse_american                               = 2,
        nyse_national                               = 3,
        nyse_chicago                                = 4,
        nyse                                        = 5,
        nyse_arca                                   = 6,
        nasdaq_gemx                                 = 7,
        nasdaq_mrx                                  = 9,
        nasdaq_omx_psx                              = 10,
        nasdaq_omx_bx                               = 11,
        nasdaq                                      = 12,
        nasdaq_options_market                       = 13,
        nasdaq_bx_options                           = 14,
        finra                                       = 16,
        international_securities_exchange           = 17,
        long_term_stock_exchange                    = 18,
        members_exchange                            = 19,
        investors_exchange                          = 20,
        boston_options_exchange                     = 21,
        miami_international_securities_exchange     = 22,
        miax_pearl                                  = 23,
        miax_emerald                                = 24,
        otc                                         = 25,
        cboe                                        = 26,            
        cboe_edga                                   = 27,
        cboe_edgx                                   = 28,
        cboe_byx                                    = 29,
        cboe_bzx                                    = 30,            
        cboe_options_exchange                       = 31,
        cboe_edgx_options                           = 32,
        cboe_c2_options_exchange                    = 33,
        cboe_bzx_options_exchange                   = 34,
        consolidated_quotation_system               = 35,
        options_price_reporting_authority           = 36,
        market_independent_sip                      = 37,    
        miax_sapphire                               = 38   
    };

} // namespace lime::md::citrius


namespace lime
{
    using citrius_participant_indicator = md::citrius::participant_indicator;
} // namespace lime