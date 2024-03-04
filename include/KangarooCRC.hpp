#ifndef KANGAROO_CRC_HPP
#define KANGAROO_CRC_HPP

#include "types.hpp"

namespace kx2
{
class KangarooCRC
{
public:
  void begin();
  void write(uint8_t data);
  void write(const uint8_t * data, size_t lengthOfData);
  void end();

public:
  inline uint16_t value() const {return _crc;}
  void value(uint16_t crc) {_crc = crc;}

  static uint16_t value(const uint8_t * data, size_t lengthOfData);

private:
  uint16_t _crc = 0;
};

}  // namespace kx2

#endif  // KANGAROO_CRC_HPP
