# GameLauncher
game launcher is a tools for select and launch the game you want (steam library-like)

# BUILD
DEFAULT:\
  make

CLASSIC BOX:\
  make classic
  
use "make clean" for delete all useless file when you have finish

# DESCRIPTION
USAGE:\
	game_launcher [PATH]\

game launcher is a tools for select and launch the game you want (steam library-like)\
	- game config file (.gcf) are in the "game_config" directory and are made of:\
		- NAME: the name of the game | (not mandatory)\
		- DESC: a description of this game | (not mandatory)\
		- BIN_PATH: the path of the game binary (from his directory | (mandatory)\
		- EMU_BIN: the emulator binary (command) you want to use (like wine). If you don't need a emulator, just ignore this var | (not mandatory)\
	- game file are in the "game" directory, the game directory need to have the same name as his game config file (without the ".gcf")\
All this file have to be in "~/game_launcher/" directory or in the directory PATH\
You can create a .gcf file with a "add" command

the default version can have some character unknown by your computer, so use the classic box version.\

# SCREENSHOT
DEFAULT display:\
[DEFAULT display screenshot](screenshot/better.png)

CLASSIC BOX display:\
[CLASSIC BOX display screenshot](screenshot/classic.png)

adding a .gcf file:\
[adding a .gcf file screenshot](screenshot/add.png)
