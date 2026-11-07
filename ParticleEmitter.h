#pragma once

#include <vector>
#include <cmath>
#include "raylib.h"

const double pi = 3.14159265358979323846;

struct Particle
{
    double x;
    double y;
    double size;
};

class ParticleEmitter
{
    std::vector<Particle> particles;
    double x;
    double y;
    double size;
    double cell_size;
    double speed;
    double number_of_particles;
    double lifetime;
    double timer;
    bool emit;

    public:
        ParticleEmitter(double _x, double _y, double _size, double _speed, double _number_of_particles, double _lifetime);

        void update(float dt);

        void draw();

        void emitParticles();

        void setX(double _x);
        
        void setY(double _y);
};