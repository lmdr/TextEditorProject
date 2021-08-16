#ifndef EDITORPARSER_H
#define EDITORPARSER_H

#include <string>

namespace Editor {

class Parser {
public:
  Parser(int, char* []);
  const std::string& GetFilename() const;
private:
  std::string _Filename;
};

}

#endif