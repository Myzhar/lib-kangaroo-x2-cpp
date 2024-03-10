#ifndef STREAM_HPP
#define STREAM_HPP

#include "SerialPort.h"

#include <atomic>
#include <string>

#include "types.hpp"

namespace kx2
{
class Stream
{
private:
  /* data */

public:
  Stream();
  ~Stream();

  bool openSerialPort(
    std::string & port_name,
    const LibSerial::BaudRate & baudrate = LibSerial::BaudRate::BAUD_1152000);
  void close();

  ssize_t writeBuffer(const uint8_t * buffer, size_t lengthOfBuffer);
  bool readByte(uint8_t & data);

protected:

private:
  std::shared_ptr<LibSerial::SerialPort> _serial;
};

}  // namespace kx2

#endif  // STREAM_HPP
