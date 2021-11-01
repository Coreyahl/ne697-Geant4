#ifndef HIT_HPP
#define HIT_HPP
#include <iostream>
#include <vector>

namespace mc1d{
    struct hit{
        public:
            hit(int argc,char* argv[]);
            
            std::vector<int> get_hit_position() const; //maybe try this without private variables
            std::vector<int> hit_position;

        //private:
        //    std::vector<int> m_hit_position;

    };


}
#endif //ends the first statement of code (the if statement)