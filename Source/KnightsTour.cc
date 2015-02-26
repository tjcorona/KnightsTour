#include <getopt.h>
#include <iostream>
#include <unistd.h>

#include "KTTypeDefs.hh"
#include "KTDisplay.hh"
#include "KTKnightGraph.hh"
#include "KTNeuralNetwork.hh"

using namespace KT;

int main(int argc,char** argv)
{
  std::string usage =
    "\n"
    "Usage: KnightsTour <options>\n"
    "\n"
    "This program searches for knight's tours using a neural network.\n"
    "\n"
    "\tAvailable options:\n"
    "\t -h, --help              (shows this message and exits)\n"
    "\t -f, --file              (set the file size of the puzzle)\n"
    "\t -r, --rank              (set the rank size of the puzzle)\n"
    "\t -i, --incomplete-tour   (allow an incomplete tour)\n"
    "\t -m, --max-iterations    (maximum # of iterations before restarting)\n"
    "\t -q, --frequency         (frequency in Hz of solution display)\n"
    ;

  static struct option longOptions[] = {
    {"help", no_argument, 0, 'h'},
    {"incomplete-tour", no_argument, 0, 'i'},
    {"file", required_argument, 0, 'f'},
    {"rank", required_argument, 0, 'r'},
    {"max-iterations", required_argument, 0, 'm'},
    {"frequency", required_argument, 0, 'q'},
  };

  static const char *optString = "hif:r:m:q:";

  gRank = 6;
  gFile = 6;

  bool requireFullTour = true;
  double frequency = 4.;
  unsigned maxIterations = 1.e5;

  while(1) {
    char optId = getopt_long(argc, argv,optString, longOptions, NULL);
    if(optId == -1) break;
    switch(optId) {
    case('h'): // help
      std::cout<<usage<<std::endl;
      return 0;
    case('i'):
      requireFullTour = false;
      break;
    case('f'):
      gFile = atoi(optarg);
      break;
    case('r'):
      gRank = atoi(optarg);
      break;
    case('t'):
      gRank = atoi(optarg);
      break;
    case('m'):
      maxIterations = atoi(optarg);
      break;
    case('q'):
      frequency = atof(optarg);
      break;
    default: // unrecognized option
      std::cout<<usage<<std::endl;
      return 1;
    }
  }

  KnightGraph graph;
  NeuralNetwork neuralNetwork;
  neuralNetwork.SetMaxIterations(maxIterations);
  Solution solution = neuralNetwork.FindTour(graph,requireFullTour);
  PrintSolution(solution,frequency);
  
  return 0;
}
