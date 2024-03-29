/*
Arduino Library for Kangaroo
Copyright (c) 2013 Dimension Engineering LLC
http://www.dimensionengineering.com/kangaroo

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE
USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "KangarooReplyReceiver.hpp"

#include <string.h>

#include "KangarooCRC.hpp"

namespace kx2
{

KangarooReplyReceiver::KangarooReplyReceiver()
{
  memset(_data, 0, sizeof(_data));
  reset();
}

void KangarooReplyReceiver::read_byte(uint8_t data)
{
  if (data >= 128 || _ready) {
    reset();
  }
  if (_length < KANGAROO_COMMAND_MAX_BUFFER_LENGTH) {
    _data[_length++] = data;
  }

  if (_length >= 5 && _data[0] >= 128) {
    if (_length - 5 == _data[2]) {
      if (KangarooCRC::value(_data, _length) == KANGAROO_CRC_GOOD_VALUE) {
        _ready = true;
      }
    }
  }
}

void KangarooReplyReceiver::reset()
{
  _length = 0;
  _ready = false;
}

}  // namespace kx2
