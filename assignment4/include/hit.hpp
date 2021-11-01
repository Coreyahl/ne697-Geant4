#ifndef HIT_HPP
#define HIT_HPP
#include <iostream>
#include <vector>

namespace mc1d{
    struct hit{
        public:
            hit(int argc,char* argv[]);
            
            std::vector<int> hit_position; //column 1 of hit vector (position of interaction)
            std::vector<int> get_hit_position() const;
            std::vector<std::string> event; //column 2 of hit vector (type of interaction, a or s)
            std::vector<std::string> get_event() const;
            //std::vector<int> get_hits() const; //maybe try this without private variables
            //std::vector<std::vector<int>> hits(std::vector<int>hit_position,std::vector<std::string>event); //hits vector will be a vector of vectors (two columns)

        //private:
        //    std::vector<int> m_hit_position;

    };


}
#endif //ends the first statement of code (the if statement)