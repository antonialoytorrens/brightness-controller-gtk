# Brightness-Controller-GTK
A Brightness Controller written in GTK3 using xbacklight (from acpilight program) property.
## Compile brightness-controller-gtk
<pre>gcc `pkg-config gtk+-3.0 --cflags` brightness.c -o brightness `pkg-config gtk+-3.0 --libs`</pre>
