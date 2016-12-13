# c335-finalproject

This is the final project for CSCI-C335 at Indiana University. 

##About the course
C335 will explore how programs written in a high level language are evaluated by a processor to control the physical world. This semester we will be using a laboratory based upon the STM32 (ARM Cortex-M4) processor and utilizing off-the-shelf modules -- these and many other modules are readily available from on-line suppliers. We will use "C" to write programs to control these modules including an LCD display, a serial interface, a Wii Nunchuk, and an audio amplifier. In the process we will touch topics covered in a number of subsequent CS classes including compilers, operating systems, computer architecture, and digital design. It's obvious that we will be skimming the surface of these topics; for example, we will examine what a compiler and its associated tools (assembler, linker) do in some detail, but not how they are implemented to perform their function. My goal is that at the end of this course every student will be able to explain, in a technically accurate manner, the path from program to I/0 and will be proficient in using one representative set of tools to write programs to control a defined physical world. The progression of experiments introduces embedded system programming, programmed I/O, common protocols including async serial, SPI, and I2C; A/D based sensors, interrupts, and DMA.

##About the project

####Develop a video game that incorporates the concepts and devices learned in the course. This game should incorporate the following devices:

    LCD
    Audio
    User Input (1 or more device)
    Nunchuk
    Board Accel, Gyro, or Mag
    SD Card

This is an opportunity to demonstrate your mastery of the lab material along with your creativity. Hopefully you will have some fun as well!
####Scoring and what to turn in

    Final Project Description (final_project.txt) TEAM submits one version of this file.
    Description of game concept and core functionality [10]
    Task Breakdown between partners for the project [5] Note: A project of this complexity should have at least 5 tasks and likely more than 10

    SUB-TOTAL [15]
    Lab Report (report.txt) EACH PARTNER SUBMITS OWN, UNIQUE VERSION. Properly formatted
    Describe each of the tasks that you were responsible for performing and how each contributed to the overall project. [15]
    What technical challenges did you encounter in completing your tasks? [5]
    What would you do differently if you could start the project over? [5]

    SUB-TOTAL [25]
    Video Game Application
    Game Play Demonstrated [20]
    Utilizes the I/O devices listed above [20]
    Creativity and Technical Merit [20]

    SUB-TOTAL [60]
    Final Project TOTAL [100]


###Very Informative Multiple-choice (VIM) Quiz
This is a head to head quiz based game. 5 questions (out of a total of
15 possible questions) are served to the players. Point values are
determined by stopping the spinning LED lights using the user button,
where each color has a point value (Green: 100, Blue: 50, Orange: 0, Red: -50.
The first player to respond to the question, is the only answer accepted.
If that player got the question correct, they get to use the point spinner
to get points. If that player got the question incorrect, their opponent
gets to use the spinner to get points. 
The player with the most points at the end of the game wins.  

The games primarily uses the board's LCD screen (displaying images). 
User input is gathered via 2 Nunchuks and the user button.
The gyro is used to maintain orientation on the menus (but not the
questions). Audio is played as a accessory when point values are granted. 
The SD card holds all of the images/questions and audio files.
```
  Tasks:  Getting 2 Nunchuks to work 
          Initial commit (gathering, verifying, and commenting previous files)
          Adaptation of gyro for orientation
          Image creation
          Audio file conversion
          Question writing & Game flow creation
          Implementation of game flow 
          LED spinning scoring portion
          Pair programming
```

###Below are the game questions we have:
```
What material was the first mouse made of?
A. Copper
B. Ivory
C. Wood 
D. Plastic

Which of the Seven Dwarfs wears glasses?
A. Doc 
B. Grumpy
C. Happy
D. Sleepy 

What is the 211th most popular name in the United States?
A. Chuck
B. Sean
C. Devin
D. Andre

How many US states border West Virginia?
A. 3
B. 6
C. 4
D. 5 

What year was banner advertisment on Websites introduced?
A. 1994 
B. 1996
C. 1988
D. 1999

What was the first registered domain name?
A. Altavista.com
B. 1.com
C: a.com
D. Symbolics.com 

What was the most common Web broswer in 1996?
A. Lynx
B. Internet Explorer
C. Netscape Navigator 
D. Opera

How many times does the average computer user blink per minute?
A. 5 times
B. 7 times 
C. 12 times
D. 19 times

What actor once had a pet Octopus?
A. Sean Connery
B. Nick Cage 
C. Chuck Norris
D. Kevin Bacon

What is an adult male duck called?
A. Duck
B. Duckling
C. Drake 
D. Swan

If you had pogonophobia what would you be afraid of?
A. Pogo sticks
B. Beards
C. Pong, the video game
D. Birds

In the pilot episode of "Walker, Texas Ranger", who did Jimmy Trivette  tell Cordell Walker was his childhood TV inspiration for his law enforcement career?
A. John Reid xx
B. Clarence Gilyard
C. Chuck Norris
D. Alex Gage

What color is the sky?
A. Cobalt
B. Midnight blue
C. Baby blue
D. Sky blue 

Who is Cleveland, Ohio named after?
A. George Washington
B. Jonathan Clevington
C. Moses Cleveland 
D. Steve McCleve

What video game character was the first one to jump?
A. Mario
B. Metroid
C. Donkey Kong 
D. Sonic
```
