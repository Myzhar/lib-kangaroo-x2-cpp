#ifndef KANGAROO_REPLY_READER_HPP
#define KANGAROO_REPLY_READER_HPP

#include "types.hpp"

namespace kx2
{
class KangarooReplyReader
{
public:
  KangarooReplyReader(const uint8_t * data, size_t length);

public:
  bool canRead() const;
  bool tryRead(uint8_t * value);
  uint8_t read();
  int32_t readBitPackedNumber();

private:
  const uint8_t * _data;
  const uint8_t * _dataEnd;
};
}  // namespace kx2

#endif  // KANGAROO_REPLY_READER_HPP
