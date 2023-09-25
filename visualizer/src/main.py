import sys
from operator import itemgetter
from exceptions import exceptions_handler, InvalidArgumentsNbr
from constants import SCREEN_WIDTH, SCREEN_HEIGHT, RED, GREEN, HILL
from classes import Game, Info, Room, Tunnel, Ant


def verify_input():
    if len(sys.argv) != 2:
        raise InvalidArgumentsNbr


def load_file() -> list[str]:
    loaded_file = []

    with open(sys.argv[1], "r") as file:
        for line in file:
            loaded_file.append(line[:-1])
    return loaded_file


def convert_input(info: Info, loaded_file: list[str]) -> None:
    info.number_of_ants = int(loaded_file[1])
    index = 3

    temp_rooms = {}
    temp_tunnels = []
    temp_ants = {str(nbr): [] for nbr in range(1, info.number_of_ants + 1)}

    color = HILL
    for line in loaded_file[index:]:
        index += 1
        if line == "##start":
            color = GREEN
            continue
        if line == "##end":
            color = RED
            continue
        if line == "#tunnels":
            break
        line = line.split(" ")
        temp_rooms[line[0]] = [int(line[1]), int(line[2]), color]
        color = HILL

    for line in loaded_file[index:]:
        index += 1
        if line == "#moves":
            break
        line = line.split("-")
        temp_tunnels.append((line[0], line[1]))

    min_bound = (max(list(temp_rooms.values()),
                     key=itemgetter(0))[0] + 0.000001)
    max_bound = (max(list(temp_rooms.values()),
                     key=itemgetter(1))[1] + 0.000001)
    for room_key, room_value in temp_rooms.items():
        room_value[0] = (int(room_value[0]) * SCREEN_WIDTH / min_bound)
        room_value[1] = (int(room_value[1]) * SCREEN_HEIGHT / max_bound)
        info.rooms.append(
            Room(room_key, room_value[0], room_value[1], room_value[2]))
        if room_value[2] == GREEN:
            info.start = (room_value[0], room_value[1])

    for tunnel in temp_tunnels:
        info.tunnels.append(Tunnel(
            start=(temp_rooms[tunnel[0]][0], temp_rooms[tunnel[0]][1]),
            end=(temp_rooms[tunnel[1]][0], temp_rooms[tunnel[1]][1])))

    for move_ind, line in enumerate(loaded_file[index:]):
        line = [i[1:].split("-") for i in line.split(" ")]
        for val in temp_ants.values():
            val.append(None)
        for i in range(len(line)):
            temp_ants[line[i][0]][move_ind] = line[i][1]

    for ant in temp_ants.items():
        for i, dest in enumerate(ant[1]):
            if dest is not None:
                ant[1][i] = tuple(temp_rooms[dest][0:2])
        info.ants.append(Ant(ant[0], ant[1], info.start))


def parse_input(info: Info):
    verify_input()
    loaded_file = load_file()
    convert_input(info, loaded_file)


@exceptions_handler
def main():
    print(f"Running with a width of {SCREEN_WIDTH}px"
          f" and a height of x{SCREEN_HEIGHT:0.0f}px")
    info = Info()
    parse_input(info)
    game = Game(info.ants)

    while game.running:
        game.clock.tick(60)
        game.listen_for_events()
        game.refresh_screen(info.rooms, info.tunnels)


if __name__ == "__main__":
    main()
