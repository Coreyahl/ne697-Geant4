#ifndef ARGPARSER_HPP //only if argparser component has not already been included
#define ARGPARSER_HPP //add the argparser header
namespace mc1d{
    class ArgParser{
        public:
            ArgParser(int argc,char* argv[]);

            int get_tracklength() const; //get track length
            float get_absorption() const; //get absorption probability
            int get_num_particles() const; //get number of particles
            int get_startposition() const; //get the starting position of particles
            float get_scatter() const; //get scatter cross section
            //these are constants, as in the functions are constants
            //they will be our getters
        private:
            int m_tracklength; //m is standard practice for private member variables
            float m_absorption;
            int m_nparticles;
            int m_startposition;
            float m_scatter;
    };


}
#endif //ends the first statement of code (the if statement)
