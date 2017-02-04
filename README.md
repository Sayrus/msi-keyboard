# msi-keyboard
Allow the user to change the keyboard backlight using hidapi

This project is based on bparker06's work but aim to fix the animated modes.

## Require
* hidapi.h available on Arch AUR or on [Github](https://github.com/signal11/hidapi)

## Usage
```
msi-keyboard [-m normal|gaming|breath|audio|wave|dual] [-r (left|middle|right)] [-c (none|red|orange|yellow|green|sky|blue|purple|white)] [-i (high|medium|low|light)] [-c2 (none|red|orange|yellow|green|sky|blue|purple|white)] [-i2 (high|medium|low|light)] [--full]
```
* `-m`: keyboard mode
* `-r`: keyboard region on which the color is going to be applied (see also --full)
* `-c`: backlight's new color
* `-i`: backlight's intensity
* `-c2`: backlight's secondary color for breath and wave mode
* `-i2`: backlight's secondary intensity for breath and wave mode
* `--full`: apply the change on the whole keyboard. `-r` will be ignored

### Usage example
```
./msi-keyboard -m normal -c green --full
```
```
./msi-keyboard -m dual -c red -c2 blue -i2 low
```
Unknown argument are ignorer, unknown value is set to the default one. The following command does the same as the first one.
```
./msi-keyboard -m iDoNotExist -c green --full
```

## Run as non-root user
If you want to run the software as a non-root user, you can add the udev rules file to your `/etc/udev/rules.d/` directory.

## Notes
The audio mode does not work on linux at the moment.

## Issues
Delay on the wave is wrong, this may comme from the delay.

## Unknown packet
`01 02 22 14 00 00 00 00`: Usually sent when switching to audio mode
