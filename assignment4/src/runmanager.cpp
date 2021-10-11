#include "runmanager.hpp"
#include <iostream>
#include <vector>
#include "particle.hpp"
#include "hit.hpp"
#include <fstream>
using namespace std;

namespace mc1d {
  //implementation of function that was declared in .hpp
  RunManager::RunManager(int track_length, float absorption, int scatter, int startposition): //calls runmanager member function in runmanager class
    m_trackLength(track_length),
    m_absorption(absorption),
    m_scatter(scatter),
    m_startposition(startposition)
  {
    cout << "Creating RunManager with track length = " << m_trackLength << ", and "
      << "starting point = "<< m_startposition << ", with an absorption probability = " << m_absorption 
      << ", and scatter probability = " << m_scatter << endl;
  }
  //implementation of function that was declared in .hpp
  //void hit::hit(std::vector<int> hit::get_hit_position() );

  void RunManager::run(int n_particles, int track_length, std::vector<int> hit_position, std::vector<std::string> event )
  //void RunManager::run(int n_particles, int track_length )
   {
    cout << "Running simulation with " << n_particles << " particles" << endl;
    
    for (int i = 0 ; i < n_particles ; i++) { //i loop iterates through each particle
      float rand_dir = float(rand())/float((RAND_MAX)); // rand_num in the range 0.1 to 1 -- (1-100)/100
      if (rand_dir > 0.5){ //if rand_num is   > 0.5, particle moves left
        for (int j = m_startposition ; j < track_length ; j++) { //j loop iterates the particle through positions
          float rand_num = float(rand())/float((RAND_MAX)); // rand_num in the range 0.1 to 1 -- (1-100)/100
          if ( (rand_num <= m_absorption + m_scatter) && (rand_num > m_absorption) ){
            hit_position.push_back(j);
            event.append('s'); //use append for strings
          }
          if (rand_num <= m_absorption){ //if rand_num is within absorp, it absorbs
            hit_position.push_back(j);
            event.append('a');
          break;
          //continue; if it meets condition, "continue" to the next j, or next loop, end this loop
          }  
        }
      }
      else {
        for (int j = m_startposition ; j > 0 ; --j ) {
          float rand_num = float(rand())/float((RAND_MAX));
          if ( (rand_num <= m_absorption + m_scatter) && (rand_num > m_absorption) ){
            hit_position.push_back(j);
            event.append('s');
          }
          if (rand_num <= m_absorption){
            hit_position.push_back(j);
            event.append('a');
          break;
          }
        }

      }
    //cout << "Number of events (hits) = " << hits.size() << endl;
    //cout << "Number of particles transmitted = " << n_particles - hits.size() << endl;
    std::ofstream myFile("hits.csv");
    for(int i = 0; i < hits.size(); ++i) {
        myFile << hits.at(i) << "\n";
    }
    // Close the file
    myFile.close();
    return;
  }
  //implementation of the function that was declared in the .hpp file
  void RunManager::write_outputs(std::string filename, std::vector<int> values) {
    // Make a CSV file with one column of integer values
    // filename - the name of the file
    // vals - an integer vector of values
    
    // Create an output filestream object
    std::ofstream myFile(filename);
    
    // Send data to the stream
    for(int i = 0; i < values.size(); ++i) {
        myFile << values.at(i) << "\n";
    }
    
    // Close the file
    myFile.close();
    return;
  }
}
