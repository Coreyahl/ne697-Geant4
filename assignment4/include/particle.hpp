#ifndef PARTICLE_HPP
#define PARTICLE_HPP
namespace mc2d{
    class particle{
        public:
            particle(int argc,char* argv[]);

            bool get_alive() const; //get status of particle
            int get_position() const; //get position of particle
            //these are constants, as in the functions are constants
            //they will be our getters
        private:
            bool m_alive; //m is standard practice for private member variables
            int m_position;
    };


}
//class particle{
//        public:
//            bool alive {true}; //initialize the particle with a value true, as in it exists
//            int position = 0; //initialize the position of the particle as zero
//};

#endif //ends the first statement of code (the if statement)