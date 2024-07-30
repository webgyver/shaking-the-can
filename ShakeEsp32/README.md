Hardware Used

https://www.amazon.de/dp/B07HGV3QVX
https://www.amazon.de/dp/B07XRK5FHP
and two 18650 batteries as well as some wires and small screws (i had that lying around)

Print parts in PLA or ABS (Petg is kind of sticky and the threads do not work correctly) and insert two m3 thread inserts to Can_top.stl. Screw the electronics_holder to the top with 3 M3 Screws.

1.) Flash IMU_Zero.ino sketch to the device, put the device upright (as in the can) and let it do its magic. Write down the values at the end.

2.) Take one of the sketches and change the values line 91 to 97 to the values you got from the calibration and flash the sketch to the esp32 (rename not needed files temporarily).
Change the name and "Manufacturer" in line 21 if you want.

