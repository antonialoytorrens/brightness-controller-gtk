# Brightness-Controller-GTK
A brightness controller written in gtk using the xbacklight property.
## Compile brightness-controller-gtk
gcc `pkg-config gtk+-3.0 --cflags` brightness.c -o brightness `pkg-config gtk+-3.0 --libs`
