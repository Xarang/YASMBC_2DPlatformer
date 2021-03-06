# YASMBC

authors : @francois.te,  @jerome.tchan, @victor.coatalem

## Introduction

**Yet Another Super Meat Boy Clone** (shortened as **YASMBC** for the remainder of this file) is a game made in 38 hours for EPITA's *Rush C* project. As the name indicates, it is a platforming game inspired by *Super Meat Boy* by Team Meat and as such, features similar gameplay mechanics (such as wall jumps for example). As of today some of the function are POSIX and therefore not supported by Windows. Sorry about that.

## Build

### Requirements

- gcc
- SDL2 (`sdl2, sdl2_image, sdl2_mixer`)

### Instructions

After cloning the repository, run the following command in the repository's root:
```make
make
```
A binary called `main` should be created at the root of the repository.

## Usage

Run `./main` to launch the game.

### Controls

- `LeftArrow`: Move left
- `RightArrow`: Move right
- `UpArrow` or `Space`: Jump
- `Shift`: Sprint
- `P`: Pause the game
- `R`: Restart the current level
- `Escape`: Quit the game

After finishing a level (when the fanfare plays), press `Enter` to go to the next one.

### How to win (or die)

The goal of the game is to reach the finish block (represented by a metal block) without touching any of the enemies (saws) or falling into the void. Each death will make you respawn to the starting point.

### Map format

Map files follow the specification described below:
```
[Width of the map]
[Height of the map]
[Starting point X]
[Starting point Y]
[Map description (see below)]
[Number of enemies]
[Enemies description (see below)]
```
- Map description is the section that describes the blocks in the map. This section should have `height` lines and each line should have `width` columns. Each character corresponds to one block in the map and the following characters can be used:
    - `.`: void (air)
    - `#`: block
    - `$`: ice block (you cannot perform a wall jump on them)
    - `S`: stone
    - `R`: rock
    - `L`: mossy rock
    - `F`: finish block
  
  Please note that blocks, stones, rocks and mossy rocks have the exact same behaviour.
- Enemy description should follow the following format:
  ```
  {
      [Enemy ID] (always 1)
      [Position X]
      [Position Y]
      [Size W]
      [Size H]
      [Speed X]
      [Speed Y]
  }
  ``` 
  The indentation should be 4 spaces. There must be as many enemy descriptions as the number of enemies declared.
## Sources

- Musics:
    - ☆ さくらなみきのかぜ ☆ by #ねここ14歳 (fether, Yamajet, ねこみみ魔法使い)
    - ピアノ協奏曲第１番"蠍火"（なんでも吸い込むピンク色のための） by fether

- Sound effects:
    - Jump sound from Sonic
    - Pause sound from Super Mario Bros.
    - Win sound from Final Fantasy VII
    - Death sound from Super Meat Boy

- Sprites:
    - Blocks and background from Super Meat Boy

## Features

- Character movements
- Jumps (the longer you hold the jump button, the higher you jump)
- Wall jumps
- Sprint (hold `Shift`)
- Quick restart (by pressing `R`)
- Quick exit (by pressing `Esc`)
- Pause (~~and pause buffer is a feature~~)
- Music and SFXs
- Enemies (moving and static ones)
- Falling into the void detection
- Win detection (it plays a fanfare when winning)
- Sprites
- Custom map format
- Different types of blocks with different behaviours (You cannot wall jump on ice blocks and they are also more slippery)
- Fancy physics overall
- Map switching after winning
- Saw animations (and red splatters on them when dying)
