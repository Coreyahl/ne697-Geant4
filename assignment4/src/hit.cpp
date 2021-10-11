#include "hit.hpp"
#include <iostream>

namespace mc1d{
    //hit::hit(int argc,char* argv[]) { //i dont understand this formatting
        //controlling input for command line arguments
    //    hits;
    //    hit_position;
    //    event;

    //}
    //std::vector<int> hit::get_hits() const { //these are our getters
        //return m_hit_position;
    //    return hit_position;
    //    return event; //doesnt work because event is a string type not int
    //}
    std::vector<int> hit::get_hit_position() const {
        return hit_position;
    }
    std::vector<std::string> hit::get_event() const {
        return event;
    }
}
