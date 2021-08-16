#include "EditorParser.h"
#include <iostream>

Editor::Parser::Parser(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cerr << "Usage: editor <filename>\n";
    std::exit(EXIT_FAILURE);
  }
  else
  {
    // check that argv[1] is a valid filename
    _Filename = argv[1];
  }
};

const std::string& Editor::Parser::GetFilename() const
{
  return _Filename;
};