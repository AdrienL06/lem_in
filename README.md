```
$$\                                     $$\   
$$ |                                    \__|  
$$ |      $$$$$$\  $$$$$$\$$$$\         $$\ $$$$$$$\  
$$ |     $$  __$$\ $$  _$$  _$$\        $$ |$$  __$$\ 
$$ |     $$$$$$$$ |$$ / $$ / $$ |       $$ |$$ |  $$ |
$$ |     $$   ____|$$ | $$ | $$ |       $$ |$$ |  $$ |
$$$$$$$$\\$$$$$$$\ $$ | $$ | $$ |       $$ |$$ |  $$ |
\________|\_______|\__| \__| \__|$$$$$$\\__|\__|  \__|
                                 \______|   
```

Grade : A🎖️ | Mark : 22/22

* [Description](#description)
* [Prerequisites](#prerequisites)
* [Installation](#installation)

## Description

- The game is about helping a group of ants cross from the entrance of an anthill to the exit.
- The goal of the game is to find the fastest way to get all the ants across to the exit.
- Each ant can only move once during each round.
- Ants must take the shortest path possible from their current room to an empty room, avoiding traffic jams.
- Only one ant can occupy each room, except for the `##start` and `##end`.
- Your job is to guide the ants through the anthill to the exit in the fewest rounds possible.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See [**program usage**](#program-usage) for notes on how to use the project after having it installed.

### Prerequisites

* `gcc`
* `make`
* `python3`
* `pygame`
* `perl` (not mandatory)

#### Fedora:

```
sudo dnf install gcc make
```

#### Ubuntu / Debian:

```
sudo apt-get install gcc make python3
```

#### Arch:

```
sudo pacman -S install gcc make python-pip
```

#### MacOs:

```
brew install gcc make python3
pip install pygame
```

### Installation

First, clone this repository and go into it :

```
git clone https://github.com/AdrienL06/lemin && cd lemin/
```

Compile the project:

```
make
```

## Program usage

Lem_in expects a map on [stdin](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) :

```
USAGE
    ./lem_in < maps/map.txt

DESCRIPTION
    < input redirection

    map.txt file containing the map with all the information to give on stdin
```

If you want to take a look at the documentation made with doxygen, go into the `doc` folder and type :

```
doxygen documentation
google-chrome html/index.html
```

`google-chrome` can be replaced with the browser of your choice.

### Generator

You can generate your own map using a perl script :

```
perl generator.pl taille densite nb > name_map.txt
```

## Visualizer

Python visualizer using pygame. It must take a valid Lem-in trace as its input. Any invalid trace will lead to undefined behavior.

```
USAGE
    python3 src/main.py maps/example.txt

DESCRIPTION
    example.txt file containing the output of a lem_in utilisation
```

| Key                   | Description                                                      |
| --------------------- | ---------------------------------------------------------------- |
| **Esc**         | Quit                                                             |
| **T**           | Toggle tunnels visibility                                        |
| **Space**       | Take a step forward in the simulation                            |
| **A**           | Toggle auto mode (only available at the start of the simulation) |
| **Left arrow**  | Decrease simulation speed                                        |
| **Right arrow** | Increase simulation speed                                        |

## Optimisation

parsing : to do

algorithm : to do

## Built With

* [C](https://en.wikipedia.org/wiki/C_(programming_language)) - Main language used
* [Python3](https://www.python.org/) - Main language used for the visualizer
* [Pygame](https://www.pygame.org/news) - Library used to built the visualizer
* [Doxygen](https://www.doxygen.nl/) - Used to generate the documentation in a website form

## Authors

* **Adrien Lachambre** - *algorithm & documentation* - [AdrienL06](https://github.com/AdrienL06)
* **Enzo Maltese** - *algorithm* - [EnzoMaltese](https://github.com/EnzoMaltese)
* **Virgile Legros** - *parsing & visualizer* - [Virgile-Legros](https://github.com/Virgile-Legros)
