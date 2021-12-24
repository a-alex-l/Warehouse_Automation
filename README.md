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
$ cd build/
$ cmake .
$ make main
```
And then

```
$ ./main <map_file> <bfs | cbs | ca_star>
```
### Settings

You can change the algorithm parameners in file `constansts.h`
* TASKS_COUNT - count of tasks
* ROBOTS_COUNT - count of agents
* HORIZON - count of steps for calc
* RECULC_PERIOD - how often we will recacl strategy

#### Example:

* Example maps in `/tests/tests_scripts/`

```
$ ./main ../tests/tests_scripts/map0.txt cbs
```

#### cbs VS ca_star:

https://user-images.githubusercontent.com/40340659/147300353-c58499dd-3bf8-4ada-b59c-4dbd6c277577.mp4

### Original article
https://aaai.org/AAAI21Papers/AAAI-563.LiJ.pdf
