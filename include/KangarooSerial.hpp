#ifndef KANGAROO_SERIAL_HPP
#define KANGAROO_SERIAL_HPP

#include "KangarooReplyReceiver.hpp"
#include "Stream.hpp"
#include "types.hpp"

namespace kx2
{

/*!
\class KangarooSerial
\brief Create a KangarooSerial for the serial port you are using, and then
attach a KangarooChannel for each channel you want to communicate with.
*/
class KangarooSerial
{
  friend class KangarooChannel;

public:
  /*!
  Constructs a KangarooSerial object.
  \param port The serial port the motion controller is on.
  */
  explicit KangarooSerial(Stream & port);

public:
  /*!
  Gets the serial port being used.
  \return The serial port.
  */
  inline Stream & port() {return _port;}

private:
  bool tryReceivePacket();

private:
  KangarooSerial(KangarooSerial & serial);  // no copy
  void operator=(KangarooSerial & serial);

private:
  KangarooReplyReceiver _receiver;
  Stream & _port;
};

}  // namespace kx2

#endif  // KANGAROO_SERIAL_HPP
