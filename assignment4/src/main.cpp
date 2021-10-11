#include "argparser.hpp"
#include "particle.hpp"
#include "hit.hpp"
#include "runmanager.hpp"
#include <iostream>
using namespace mc1d;
using namespace std;

int main(int argc, char* argv[]) {
  try {
    ArgParser arg_parser(argc, argv); //i dont understand this syntax or what its purpose is
    
    hit hit_(argc,argv); 

    RunManager run_manager(arg_parser.get_tracklength(), arg_parser.get_absorption(), arg_parser.get_scatter(), arg_parser.get_startposition());

    run_manager.run(arg_parser.get_num_particles(),arg_parser.get_tracklength(),hit_.get_hit_position(), hit_.get_event() );
    //run_manager.run(arg_parser.get_num_particles(),arg_parser.get_tracklength());

    //run_manager.write_outputs("hits.csv", hit_.get_hit_position());
  } 

  catch (invalid_argument const& ex) {
  cout << "Usage: ./mc2d [track length] [start position] [absorption] [scatter] [n particles]" << endl;
  //cout << "Maximum [track length]: " << ArgParser::MAX_TRACK_LENGTH << endl;
  cout << "Error: " << ex.what() << endl;
  }

  //mc1d::RunManager run(int n_particles, int track_length, std::vector<int> hit_position );

  //mc1d::RunManager write_outputs(std::string filename, std::vector<int> values);
  //write_outputs("hits.csv", hit_position() );
  //mc1d::RunManager write_outputs("hits.csv", hit_position);

  return 0;
}
