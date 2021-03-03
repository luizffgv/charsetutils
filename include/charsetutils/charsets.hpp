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
 * @brief Provides utilities related to sets of characters.
 * @version 1.0
 * @date 2021-03-03
 *
 * @copyright Copyright (c) 2021
 */

#ifndef CHARSETUTILS_CHARSETS_HPP
#define CHARSETUTILS_CHARSETS_HPP

#include <vector>





namespace charsetutils
{

/// Represents a set of characters.
using Charset = std::vector<char>;


/**
 * @brief Gets a random character from a Charset.
 *
 * @param charset Chosen Charset
 *
 * @return Random character
 */
char GetChar(const Charset &charset);

/// Charset representing the English alphabet.
extern const Charset alpha;
/// Charset representing all decimal digits.
extern const Charset num;
/// Charset representing many symbols.
extern const Charset symbol;
/// Charset representing symbols that might be hard to type on some keyboards.
extern const Charset symbol_hard;

} // namespace charsetutils

#endif // #ifndef CHARSETUTILS_CHARSETS_HPP
