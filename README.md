# CarBattlersParts

My attempts at recreating the game Car Battler Joe's elements

Car Battler Joe (激闘！カーバトラーGO！！ Gekitou! Car Battler Go!!) is a car battling video game for the Game Boy Advance, developed by Ancient and published by Natsume. The game involves using cars to fight opponents in action-styled battles, with role-playing video game game mechanics. It combined vehicular combat with action RPG elements in a similar manner to the earlier 1985 game Autoduel based on Car Wars, and later 2006 MMO game Auto Assault.

More information on the game [here](https://en.wikipedia.org/wiki/Car_Battler_Joe).

##Build steps

Make sure SFML is installed. If not, on Ubuntu, do:
`sudo apt-get install libsfml-dev`

Alternatively, put SFML into `ext/SFML-<version_no>` and change the `$(SFMLVER)` variable in the makefile. Make sure that SFML is compatible with your compiler version.

Then, build with:
```
cd <project to build>
make
```

