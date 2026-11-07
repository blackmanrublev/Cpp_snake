#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(double _x, double _y, double _size, double _speed, double _number_of_particles, double _lifetime) : x(_x), y(_y), size(_size), cell_size(_size), number_of_particles(_number_of_particles), speed(_size * 10), lifetime(_lifetime)
        {
            for (int i = 0; i < number_of_particles; i++)
            {
                particles.push_back(Particle{x, y, size / 2});
            }
        }

        void ParticleEmitter::update(float dt)
        {
            if (emit == true) {
                if (timer < lifetime)
                {  
                    timer += dt;
                    for (int i = 0; i < number_of_particles; i++)
                    {
                        double angle = (i / number_of_particles) * 360;
                        double radians = angle * (pi / 180);

                        particles[i].x += (speed * dt) * std::cos(radians);
                        particles[i].y += (speed * dt) * std::sin(radians);

                    }
                }
                else
                {
                    timer = 0;
                    emit = false;
                }
            }
        }

        void ParticleEmitter::draw()
        {
            if (emit == true)
            {
                for (auto& particle : particles)
                {
                    DrawRectangle(particle.x + (size / 2 - particle.size / 2), particle.y + (size / 2 - particle.size / 2), particle.size, particle.size, Fade(RED, 1 - (timer / lifetime)));
                }
            }

        }

        void ParticleEmitter::emitParticles()
        {
            emit = true;
        }

        void ParticleEmitter::setX(double _x)
        {
            x = _x;
            for (auto& particle : particles)
            {
                particle.x = _x;
            }
        }
        
        void ParticleEmitter::setY(double _y)
        {
            y = _y;
            for (auto& particle : particles)
            {
                particle.y = _y;
            }
        }