#ifndef EDITORLINEBREAKSTRATEGY_H
#define EDITORLINEBREAKSTRATEGY_H

#include <string>

namespace Editor {

class LineBreakStrategy {
public:
  virtual ~LineBreakStrategy() {};
  virtual std::string::iterator Compose(const std::string&, std::string::iterator, int) = 0;
};

class WholeWordLineBreak : public LineBreakStrategy {
public:
  std::string::iterator Compose(const std::string&, std::string::iterator, int);
};

}

#endif