#include "hit.hpp"
#include <iostream>

namespace mc2d{
    hit::hit(int argc,char* argv[]) { //i dont understand this formatting
        //controlling input for command line arguments

        //m_hit_position;
        hit_position;

    }
    std::vector<int> hit::get_hit_position() const { //these are our getters
        //return m_hit_position;
        return hit_position;
    }
}
