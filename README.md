
Outline

This project aim is to develop a set of C++ classes / data structures and algorithms that provide a high level OpenGL object/scene management for a simple 3D game, it also uses NGL and SDL libraries. The game idea is that the player must collect as many fruits as possible, scoring points in this way, till the player touches the bad fruit (red troll), then game terminates. 

Implementation

The way I have developed the final game was implementing the code from NGLLabs/Game/. The Fruit, Player, BadFruit, Walls, Empty are all created by using entity component system. This way the array is not needed to store all the empty places or other objects, but it refers to it as one object. In order to use strings as an identifier in the game in the beginning of Arena.cpp it is referred to each object of the class by const static char*. Void Arena::createDefaultObjects method creates new objects, the GameObject holds an abstraction to the object and, for instance, Player as it inherits from GameObject works as specialisation. 
I have added the Fruit and BadFruit by creating a separate Fruit.h, BadFruit.h and Fruit.cpp, BadFruit.cpp files and linked it in the Arena.cpp. The void Arena::update method has pointers to fruits position that is useful when it comes to collision. The collision happens when the player position is equal to fruit position. The game logic is that when the player touches the fruit it moves to another random position (newPosf/newPosbf). The random position is achieved by having a rand() function, however it is not truly random as when the program is executed multiple times, each time it picks the same positions. This is due to computer nature, but rand() could be perfected with an algorithm that takes a value that depends on a player actions. For instance, having the timing between two mouse clicks influence the random number array. This way, the fruit positions would differ each time since it is not only depending on the computer, but also on who is using it.

Another important collision detection that had to be implemented is when the fruit moves, it has to move only in empty area. This is solved with a while loop that keeps looping if the new position of the fruit is equal to the object Wall of the class ItemType. In this if statement that I include while loop there is a line to count the points, which is printed out in the console.
When the player moves, it stays static. To change that it rotates according to the direction it is going I have added four if statements in the Arena::update method that manipulates the angle which is used in Player.cpp with setRotation. 
To make the game more interesting I have created a BadFruit that is small red troll, which terminates the game when touches the player. The way it works is very similar to the fruit, but it changes position when the update count can be divided by 4. If the player touches it console prints out “GAME OVER” and the game terminates.
The last thing to adjust was the aesthetical side of the game. I have changed the colours of the shaders and checker shader, scaled the fruit, trolls, changed the position of the camera and depth of field.

Research

The sources I found very useful were the NCCA/NGLLabs on GitHub, which consisted most of my code. I have watched some YouTube videos by NVitanovic and Let’s Make Games channels that explain the snake game algorithms that are very similar to what I used to move the fruit. I found it very useful to watch someone creating a code from scratch and understand their logic.
To understand NGL library I have investigated the documentation on Bournemouth.ac.uk webpage. 
Gameprogrammingpatterns.com website has some useful information on object oriented programming and helps to understand its principles better.

Design

The idea of the game is that the player (troll) can walk around the arena by pressing up, down, left, right keyboard keys. The goal is to collect as many fruits as possible and score points. The game terminates if the player collides with the red troll that keep s changing its position. It can also terminate if the user press esc button.

The look of the game is to make it feel as if it is a night-time, the colour palette consist of different tones of blue making the arena look like it is lit by the moonlight. The fruit resembles little moons. The bad troll is red since the colour symbolises danger. 
The most used class is the Arena class, which store height, width, items has functions: draw, update, Arena, keyPressEvent, setItem. Arena class is linked to GameItem struct which is linked to GameObject and ItemType. Fruit, BadFruit, Player are linked to GameObject. RenderGlobals class is used in main.cpp and RenderGlobals.cpp.



Conclusion

By making this project I have gained some knowledge about object-oriented programming and could state it is more efficient than the procedural programming with c. I have discovered about the algorithms that could be implemented in a 3D game. I have learned how to code in c++ language using NGL, SDL libraries. Overall, I am quite happy with the result of the code. This game has a lot of room to become better and could be more ambitious, but regarding my aims of programming knowledge, which is to be able to read the code and understand the programming concepts, I feel as I have improved.  


References

En.wikipedia.org. 2020. Entity Component System. [online] Available at: <https://en.wikipedia.org/wiki/Entity_component_system> [Accessed 28 June 2020].

Macey, J., n.d. NGL (NCCA Graphics Library). [online] Nccastaff.bournemouth.ac.uk. Available at: <https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/> [Accessed 28 June 2020].

NVitanovic, 2015. C++ Tutorial 18 - Simple Snake Game. [online] YouTube. Available at: <https://www.youtube.com/watch?v=E_-lMZDi7Uw&t=541s> [Accessed 28 June 2020].

Nystrom, R., 2014. Game Programming Patterns. [online] Gameprogrammingpatterns.com. Available at: <https://gameprogrammingpatterns.com/> [Accessed 28 June 2020].

Tug.org. 2020. [online] Available at: <https://tug.org/pracjourn/2007-4/walden/color.pdf> [Accessed 28 June 2020].

Youtube.com. n.d. Youtube. [online] Available at: <https://www.youtube.com/user/creaper> [Accessed 28 June 2020].




