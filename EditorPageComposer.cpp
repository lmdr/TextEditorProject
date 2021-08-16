#include "EditorPageComposer.h"
#include "EditorController.h"
#include "EditorLineBreakStrategy.h"
#include "EditorModel.h"
#include "EditorView.h"
#include <iterator>

Editor::Page::Page(int paragraph, int position) :
  _paragraph(paragraph),
  _position(position)
{};

Editor::PageComposer::PageComposer(Editor::Controller& Controller) :
  _Controller(Controller),
  _LineBreakStrategy(new Editor::WholeWordLineBreak),
  _Pages(),
  _CurrentPage(_Pages.begin())
{};

Editor::PageComposer::~PageComposer()
{
  delete _LineBreakStrategy;
};

void Editor::PageComposer::Init()
{
  AddPage(0, 0);
  _CurrentPage = _Pages.begin();
  ComposePage();
};

void Editor::PageComposer::ComposePage()
{
  RecalculatePages();
  _Controller.GetView().InitRows();
  
  int remaining_lines = _Controller.GetView().GetRowNumInView();
  int document_it = _CurrentPage->_paragraph;
  int offset = _CurrentPage->_position;
  
  while(remaining_lines)
  {
    auto& paragraph = const_cast<std::string&>(_Controller.GetModel().GetLine(document_it));
    ++document_it;
    
    auto paragraph_start = paragraph.begin() + offset;
    offset = 0;
    
    while(remaining_lines && !(paragraph_start == paragraph.end()))
    {
      auto paragraph_stop = _LineBreakStrategy->Compose(_Controller, paragraph, paragraph_start);
      _LineBreakStrategy->AddRow(_Controller, paragraph_start, paragraph_stop);
      --remaining_lines;
      paragraph_start = paragraph_stop;
    }
    
    if(document_it == _Controller.GetModel().GetNumberLines())
      break;
  }
};

void Editor::PageComposer::NextPage()
{
  if(!(_CurrentPage == _Pages.end()))
    ++_CurrentPage;
};

void Editor::PageComposer::PrevPage()
{
  if(!(_CurrentPage == _Pages.begin()))
    --_CurrentPage;
};

void Editor::PageComposer::SetPage(int position, int paragraph)
{
  _CurrentPage = _Pages.begin();
  while(_CurrentPage->_paragraph < paragraph && !(_CurrentPage == _Pages.end() - 1))
    ++_CurrentPage;
  if(_CurrentPage->_paragraph == paragraph && position < _CurrentPage->_position)
    --_CurrentPage;
};

int Editor::PageComposer::GetParagraph() const
{
  int cursor_y = _Controller.GetView().GetCursorY();
  int current_paragraph = _CurrentPage->_paragraph;
  int x_offset = _CurrentPage->_position;
  int y_offset = 0;
  
  
  while(y_offset < cursor_y)
  {
    auto& paragraph_string = const_cast<std::string&>(_Controller.GetModel().GetLine(current_paragraph));
    
    auto paragraph_it = paragraph_string.begin() + x_offset;
    x_offset = 0;
    
    while(!(paragraph_it == paragraph_string.end()) && y_offset < cursor_y)
    {
      paragraph_it = _LineBreakStrategy->Compose(_Controller, paragraph_string, paragraph_it);
      ++y_offset;
    }
    
    if(y_offset != cursor_y)
      ++current_paragraph;
  }
  
  return current_paragraph;
};

int Editor::PageComposer::GetPosition() const
{
  int cursor_x = _Controller.GetView().GetCursorX();
  int cursor_y = _Controller.GetView().GetCursorY();
  int current_paragraph = _CurrentPage->_paragraph;
  int x_offset = _CurrentPage->_position;
  int y_offset = 0;
  std::string::iterator paragraph_begin,
                        paragraph_it;
  
  
  while(y_offset <= cursor_y)
  {
    auto& paragraph_string = const_cast<std::string&>(_Controller.GetModel().GetLine(current_paragraph));
    ++current_paragraph;
    
    paragraph_it = paragraph_string.begin() + x_offset;
    x_offset = 0;
    
    while(!(paragraph_it == paragraph_string.end()) && y_offset <= cursor_y)
    {
      paragraph_it = _LineBreakStrategy->Compose(_Controller, paragraph_string, paragraph_it);
      ++y_offset;
    }
  }
  
  return std::distance(paragraph_it, paragraph_it + cursor_x);
};

void Editor::PageComposer::SetCursor(int position, int paragraph)
{
  SetPage(position, paragraph);
  
  int y_offset = 0,
      x_offset = 0;
  int current_paragraph = _CurrentPage->_paragraph;
  int offset = _CurrentPage->_position;
  
  while(current_paragraph < paragraph)
  {
    auto& paragraph_string = const_cast<std::string&>(_Controller.GetModel().GetLine(current_paragraph));
    ++current_paragraph;
    
    auto paragraph_it = paragraph_string.begin() + offset;
    offset = 0;
    
    while(!(paragraph_it == paragraph_string.end()))
    {
      paragraph_it = _LineBreakStrategy->Compose(_Controller, paragraph_string, paragraph_it);
      ++y_offset;
    }
  }
  
  auto& paragraph_string = const_cast<std::string&>(_Controller.GetModel().GetLine(current_paragraph));
  auto paragraph_start = paragraph_string.begin();
  auto paragraph_stop = _LineBreakStrategy->Compose(_Controller, paragraph_string, paragraph_start);
  
  while(std::distance(paragraph_string.begin(), paragraph_stop) < position)
  {
    paragraph_start = paragraph_stop;
    paragraph_stop = _LineBreakStrategy->Compose(_Controller, paragraph_string, paragraph_start);
    ++y_offset;
  }
  
  x_offset = std::distance(paragraph_start, paragraph_string.begin() + position);
  
  _Controller.GetView().SetCursorX(x_offset);
  _Controller.GetView().SetCursorY(y_offset);
};

void Editor::PageComposer::RecalculatePages()
{
  int cursor_paragraph = GetParagraph();
  int cursor_position = GetPosition();
  
  _CurrentPage = _Pages.begin();
  _Pages.erase(_Pages.begin() + 1, _Pages.end());
  
  int lines = _Controller.GetView().GetRowNumInView();
  int remaining_lines = lines - 1;
  
  for(int document_it = 0; document_it < _Controller.GetModel().GetNumberLines(); ++document_it)
  {
    auto& paragraph = const_cast<std::string&>(_Controller.GetModel().GetLine(document_it));
    auto paragraph_it = paragraph.begin();
    
    while(!(paragraph_it == paragraph.end()))
    {
      paragraph_it = _LineBreakStrategy->Compose(_Controller, paragraph, paragraph_it);
      
      if(remaining_lines == 0)
      {
        AddPage(document_it, std::distance(paragraph.begin(), paragraph_it));
        remaining_lines = lines - 1;
      }
      else
        --remaining_lines;
    }
  }
  
  SetCursor(cursor_position, cursor_paragraph);
};

void Editor::PageComposer::AddPage(int paragraph, int position)
{
  _Pages.push_back(Editor::Page(paragraph, position));
};