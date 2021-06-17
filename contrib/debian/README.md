
Debian
====================
This directory contains files used to package hempycoind/hempycoin-qt
for Debian-based Linux systems. If you compile hempycoind/hempycoin-qt yourself, there are some useful files here.

## hempycoin: URI support ##


hempycoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hempycoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hempycoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/hempycoin128.png` to `/usr/share/pixmaps`

hempycoin-qt.protocol (KDE)

