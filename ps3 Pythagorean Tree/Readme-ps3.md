# PS3: Pythagorean Tree

## Contact
Name:               Thomas O'Connor
Section:            202
Time to Complete:   5 Hours


## Description
Takes in a double lengthL and int depthN and draws a Pythagorean tree.
First square is lengthL x lengthL in dimension, with consecutive squares forming right triangles on top of previous squares.
Draws depthN iterations. 

### Features
Pretty light weight object - only contains the length and depth of the object.
The bulk of the implimentation is in the recursive draw function which takes 2 coordinate pairs
and draws new squares of appropriate size and rotation through depth 0.

### Issues
Had issues with finding new points of rotated squares after they were generated and drawn. I learned how to use the getGlobalBounds method to find the window-based coordinates of my placed squares, allowing me to calculate the new points based on rotation and distance from center.
Everything works as intended.

### Extra Credit
Not for extra credit, but added a shortcut (X) that closes the window
I use multiple colors at different levels of the tree


## Acknowledgements
None

