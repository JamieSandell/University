[![](http://img.youtube.com/vi/wDhalbovFm8/0.jpg)](http://www.youtube.com/watch?v=wDhalbovFm8 "The Gibraltar Invasion")

The objective of this ACW is to develop a program using C++ in order to produce the following specification (depicted
in fig 1):
Minimum Specification (45%)
1. A display window consists of a cliff face (shown in green), the sea (shown in blue), and a cannon (shown on top
of the cliff).
2. The boat moves horizontally on the water from side to side in the window (e.g. from left to right, then right to
left, and so on).
3. The cannon’s elevation/pitch is controllable by using the up/down cursor keys.
15/02/2008 4
4. A cannonball can be fired from the cannon in the direction that the cannon is pointing by using the space bar. For this minimum specification, the cannon ball can travel in a straight line. The cannonball class must be extended from a base class called NewtonianObject.
5. The NewtonianObject class has at least a pure virtual function called Update(float dt). This function must be used to update the Cannonball’s position etc.
6. If the cannonball hits the ship then the ship will sink. At which point another ship will sail into view from one of the sides of the screen.
7. The program should use a clock so that there is processor independent animation. For example, the position of the cannonball per frame would equate to cannonBallPos += velocity*dt
8. You should also display a frames per second counter and also a timer which shows the amount of times that has elapsed since the program started.
9. The boat moves at random speeds as it moves across the water.
Bonus Specification (25%):
1. Provide the user with the ability to change the power of shot by using the left/right cursor keys. Also provide a visual system to show the user the power (e.g. display the power value as text, implement a power bar).
2. Add more realistic movement to the cannonball’s motion (modelling gravity etc).
3. Multiple boats based on a base Ship class containing virtual draw functions. For example two different ships.
Quality of Code (25%):
1. Design approach and class design (e.g. Object Orientated Design). Include a class diagram in the report (see below).
