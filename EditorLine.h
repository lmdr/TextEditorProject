#ifndef EDITORLINE_H
#define EDITORLINE_H

#include <string>

namespace Editor {

class Line {
public:
  Line(int, int);
  bool IsPositionIn(int) const;
  int GetPositionOffset(int) const;
  int GetStartPosition() const;
  int GetStopPosition() const;
private:
  int _Start,
      _Stop;
};

}

#endif