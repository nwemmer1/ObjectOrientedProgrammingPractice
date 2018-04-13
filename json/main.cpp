
#include "json.hpp"

#include <iostream>
#include <fstream>
#include <iterator>

int
main(int argc, char* argv[]) 
{
  if (argc < 2)
    return 1;
  
  // Read an input file into a string.
  std::ifstream ifs(argv[1]);
  std::istreambuf_iterator<char> first(ifs);
  std::istreambuf_iterator<char> last;
  std::string str(first, last);

  Value* val = parse(str);
  val->print();
}

//dont know what you wanted me to do on reddit, i think i did what i was supposed to but got confused when 
//you wanted me to go on reddit and get json stuff off of there.
