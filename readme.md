# UCS8904B

UCS8904B chip is a LED drive cascade chip with 16bit colors, RGBW output.

I'm trying to gather information about the chip to be able to send data from a microcontroller.  
manufacturer: http://www.szucs.cn/  
I've write to the manufacturer to ask the complete datasheet, no answer there.

## Pinout
```
       +---------+
OUTR --| o       |-- OUTW
OUTG --|         |-- VDD
OUTB --|         |-- DIN
 GND --|         |-- DOUT
       +---------+
```

## Data Packet  
|    PIN   |   R   |   G   |   B   |   W   |
|:--------:|:-----:|:-----:|:-----:|:-----:|
| Data bit | 16bit | 16bit | 16bit | 16bit |

## Pulse width timing. 
The recommand value for controller  
reference: https://www.gree-leds.com/ic-protocol/ucs8904b-ic-protocol-and-datasheet.html
|  Name  |        Description        | Typical Value | Unit |
|:------:|:-------------------------:|:-------------:|:----:|
|   T0H  |   0 code,high level time  |      0.4      |  μs  |
|   T1H  |   1 code,high level time  |      0.85     |  μs  |
|   T0L  |   0 code,low level time   |     ≥0.85     |  μs  |
|   T1L  |   1 code,low level time   |      ≥0.4     |  μs  |
| Treset | Reset code,low level time |       48      |  μs  |


## Datasheets

English
https://github.com/Differentunic/UCS8904-Datasheet/blob/main/UCS8904B.pdf  
Chinese
http://www.led-stuebchen.de/download/UCS8904B.pdf  
Greeled
https://www.gree-leds.com/web/userfiles/download/UCS8904BICEnglishdatasheet.pdf  
https://www.gree-leds.com/ic-protocol/ucs8904b-ic-protocol-and-datasheet.html  


## Relevant Discussion

https://forum.pjrc.com/index.php?threads/help-using-ucs8904b.75567/  
https://giters.com/Makuna/NeoPixelBus/issues/516  

