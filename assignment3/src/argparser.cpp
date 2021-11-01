#include "argparser.hpp" //include the header
#include <iostream>
#include <stdlib.h> //atof and atoi this may be redundant due to iostream but idk

namespace mc1d{
    ArgParser::ArgParser(int argc,char* argv[]) { //i dont understand this formatting
        //controlling input for command line arguments

        m_tracklength = std::atoi(argv[1]); //m_tracklength will be the first argument (argv[1])
        // taken from the command line... argv[0] is the program itself (mc1d)
        if(m_tracklength >= 100 || m_tracklength < 0) { //check if there is a valid input, throw an exception
            throw std::invalid_argument("Track Length is out of bounds, input 0-100");
        }

        m_absorption = std::atof(argv[2]); //atof for converting string to float (atoi is for integer)
        if(m_absorption > 1 || m_absorption <= 0) {
            throw std::invalid_argument("Absorption probability invalid, input 0-1");
        }

        m_nparticles = std::atoi(argv[3]);
        if(m_nparticles < 1) {
            throw std::invalid_argument("Invalid number of particles, input integer >=1");
        }

    }
    int ArgParser::get_tracklength() const { //these are our getters
        return m_tracklength;
    }
    float ArgParser::get_absorption() const {
        return m_absorption;
    }
    int ArgParser::get_num_particles() const {
        return m_nparticles; 
    }
}