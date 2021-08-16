#include "EditorApplication.h"
#include "EditorParser.h"

int main(int argc, char *argv[])
{
  Editor::Parser parser(argc, argv);
  
  Editor::Application app(parser.GetFilename());
  
  std::exit(EXIT_SUCCESS);
}