# msi-keyboard
Allow the user to change the keyboard backlight using hidapi

This project is based on bparker06's work but aim to fix the animated modes.

## Require
* hidapi.h available on Arch AUR or on [Github](https://github.com/signal11/hidapi)

## Usage
```
msi-keyboard [-m normal] [-r (left|middle|right)] [-c (none|red|orange|yellow|green|sky|blue|purple|white)] [-i (high|medium|low|light)] [--full]
```
* `-m`: keyboard mode
* `-r`: keyboard region on which the color is going to be applied (see also --full)
* `-c`: backlight's new color
* `-i`: backlight's intensity
* `--full`: apply the change on the whole keyboard. `-r` will be ignored

## Run as non-root user
If you want to run the software as a non-root user, you can add the udev rules file to your `/etc/udev/rules.d/` directory.

## Notes
The audio mode does not work on linux at the moment.

## Unknown packet
`01 02 22 14 00 00 00 00`: Usually sent when switching to audio mode
