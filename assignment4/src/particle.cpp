#include "particle.hpp"
#include <iostream>

namespace mc2d{
    particle::particle(int argc,char* argv[]) { //i dont understand this formatting
        //controlling input for command line arguments
        m_alive = true;

        m_position = 0;

    }
    bool particle::get_alive() const { //these are our getters
        return m_alive;
    }
    int particle::get_position() const {
        return m_position;
    }

}
