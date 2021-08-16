#ifndef EDITORPAGE_H
#define EDITORPAGE_H

#include <utility>

namespace Editor {

class Page {
public:
  Page(int, int, int, int);
  bool IsLineIn(int, int);
  int GetStartParagraph() const;
  int GetStopParagraph() const;
  int GetStartLine() const;
  int GetStopLine() const;
private:
  std::pair<int, int> _Start,
  	_Stop;
};

}

#endif