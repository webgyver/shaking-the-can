killall -9 pico8_dyn
P1="84:0D:8E:25:97:2E" # red
P2="84:0D:8E:1D:E1:1E" # blue
# echo -e "remove $P1 \n remove $P2 \n pair $P1 \n pair $P2 \n connect $P1 \n connect $P2 \n quit \n" | bluetoothctl
# sleep 2
sleep 1
echo -e "remove $P1 \n pair $P1 \n connect $P1 \n quit \n" | bluetoothctl
sleep 1
echo -e "remove $P2 \n pair $P2 \n connect $P2 \n quit \n" | bluetoothctl
sleep 1
~/pico-8/pico8_dyn -run ./shaking-the-can.p8 &
