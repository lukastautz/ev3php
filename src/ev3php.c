
/*
EV3PHP v1.0 <https://github.com/lukastautz/ev3php>
Copyright (C) 2022 Lukas Tautz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

You can use EV3PHP for free in your projects, you can also modify it BUT YOU ARE NOT ALLOWED TO DELETE THIS COMMENT!

ev3php uses ev3c <https://github.com/theZiz/ev3c>, wich is also licensed under the GPL, but is not by me.
*/

// Includes
#include <php.h>
#include "ev3c.c"


// Macros
#define PHP_STR_CONSTANT(name, value)   zend_register_stringl_constant(name, sizeof(name) - 1, value, sizeof(value) - 1, 0, CONST_CS | CONST_PERSISTENT) // CONST_CS: case sensitive, CONST_PERSISTENT: persistent
#define PHP_INT_CONSTANT(name, value)   zend_register_long_constant(name, sizeof(name) - 1, value, 0, CONST_CS | CONST_PERSISTENT) // CONST_CS: case sensitive, CONST_PERSISTENT: persistent
#define PARSE_ARGS(format, ...)         if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), format, __VA_ARGS__) == FAILURE) return
#define PHP_FUNCTION_BLOCK(name)        static ZEND_NAMED_FUNCTION(_internal_##name)
#define PHP_FUNCTION_ENTRY(name)        ZEND_FENTRY(name, _internal_##name, NULL, 0)
#define php_str                         zend_string *
#define c_str(php_string)               ZSTR_VAL(php_string)
#define SPEAKER_MAX_TEXT_LENGTH         2500
#define EV3PHP_VERSION                  "1.0"


// Init function
PHP_MINIT_FUNCTION(ev3php) {
    // Version
    PHP_STR_CONSTANT("EV3PHP_VERSION", EV3PHP_VERSION);

    // Ports
    PHP_STR_CONSTANT("PORT_A", "A");
    PHP_STR_CONSTANT("PORT_B", "B");
    PHP_STR_CONSTANT("PORT_C", "C");
    PHP_STR_CONSTANT("PORT_D", "D");
    PHP_STR_CONSTANT("PORT_1", "1");
    PHP_STR_CONSTANT("PORT_2", "2");
    PHP_STR_CONSTANT("PORT_3", "3");
    PHP_STR_CONSTANT("PORT_4", "4");

    // Buttons
    PHP_STR_CONSTANT("BUTTON_LEFT", "BUTTON_LEFT");
    PHP_STR_CONSTANT("BUTTON_RIGHT", "BUTTON_RIGHT");
    PHP_STR_CONSTANT("BUTTON_UP", "BUTTON_UP");
    PHP_STR_CONSTANT("BUTTON_DOWN", "BUTTON_DOWN");
    PHP_STR_CONSTANT("BUTTON_CENTER", "BUTTON_CENTER");
    PHP_STR_CONSTANT("BUTTON_BACK", "BUTTON_BACK");

    // Infrared-Buttons
    PHP_STR_CONSTANT("IR_BUTTON_LEFT_UP", "IR_BUTTON_LEFT_UP");
    PHP_STR_CONSTANT("IR_BUTTON_LEFT_DOWN", "IR_BUTTON_LEFT_DOWN");
    PHP_STR_CONSTANT("IR_BUTTON_RIGHT_UP", "IR_BUTTON_RIGHT_UP");
    PHP_STR_CONSTANT("IR_BUTTON_RIGHT_DOWN", "IR_BUTTON_RIGHT_DOWN");

    // Infrared-Channels
    PHP_INT_CONSTANT("CHANNEL_1", 1);
    PHP_INT_CONSTANT("CHANNEL_2", 2);
    PHP_INT_CONSTANT("CHANNEL_3", 3);
    PHP_INT_CONSTANT("CHANNEL_4", 4);

    // LEDs
    PHP_STR_CONSTANT("LED_LEFT", "LED_LEFT");
    PHP_STR_CONSTANT("LED_RIGHT", "LED_RIGHT");

    // Colors
    PHP_STR_CONSTANT("COLOR_RED", "COLOR_RED");
    PHP_STR_CONSTANT("COLOR_GREEN", "COLOR_GREEN");
    PHP_STR_CONSTANT("COLOR_BLACK", "COLOR_BLACK");
    PHP_STR_CONSTANT("COLOR_NONE", "COLOR_NONE");
    PHP_STR_CONSTANT("COLOR_BLUE", "COLOR_BLUE");
    PHP_STR_CONSTANT("COLOR_YELLOW", "COLOR_YELLOW");
    PHP_STR_CONSTANT("COLOR_WHITE", "COLOR_WHITE");
    PHP_STR_CONSTANT("COLOR_BROWN", "COLOR_BROWN");

    // LCD
    PHP_INT_CONSTANT("LCD_X", 178);
    PHP_INT_CONSTANT("LCD_Y", 128);

    PHP_INT_CONSTANT("FONT_TINY_HEIGHT", 7);
    PHP_INT_CONSTANT("FONT_TINY_WIDTH", 5);
    PHP_INT_CONSTANT("FONT_SMALL_HEIGHT", 8);
    PHP_INT_CONSTANT("FONT_SMALL_WIDTH", 8);
    PHP_INT_CONSTANT("FONT_NORMAL_HEIGHT", 9);
    PHP_INT_CONSTANT("FONT_NORMAL_WIDTH", 8);
    PHP_INT_CONSTANT("FONT_BIG_HEIGHT", 16);
    PHP_INT_CONSTANT("FONT_BIG_WIDTH", 16);

    // Speaker
    PHP_STR_CONSTANT("LANG_EN", "en");
    PHP_STR_CONSTANT("LANG_FR", "fr");
    PHP_STR_CONSTANT("LANG_DE", "de");

    return SUCCESS;
}


// PHP functions

/* LCD */

// ev3_lcd_start();
// Starts the LCD mode
PHP_FUNCTION_BLOCK(ev3_lcd_start) {
    ev3_init_lcd();
    ev3_clear_lcd();
}

// ev3_lcd_pixel(int x, int y);
// Adds a black pixel
PHP_FUNCTION_BLOCK(ev3_lcd_pixel) {
    long x, y;
    PARSE_ARGS("ll", &x, &y);
    EV3_PIXEL_SET(x, y);
}

// ev3_lcd_pixel_remove(int x, int y);
// Removes a black pixel
PHP_FUNCTION_BLOCK(ev3_lcd_pixel_remove) {
    long x, y;
    PARSE_ARGS("ll", &x, &y);
    EV3_PIXEL_UNSET(x, y);
}

// ev3_lcd_clear();
// Clears the LCD
PHP_FUNCTION_BLOCK(ev3_lcd_clear) {
    ev3_clear_lcd();
}

// ev3_lcd_tiny(int x, int y, string text);
// Write tiny <text> at <x>, <y>
PHP_FUNCTION_BLOCK(ev3_lcd_tiny) {
    long x, y;
    php_str str;
    PARSE_ARGS("llS", &x, &y, &str);
    ev3_text_lcd_tiny(x, y, c_str(str));
}

// ev3_lcd_small(int x, int y, string text);
// Write small <text> at <x>, <y>
PHP_FUNCTION_BLOCK(ev3_lcd_small) {
    long x, y;
    php_str str;
    PARSE_ARGS("llS", &x, &y, &str);
    ev3_text_lcd_small(x, y, c_str(str));
}

// ev3_lcd_normal(int x, int y, string text);
// Write normal <text> at <x>, <y>
PHP_FUNCTION_BLOCK(ev3_lcd_normal) {
    long x, y;
    php_str str;
    PARSE_ARGS("llS", &x, &y, &str);
    ev3_text_lcd_normal(x, y, c_str(str));
}

// ev3_lcd_big(int x, int y, string text);
// Write big <text> at <x>, <y>
PHP_FUNCTION_BLOCK(ev3_lcd_big) {
    long x, y;
    php_str str;
    PARSE_ARGS("llS", &x, &y, &str);
    ev3_text_lcd_large(x, y, c_str(str));
}

// ev3_lcd_rectangle(int x, int y, int w, int h);
// Add rectangle at <x>, <y> with width <w> and height <h>.
PHP_FUNCTION_BLOCK(ev3_lcd_rectangle) {
    long x, y, w, h;
    PARSE_ARGS("llll", &x, &y, &w, &h);
    ev3_rectangle_lcd_out(x, y, w, h);
}

// ev3_lcd_rectangle_filled(int x, int y, int w, int h [, bool black]);
// Add filled rectangle at <x>, <y> with width <w> and height <h>.
// If <black> is false, the rectangle will be white and all black pixels inside removed.
PHP_FUNCTION_BLOCK(ev3_lcd_rectangle_filled) {
    long x, y, w, h;
    zend_bool black = 1;
    PARSE_ARGS("llll|b", &x, &y, &w, &h, &black);
    ev3_rectangle_lcd(x, y, w, h, (char)black);
}

// ev3_lcd_circle(int x, int y, int r);
// Add circle at <x>, <y> with radius <r>. (<x>, <y> are the center of the circle)
PHP_FUNCTION_BLOCK(ev3_lcd_circle) {
    long x, y, r;
    PARSE_ARGS("lll", &x, &y, &r);
    ev3_circle_lcd_out(x, y, r);
}

// ev3_lcd_circle_filled(int x, int y, int r [, bool black]);
// Add filled circle at <x>, <y> with radius <r>. (<x>, <y> are the center of the circle)
// If <black> is false, the circle will be white and all black pixels inside removed.
PHP_FUNCTION_BLOCK(ev3_lcd_circle_filled) {
    long x, y, r;
    zend_bool black = 1;
    PARSE_ARGS("lll|b", &x, &y, &r, &black);
    ev3_circle_lcd(x, y, r, (char)black);
}

// ev3_lcd_ellipse(int x, int y, int rx, int ry);
// Add ellipse at <x>, <y> with radius <rx> and <ry>. (<x>, <y> are the center of the ellipse)
PHP_FUNCTION_BLOCK(ev3_lcd_ellipse) {
    long x, y, rx, ry;
    PARSE_ARGS("llll", &x, &y, &rx, &ry);
    ev3_ellipse_lcd_out(x, y, rx, ry);
}

// ev3_lcd_ellipse_filled(int x, int y, int rx, int ry [, bool black]);
// Add filled ellipse at <x>, <y> with radius <rx> and <ry>. (<x>, <y> are the center of the ellipse)
// If <black> is false, the ellipse will be white and all black pixels inside removed.
PHP_FUNCTION_BLOCK(ev3_lcd_ellipse_filled) {
    long x, y, rx, ry;
    zend_bool black = 1;
    PARSE_ARGS("llll|b", &x, &y, &rx, &ry, &black);
    ev3_ellipse_lcd(x, y, rx, ry, (char)black);
}

// ev3_lcd_line(int x0, int y0, int x1, int y1);
// Add line with <x0>, <y0> as start and <x1> and <y1> as end.
PHP_FUNCTION_BLOCK(ev3_lcd_line) {
    long x0, y0, x1, y1;
    PARSE_ARGS("llll", &x0, &y0, &x1, &y1);
    ev3_line_lcd(x0, y0, x1, y1);
}

// ev3_lcd_end();
// Exits the LCD mode
PHP_FUNCTION_BLOCK(ev3_lcd_end) {
    ev3_quit_lcd();
}

/* BUTTONS */

// ev3_button_start();
// Starts the button mode
PHP_FUNCTION_BLOCK(ev3_button_start) {
    ev3_init_button();
}

// bool ev3_button_pressed(string button_name);
// Checks whether the button is pressed
// Available buttons:
//  BUTTON_LEFT
//  BUTTON_RIGHT
//  BUTTON_UP
//  BUTTON_DOWN
//  BUTTON_CENTER
//  BUTTON_BACK
PHP_FUNCTION_BLOCK(ev3_button_pressed) {
    php_str _button;
    PARSE_ARGS("S", &_button);
    char *button = c_str(_button);
    enum ev3_button_identifier ev3_button;
    if (strcmp(button, "BUTTON_LEFT") == 0) ev3_button = BUTTON_LEFT;
    else if (strcmp(button, "BUTTON_RIGHT") == 0) ev3_button = BUTTON_RIGHT;
    else if (strcmp(button, "BUTTON_UP") == 0) ev3_button = BUTTON_UP;
    else if (strcmp(button, "BUTTON_DOWN") == 0) ev3_button = BUTTON_DOWN;
    else if (strcmp(button, "BUTTON_CENTER") == 0) ev3_button = BUTTON_CENTER;
    else if (strcmp(button, "BUTTON_BACK") == 0) ev3_button = BUTTON_BACK;
    else {
        php_error_docref(NULL, E_WARNING, "Unknown button");
        return;
    }
    if (ev3_button_pressed(ev3_button) == 1) RETVAL_TRUE;
    else RETVAL_FALSE;
}

// string|false ev3_button_get_pressed();
// Get the currently pressed button (BUT ONLY ONE! USE ev3_button_pressed INSTEAD!)
// Available buttons:
//  BUTTON_BACK
//  BUTTON_CENTER
//  BUTTON_DOWN
//  BUTTON_UP
//  BUTTON_LEFT
//  BUTTON_RIGHT
PHP_FUNCTION_BLOCK(ev3_button_get_pressed) {
    if (ev3_button_pressed(BUTTON_BACK) == 1) {
        RETVAL_STRINGL("BUTTON_BACK", 11);
    } else if (ev3_button_pressed(BUTTON_CENTER) == 1) {
        RETVAL_STRINGL("BUTTON_CENTER", 13);
    } else if (ev3_button_pressed(BUTTON_DOWN) == 1) {
        RETVAL_STRINGL("BUTTON_DOWN", 11);
    } else if (ev3_button_pressed(BUTTON_UP) == 1) {
        RETVAL_STRINGL("BUTTON_UP", 9);
    } else if (ev3_button_pressed(BUTTON_LEFT) == 1) {
        RETVAL_STRINGL("BUTTON_LEFT", 11);
    } else if (ev3_button_pressed(BUTTON_RIGHT) == 1) {
        RETVAL_STRINGL("BUTTON_RIGHT", 12);
    } else RETVAL_FALSE;
}

// ev3_button_end();
// Exits the button mode
PHP_FUNCTION_BLOCK(ev3_button_end) {
    ev3_quit_button();
}

/* BATTERY */

// int ev3_battery_current();
// Returns the current of the battery in µA
PHP_FUNCTION_BLOCK(ev3_battery_current) {
    RETVAL_LONG(ev3c_current());
}

// int ev3_battery_voltage();
// Returns the voltage of the battery in µV
PHP_FUNCTION_BLOCK(ev3_battery_voltage) {
    RETVAL_LONG(ev3c_voltage());
}

/* LEDs */

// ev3_led_start();
// Starts the LED mode
PHP_FUNCTION_BLOCK(ev3_led_start) {
    ev3_init_led();
}

// ev3_led_set(string led_name, string color, int brightness);
// Changes the mode of <led_name> to color: <color> and brightness: <brightness>
// Supported LEDs:
//  LED_LEFT
//  LED_RIGHT
// Supported colors:
//  COLOR_GREEN
//  COLOR_RED
// Brightness is between 0 and 255
PHP_FUNCTION_BLOCK(ev3_led_set) {
    php_str _led_name;
    php_str _color;
    long brightness;
    PARSE_ARGS("SSl", &_led_name, &_color, &brightness);
    char *led_name = c_str(_led_name);
    char *color = c_str(_color);
    enum ev3_led_name ev3_led_name;
    enum ev3_led_color ev3_led_color;
    if (strcmp(led_name, "LED_LEFT") == 0) ev3_led_name = LEFT_LED;
    else if (strcmp(led_name, "LED_RIGHT") == 0) ev3_led_name = RIGHT_LED;
    else {
        php_error_docref(NULL, E_WARNING, "Unknown LED");
        return;
    }
    if (strcmp(color, "COLOR_GREEN") == 0) ev3_led_color = GREEN_LED;
    else if (strcmp(color, "COLOR_RED") == 0) ev3_led_color = RED_LED;
    else {
        php_error_docref(NULL, E_WARNING, "Unknown color");
        return;
    }
    ev3_set_led(ev3_led_name, ev3_led_color, brightness);
}

// ev3_led_color(string color);
// Changes the mode of both LEDs to color: <color>
// Supported colors:
//  COLOR_GREEN
//  COLOR_RED
PHP_FUNCTION_BLOCK(ev3_led_color) {
    php_str _color;
    PARSE_ARGS("S", &_color);
    char *color = c_str(_color);
    if (strcmp(color, "COLOR_GREEN") == 0) {
        ev3_set_led(LEFT_LED, RED_LED, 0);
        ev3_set_led(RIGHT_LED, RED_LED, 0);
        ev3_set_led(LEFT_LED, GREEN_LED, 255);
        ev3_set_led(RIGHT_LED, GREEN_LED, 255);
    } else if (strcmp(color, "COLOR_RED") == 0) {
        ev3_set_led(LEFT_LED, GREEN_LED, 0);
        ev3_set_led(RIGHT_LED, GREEN_LED, 0);
        ev3_set_led(LEFT_LED, RED_LED, 255);
        ev3_set_led(RIGHT_LED, RED_LED, 255);
    } else {
        php_error_docref(NULL, E_WARNING, "Unknown color");
    }
}

// ev3_led_color_brightness(string color, int brightness);
// Changes the mode of both LEDs to color: <color>
// Supported colors:
//  COLOR_GREEN
//  COLOR_RED
PHP_FUNCTION_BLOCK(ev3_led_color_brightness) {
    php_str _color;
    long brightness;
    PARSE_ARGS("Sl", &_color, &brightness);
    char *color = c_str(_color);
    if (strcmp(color, "COLOR_GREEN") == 0) {
        ev3_set_led(LEFT_LED, RED_LED, 0);
        ev3_set_led(RIGHT_LED, RED_LED, 0);
        ev3_set_led(LEFT_LED, GREEN_LED, brightness);
        ev3_set_led(RIGHT_LED, GREEN_LED, brightness);
    } else if (strcmp(color, "COLOR_RED") == 0) {
        ev3_set_led(LEFT_LED, GREEN_LED, 0);
        ev3_set_led(RIGHT_LED, GREEN_LED, 0);
        ev3_set_led(LEFT_LED, RED_LED, brightness);
        ev3_set_led(RIGHT_LED, RED_LED, brightness);
    } else {
        php_error_docref(NULL, E_WARNING, "Unknown color");
    }
}

// ev3_led_end();
// Exits the LED mode
PHP_FUNCTION_BLOCK(ev3_led_end) {
    ev3_quit_led();
}

/* MOTORS */

static ev3_motor_ptr ev3_all_motors;

// ev3_motor_start();
// Loads all motors
PHP_FUNCTION_BLOCK(ev3_motor_start) {
    ev3_all_motors = ev3_load_motors();
}

// string|false ev3_motor_info(string port);
// Returns the name of a motor
// <port> is A, B, C or D
PHP_FUNCTION_BLOCK(ev3_motor_info) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            RETVAL_STRINGL(motor->driver_name, strlen(motor->driver_name));
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_motor_run(string port, int speed, int degree);
// Turns a motor around <degree> degrees.
// <port> is A, B, C or D
// <speed> is 0 - 100
PHP_FUNCTION_BLOCK(ev3_motor_run) {
    php_str _port;
    long speed, degree;
    PARSE_ARGS("Sll", &_port, &speed, &degree);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            ev3_stop_action_motor_by_name(motor, "hold");
            if (speed < 0) degree = 0 - degree;
            ev3_set_position_sp(motor, degree);
            ev3_set_speed_sp(motor, (motor->max_speed / 100) * speed);
            ev3_command_motor(motor, 2);
            RETVAL_TRUE;
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_motor_run_without_brake(string port, int speed, int degree);
// Turns a motor around <degree> degrees and let it roll out.
// <port> is A, B, C or D
// <speed> is 0 - 100
PHP_FUNCTION_BLOCK(ev3_motor_run_without_brake) {
    php_str _port;
    long speed, degree;
    PARSE_ARGS("Sll", &_port, &speed, &degree);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            ev3_stop_action_motor_by_name(motor, "coast");
            if (speed < 0) degree = 0 - degree;
            ev3_set_position_sp(motor, degree);
            ev3_set_speed_sp(motor, (motor->max_speed / 100) * speed);
            ev3_command_motor(motor, 2);
            RETVAL_TRUE;
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_motor_stop(string port);
// Stops a motor
// <port> is A, B, C or D
PHP_FUNCTION_BLOCK(ev3_motor_stop) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            ev3_reset_motor(motor);
            ev3_close_motor(motor);
            RETVAL_TRUE;
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_motor_run_forever(string port, int speed);
// Runs a motor forever.
// <port> is A, B, C or D
// <speed> is 0 - 100
PHP_FUNCTION_BLOCK(ev3_motor_run_forever) {
    php_str _port;
    long speed;
    PARSE_ARGS("Sl", &_port, &speed);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            ev3_stop_action_motor_by_name(motor, "hold");
            if (speed < 0) ev3_set_polarity(motor, -1);
            else ev3_set_polarity(motor, 1);
            ev3_set_speed_sp(motor, (motor->max_speed / 100) * speed);
            ev3_command_motor(motor, 0);
            RETVAL_TRUE;
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// int|false ev3_motor_get_position(string port);
// Returns the position of the motor in degree.
// <port> is A, B, C or D
PHP_FUNCTION_BLOCK(ev3_motor_get_position) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            RETVAL_LONG(ev3_get_position(motor));
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_motor_set_position(string port, int degree);
// Sets the position of the motor in degree.
// <port> is A, B, C or D
PHP_FUNCTION_BLOCK(ev3_motor_set_position) {
    php_str _port;
    long degree;
    PARSE_ARGS("Sl", &_port, &degree);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (ev3_all_motors) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            ev3_set_position(motor, degree);
            RETVAL_TRUE;
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_motor_wait(string port);
// Waits until motor is not moving
// <port> is A, B, C or D
PHP_FUNCTION_BLOCK(ev3_motor_wait) {
    php_str _port;
    int32_t last_pos;
    PARSE_ARGS("S", &_port);
    char port = toupper(c_str(_port)[0]);
    ev3_motor_ptr motor = ev3_all_motors;
    while (motor) {
        if (motor->port == port) {
            ev3_open_motor(motor);
            while (last_pos != ev3_get_position(motor)) {
                last_pos = ev3_get_position(motor);
                usleep(5000); // 5 milliseconds
            }
            RETVAL_TRUE;
            return;
        }
        motor = motor->next;
    }
    RETVAL_FALSE;
}

// ev3_motor_end();
// Unload the motors
PHP_FUNCTION_BLOCK(ev3_motor_end) {
    ev3_delete_motors(ev3_all_motors);
}

/* SENSORS */

static ev3_sensor_ptr ev3_all_sensors;

// ev3_sensor_start();
// Loads all sensors
PHP_FUNCTION_BLOCK(ev3_sensor_start) {
    ev3_all_sensors = ev3_load_sensors();
}

// string|false ev3_sensor_info(string port);
// Returns the driver/name of a sensor
// <port> is 1, 2, 3 or 4
PHP_FUNCTION_BLOCK(ev3_sensor_info) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            RETVAL_STRINGL(sensor->driver_name, strlen(sensor->driver_name));
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_sensor_touch(string port);
// Checks whether the touch button is pressed
// <port> is 1, 2, 3 or 4
PHP_FUNCTION_BLOCK(ev3_sensor_touch) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            ev3_open_sensor(sensor);
            ev3_mode_sensor(sensor, 0);
            ev3_update_sensor_val(sensor);
            if (sensor->val_data[0].s32 == 0) RETVAL_FALSE;
            else RETVAL_TRUE;
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// int|false ev3_sensor_ultrasonic(string port);
// Returns the distance of the utrasonic sensor (in mm)
// If return value is 0, it is assumed that there is no known value!
// <port> is 1, 2, 3 or 4
PHP_FUNCTION_BLOCK(ev3_sensor_ultrasonic) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            ev3_open_sensor(sensor);
            ev3_mode_sensor(sensor, 0);
            ev3_update_sensor_bin(sensor);
            if (sensor->bin_data[0].s32 != 2550) {
                RETVAL_LONG(sensor->bin_data[0].s32);
            } else {
                RETVAL_LONG(0); // 2550 seems to mean unknown, return 0
            }
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// string|false ev3_sensor_color(string port);
// Returns the current measured color of the color sensor
// Available colors:
//  COLOR_RED
//  COLOR_GREEN
//  COLOR_BLACK
//  COLOR_NONE
//  COLOR_BLUE
//  COLOR_YELLOW
//  COLOR_WHITE
//  COLOR_BROWN
// <port> is 1, 2, 3 or 4
PHP_FUNCTION_BLOCK(ev3_sensor_color) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            ev3_open_sensor(sensor);
            ev3_mode_sensor(sensor, 2);
            ev3_update_sensor_bin(sensor);
            switch (sensor->bin_data[0].s32) {
                case 1:
                    RETVAL_STRINGL("COLOR_BLACK", 11);
                    break;
                case 2:
                    RETVAL_STRINGL("COLOR_BLUE", 10);
                    break;
                case 3:
                    RETVAL_STRINGL("COLOR_GREEN", 11);
                    break;
                case 4:
                    RETVAL_STRINGL("COLOR_YELLOW", 12);
                    break;
                case 5:
                    RETVAL_STRINGL("COLOR_RED", 9);
                    break;
                case 6:
                    RETVAL_STRINGL("COLOR_WHITE", 11);
                    break;
                case 7:
                    RETVAL_STRINGL("COLOR_BROWN", 11);
                    break;
                default:
                    RETVAL_STRINGL("COLOR_NONE", 10);
            }
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// string|false ev3_sensor_color_rgb(string port);
// Returns the current measured color (rgb) in format "RED,GREEN,BLUE" of the color sensor
// <port> is 1, 2, 3 or 4
PHP_FUNCTION_BLOCK(ev3_sensor_color_rgb) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            ev3_open_sensor(sensor);
            ev3_mode_sensor(sensor, 4);
            ev3_update_sensor_val(sensor);
            char result[15];
            sprintf(result, "%i,%i,%i", sensor->val_data[0].s32, sensor->val_data[1].s32, sensor->val_data[2].s32);
            RETVAL_STRINGL(result, strlen(result));
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// int|false ev3_sensor_infrared_distance(string port);
// Returns the distance measured by the infrared sensor in percent
// <port> is 1, 2, 3 or 4
PHP_FUNCTION_BLOCK(ev3_sensor_infrared_distance) {
    php_str _port;
    PARSE_ARGS("S", &_port);
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            ev3_open_sensor(sensor);
            ev3_mode_sensor(sensor, 0);
            ev3_update_sensor_bin(sensor);
            RETVAL_LONG(sensor->bin_data[0].s32);
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// bool ev3_sensor_infrared_pressed(string port, int channel, string button);
// Checks whether <button> is pressed
// <port> is 1, 2, 3 or 4
// <channel> is 1, 2, 3 or 4 (the selected channel on the remote controller)
// Available buttons:
//  IR_BUTTON_LEFT_UP
//  IR_BUTTON_LEFT_DOWN
//  IR_BUTTON_RIGHT_UP
//  IR_BUTTON_RIGHT_DOWN
// The top button is NOT available because of it seems like that the sensor is stopping sending while the top button is pressed!
PHP_FUNCTION_BLOCK(ev3_sensor_infrared_pressed) {
    php_str _port;
    php_str _button;
    long channel;
    PARSE_ARGS("SlS", &_port, &channel, &_button);
    char *button = c_str(_button);
    unsigned short btn_id = 0;
    if (strcmp(button, "IR_BUTTON_LEFT_UP") == 0) btn_id = 1;
    else if (strcmp(button, "IR_BUTTON_LEFT_DOWN") == 0) btn_id = 2;
    else if (strcmp(button, "IR_BUTTON_RIGHT_UP") == 0) btn_id = 3;
    else if (strcmp(button, "IR_BUTTON_RIGHT_DOWN") == 0) btn_id = 4;
    else {
        php_error_docref(NULL, E_WARNING, "Unknown button");
        RETVAL_FALSE;
        return;
    }
    channel--;
    int32_t port = atoi(c_str(_port));
    ev3_sensor_ptr sensor = ev3_all_sensors;
    while (sensor) {
        if (sensor->port == port) {
            ev3_open_sensor(sensor);
            ev3_mode_sensor(sensor, 2);
            ev3_update_sensor_val(sensor);
            port = 0; // port is not needed, so use it for other purpose for lesser RAM usage
                      // port == 1 : RETVAL_TRUE ? RETVAL_FALSE
            switch (sensor->val_data[channel].s32) {
                case 1:
                    if (btn_id == 1) port = 1;
                    break;
                case 2:
                    if (btn_id == 2) port = 1;
                    break;
                case 3:
                    if (btn_id == 3) port = 1;
                    break;
                case 4:
                    if (btn_id == 4) port = 1;
                    break;
                case 5:
                    if (btn_id == 1 || btn_id == 3) port = 1;
                    break;
                case 6:
                    if (btn_id == 1 || btn_id == 4) port = 1;
                    break;
                case 7:
                    if (btn_id == 2 || btn_id == 3) port = 1;
                    break;
                case 8:
                    if (btn_id == 2 || btn_id == 4) port = 1;
                    break;
                case 10:
                    if (btn_id == 1 || btn_id == 2) port = 1;
                    break;
                case 11:
                    if (btn_id == 3 || btn_id == 4) port = 1;
            }
            if (port == 1) RETVAL_TRUE;
            else RETVAL_FALSE;
            return;
        }
        sensor = sensor->next;
    }
    RETVAL_FALSE;
}

// ev3_sensor_end();
// Unload the sensors
PHP_FUNCTION_BLOCK(ev3_sensor_end) {
    ev3_delete_sensors(ev3_all_sensors);
}

/* SPEAKER */

// ev3_speak(string lang, string text [, int volume, int speed]);
// Speaks a text and waits until finished.
// <lang> is en (English), fr (French), de (German) and similar
// <volume> is 0 - 200, default: 100
// <speed> is words per minute (80 - 450), default: 175
// <text> maxlength is 2500 (changable in the c constant SPEAKER_MAX_TEXT_LENGTH)
// DO NOT USE " IN <text>!
PHP_FUNCTION_BLOCK(ev3_speak) {
    php_str _lang;
    php_str _text;
    long _volume = 100;
    long _speed = 175;
    PARSE_ARGS("SS|ll", &_lang, &_text, &_volume, &_speed);
    char call[58 + SPEAKER_MAX_TEXT_LENGTH];
    sprintf(call, "espeak --stdout -v%s -a%i -s%i \"%s\"|aplay -q 2>/dev/null", c_str(_lang), _volume, _speed, c_str(_text));
    system(call);
}

// ev3_speak_background(string lang, string text [, int volume, int speed]);
// Speaks a text in background.
// <lang> is en (English), fr (French), de (German) and similar
// <volume> is 0 - 200, default: 100
// <speed> is words per minute (80 - 450), default: 175
// <text> maxlength is 2500 (changable in the c constant SPEAKER_MAX_TEXT_LENGTH)
// DO NOT USE " IN <text>!
PHP_FUNCTION_BLOCK(ev3_speak_background) {
    php_str _lang;
    php_str _text;
    long _volume = 100;
    long _speed = 175;
    PARSE_ARGS("SS|ll", &_lang, &_text, &_volume, &_speed);
    char call[59 + SPEAKER_MAX_TEXT_LENGTH];
    sprintf(call, "espeak --stdout -v%s -a%i -s%i \"%s\"|aplay -q 2>/dev/null&", c_str(_lang), _volume, _speed, c_str(_text));
    system(call);
}


// PHP function list
static zend_function_entry ev3php_functions[] = {
    // LCD
    PHP_FUNCTION_ENTRY(ev3_lcd_start)
    PHP_FUNCTION_ENTRY(ev3_lcd_pixel)
    PHP_FUNCTION_ENTRY(ev3_lcd_pixel_remove)
    PHP_FUNCTION_ENTRY(ev3_lcd_clear)
    PHP_FUNCTION_ENTRY(ev3_lcd_tiny)
    PHP_FUNCTION_ENTRY(ev3_lcd_small)
    PHP_FUNCTION_ENTRY(ev3_lcd_normal)
    PHP_FUNCTION_ENTRY(ev3_lcd_big)
    PHP_FUNCTION_ENTRY(ev3_lcd_rectangle)
    PHP_FUNCTION_ENTRY(ev3_lcd_rectangle_filled)
    PHP_FUNCTION_ENTRY(ev3_lcd_circle)
    PHP_FUNCTION_ENTRY(ev3_lcd_circle_filled)
    PHP_FUNCTION_ENTRY(ev3_lcd_ellipse)
    PHP_FUNCTION_ENTRY(ev3_lcd_ellipse_filled)
    PHP_FUNCTION_ENTRY(ev3_lcd_line)
    PHP_FUNCTION_ENTRY(ev3_lcd_end)

    // BUTTONS
    PHP_FUNCTION_ENTRY(ev3_button_start)
    PHP_FUNCTION_ENTRY(ev3_button_pressed)
    PHP_FUNCTION_ENTRY(ev3_button_get_pressed)
    PHP_FUNCTION_ENTRY(ev3_button_end)

    // BATTERY
    PHP_FUNCTION_ENTRY(ev3_battery_current)
    PHP_FUNCTION_ENTRY(ev3_battery_voltage)

    // LEDs
    PHP_FUNCTION_ENTRY(ev3_led_start)
    PHP_FUNCTION_ENTRY(ev3_led_set)
    PHP_FUNCTION_ENTRY(ev3_led_color)
    PHP_FUNCTION_ENTRY(ev3_led_color_brightness)
    PHP_FUNCTION_ENTRY(ev3_led_end)

    // MOTORS
    PHP_FUNCTION_ENTRY(ev3_motor_start)
    PHP_FUNCTION_ENTRY(ev3_motor_info)
    PHP_FUNCTION_ENTRY(ev3_motor_run)
    PHP_FUNCTION_ENTRY(ev3_motor_run_without_brake)
    PHP_FUNCTION_ENTRY(ev3_motor_stop)
    PHP_FUNCTION_ENTRY(ev3_motor_run_forever)
    PHP_FUNCTION_ENTRY(ev3_motor_get_position)
    PHP_FUNCTION_ENTRY(ev3_motor_set_position)
    PHP_FUNCTION_ENTRY(ev3_motor_wait)
    PHP_FUNCTION_ENTRY(ev3_motor_end)

    // SENSORS
    PHP_FUNCTION_ENTRY(ev3_sensor_start)
    PHP_FUNCTION_ENTRY(ev3_sensor_info)
    PHP_FUNCTION_ENTRY(ev3_sensor_touch)
    PHP_FUNCTION_ENTRY(ev3_sensor_ultrasonic)
    PHP_FUNCTION_ENTRY(ev3_sensor_color)
    PHP_FUNCTION_ENTRY(ev3_sensor_color_rgb)
    PHP_FUNCTION_ENTRY(ev3_sensor_infrared_distance)
    PHP_FUNCTION_ENTRY(ev3_sensor_infrared_pressed)
    PHP_FUNCTION_ENTRY(ev3_sensor_end)

    // SPEAKER
    PHP_FUNCTION_ENTRY(ev3_speak)
    PHP_FUNCTION_ENTRY(ev3_speak_background)

    {NULL, NULL, NULL}
};


// Module
static zend_module_entry ev3php_module_entry = {
    STANDARD_MODULE_HEADER,
    "ev3php",
    ev3php_functions,
    PHP_MINIT(ev3php),
    NULL,
    NULL,
    NULL,
    NULL,
    EV3PHP_VERSION,
    STANDARD_MODULE_PROPERTIES
};
ZEND_GET_MODULE(ev3php)
