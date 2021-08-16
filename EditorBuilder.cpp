#include "EditorBuilder.h"
#include "EditorComposer.h"
#include "EditorView.h"
#include <algorithm>
#include <iostream>

Editor::Builder::Builder() :
  _Pages(),
  _CurrentPage(0),
  _Height(0)
{
	_Pages.push_back(Editor::Page(0, 0, 1, 0));
};

void Editor::Builder::Init(const Editor::Composer& Composer, int height)
{
  std::cerr << "Before Composer Init() set height\n";
  _Height = height;
  std::cerr << "After Composer Init() set height\n";
  std::cerr << "Before Composer Init() create page\n";
  _Pages.push_back(CreatePage(Composer, 0, 0));
  std::cerr << "After Composer Init() create page\n";
};

void Editor::Builder::Build(const Editor::Composer& Composer, int position, int paragraph)
{
  int page_it = 0;
  while(!(_Pages.begin() + page_it)->IsLineIn(0, paragraph))
  {
    ++page_it;
    if(_Pages.begin() + page_it == _Pages.end())
    {
      auto start = FindStart(Composer, page_it);
      _Pages.push_back(CreatePage(Composer, start.first, start.second));
    }
  }
  _Pages.erase(_Pages.begin() + page_it, _Pages.end());
  
  *(_Pages.begin() + page_it) = CreatePage(Composer,
    (_Pages.begin() + page_it)->GetStartLine(),
    (_Pages.begin() + page_it)->GetStartParagraph());
};

void Editor::Builder::NextPage(const Editor::Composer& Composer)
{
  if(GetPage().GetStopParagraph() == Composer.GetNumberParagraphs() - 1 &&
    GetPage().GetStopLine() == Composer.GetNumberLines(Composer.GetNumberParagraphs() - 1))
    return;
  
  ++_CurrentPage;
  if(_Pages.begin() + _CurrentPage == _Pages.end())
  {
    auto start = FindStart(Composer, _CurrentPage);
    _Pages.push_back(CreatePage(Composer, start.first, start.second));
  }
};

void Editor::Builder::PrevPage()
{
  if(_CurrentPage)
    --_CurrentPage;
};

const Editor::Page& Editor::Builder::GetPage() const
{
  return *(_Pages.begin() + _CurrentPage);
};

int Editor::Builder::GetParagraph(const Editor::Composer& Composer, int cursor_x, int cursor_y) const
{
  int paragraph_it = (_Pages.begin() + _CurrentPage)->GetStartParagraph(),
    line_offset = (_Pages.begin() + _CurrentPage)->GetStartLine(),
    line_it = 0;
  
  while(line_it + Composer.GetNumberLines(paragraph_it) - line_offset < cursor_y)
  {
    line_it += Composer.GetNumberLines(paragraph_it) - line_offset;
    line_offset = 0;
    ++paragraph_it;
  }
  
  return paragraph_it;
};

int Editor::Builder::GetParagraphOffset(const Editor::Composer& Composer, int paragraph) const
{
  int paragraph_it = (_Pages.begin() + _CurrentPage)->GetStartParagraph(),
    line_offset = (_Pages.begin() + _CurrentPage)->GetStartLine(),
    line_it = 0;
  
  while(paragraph_it < paragraph)
  {
    line_it += Composer.GetNumberLines(paragraph_it) - line_offset;
    line_offset = 0;
    ++paragraph_it;
  }
  
  return line_it;
};

int Editor::Builder::GetPosition(const Editor::Composer& Composer, int cursor_x, int cursor_y) const
{
  int paragraph_it = (_Pages.begin() + _CurrentPage)->GetStartParagraph(),
    line_offset = (_Pages.begin() + _CurrentPage)->GetStartLine(),
    line_it = 0;
  
  while(line_it + Composer.GetNumberLines(paragraph_it) - line_offset < cursor_y)
  {
    line_it += Composer.GetNumberLines(paragraph_it) - line_offset;
    line_offset = 0;
    ++paragraph_it;
  }
  
  while(line_it < cursor_y)
    ++line_it;
  
  return Composer.GetStartPosition(line_it, paragraph_it) + cursor_x;
};

void Editor::Builder::SetCursor(Editor::View& View, const Editor::Composer& Composer, int position, int paragraph)
{
  _CurrentPage = 0;
  while(!(_Pages.begin() + _CurrentPage)->IsLineIn(position, paragraph))
  {
    ++_CurrentPage;
    if((_Pages.begin() + _CurrentPage) == _Pages.end())
    {
      auto start = FindStart(Composer, _CurrentPage);
      _Pages.push_back(CreatePage(Composer, start.first, start.second));
    }
  }
  
  int y_cursor = 0,
    paragraph_it = (_Pages.begin() + _CurrentPage)->GetStartParagraph(),
    line_offset = (_Pages.begin() + _CurrentPage)->GetStartLine();
  
  while(paragraph_it < paragraph)
  {
    y_cursor += Composer.GetNumberLines(paragraph_it) - line_offset;
    line_offset = 0;
    ++paragraph_it;
  }
  
  int line_it = 0;
  while(!Composer.IsPositionIn(position, line_it, paragraph))
  {
    ++y_cursor;
    ++line_it;
  }
  
  View.SetCursorX(Composer.GetPositionOffset(position, line_it, paragraph));
  View.SetCursorY(y_cursor);
};

Editor::Page Editor::Builder::CreatePage(const Editor::Composer& Composer, int start_line, int start_paragraph)
{
  int remaining_rows = _Height,
    paragraph_it = start_paragraph,
    line_offset = start_line,
    stop_line = line_offset;
  
  while(remaining_rows)
  {
    if(paragraph_it + 1 == Composer.GetNumberParagraphs() && stop_line + 1 == Composer.GetNumberLines(paragraph_it))
      break;
    
    stop_line = std::min(Composer.GetNumberLines(paragraph_it) - line_offset, remaining_rows);
    remaining_rows -= stop_line;
    ++paragraph_it;
  }
  
  return Editor::Page(start_line, start_paragraph, stop_line, paragraph_it);
};

std::pair<int, int> Editor::Builder::FindStart(const Editor::Composer& Composer, int page)
{
  if(!page)
    return std::pair<int, int>(0, 0);
  
  int paragraph_start = (_Pages.begin() + page - 1)->GetStopParagraph(),
    line_start = (_Pages.begin() + page - 1)->GetStopLine() + 1;
  
  if(Composer.GetNumberLines(paragraph_start) <= line_start)
  {
    ++paragraph_start;
    line_start = 0;
  }
  
  return std::pair<int, int>(line_start, paragraph_start);
};