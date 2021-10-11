#ifndef RUNMANAGER_HPP
#define RUNMANAGER_HPP
#include <iostream>
#include <vector>

namespace mc1d {
  class RunManager {
    public:
      RunManager(int track_length, float absorption, int scatter, int startposition); //declaration of the functions

      void run(int n_particles, int track_length, std::vector<int> hits);
      //void run(int n_particles, int track_length);

      void write_outputs(std::string filename, std::vector<int> values);

    private:
      int m_trackLength;
      float m_absorption;
      // TODO
  };
}

#endif
