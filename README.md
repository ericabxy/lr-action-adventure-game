# LR Action Adventure Game

![Latest example screenshot.]('LR Action Adventure Game-260828-160032.png')

_LR Action Adventure Game_ is a LibRetro core inspired by Warren Robinett's 1980 game _Adventure_.

## Building

You can obtain _LR Action Adventure Game_ from the Git repository at Github or Gitlab using a command-line interface.

    git clone https://github.com/ericabxy/lr-action-adventure-game

Enter the root folder and run GNU Make.

    cd lr-action-adventure-game
    make

Run the generated core using RetroArch.

    retroarch -L action_adventure_game_libretro.so

If you are going to push changes to the repository, clean up after the build process.

    make clean
