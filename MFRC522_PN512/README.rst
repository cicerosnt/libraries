MFRC522_PN512
=======
Arduino library for MFRC522 , **PN512 NFC Reader module.** and other RFID RC522 based modules.

Original Readme:
https://github.com/miguelbalboa/rfid/blob/master/README.rst

Read and write different types of Radio-Frequency IDentification (RFID) cards
on your Arduino using a PN512 based reader connected via the Serial Peripheral
Interface (SPI) interface.

.. _changes made to the original library:
Changes made to the original library
----------
This library is a modified version of  `Miguelbalboa's RFID library <https://github.com/miguelbalboa/rfid>`_.

It is compatible with the PN512 NFC Module (an Arduino base module available from `Digital Logic Ltd <https://www.d-logic.com/>`_.) as well as other MFRC522 modules for which this library was previously utilized.

**The main changes that were made:**

* Registers that initialize the chip were changed. 
* Added firmware version for PN512 chip. 
* Added examples for the PN512 reader.


All the changes that were made are in the document `PN512_NFC_Reader_Based_on_Arduino <https://github.com/nfc-rfid-reader-sdk/MFRC522_PN512/blob/master/doc/PN512_NFC_Reader_Based_on_Arduino.pdf>`_ in the doc folder.

.. _development:
Development
-----------
**Maintenance status: periodically**

.. _protocol:
Protocols
---------

1. The microcontroller  and the reader use SPI for communication.

* The protocol is described in the `NXP PN512 <https://www.nxp.com/docs/en/data-sheet/PN512.pdf>`_ datasheet.

* Pin Layout is described in the official document provided by the Digital Logic Ltd. Details can be found in the  `PN512 NFC Reader <https://github.com/nfc-rfid-reader-sdk/MFRC522_PN512/blob/master/doc/PN512_NFC_Reader_Based_on_Arduino.pdf>`_ document in the **doc** folder.

2. The reader and the tags communicate using a 13.56 MHz electromagnetic field.

* The protocol is defined in ISO/IEC 14443-3:2011 Part 3 Type A.

  * Details are found in chapter 6 *"Type A – Initialization and anticollision"*.
  
  * See http://wg8.de/wg8n1496_17n3613_Ballot_FCD14443-3.pdf for a free version
    of the final draft (which might be outdated in some areas).
    
  * The reader does not support ISO/IEC 14443-3 Type B.

.. _security:
Security
--------
* The **UID** of a card **can not be used** as an unique identification for security related projects. Some Chinese cards allow you to change the UID which means you can easily clone a card. For projects like *access control*, *door opener* or *payment systems* you **must implement** an **additional security mechanism** like a password or normal key.

* This library only supports crypto1-encrypted communication. Crypto1 has been known as `broken`_ for a few years, so it does NOT offer ANY security, it is virtually unencrypted communication. **Do not use it for any security related applications!**

* This library does not offer 3DES or AES authentication used by cards like the Mifare DESFire, it may be possible to be implemented because the datasheet says there is support. We hope for pull requests :).

.. _support:
Support
--------
For more details, visit us at:
https://www.d-logic.com/nfc-rfid-reader-sdk/general-support/

.. _license:
License
-------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to https://unlicense.org/


.. _dependency:
Dependency
----------

* **Arduino.h**

  * From: Arduino IDE / target specific
  * License: (target: Arduino) GNU Lesser General Public License 2.1
  
* **SPI.h**

  * From: Arduino IDE / target specific
  * License: (target: Arduino) GNU Lesser General Public License 2.1
  
* **stdint.h**

  * From: Arduino IDE / Compiler and target specific
  * License: different
