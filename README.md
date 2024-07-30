# Shaking the Can

## Setup

### Raspberry Pi OS

> I Followed this tutorial: https://www.lexaloffle.com/bbs/?tid=140366

1. Prepare the SD-Card, I used [Raspberry Pi Imager](https://www.raspberrypi.com/software/)

   - Raspberry Pi OS Lite 64-bit (2024-03-15, bookworm, kernel 6.6)

2. Connect to the Raspberry Pi

   - First I had WiFi issues, so I run `sudo raspi-config` -> "1 System Options" -> "S1 Wireless LAN" to re-setup

   - I hate passwords, so I run `ssh-copy-id pico8@192.168.68.68` (remote user @ remote address) and added the following to `~/.ssh/config`

     ```
     Host pico-8
       HostName 192.168.68.68
       User root
     ```

   - connect like `ssh pico-8`

3. Setup Raspberry Pi OS

   ```
   sudo apt update
   sudo apt upgrade
   sudo apt install libsdl2-dev pulseaudio git

   sudo raspi-config
   # - "5 Localisation Options" -> "L4 WLAN Country" -> ...
   # - "1 System Options" -> "S1 Wireless LAN" -> ...
   # - "1 System Options" -> "S5 Boot / Auto Login" -> "B2 Console Autologin"
   ```

4. Download & extract PICO-8

   > Find download URL here: https://www.lexaloffle.com/games.php?page=updates

   ```
   cd ~/
   wget https://www.lexaloffle.com/.../pico-8_raspi.zip
   unzip pico-8_raspi.zip
   ```

5. Clone repository

   ```
   cd ~/
   git clone https://github.com/webgyver/shaking-the-can.git
   ```

6. Add `~/shaking-the-can/start.sh` at the end of the `~/.bashrc`

## TODO

- [ ] Find a better place to run the start script?
- [ ] Fill README
