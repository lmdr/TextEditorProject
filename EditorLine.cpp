#include "EditorLine.h"

Editor::Line::Line(int start, int stop) :
  _Start(start),
  _Stop(stop)
{};

bool Editor::Line::IsPositionIn(int position) const
{
  return !(position < GetStartPosition() || GetStopPosition() <= position);
};

int Editor::Line::GetPositionOffset(int position) const
{
  return position - GetStartPosition();
};

int Editor::Line::GetStartPosition() const
{
  return _Start;
};

int Editor::Line::GetStopPosition() const
{
  return _Stop;
};