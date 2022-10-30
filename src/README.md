# ev3php/src
Here is the source code for the plugin.
<br>
You have to install `build-essential` and `php7.0-dev`.
<br>
Simple run `./build.sh` for building. Afterwards, the ev3php.so is in the directory `modules/ev3php.so`.<br>
Alternatively, you can cross-compile it with `cross.sh`.
<br>
**Warning**: Building ev3php from source on the ev3 itself needs time, usually ~30min, I reccommend cross-compling it in docker ([tutorial](https://www.ev3dev.org/docs/tutorials/using-docker-to-cross-compile)), with `cross.sh`, wich needs only ~1min.
* * *
Copyright (C) 2022 Lukas Tautz
