PHP_ARG_ENABLE(ev3php, Whether to enable the ev3php extension, [--enable-ev3php  Enable ev3php])
if test "$EV3PHP" != "no"; then
    PHP_NEW_EXTENSION(ev3php, ev3php.c, $ext_shared)
fi
