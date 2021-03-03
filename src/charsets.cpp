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

#include <random>

#include "../include/charsetutils/charsets.hpp"





namespace charsetutils
{

const Charset alpha{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
};

const Charset num{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

const Charset symbol{
    '@', '%', '+', '\\', '/', '!', '#', '$', '%', '?', ':', ',',
    '(', ')', '{', '}', '[', ']', '-', '_', '.'
};


const Charset symbol_hard{'\'', '^', '~', '`'};

char GetChar(const Charset &charset)
{
    thread_local std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, charset.size() - 1);

    return charset[dist(engine)];
}

} // namespace passwd::charsets
