# Battleships

A simple console application made in C++ without much OOP. 
[More about battleships](https://en.wikipedia.org/wiki/Battleship_(game)#Description)

## Installation
You can run the game directly on Windows using battleships.exe.

You can also compile the game yourself using Makefile or CMakeLists or gcc, gpp, g++ directly.

## How to play
### 1. Input Guide (input settings)

	1. Game Type - 1. New game 2. Load game from file
	Game Type = 1:
		2. Should player repeat turn after successful hit? - 1. Yes 2. No
		3. Map size - [5 - 20]
		4. Amount of ships to place with size 2
		5. Amount of ships to place with size 3
		6. Amount of ships to place with size 4
		7. Amount of ships to place with size 5
		8. Game mode - 1. Singleplayer 2. Multiplayer
		Game mode = 1:
			9. Bot difficulty - 1. Easy 2. Medium 3. Hard 4. Impossible
			Difficulty != 4:
				Can bot cheat - 1. Yes 2. No
    Game Type = 2:
        Enter file name . . .
	Map Type - 1. Custom 2. Load from file 3. Random
	Map Type = 1:
		Enter ship coords . . .
    Map Type = 2:
        Enter file name . . .
	Save map to file? - 1. Yes 2. No
    SaveToFile = 1:
        Enter file name . . .

### 2. Gameplay guide
#### 2.1 Map tiles meaning
	~ - Water
	O - Miss
	X - Hit
	@ - Sunk
#### 2.4 Singleplayer (vs computer)
There are 4 computer difficulties:
- Easy - Computer shoots randomly
- Medium - Computer shoots randomly until a ship is hit. If a ship is hit the computer tries to sink the ship fully before going for 
random shots again.
- Hard - Computer shoots every n tiles where n is the size of the smallest ship. If a ship is hit it tries to sink it fully.
- Impossible - Computer shoots your ship tiles without missing. Only way to defeat the computer is to not miss a single shot. Good luck!

##### Computer randomness:
If the option for computer "cheating" is enabled the computer has a 10% chance to directly hit one of your ships. Each time the computer
misses the chance to directly hit one of your ships goes up by 15% until a ship is hit and the chance resets back to 10%.
#### 2.3 Gameplay
Players take turns inputting coordinates in the format [letter number]. The number is the x-axis coordinate and the letter is the y-axis 
coordinate. If one of the players hits a ship and the option for repeating turn after a successful hit has been enabled, the player repeats
his turn by shooting another tile.

The game starts off with Player 1's turn and prints Player 2's map hiding the ship locations and also prints how many ships of each type
(size) are left on the opponent's field. Player 1 must input his shot coordinates and try to hit Player 2's ships. After entering a valid 
shot coordinate (if the show was inside the map and the shot tile has not been shot before) the screen will be cleared and 2 boards will be
printed - the left one is the opponent's board before the shot and the right one is the one after the shot. Then if the shot was a hit and
the option for repeating turn was enabled the player goes again. Otherwise, it's Player 2's turn. After Player 2's turn the game will ask
if you would like to save the game state and quit or continue playing. The game ends when one of the players successfully sinks all the
opponent's ships.