# Othello
It was initially an Othello game written in C using on minimax algorithm at depth up to 6. It includes some recursive call but it is mainly for the increment of depth.
This program once reached #6 on UofT APS105(Computer Fundamentals) lab8 reversi Leaderboard...

I remade this game in C++ using Qt to embody my codes with a GUI which allows human-human and human-computer matches with ab-pruning and some run-time optimization. Now it's faster and more efficient!

#### If you are new to QT and you are a student, you can request QT's [educational license](https://www.qt.io/qt-educational-license) here!
## Deployment

To deploy this project on your computer, you can either:

```sh
git clone https://github.com/GaryZhous/Othello <your project file>
```

or download the released source code and build the project after installing Qt Designer
## Content
### main.cpp
This file contains the terminal-based C++ version of the original Othello game, which you can play directly from the command line without a UI.
### othello_qt
This directory contains the version of the game with a Qt-based GUI. You'll need to open and build it in Qt Designer to enjoy the enhanced visual experience.


![](https://github.com/GaryZhous/Othello/blob/main/othello.gif)
