#include "EditorComposableParagraph.h"

Editor::ComposableParagraph::ComposableParagraph() :
	_Lines()
{};

Editor::ComposableParagraph::ComposableParagraph(const Editor::ComposableParagraph& Other) :
  _Lines(Other._Lines)
{};

Editor::ComposableParagraph& Editor::ComposableParagraph::operator=(const Editor::ComposableParagraph& Other)
{
  _Lines = Other._Lines;
  return *this;
};

void Editor::ComposableParagraph::AddLine(const Editor::Line Line)
{
	_Lines.push_back(Line);
};

bool Editor::ComposableParagraph::IsPositionIn(int position, int line) const
{
  return (_Lines.begin() + line)->IsPositionIn(position);
};

const Editor::Line& Editor::ComposableParagraph::GetLine(int line) const
{
	return *(_Lines.begin() + line);
};

int Editor::ComposableParagraph::GetNumberLines() const
{
	return _Lines.size();
};

int Editor::ComposableParagraph::GetPositionOffset(int position, int line) const
{
  return (_Lines.begin() + line)->GetPositionOffset(position);
};

int Editor::ComposableParagraph::GetStartPosition(int line) const
{
  return (_Lines.begin() + line)->GetStartPosition();
};