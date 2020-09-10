# Brightness-Controller-GTK
A Brightness Controller written in GTK3 using xbacklight (from acpilight program) property.
Note: You have to manually set permissions on /sys/class/backlight/ manually.
Run: 
<pre>$ sudo chmod -R 777 /sys/class/backlight/</pre>
or if you want to set it up automatically on startup using a service (openrc, for example):
<pre>cat > /etc/local.d/enable-backlight.start << "EOF"
#!/bin/sh
/bin/chmod -R 777 /sys/class/backlight/
EOF</pre>
## Compile brightness-controller-gtk
<pre>gcc `pkg-config gtk+-3.0 --cflags` brightness-controller-gtk.c -o brightness-controller-gtk `pkg-config gtk+-3.0 --libs`</pre>
