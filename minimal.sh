#!/bin/sh
# ev3php minmal installer
# Copyright (C) 2022 Lukas Tautz
EV3PHP_PLUGIN_URL=https://github.com/lukastautz/ev3php/releases/download/ev3php-1.0/ev3php.so
apt update
echo "ev3php is installed!" >> /etc/motd
echo "PermitRootLogin yes" > /etc/ssh/sshd_config
sudo service sshd restart
apt install php7.0-cli -y
systemctl stop bluetooth
systemctl stop brickman
systemctl stop ev3-bluetooth
systemctl disable bluetooth
systemctl disable brickman
systemctl disable ev3-bluetooth
mkdir /ev3php
cd /ev3php
mkdir php
cp -r /usr/lib/php/20151012/*.so /ev3php/php
cd php
rm opcache.so sysvmsg.so sysvshm.so phar.so sysvsem.so shmop.so exif.so gettext.so pdo.so tokenizer.so
cd ..
rm -r /usr/lib/php
rm -r /etc/php/7.0
mkdir /etc/php/7.0
mkdir /etc/php/7.0/cli
echo "[PHP]" > /etc/php/7.0/cli/php.ini
echo "engine = On" >> /etc/php/7.0/cli/php.ini
echo "short_open_tag = Off" >> /etc/php/7.0/cli/php.ini
echo "precision = 14" >> /etc/php/7.0/cli/php.ini
echo "zlib.output_compression = Off" >> /etc/php/7.0/cli/php.ini
echo "implicit_flush = On" >> /etc/php/7.0/cli/php.ini
echo "serialize_precision = 17" >> /etc/php/7.0/cli/php.ini
echo "zend.enable_gc = On" >> /etc/php/7.0/cli/php.ini
echo "expose_php = Off" >> /etc/php/7.0/cli/php.ini
echo "max_execution_time = 0" >> /etc/php/7.0/cli/php.ini
echo "max_input_time = 600" >> /etc/php/7.0/cli/php.ini
echo "memory_limit = 56M" >> /etc/php/7.0/cli/php.ini
echo "error_reporting = E_ALL & ~E_DEPRECATED & ~E_STRICT" >> /etc/php/7.0/cli/php.ini
echo "display_errors = On" >> /etc/php/7.0/cli/php.ini
echo "display_startup_errors = On" >> /etc/php/7.0/cli/php.ini
echo "log_errors = Off" >> /etc/php/7.0/cli/php.ini
echo "report_memleaks = On" >> /etc/php/7.0/cli/php.ini
echo "track_errors = Off" >> /etc/php/7.0/cli/php.ini
echo "html_errors = Off" >> /etc/php/7.0/cli/php.ini
echo "variables_order = \"SE\"" >> /etc/php/7.0/cli/php.ini
echo "register_argc_argv = On" >> /etc/php/7.0/cli/php.ini
echo "auto_globals_jit = On" >> /etc/php/7.0/cli/php.ini
echo "post_max_size = 1" >> /etc/php/7.0/cli/php.ini
echo "default_charset = \"UTF-8\"" >> /etc/php/7.0/cli/php.ini
echo "enable_dl = On" >> /etc/php/7.0/cli/php.ini
echo "file_uploads = Off" >> /etc/php/7.0/cli/php.ini
echo "allow_url_fopen = On" >> /etc/php/7.0/cli/php.ini
echo "allow_url_include = On" >> /etc/php/7.0/cli/php.ini
echo "default_socket_timeout = 60" >> /etc/php/7.0/cli/php.ini
echo "[CLI Server]" >> /etc/php/7.0/cli/php.ini
echo "cli_server.color = On" >> /etc/php/7.0/cli/php.ini
echo "[Extensions]" >> /etc/php/7.0/cli/php.ini
echo "extension_dir = \"/ev3php/php\"" >> /etc/php/7.0/cli/php.ini
echo "extension=calendar.so" >> /etc/php/7.0/cli/php.ini
echo "extension=fileinfo.so" >> /etc/php/7.0/cli/php.ini
echo "extension=iconv.so" >> /etc/php/7.0/cli/php.ini
echo "extension=json.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=simplexml.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=dom.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=readline.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=posix.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=sockets.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=ftp.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=ctype.so" >> /etc/php/7.0/cli/php.ini
echo "; extension=gd.so ; You have to execute 'apt install php7.0-gd'" >> /etc/php/7.0/cli/php.ini
echo "; extension=curl.so ; You have to execute 'apt install php7.0-curl'" >> /etc/php/7.0/cli/php.ini
echo "extension=ev3php.so" >> /etc/php/7.0/cli/php.ini
ln /etc/php/7.0/cli/php.ini /ev3php/php/php.ini
echo 200 > /sys/bus/iio/devices/trigger0/sampling_frequency
systemctl mask systemd-journald.socket
systemctl mask systemd-journald.service
systemctl mask systemd-logind.service
echo "[Unit]" > /etc/systemd/system/ev3php.service
echo "Description=ev3php interface" >> /etc/systemd/system/ev3php.service
echo "After=multi-user.target" >> /etc/systemd/system/ev3php.service
echo "StartLimitIntervalSec=0" >> /etc/systemd/system/ev3php.service
echo "[Service]" >> /etc/systemd/system/ev3php.service
echo "Type=simple" >> /etc/systemd/system/ev3php.service
echo "User=root" >> /etc/systemd/system/ev3php.service
echo "WorkingDirectory=/ev3php" >> /etc/systemd/system/ev3php.service
echo "ExecStart=/bin/sh -c \"sleep 60;php ev3.php 2>&1 >> stdout.txt\"" >> /etc/systemd/system/ev3php.service
echo "Restart=always" >> /etc/systemd/system/ev3php.service
echo "[Install]" >> /etc/systemd/system/ev3php.service
echo "WantedBy=multi-user.target" >> /etc/systemd/system/ev3php.service
echo '#!/bin/sh' > /bin/ev3
echo 'sudo systemctl stop ev3php' >> /bin/ev3
echo 'sudo pkill php' >> /bin/ev3
echo 'cd /ev3php' >> /bin/ev3
echo 'sudo php ev3.php' >> /bin/ev3
chmod 555 /bin/ev3
wget -O /ev3php/php/ev3php.so "$EV3PHP_PLUGIN_URL"
echo "<?php ev3_lcd_start(); exec('hostname -I', \$data); ev3_lcd_normal(0, 10, \$data[0]); ev3_button_start(); for (;;) { if (ev3_button_pressed(BUTTON_BACK)) { exec('shutdown now'); } elseif (ev3_button_pressed(BUTTON_CENTER)) { ev3_speak(LANG_EN, 'My IP is ' . \$data[0]); }}" >> /ev3php/ev3.php
chmod -R 777 /ev3php
rm /etc/systemd/system/getty.target.wants/getty@tty1.service
systemctl daemon-reload
systemctl enable ev3php
reboot now
