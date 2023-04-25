This makes print a text to png file
Usage is simple, example down bellow:
./app-static <name>.ttf <name>.png "sample text"

Fonts is keeped in /src/fonts
Png file will be created in the same directory,
where are you've been used it.

This app was made by libs: libpng, zlib, freetype;
May be you should clone zlib, freetype, libpng up-to-date versions.

This project created on Ubuntu 22.04

Makefile has different types of usage:
1. all
2. static
3. clean
4. clean-lib
5. dynamic
6. blob
7. libstatic
8. libdynamic

Directory lab1 tree:
. \n
├── app \n
│   └── main.c \n
├── build
│   ├── app-dynamic.bin
│   └── app-static.bin
├── freetype
│   ├── include
│   │   └── freetype2
│   │       ├── freetype
│   │       │   ├── config
│   │       │   └── *.h
│   │       └── *.h
│   ├── lib
│   └── src
├── libpng
│   ├── include
│   ├── lib
│   └── src
├── libs
│   ├── dynamic
│   └── static
├── Makefile
└── zlib
  

