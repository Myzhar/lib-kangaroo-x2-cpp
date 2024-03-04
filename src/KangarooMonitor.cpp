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

#include "KangarooMonitor.hpp"

#include "KangarooChannel.hpp"
#include "KangarooStatus.hpp"
#include "KangarooTimeout.hpp"

namespace kx2
{

KangarooMonitor::KangarooMonitor()
{
}

KangarooMonitor::KangarooMonitor(
  KangarooChannel * channel,
  uint32_t monitorCode)
{
  _channel = channel;
  _monitorCode = monitorCode;
}

KangarooStatus KangarooMonitor::status() const
{
  return valid() ? _channel->_monitoredGetResult :
         KangarooStatus::createInvalidStatus();
}

bool KangarooMonitor::valid() const
{
  return _channel && _monitorCode == _channel->_monitorCode;
}

KangarooMonitor KangarooMonitor::update()
{
  return update(_channel->commandTimeout());
}

KangarooMonitor KangarooMonitor::update(int32_t timeoutMS)
{
  KangarooTimeout timeout(timeoutMS);
  return update(timeout);
}

KangarooMonitor KangarooMonitor::update(const KangarooTimeout & timeout)
{
  while (valid() && !_channel->updateMonitoredResult(timeout, true)) {
  }
  return *this;
}

KangarooMonitor KangarooMonitor::wait(int32_t timeoutMS)
{
  KangarooTimeout timeout(timeoutMS);
  return wait(timeout);
}

KangarooMonitor KangarooMonitor::wait(const KangarooTimeout & timeout)
{
  while (!status().done()) {
    update(timeout);
  }
  return *this;
}

bool waitAll(size_t count, KangarooMonitor * monitors[], int32_t timeoutMS)
{
  KangarooTimeout timeout(timeoutMS);
  return waitAll(count, monitors, timeout);
}

bool waitAll(
  size_t count, KangarooMonitor * monitors[],
  const KangarooTimeout & timeout)
{
  for (size_t i = 0; i < count; i++) {
    if (!monitors[i]) {
      continue;
    }

    monitors[i]->wait(timeout);

    if (monitors[i]->status().timedOut()) {
      return false;
    }
  }

  return true;
}

int waitAny(size_t count, KangarooMonitor * monitors[], int32_t timeoutMS)
{
  KangarooTimeout timeout(timeoutMS);
  return waitAny(count, monitors, timeout);
}

int waitAny(
  size_t count, KangarooMonitor * monitors[],
  const KangarooTimeout & timeout)
{
  while (1) {
    if (timeout.expired()) {
      return -1;
    }

    for (size_t i = 0; i < count; i++) {
      if (!monitors[i]) {
        continue;
      }

      monitors[i]->update(timeout);
      if (monitors[i]->status().timedOut()) {
        return -1;
      }
      if (monitors[i]->status().done()) {
        return i;
      }
    }
  }
}

}  // namespace kx2
