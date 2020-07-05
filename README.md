# Aalto MIDI controller Arduino Mega 2560
This is a code I have used to create my own Madronalab's Aalto VST (https://madronalabs.com/products/aalto) MIDI controller.

There are several way to make Arduino send MIDI over USB:
- by flashing Arduino USB Controller
  PROs:
  - you don't have to install any software on your PC
  CONs:
  - while prototyping you have to flash the firmware to the original version to upload the code, flash it back in "midi mode", test, flash it back to original firmware.

- by using Arduino as it is, sending normal Serial Data but using an additional software in your Computer
  PROs:
  - prototyping is extremely easy, you don't have to flash anything, it just works
  CONs:
  - you have to use Hairless MIDI Serial (if you want to consider that a CON): https://projectgus.github.io/hairless-midiserial/

I DON'T recommend to use the first approach UNLESS you're 100% sure your project is completed and you won't touch your code anymore.

If you want to see more on this project, follow this Instractable at https://www.instructables.com/id/Arduino-MIDI-Controller-for-Aalto/

Me on Instagram with videos of the project: weirdest.worry
Me on Spotify: https://open.spotify.com/track/725nTtDs581feNjHHhDJ92?si=25YK9WobRiCmTu0RHJR6Ug
