# msi-keyboard
Allow the user to change the keyboard backlight using hidapi

This project is based on bparker06's work.

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
