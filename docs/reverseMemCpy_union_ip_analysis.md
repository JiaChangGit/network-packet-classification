## Origin:

### rule:
@194.186.113.175/32	86.247.120.60/32	0 : 65535	31000 : 31000	0x06/0xFF	0x0000/0x0200
@194.186.113.234/32	85.92.108.225/32	0 : 65535	5555 : 5555	0x06/0xFF	0x0000/0x0200

### packet:
3266998700	1458994818	0	1521	6	268439552	214
1431935006	3770895350	0	65535	6	0	739

---

### rule copy with arr[0~3] and eightBitsGroup_ip_merge once: Correct
Priority: 1
Source IP: 3266998703/32    11000010 10111010 01110001 10101111 => 194.186.113.175
Destination IP: 1459058748/32    01010110 11110111 01111000 00111100 => 86.247.120.60
Source Port: 0 : 65535
Destination Port: 31000 : 31000
Protocol: 0x6 / 0xff

Priority: 2
Source IP: 3266998762/32    11000010 10111010 01110001 11101010 => 194.186.113.234
Destination IP: 1432120545/32    01010101 01011100 01101100 11100001 => 85.92.108.225
Source Port: 0 : 65535
Destination Port: 5555 : 5555
Protocol: 0x6 / 0xff


Priority: 1
Source IP: 194.186.113.175/32
Destination IP: 86.247.120.60/32
Source Port: 0 : 65535
Destination Port: 31000 : 31000
Protocol: 0x6 / 0xff

Priority: 2
Source IP: 194.186.113.234/32
Destination IP: 85.92.108.225/32
Source Port: 0 : 65535
Destination Port: 5555 : 5555
Protocol: 0x6 / 0xff


### packet reverse copy number and eightBitsGroup_ip_merge once: Correct
Source IP: 3266998700        11000010 10111010 01110001 10101100 => 194.186.113.172
Destination IP: 1458994818        01010110 11110110 01111110 10000010 => 86.246.126.130
Source Port: 0
Destination Port: 1521
Protocol: 0x6

Source IP: 1431935006        01010101 01011001 10011000 00011110 => 85.89.152.30
Destination IP: 3770895350        11100000 11000011 01001011 11110110 => 224.195.75.246
Source Port: 0
Destination Port: 65535
Protocol: 0x6


Source IP: 194.186.113.172
Destination IP: 86.246.126.130
Source Port: 0
Destination Port: 1521
Protocol: 0x6

Source IP: 85.89.152.30
Destination IP: 224.195.75.246
Source Port: 0
Destination Port: 65535
Protocol: 0x6

---

### rule copy with arr[0~3] and eightBitsGroup_ip_merge twice: Error 8bits-a-group reverse
Priority: 1
Source IP: 2943466178/32    10101111 01110001 10111010 11000010 => 175.113.186.194
Destination IP: 1014560598/32    00111100 01111000 11110111 01010110 => 60.120.247.86
Source Port: 0 : 65535
Destination Port: 31000 : 31000
Protocol: 0x6 / 0xff

Priority: 2
Source IP: 3933321922/32    11101010 01110001 10111010 11000010 => 234.113.186.194
Destination IP: 3781975125/32    01110000 10110110 001011100 01010101 => 112.182.92.85
Source Port: 0 : 65535
Destination Port: 5555 : 5555
Protocol: 0x6 / 0xff


### packet reverse copy number and eightBitsGroup_ip_merge twice: Error 8bits-a-group reverse
Source IP: 2893134530        10101100 01110001 10111010 11000010 => 172.113.186.194
Destination IP: 2189358678        10000010 01111110 11110110 01010110 => 130.126.246.86
Source Port: 0
Destination Port: 1521
Protocol: 0x6

Source IP: 513300821        00011110 10011000 01011001 01010101 => 30.152.89.85
Destination IP: 4132160480        11110110 01001011 11000011 11100000 => 246.75.195.224
Source Port: 0
Destination Port: 65535
Protocol: 0x6

---

### rule copy with arr[0~3] and eightBitsGroup_ip_merge three times: Correct
Priority: 1
Source IP: 3266998703/32
Destination IP: 1459058748/32
Source Port: 0 : 65535
Destination Port: 31000 : 31000
Protocol: 0x6 / 0xff

Priority: 2
Source IP: 3266998762/32
Destination IP: 1432120545/32
Source Port: 0 : 65535
Destination Port: 5555 : 5555
Protocol: 0x6 / 0xff


### packet reverse copy number and eightBitsGroup_ip_merge three times: Correct
Source IP: 3266998700
Destination IP: 1458994818
Source Port: 0
Destination Port: 1521
Protocol: 0x6

Source IP: 1431935006
Destination IP: 3770895350
Source Port: 0
Destination Port: 65535
Protocol: 0x6
