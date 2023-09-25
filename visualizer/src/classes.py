from typing import Any

import pygame
from constants import SCREEN_WIDTH, SCREEN_HEIGHT, DIM, GROUND, BLUE

GLOBAL_SPEED = 200


class Info:
    def __init__(self) -> None:
        self.number_of_ants: int = 0
        self.rooms: list(Room) = []
        self.tunnels: list(Tunnel) = []
        self.ants: list[Ant] = []
        self.start: Room = None


class Room():
    def __init__(self, name: str, x: int, y: int, color: tuple[int]):
        self.name = name
        self.shape = pygame.Rect((x - DIM / 2, y - DIM / 2, DIM, DIM))
        self.color = color


class Tunnel():
    def __init__(self, start: tuple[int | Any, Any | int],
                 end: tuple[int | Any, Any | int]) -> None:
        self.start = start
        self.end = end


class Circle():
    def __init__(self, center: tuple[int, int], radius: int):
        self.center = center
        self.radius = radius


class Ant():
    def __init__(self, nbr, moves, start: tuple[Any, Any]):
        self.nbr = nbr
        self.moves = moves
        self.pos = [start[0], start[1]]
        self.next_pos = [0, 0]
        self.to_travel = [0, 0]
        self.speed = [0, 0]
        self.is_moving = False

    def set_distance(self):
        self.to_travel = self.next_pos[0] - \
            self.pos[0], self.next_pos[1] - self.pos[1]

    def set_speed(self):
        self.speed = self.to_travel[0] / \
            GLOBAL_SPEED, self.to_travel[1] / GLOBAL_SPEED

    def move(self):
        self.to_travel = self.to_travel[0] - \
            self.speed[0], self.to_travel[1] - self.speed[1]
        self.pos = self.pos[0] + self.speed[0], self.pos[1] + self.speed[1]


class Game:
    def __init__(self, ants: list[Ant]) -> None:
        pygame.init()
        self.MOVE_ANT_EVENT = pygame.USEREVENT + 1
        pygame.time.set_timer(self.MOVE_ANT_EVENT, 10)
        self.width = SCREEN_WIDTH
        self.height = SCREEN_HEIGHT
        self.running = True
        self.clock = pygame.time.Clock()
        self.screen = pygame.display.set_mode((self.width, self.height))
        self.ants: list[Ant] = ants
        self.are_ants_moving = False
        self.delay = GLOBAL_SPEED
        self.can_activate_auto = True
        self.auto_mode = False
        self.draw_tunnels = True

    def set_ant_state(self):
        for ant in self.ants:
            if not ant.moves:
                self.running = False
                break
            ant.next_pos = ant.moves.pop(0)
            if ant.next_pos is not None:
                ant.set_distance()
                ant.set_speed()
            self.are_ants_moving = True
            self.delay = GLOBAL_SPEED - 1

    def move_all_ants(self):
        if self.are_ants_moving:
            if self.delay == 0:
                global GLOBAL_SPEED
                self.delay = GLOBAL_SPEED
                self.are_ants_moving = False
            for ant in self.ants:
                if ant.next_pos is not None:
                    ant.move()
            self.delay -= 1

    def listen_for_events(self) -> None:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    self.running = False
                if event.key == pygame.K_t:
                    self.draw_tunnels = not self.draw_tunnels
                if event.key == pygame.K_RIGHT:
                    global GLOBAL_SPEED
                    if GLOBAL_SPEED > 5:
                        GLOBAL_SPEED -= 5
                if event.key == pygame.K_LEFT:
                    GLOBAL_SPEED += 5
                if self.can_activate_auto and event.key == pygame.K_a:
                    print("Auto mode activated")
                    self.auto_mode = True
                    self.are_ants_moving = True
                if not self.are_ants_moving and not self.auto_mode and event.key == pygame.K_SPACE:
                    print("Stepping into the simulation")
                    self.can_activate_auto = False
                    self.set_ant_state()

            if event.type == self.MOVE_ANT_EVENT:
                self.move_all_ants()

            if self.auto_mode and not self.are_ants_moving:
                self.set_ant_state()

    def refresh_screen(self, rooms: list[Room], tunnels: list[Tunnel]) -> None:
        self.screen.fill(GROUND)
        if self.draw_tunnels:
            for tunnel in tunnels:
                pygame.draw.line(self.screen, (0, 0, 0),
                                 tunnel.start, tunnel.end, 1)
        for room in rooms:
            pygame.draw.rect(self.screen, room.color, room.shape)
            pygame.draw.rect(self.screen, (0, 0, 0), room.shape, 3, 3)
        for ant in self.ants:
            if ant.pos is not None:
                pygame.draw.circle(self.screen, BLUE,
                                   (ant.pos[0], ant.pos[1]), 10)
        pygame.display.flip()
