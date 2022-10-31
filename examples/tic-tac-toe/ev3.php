<?php
/*
ev3php Tic-Tac-Toe
Copyright (C) 2022 Lukas Tautz
*/
ev3_lcd_start();
ev3_button_start();
function drawField($x, $y, $type) {
    $x = 39 + $x * 35;
    $y = 12 + $y * 35;
    ev3_lcd_rectangle($x, $y, 35, 35);
    switch ($type) {
        case 1:
            ev3_lcd_circle_filled($x + 17.5, $y + 17.5, 10);
            break;
        case 2:
            ev3_lcd_line($x + 7.5, $y + 7.5, $x + 27.5, $y + 27.5);
            ev3_lcd_line($x + 27.5, $y + 7.5, $x + 7.5, $y + 27.5);
    }
}
function drawFields($fields) {
    ev3_lcd_clear();
    drawField(0, 0, $fields[0]);
    drawField(1, 0, $fields[1]);
    drawField(2, 0, $fields[2]);
    drawField(0, 1, $fields[3]);
    drawField(1, 1, $fields[4]);
    drawField(2, 1, $fields[5]);
    drawField(0, 2, $fields[6]);
    drawField(1, 2, $fields[7]);
    drawField(2, 2, $fields[8]);
    $winner = 0;
    if ($fields[0] != 0 && $fields[0] == $fields[1] && $fields[1] == $fields[2]) $winner = $fields[0];
    if ($fields[0] != 0 && $fields[0] == $fields[4] && $fields[4] == $fields[8]) $winner = $fields[0];
    if ($fields[0] != 0 && $fields[0] == $fields[3] && $fields[3] == $fields[6]) $winner = $fields[0];
    if ($fields[1] != 0 && $fields[1] == $fields[4] && $fields[4] == $fields[7]) $winner = $fields[1];
    if ($fields[2] != 0 && $fields[2] == $fields[5] && $fields[5] == $fields[8]) $winner = $fields[2];
    if ($fields[2] != 0 && $fields[2] == $fields[4] && $fields[4] == $fields[6]) $winner = $fields[2];
    if ($fields[3] != 0 && $fields[3] == $fields[4] && $fields[4] == $fields[5]) $winner = $fields[3];
    if ($fields[6] != 0 && $fields[6] == $fields[7] && $fields[7] == $fields[8]) $winner = $fields[6];
    if ($winner != 0) {
        // A player has won!
        if ($winner == 1) {
            ev3_speak(LANG_EN, 'Circle won!');
            ev3_lcd_clear();
            ev3_lcd_normal(0, 5, 'Circle won!');
        } else {
            ev3_speak(LANG_EN, 'Cross won!');
            ev3_lcd_clear();
            ev3_lcd_normal(0, 5, 'Cross won!');
        }
        sleep(10);
        startTicTacToe();
    } else {
        if ($fields[0] != 0 && $fields[1] != 0 && $fields[2] != 0 && $fields[3] != 0 && $fields[4] != 0 && $fields[5] != 0 && $fields[6] != 0 && $fields[7] != 0 && $fields[8] != 0) {
            // Nobody won
            ev3_speak(LANG_EN, 'Nobody won!');
            ev3_lcd_clear();
            ev3_lcd_normal(0, 5, 'Nobody won!');
            sleep(10);
            startTicTacToe();
        }
    }
}
function drawPos($pos, $fields) {
    if ($pos == 0) { $x = 0; $y = 0; }
    else if ($pos == 1) { $x = 1; $y = 0; }
    else if ($pos == 2) { $x = 2; $y = 0; }
    else if ($pos == 3) { $x = 0; $y = 1; }
    else if ($pos == 4) { $x = 1; $y = 1; }
    else if ($pos == 5) { $x = 2; $y = 1; }
    else if ($pos == 6) { $x = 0; $y = 2; }
    else if ($pos == 7) { $x = 1; $y = 2; }
    else if ($pos == 8) { $x = 2; $y = 2; }
    $x = 56.5 + $x * 35;
    $y = 29.5 + $y * 35;
    drawFields($fields);
    if ($fields[$pos] == 1) ev3_lcd_circle_filled($x, $y, 3, false);
    else ev3_lcd_circle_filled($x, $y, 3);
}
function startTicTacToe() {
    $fields = [
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    ];
    drawPos(0, $fields);
    $pos = 0;
    $curPlayer = 1;
    while (true) {
        if (ev3_button_pressed(BUTTON_BACK)) exec('shutdown now'); // Shutdown
        else if (ev3_button_pressed(BUTTON_CENTER)) {
            if ($fields[$pos] != 0) continue;
            $fields[$pos] = $curPlayer;
            drawPos($pos, $fields);
            if ($curPlayer == 1) $curPlayer = 2;
            else $curPlayer = 1;
            while (ev3_button_get_pressed() != false);
        }
        else if (ev3_button_pressed(BUTTON_RIGHT)) {
            if ($pos < 8) $pos++;
            drawPos($pos, $fields);
            while (ev3_button_get_pressed() != false);
        }
        else if (ev3_button_pressed(BUTTON_LEFT)) {
            if ($pos > 0) $pos--;
            drawPos($pos, $fields);
            while (ev3_button_get_pressed() != false);
        }
        else if (ev3_button_pressed(BUTTON_UP)) {
            if ($pos > 2) $pos = $pos - 3;
            drawPos($pos, $fields);
            while (ev3_button_get_pressed() != false);
        }
        else if (ev3_button_pressed(BUTTON_DOWN)) {
            if ($pos < 6) $pos = $pos + 3;
            drawPos($pos, $fields);
            while (ev3_button_get_pressed() != false);
        }
    }
}
startTicTacToe();
