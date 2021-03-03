/*
    Copyright © 2021 Luiz Fernando F. G. Valle
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @author Luiz Fernando F. G. Valle (github.com/luizffgv)
 * @brief Implements the AtrGenerator class
 *
 * @version 1.0
 * @date 2021-02-28
 *
 * @copyright Copyright (c) 2021
 */
#ifndef CHARSETUTILS_INCLUDE_STRGENERATOR_HPP
#define CHARSETUTILS_INCLUDE_STRGENERATOR_HPP

// GCC only uses the value 202002L on version 11 onwards, so we gotta compare
//   against C++17 rather than C++20 since I'm using GCC 10.2. :(
#if __cplusplus <= 201703L
#error You need the C++20 standard or newer to use this header.
#else 

#include <cctype>
#include <concepts>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "charsets.hpp"





namespace charsetutils
{

/**
 * @brief Functor that generates a string from various Charsets.
 *
 * @tparam CharsetIndexRange Type used to store the number of Charsets.
 */
template <std::integral CharsetIndexRange = size_t>
class StrGenerator
{
public:

    /**
     * @brief Reports erros that arise due to an invalid fmt being used.
     */
    class BadFmt : public std::invalid_argument
    {
    public:
        /// Does Doxygen document this?
        using std::invalid_argument::invalid_argument;
    };





// RAII ---------------------------------------------------------------------- >

    /**
     * @brief Creates an StrGenerator with the provided data.
     *
     * The format string should be a comma-separated list of values, that 
     * define which charset will be used for each position.
     *
     * Each value should use either format: "I" (e.g. 5) or "IxC" (e.g. 1x3)
     * with "I" meaning "Index" and "C" meaning "Count".
     *
     * The string "3,1x8,0" means the first character will use the fourth
     * Charset (index [3]), the next eight will use the second ([1]) Charset
     * and the tenth character will use Charset [0].
     *
     * @param sets Charsets that will be used
     * @param fmt Format string that defines how the generator will behave
     */
    StrGenerator(std::vector<Charset> sets, std::string fmt);





// Member functions ---------------------------------------------------------- >

    /// Changes the generator's format string.
    void FmtChange(std::string fmt);





// Operators ----------------------------------------------------------------- >

    /// Generates a string using the format string.
    std::string operator()();





// Member variables ---------------------------------------------------------- >

    /// Usable charsets.
    std::vector<Charset> sets;

    /// Format string.
    std::string fmt;

private:
    /// Cached data extracted from the format string.
    std::vector<std::pair<CharsetIndexRange, std::size_t>> fmt_data;
};










// Template definitions ----------------------------------------------------- >>

template <std::integral CharsetIndexRange>
StrGenerator<CharsetIndexRange>::StrGenerator(std::vector<Charset> sets, std::string fmt)
    : sets{sets}
{
    FmtChange(std::move(fmt));
}

template <std::integral CharsetIndexRange>
void StrGenerator<CharsetIndexRange>::FmtChange(std::string fmt_new)
{
    decltype(fmt_data) fmt_data_new;
    std::stringstream fmt_stream{fmt_new};

    enum {before_first, before_char, before_second, done} state = before_first;
    while (state != done)
    {
        switch (state)
        {
        case before_first:
            if (auto peek{fmt_stream.peek()}; std::isdigit(peek))
            {
                fmt_data_new.emplace_back();
                fmt_stream >> fmt_data_new.back().first;
                state = before_char;
            }
            else if (peek == decltype(fmt_stream)::traits_type::eof())
                state = done;
            else
                throw BadFmt("(PLACEHOLDER STRING)");
            break;

        case before_char:
            if (auto ch{fmt_stream.get()}; ch == 'x')
                state = before_second;
            else
            {
                fmt_data_new.back().second = 1;
                if (ch == ',')
                    state = before_first;
                else if (ch == decltype(fmt_stream)::traits_type::eof())
                    state = done;
                else
                    throw BadFmt("(PLACEHOLDER STRING)");
            }
            break;

        case before_second:
            if (std::isdigit(fmt_stream.peek()))
            {
                fmt_stream >> fmt_data_new.back().second;

                if (fmt_stream.get() == ',')
                    state = before_first;
                else
                    state = done;
            }
            else
                throw BadFmt("(PLACEHOLDER STRING)");
            break;
        }
    }

    fmt = std::move(fmt_new);
    fmt_data = std::move(fmt_data_new);
}

template <std::integral CharsetIndexRange>
std::string StrGenerator<CharsetIndexRange>::operator()()
{
    std::string ret;
    ret.reserve(fmt_data.size());

    for (auto &[charset, repeat] : fmt_data)
        for (size_t i = 0; i < repeat; ++i)
            ret += GetChar(sets[charset]);

    return ret;
}

} // namespace charsetutils

#endif // #else of #if __cplusplus < 201703L

#endif // #ifndef CHARSETUTILS_INCLUDE_STRGENERATOR_HPP
