# PS4b: Checkers

## Contact
Name:       Thomas O'Connor
Section:    202
Time to Complete:   8 Hours


## Description
Created a Checkers game class that displays the default game configuration on startup.
Left click on pawns to select them during your turn indicated in the top left.
Right click to deselect pawns on your turn.
To move your selected pawn, click on the starred area to move and capture pawns.
Win by capturing all of your opponents pawns, or by making your opponent unable to move.

### Features
Created an initialize function that sets up the board in the default configuration
Created a mouseInGameBounds helper function that detects when the cursor is within
the bounds of the checkerboard arena, excluding the decorative border.
Created a selectPiece function that checks for the current player's turn,
and changes currentGameState memory to reflect selected pieces.
Created a visual move assist that stars moveable tiles based on selected pawn.
Crowns pieces in the last row using the finishLine function.
Detects victory and plays a fanfare.

### Memory
Used no smart pointers.
Used a 2D array to store game state.
Boolean variables for triggering actions:
playerTurn for keeping track of player turn.
stillPlaying to keep track of piece selection.
setWinTrue to automatically call win condition when unable to move

### Lambdas
Used algorithms at lines 70, 72, 77, 80 and 81.
The algorithms at lines 70, 72 and 77 are find_if algorithms that scan
through the 2D gamestate vector for the characters w or W.
The algorithms at lines 80 and 81 are distance algorithms that simply calculate the distance
from the beginning of the vector to the position of the iterator after it finds the specified character.

Used lambdas at lines 71, 72 and 77.
These lambdas are for the purpose of finding the specified character.
They return the row (vector of chars) or they return a bool (c == 'w' or c == 'W').

### Issues
Cannot multi-jump pieces.
Jumps are not required.
Occasionally textures flicker.

### Extra Credit
Added visual move assist for selected pawns using stars.
Added game border using wood texture.
Added deselect pawn feature (Right-Click).
Added restart game shortcut (R).
Added a close window shortcut (X).


## Acknowledgements
Dr. Daly's premade checkers pieces

Wood texture for border: Courtesy of rawpixel.com at
https://www.freepik.com/free-photo/walnut-wood-textured-background-design_18835083.htm#query=dark%20oak&position=1&from_view=keyword&track=ais

jbsweeno at https://tuna.voicemod.net/sound/90cfd1c7-d328-4340-b206-bfce0da29c42 for the victory sound

Paomedia at https://www.shareicon.net/star-94629#google_vignette for the star icon
