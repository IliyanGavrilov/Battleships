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
		2. Map size - [5 - 20]
        3. Should player repeat turn after successful hit? - 1. Yes 2. No
        4. Game mode - 1. Singleplayer 2. Multiplayer
            Game mode = 1:
                5. Bot difficulty - 1. Easy 2. Medium 3. Hard 4. Impossible
            Difficulty != 4:
                6. Can bot cheat - 1. Yes 2. No

		7. Amount of ships to place with size 2
		8. Amount of ships to place with size 3
		9. Amount of ships to place with size 4
		10. Amount of ships to place with size 5
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

# Algorithms used
## Computer sink a hit ship
The Medium and Hard difficulty computer tries to sink a ship fully if it has hit one. First the algorithm checks if there are any hit tiles
after that it locates the first hit tile's coordinates and tries to go in every vertical and horizontal direction (because the ships are
straight) going top, down, right left. The algorithm tries going into each of those directions in that order until it has reached the end
of the map or that direction has already been fully checked (a.k.a the next tile in that direction is a missed shot tile or a sunken ship
tile). Then it goes to check the next direction and iterates through all directions until the ship is fully sunken before ending the
algorithm and making normal shots.
## Computer parity shot
An effective strategy in Battleships is to not shoot every single tile on the map, because that wouldn't be effective. Instead, the player
should try to shoot every n tiles where n is the smallest ship size left. For example if the smallest ship left is with size 3 the player
should shoot every 3 tiles and leave 2 space vertical and horizontal gaps and that way he's still guaranteed the hit the smallest ship, and
it would be a way faster method then just shooting at every single tile on the map.
The Hard difficulty computer also does this by finding the smallest ship that is still not sunk/hit and then shoots every n tiles. So  if
the smallest ship size left is 2, computer would shoot at the first, third, fifth, seventh, etc. tile on every odd numbered column
and shoot at the second, fourth, sixth, eight, etc. tile on every even numbered column.
## Computer rigged randomness
If the rigged randomness (can computer cheat) setting is enabled the computer has a 10% chance to hit any ship directly instead of making
a random guess (or parity shot for Hard difficulty computer). This chance increases by 15% each time the computer shoots and misses and
resets back to 10% if it has successfully hit a ship. This algorithm is achieved by a static variable and an array of all ship tiles.