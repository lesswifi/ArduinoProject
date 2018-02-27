# ArduinoProject

![alt text](https://github.com/lesswifi/ArduinoProject/blob/master/IMG_5117.JPG)

For the Reverse-Engineer the Brain challenge, we had three main tasks. 

1. 
The robot should first be able to follow a black line to circle the continent and stop at a hash mark when 
it finishes circling the continent. There is a plastic brain at the center of the circle. To address the 
first task, QTI sensors were used. QTI sensors tell the difference between black and white surface, which 
allows the bot to follow the black line. For the line following task, it can be applied to robots transporting 
packages in factories in a fixed route. The robots will use engines instead of motors to run fast, and the 
space between QTI sensors have to be wide enough for thicker lines.

2. 
The bot then should be able to sense if there is a magnet existing under the brain. After knowing the answer 
for whether the magnet exists or not, the bot should send this answer to the whole team. For the second task 
to sense the magnet, the hall effect sensor was used at first but then was replaced by the compass module because 
of a much longer sensing range. For the magnet sensing, in the real world, the compass module is used to detect 
the direction, or where North is.The compass module can also be used in any circumstances that need to sense where 
the nearest magnetic field is.

3. 
Each robot should be able to communicate with other robots and sum up the numbers to collectively determine 
and display the “Next biggest” Grand Challenge according to the sum. For the third task to communicate, the XBee 
chip was used to communicate among the team and LCD was used for result display. Arduino code was uploaded into 
the bot for all the tasks. For XBee communication, any team of robots can communicate with each other and perform 
team tasks, such as a robot soccer team or a robot dancing team.

4. 
In the end, the whole team should perform a coordinated routine. By conducting this whole set of challenges, 
an investigation into how a BOE-bot can be tasked on both a hardware and software level to perform several crucial 
functions is launched.

