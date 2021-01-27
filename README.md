# README #

Hello!
I´m glad to see you have access to the Whammy Bombs Game!

![Screenshot01](https://bytebucket.org/insanertprogrammers/wam/raw/e71aae78b1212e813f723482e43ea9d7b456af21/Screenshot01.jpg)


### What is this repository for? ###

The Whammy Bombs Game (WAM) is a remake of the classic game Bomberman!
The entire game are being developed with Unreal 4 and C++ , i will be using this repository to store all te assets and code for the game.
I Hope you enjoy see the progress of the project and for any comment i will be avaliable for any question ok?

* Version
1.0

### How do I get set up? ###

All the code stored are using a .gitignore file removing unecessary Visual Studio files and Unreal Intermediate files, so basically
to install the code, just copy the WAM folder to the Unreal Project Files folder of your instalation configuration.
If necessary rebuild the project before open it in Unreal Editor.

All the project have a main purpose of mantain some classic characteristics of the original game, and build the entire game 
logic in C++ using Unreal only for complex and control stuff in blueprints.
So, as you will see in the code, many functions used to build the map and control the characters, are using custom C++ functions
being called directly thru Blueprints.

There is no plug-in being used except the standard C++ Libraries and the C++ Unreal Engine, so there is no third-party component that needs
be installed to compile and release the game.

There is no database yet for the game, but i expect have it when we have more functions on it.

To Run the tests, just use the Unreal execution tools as you want and see the results! ;)

The deployment of the game, are being used default deployment configurations of Unreal, since we are using native SO C++ code to 
mantain the core funtionality of the game.

### How can i Play it? ###

For now, the game have 2 players in a map, and only the keyboard can be used to play the Game where:

![Screenshot02](https://bytebucket.org/insanertprogrammers/wam/raw/dcd503c44cb26d4c3def410ffa8a1b35129c734e/Screenshot02.jpg)


* Player 01 Commands
Use the Arrow Keys Up,Down,Left,Right to walk with the player.
Use the Right Shift Key to place a Bomb.



* Player 02 Commands
Use the Keys T (Up),G (Down) ,F (Left) ,H (Right) to walk with the player.
Use the Left Shift Key to place a Bomb.

### Features of the Game ###

The project are in it´s initial states, but we already have a interesting list of features to show:

* Two Players Game
* Dinamic Map Creation
* Custom Functions and Structs for the game reducing the size of blueprints and increasing portability.
* All Game logic in a single Tick Level Event(Main Game Loop) with a single WAMGameStruct.
* A Low Level Map Management for the game thru a Unreal Library Access.
* A Custom AI for the game without use behaviour tree.

![Screenshot03](https://bytebucket.org/insanertprogrammers/wam/raw/a4345acc84871fb043003a71b3f5187da315bc5f/ScreenShot05.jpg)

### Who do I talk to? ###

* Insane RT Programmers - William D. Wolff - KnightMareWolff
* wolff@insaneframework.com.br or wolff@wdw.com.br