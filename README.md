# ev3php
ev3php is a PHP extension for ev3dev.
<br>
With ev3php, you can use (nearly) the full power of ev3dev with PHP.

## Why PHP?
When I looked after the [supported programming languages](https://www.ev3dev.org/docs/programming-languages) by ev3dev, I have to decide which I want to use. For me, compiled languages were out of the question because, in my opinion, it is a hindrance to always have to wait until the program has been compiled.
<br>
Fitting my needs, there would be (Micro-)Python, Perl, Prolog and Ruby. But I doesn't like the syntax of those languages/have no knowledge. First, I have used MicroPython because of it's official LEGO edition. But after a few hours I didn't feel like coding python anymore, because of it's (in my view) weird syntax. Perl would be an alternative, but is wasn't updated since 2015 and has a big library file. Then I have the idea of writing an extension for a simple, interpreted scripting language. I've selected PHP because of it's simple opportunity to write an extension. But I doens't want to write an own wrapper for ev3dev, so I looked for a simple and small C wrapper. The [normal library](https://github.com/in4lio/ev3dev-c) is very big and has a complicated interface, but under [abadoned/unfinished libraries](https://www.ev3dev.org/docs/programming-languages#out-of-date-abandoned-and-unfinished-implementations) was [ev3c](https://github.com/theZiz/ev3c), which is very small (~80KB) and has a simple interface. The only matter was that there was a bug with drawing rectangles on LCD, but I was able to fix it. Then I wrote an interface for PHP with only ~1000 lines of code. Compiled to .so it is only 55 KB big, only 14% of the size of the Perl wrapper!

## Supported functions
ev3php supports nearly all functions of ev3dev, if you think I have forgotten one, please open an issue.
- LCD (text, rectangles, ellipses, circles, lines, pixels, clear screen)
- Buttons (get pressed, is pressed)
- Battery (current, voltage)
- Motors (run degree, run forever, stop, get position, set position, wait until finished)
- Sensors (set driver, touch sensor, ultrasonic sensor, infrared sensor including controller, color sensor)
- Speaker

## Installation:
At first you have to install ev3dev on a microSD-card ([tutorial](https://www.ev3dev.org/docs/getting-started)).
<br>
To run an ev3php program, you have to stop/remove brickman, because of otherwise they would get in each other's way. I recommend using the installer, but with the installer, you **are NOT able to use another programming language**! It is not documented how to use ev3php without the installer, but it's clear: you have to download/compile the `ev3php.so` and include it in the `php.ini` with `extension=ev3php.so`.
If you want to use the installer, first you have to add internet access to the ev3 ([e.g. with USB cable or WiFi-Dongle](https://www.ev3dev.org/docs/networking)).
Then you have to run the following command:
```bash
wget -O - https://raw.githubusercontent.com/lukastautz/ev3php/main/install.sh | sudo sh
```
**Important**: If you don't use ev3dev stretch, I don't know whether you will have to compile ev3php yourself.

## Usage
The main program is in `/ev3php/ev3.php`. If you have edited it and don't want to reboot every time.., there is a solution: Simply run `ev3php` in the terminal and you will see the output of the program in the terminal. If you want to log things and doesn't want to start a ssh session every time, you can easy output to standard output, e.g. with `echo` or `printf` or similar. The output is saved in `/ev3php/stdout.txt`. If you want to install a PHP extension, you can copy the .so file in `/ev3php/php` and edit the `/ev3php/php/php.ini`.

## Documentation
[lukastautz.github.io/ev3php](https://lukastautz.github.io/ev3php)

## Examples
[ev3php/examples](https://github.com/lukastautz/ev3php/tree/main/examples)

## License
ev3php is licensed under the GNU General Public License 3.0 (check out [LICENSE](https://github.com/lukastautz/ev3php/blob/main/LICENSE)).
Copyright (C) 2022 Lukas Tautz
