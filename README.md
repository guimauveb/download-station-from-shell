# Synology Download Station Command Line Interface (Work in progress) 

## Dependencies
- C++17
- libpqxx 7.3 
- ncurses 6.2 

## Synology DSM versions
- Currently in development for DSM 5.3 to 6.2

## Features
Working on creating a command line interface to manage Download Station on Synology NAS DSM via SSH. Inspired by Matthias Radig original code that is not working on DSM most recent versions and is unfortunately not maintained anymore.
Download station will be controllable via both command line arguments and interactively via a fully fledged ncurses interface.

## TODO
- Add support for torrents
- Use a vim like command bar to perform command line actions or use the ncurses menus (both in ncurses)
- Add support for packages
