<?php
/*
ev3php headers
Copyright (C) 2022 Lukas Tautz
*/
if (!defined('EV3PHP_VERSION')) {
    define('EV3PHP_VERSION', '1.0_HEADER_ONLY');
    define('PORT_A', 'A');
    define('PORT_B', 'B');
    define('PORT_C', 'C');
    define('PORT_D', 'D');
    define('PORT_1', '1');
    define('PORT_2', '2');
    define('PORT_3', '3');
    define('PORT_4', '4');
    define('BUTTON_LEFT', 'BUTTON_LEFT');
    define('BUTTON_RIGHT', 'BUTTON_RIGHT');
    define('BUTTON_UP', 'BUTTON_UP');
    define('BUTTON_DOWN', 'BUTTON_DOWN');
    define('BUTTON_CENTER', 'BUTTON_CENTER');
    define('BUTTON_BACK', 'BUTTON_BACK');
    define('IR_BUTTON_LEFT_UP', 'IR_BUTTON_LEFT_UP');
    define('IR_BUTTON_LEFT_DOWN', 'IR_BUTTON_LEFT_DOWN');
    define('IR_BUTTON_RIGHT_UP', 'IR_BUTTON_RIGHT_UP');
    define('IR_BUTTON_RIGHT_DOWN', 'IR_BUTTON_RIGHT_DOWN');
    define('CHANNEL_1', 1);
    define('CHANNEL_2', 2);
    define('CHANNEL_3', 3);
    define('CHANNEL_4', 4);
    define('LED_LEFT', 'LED_LEFT');
    define('LED_RIGHT', 'LED_RIGHT');
    define('COLOR_NONE', 'COLOR_NONE');
    define('COLOR_RED', 'COLOR_RED');
    define('COLOR_GREEN', 'COLOR_GREEN');
    define('COLOR_BLACK', 'COLOR_BLACK');
    define('COLOR_BLUE', 'COLOR_BLUE');
    define('COLOR_YELLOW', 'COLOR_YELLOW');
    define('COLOR_WHITE', 'COLOR_WHITE');
    define('COLOR_BROWN', 'COLOR_BROWN');
    define('LCD_X', 178);
    define('LCD_Y', 128);
    define('FONT_TINY_HEIGHT', 7);
    define('FONT_TINY_WIDTH', 5);
    define('FONT_SMALL_HEIGHT', 8);
    define('FONT_SMALL_WIDTH', 8);
    define('FONT_NORMAL_HEIGHT', 9);
    define('FONT_NORMAL_WIDTH', 8);
    define('FONT_BIG_HEIGHT', 16);
    define('FONT_BIG_WIDTH', 16);
    define('LANG_EN', 'en');
    define('LANG_FR', 'fr');
    define('LANG_DE', 'de');
    function ev3_lcd_start() {}
    function ev3_lcd_pixel(int $x, int $y) {}
    function ev3_lcd_pixel_remove(int $x, int $y) {}
    function ev3_lcd_clear() {}
    function ev3_lcd_tiny(int $x, int $y, string $text) {}
    function ev3_lcd_small(int $x, int $y, string $text) {}
    function ev3_lcd_normal(int $x, int $y, string $text) {}
    function ev3_lcd_big(int $x, int $y, string $text) {}
    function ev3_lcd_rectangle(int $x, int $y, int $w, int $h) {}
    function ev3_lcd_rectangle_filled(int $x, int $y, int $w, int $h, bool $black= true) {}
    function ev3_lcd_circle(int $x, int $y, int $r) {}
    function ev3_lcd_circle_filled(int $x, int $y, int $r, bool $black = true) {}
    function ev3_lcd_ellipse(int $x, int $y, int $rx, int $ry) {}
    function ev3_lcd_ellipse_filled(int $x, int $y, int $rx, int $ry, bool $black = true) {}
    function ev3_lcd_line(int $x0, int $y0, int $x1, int $y1) {}
    function ev3_lcd_end() {}
    function ev3_button_start() {}
    function ev3_button_pressed(string $button_name):bool {}
    function ev3_button_get_pressed():string|false {}
    function ev3_button_end() {}
    function ev3_battery_current():int {}
    function ev3_battery_voltage():int {}
    function ev3_led_start() {}
    function ev3_led_set(string $led_name, string $color, int $brightness) {}
    function ev3_led_color(string $color) {}
    function ev3_led_color_brightness(string $color, int $brightness) {}
    function ev3_led_end() {}
    function ev3_motor_start() {}
    function ev3_motor_info(string $port):string|false {}
    function ev3_motor_run(string $port, int $speed, int $degree):bool {}
    function ev3_motor_run_without_brake(string $port, int $speed, int $degree):bool {}
    function ev3_motor_stop(string $port):bool {}
    function ev3_motor_run_forever(string $port, int $speed):bool {}
    function ev3_motor_get_position(string $port):int|false {}
    function ev3_motor_set_position(string $port, int $degree):bool {}
    function ev3_motor_wait(string $port):bool {}
    function ev3_motor_end() {}
    function ev3_sensor_start() {}
    function ev3_sensor_info(string $port):string|false {}
    function ev3_sensor_touch(string $port):bool {}
    function ev3_sensor_ultrasonic(string $port):int|false {}
    function ev3_sensor_color(string $port):string|false {}
    function ev3_sensor_color_rgb(string $port):string|false {}
    function ev3_sensor_infrared_distance(string $port):int|false {}
    function ev3_sensor_infrared_pressed(string $port, int $channel, string $button):bool {}
    function ev3_sensor_end() {}
    function ev3_speak(string $lang, string $text, int $volume = 100, int $speed = 175) {}
    function ev3_speak_background(string $lang, string $text, int $volume = 100, int $speed = 175) {}
}
