# Rolling-Horizon Collision Resolution

Rolling-Horizon Collision Resolution (WHCR) is an efficient algorithm for solving lifelong Multi-Agent Path Finding where we are asked to plan collision-free paths for a large number of agents that are constantly engaged with new goal locations. WHCR calls a Windowed MAPF solver every `h` timestamps that resolves collisions only for the next `w` timestamps (`w >= h`).

### Dependence

* BOOST (https://www.boost.org)
* SFML (https://www.sfml-dev.org)

### Install

#### Debian / Ubuntu / Mint

```
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install libsfml-dev
```

#### ArchLinux

```
$ sudo pacman -S boost
$ sudo pacman -S sfml
```

### Run

```
$ cmake .
$ make
```
And then

```
$ ./main <map_file> <bfs | ...>
```

#### Example:

```
$ ./main ../tests/tests_scripts/map0.txt bfs
```

### Original article
https://aaai.org/AAAI21Papers/AAAI-563.LiJ.pdf
