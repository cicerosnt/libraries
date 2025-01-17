/*
 * MIT License
 * Copyright (c) 2018 Brian T. Park
 */

#include <Print.h>
#include "TimeZone.h"

namespace ace_time {

void TimeZone::printTo(Print& printer, bool followLink) const {
  switch (mType) {
    case kTypeError:
    case kTypeReserved:
      printer.print("<Error>");
      break;

    case kTypeManual:
      if (isUtc()) {
        printer.print("UTC");
      } else {
        TimeOffset::forMinutes(mStdOffsetMinutes).printTo(printer);
        TimeOffset::forMinutes(mDstOffsetMinutes).printTo(printer);
      }
      break;

    default:
      getBoundZoneProcessor()->printNameTo(printer, followLink);
      break;
  }
}

void TimeZone::printShortTo(Print& printer, bool followLink) const {
  switch (mType) {
    case kTypeError:
    case kTypeReserved:
      printer.print("<Error>");
      break;

    case kTypeManual:
      if (isUtc()) {
        printer.print("UTC");
      } else {
        auto utcOffset = TimeOffset::forMinutes(
            mStdOffsetMinutes + mDstOffsetMinutes);
        utcOffset.printTo(printer);
        printer.print('(');
        printer.print((mDstOffsetMinutes != 0) ? "D" : "S");
        printer.print(')');
      }
      break;

    default:
      getBoundZoneProcessor()->printShortNameTo(printer, followLink);
      break;
  }
}

}
