# PS2b: Sokoban

## Contact
Name:               Thomas O'Connor
Section:            202
Time to Complete:   20 hours

## Description
Reads in a text file and generates a graphic window with the Sokoban level. 
Gameplay controls (W, A, S, D, Up, Left, Down, Right, R, X, Z).
Player controls Janitor that can push boxes around a map.
The player wins when every box is placed into a storage location.

### Features
Chose to impliment game storage structure in row-major order.
This is how the program reads the file char by char,
so it made sense for me to leave it in that implimentation.
Created a seperate vector of directions called face.
This is used in combination with the turn variable to store the
direction the janitor is facing turn by turn.

### Memory
Data structure: 3D vector of chars.
2D vector for storing single game states,
3rd vector for storing consecutive turns.
Did not use smart pointers.

### Algorithms and Lambdas
Included find_if algorithm at line 22 of Sokoban.cpp.
This algorithm checks for the win condition (No empty storage locations).
Included any_of algorithm at line 23 of Sokoban.cpp.
This algorithm checks for specific criterion in a single line (any 'A' or '2').
Included lambda at line 23 of Sokoban.cpp.
Passes a vector of chars as a parameter (one game line) and applies above algorithm.
Included lambda at line 24 of Sokoban.cpp.
Passes a single character as a parameter (one game piece) and checks for any 'A' or '2'.

### Issues
Janitor is unable to push stored boxes out of storage areas.
Stored boxes turn blue and act as walls.
Occasionally, textures flicker.

### Extra Credit
Implimented an elapsed-time clock in the upper-left hand side of the screen
Janitor turns to face direction of movement
Implimented a sound on win screen, along with completion time
Included previous turn command (Z)
Included close window command (X)
Included restart game command (R)

## Acknowledgements
Kenney Vleugels for the Sokoban pack
jbsweeno at https://tuna.voicemod.net/sound/90cfd1c7-d328-4340-b206-bfce0da29c42 for the victory sound