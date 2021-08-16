#include "EditorComposer.h"
#include "EditorDocument.h"
#include "EditorLine.h"
#include "EditorLineBreakStrategy.h"
#include <iterator>

Editor::Composer::Composer() :
  _LineBreakStrategy(new Editor::WholeWordLineBreak),
  _ComposableParagraphs(),
  _Width(1)
{};

void Editor::Composer::Init(const Editor::Document& Document, int width)
{
  _Width = width;
  for(int paragraph = 0; paragraph < Document.GetNumberParagraphs(); ++paragraph)
  	Compose(Document, paragraph, true);
};

void Editor::Composer::Compose(const Editor::Document& Document, int paragraph, bool insert)
{
  Editor::ComposableParagraph composable;
	
	auto paragraph_string = Document.GetParagraph(paragraph);
	
	auto line_start = paragraph_string.begin();
	do
	{
		auto line_stop = _LineBreakStrategy->Compose(paragraph_string, line_start, _Width);
		composable.AddLine(Editor::Line(std::distance(paragraph_string.begin(), line_start),
		                                std::distance(paragraph_string.begin(), line_stop)));
		line_start = line_stop;
	} while(!(line_start == paragraph_string.end()));
	
	if(insert)
		_ComposableParagraphs.insert(_ComposableParagraphs.begin() + paragraph, composable);
	else
		*(_ComposableParagraphs.begin() + paragraph) = composable;
};

void Editor::Composer::RemoveParagraph(int paragraph)
{
  _ComposableParagraphs.erase(_ComposableParagraphs.begin() + paragraph);
};

bool Editor::Composer::IsPositionIn(int position, int line, int paragraph) const
{
  return (_ComposableParagraphs.begin() + paragraph)->IsPositionIn(position, line);
};

const std::string Editor::Composer::GetLine(const std::string& paragraph_string, int line, int paragraph) const
{
  return std::string(paragraph_string.begin() + (_ComposableParagraphs.begin() + paragraph)->GetLine(line).GetStartPosition(),
    paragraph_string.begin() + (_ComposableParagraphs.begin() + paragraph)->GetLine(line).GetStopPosition());
};

int Editor::Composer::GetNumberLines(int paragraph) const
{
  return (_ComposableParagraphs.begin() + paragraph)->GetNumberLines();
};

int Editor::Composer::GetNumberParagraphs() const
{
  return _ComposableParagraphs.size();
};

int Editor::Composer::GetPositionOffset(int position, int line, int paragraph) const
{
  return (_ComposableParagraphs.begin() + paragraph)->GetPositionOffset(position, line);
};

int Editor::Composer::GetStartPosition(int line, int paragraph) const
{
  return (_ComposableParagraphs.begin() + paragraph)->GetStartPosition(line);
};