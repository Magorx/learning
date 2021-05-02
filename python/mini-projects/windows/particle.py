from random import randint
from vector import *
from color import *

class Particle():
    def __init__(self, world, coords, movement, color, livetime=-1):
        self.world = world
        self.coords = coords
        self.movement = movement
        self.color = color
        self.livetime = livetime
    
    def tick(self):
        self.livetime -= 1
        if not self.livetime:
            self.delete()
            return

        self.movement(self)
    
    def delete(self):
        del self.world.tickable[self.world.tickable.index(self)]
        del self.world.particles[self.world.particles.index(self)]


class ParticleSource():
    def __init__(self, world, coords, color_min, color_max, movement_logic, particles_per_tick=1, particles_per_spawn=1, particles_livetime=10000000):
        self.world = world
        self.coords = coords
        self.color_min = color_min
        self.color_max = color_max
        self.particles_per_tick = particles_per_tick
        self.particles_per_spawn = particles_per_spawn
        self.particles_livetime = particles_livetime
        self.movement_logic = movement_logic
        
        self.particle_generation_counter = 0
    
    def spawn_particle(self):
        color = color_from_limit(self.color_min, self.color_max)
        movement = self.movement_logic
        p = Particle(self.world, self.coords.cp(), movement, color, self.particles_livetime)
        self.world.tickable.append(p)
        self.world.particles.append(p)
    
    def spawn_particles(self):
        for _ in range(self.particles_per_spawn):
            self.spawn_particle()
    
    def tick(self):
        self.particle_generation_counter += self.particles_per_tick
        for _ in range(int(self.particle_generation_counter // 1)):
            self.spawn_particles()
        self.particle_generation_counter = self.particle_generation_counter % 1

def fire(self):
    if randint(1, 100) < 90:
        if randint(1, 100) < 10 * (10 - self.livetime):
            self.coords.y -= 2
        else:
            self.coords.y -= 1
    else:
        self.coords.z += 2
    if randint(1, 100) > 80 - (10 - self.livetime) * 3:
        self.coords.x += randint(-1, 1)