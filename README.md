# Brightness-Controller-GTK
A brightness controller written in gtk using the xbacklight (from acpilight program) property.
## Compile brightness-controller-gtk
<pre>gcc `pkg-config gtk+-3.0 --cflags` brightness.c -o brightness `pkg-config gtk+-3.0 --libs`</pre>
