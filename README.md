# VRD
Very random dungeon. A text-based rogue-like with RPG elements about a novice knight, an endless dungeon and defeating a dragon.

- the game works in a command line window.
- there are no additional requirements for the game.
- the game has a cheat code similar to GOD MODE (makes the character much stronger than all opponents). To activate in the move menu, enter G as a command and press Enter.
- there is an option to buy items from the NPC "Goblin-Merchant", it can be found randomly in the dungeon.
- the battle takes place automatically.

# How to build (win/mac/linux)

You can compile "main.c" with any C compiler, but for convenience I wrote simple "CMakeLists.txt" file.

For visual studio (to reduce size of .exe):

```
cmake -B build
cmake --build build --config Release
```

For others:

```
cmake -B build
cmake --build build
```
	
# How to build (DOS)

Just convert "main.c" to ANSI encoding and compile it for example in GCC under DOS.

For launch in DOS you may need cwsdpmi (DOS extender). 

You can download it from here: http://sandmann.dotster.com/cwsdpmi/

# How to run game

Just run the executable file suitable for your system in terminal/command prompt.
