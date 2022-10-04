#include "Sequencer.h"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
  if (argc < 2)
    {
      cout << "You are missing a data file." << endl;
      cout << "Expected usage ./proj3 proj3_case1.txt" << endl;
      cout << "File 1 should be a file with one or more DNA strands" << endl;
    }
  else
    {
      cout << endl << "***DNA Profiler***" << endl << endl;
      Sequencer D = Sequencer(argv[1]);
    }
  return 0;
}
