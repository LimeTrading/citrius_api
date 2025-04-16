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


#include <include/endian.h>
#include <include/string_array.h>
#include <include/type_rich.h>

#include <concepts>
#include <utility>


namespace lime::md
{

    template <std::integral T> 
    class symbol_mapping : public type_rich<struct symbol_mapping_tag, T>
    {
    public:

        constexpr symbol_mapping() = default;
        explicit constexpr symbol_mapping(T value):type_rich<struct symbol_mapping_tag, T>(value){}
        constexpr symbol_mapping(symbol_mapping const &) = default;
        constexpr symbol_mapping & operator = (symbol_mapping const &) = default;
        constexpr symbol_mapping(symbol_mapping &&) = default;
        constexpr symbol_mapping & operator = (symbol_mapping &&) = default;
        ~symbol_mapping() = default;

        symbol_mapping
        (
            string_array_concept auto const & stringArray 
        ):
            type_rich<struct symbol_mapping_tag, T>(std::hash<std::decay_t<decltype(stringArray)>>()(stringArray))
        {
        } 

        symbol_mapping & operator =
        (
            string_array_concept auto const & stringArray 
        )
        {
            type_rich<struct symbol_mapping_tag, T>::operator = ((T)std::hash<std::decay_t<decltype(stringArray)>>()(stringArray));
            return *this;
        }        
    };

    template <typename T>
    concept symbol_mapping_concept = std::is_same_v<T, symbol_mapping<typename T::value_type>>;


    //==============================================================================
    [[__maybe_unused__]]
    static inline constexpr auto byte_swap
    (
        symbol_mapping_concept auto value
    ) -> std::decay_t<decltype(value)>
    {
        using lime::byte_swap;
        return std::decay_t<decltype(value)>(byte_swap(value.get()));
    }

} // namespace lime::md


//=============================================================================
namespace std
{

    template <lime::md::symbol_mapping_concept T>
    struct hash<T>
    {
        auto operator()(T source)const{return source.get();}
    };

} // namespace std
