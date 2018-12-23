# All-Quiet-on-the-Western-Front
This was a project done for Computer Graphics (2017) course at Faculty of Mathematics, University of Belgrade, Serbia.

It is a simple two-player game implemented in C using OpenGL.

_The idea is to deal more damage to the opponent, which can be done by using the indicator at the bottom of the screen. There are three levels of damage that can be inflicted:_
* _**high** - center of green_
* _**medium** - greenish/reddish_
* _**low** - either side of red part of the bar_
___

## Requirements
* **OpenGL** -  Graphics rendering API used for this project
* **gcc** - Compiler system used for this project. Others may work as well.
* **make** - Build automation tool

**To install _OpenGL_, run in terminal:**

```$ sudo apt-get update```

```$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev```

**To install _gcc_ and _make_, run:**

```$ sudo apt-get install build-essential```

## Setting up
You can clone this project by copying its url, opening up your terminal and using it with `git clone <url>` command. Or just execute this command:
```$ git clone https://github.com/ajvazz/All-Quiet-on-the-Western-Front.git```.

Then, navigate to newly created folder, and then run _make_: 
`$ make` or `$ make mainProgram` to compile all files need for the game itself, and then run: 
```$ make mainMenu``` to compile main menu program.

Then, run `$ ./mainMenu` to start the game!

## Game Instructions
When you start the game, main menu presents options to the user to start or exit the game. Upon clicking `ENTER`, the game is started.
_**When it is opened, you are required to click `ENTER`, `G` or `g` to initialize animations!**_

The idea is to win in a gun duel between two weird, faceless cowboys in a town that is apparently to small for both of them. That can be done by dealing more damage to the opponent, using pinpoint precision and good timing :) The more cowboys are closer to death the more chaotic will the indicator move.

## Controls

| Button        | Action        |
| ------------- |:-------------:|
| `ENTER`       | start         |
| `ESCAPE`      | exit          |
| `G` or `g`    | initialize animations      |
| `SPACE`       | fire          |

## Known Bugs
After one player has finished his turn, the other player should wait for the opponent to put the gun down, then raise his. This process is automatic, but only when the indicator stars moving again should the next cowboy shoot. If not, the animation may be partly broken and the player won't be able to take his turn, thus making the game unplayable.

_Fortunately, this stupid bug occurs sometimes, even if the player (more often than not) intentionally wants to break the game._

# ENJOY!
