# L-systems

This project houses work done for university on l-systems and fractals.

## What it does

Currently, the program will load in a specific file, and its adjacent '.rules' file and present it at a static length
to the user.

The l-system works as expected for edge-rewriting based rules.

## What you will need to run it

- SDL2
- Linux (Should also work on Mac and Windows, but only tested on Linux)
- GCC/G++ (You can just edit the Makefile if you use another compiler)

## Known issues

- The output can be a bit noisy at shorted lengths
- All values are static and cannot be adjusted unless edits are made via code
