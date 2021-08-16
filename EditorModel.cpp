#include "EditorModel.h"
#include "EditorLine.h"
#include "EditorPage.h"
#include "EditorView.h"
#include <iostream>

Editor::Model::Model() :
  _Builder(),
  _Composer(),
  _Document()
{};

void Editor::Model::Init(int width, int height)
{
  std::cerr << "Before Composer Init()\n";
  _Composer.Init(_Document, width);
  std::cerr << "After Composer Init()\n";
  std::cerr << "Before Builder Init()\n";
  _Builder.Init(_Composer, height);
  std::cerr << "After Builder Init()\n";
};

void Editor::Model::Draw(Editor::View& View)
{
  View.InitRows();
  
  auto page = _Builder.GetPage();
  int line_offset = page.GetStartLine(),
    paragraph_it = page.GetStartParagraph();
  
  while(paragraph_it < page.GetStopParagraph())
  {
    const auto paragraph_string = GetParagraph(paragraph_it);
    ++paragraph_it;
    int line_it = line_offset;
    line_offset = 0;
    
    while(line_it < _Composer.GetNumberLines(paragraph_it))
      View.AddRow(_Composer.GetLine(paragraph_string, line_it, paragraph_it));
  }
  
  const auto stop_paragraph_string = GetParagraph(paragraph_it);
  int stop_line_it = 0;
  
  while(stop_line_it <= page.GetStopLine())
    View.AddRow(_Composer.GetLine(stop_paragraph_string, stop_line_it, paragraph_it));
};

void Editor::Model::InsertCharacter(int position, int paragraph, char character)
{
	_Document.InsertCharacter(position, paragraph, character);
	_Composer.Compose(_Document, paragraph);
	_Builder.Build(_Composer, position, paragraph);
};

void Editor::Model::RemoveCharacter(int position, int paragraph)
{
  _Document.RemoveCharacter(position, paragraph);
  _Composer.Compose(_Document, paragraph);
  _Builder.Build(_Composer, position, paragraph);
};

void Editor::Model::AddParagraph(const std::string& paragraph_string)
{
  _Document.AddParagraph(paragraph_string);
  _Composer.Compose(_Document, _Document.GetNumberParagraphs(), true);
  _Builder.Build(_Composer, 0, 0);
};

void Editor::Model::InsertParagraph(int position, int paragraph)
{
  _Document.InsertParagraph(position, paragraph);
  _Composer.Compose(_Document, paragraph, true);
  _Builder.Build(_Composer, position, paragraph);
};

void Editor::Model::RemoveParagraph(int paragraph)
{
  _Document.RemoveParagraph(paragraph);
  _Composer.RemoveParagraph(paragraph);
  _Composer.Compose(_Document, paragraph - 1);
  _Builder.Build(_Composer, 0, paragraph);
};

void Editor::Model::NextPage()
{
  _Builder.NextPage(_Composer);
};

void Editor::Model::PrevPage()
{
  _Builder.PrevPage();
};

const std::string Editor::Model::GetLine(int line, int paragraph) const
{
  return _Composer.GetLine(_Document.GetParagraph(paragraph), line, paragraph);
};

const std::string& Editor::Model::GetParagraph(int paragraph) const
{
  return _Document.GetParagraph(paragraph);
};

int Editor::Model::GetParagraph(const Editor::View& View) const
{
  return _Builder.GetParagraph(_Composer, View.GetCursorX(), View.GetCursorY());
};

int Editor::Model::GetPosition(const Editor::View& View) const
{
  return _Builder.GetPosition(_Composer, View.GetCursorX(), View.GetCursorY());
};

int Editor::Model::GetNumberLines(int paragraph) const
{
  return _Composer.GetNumberLines(paragraph);
};

int Editor::Model::GetNumberParagraphs() const
{
  return _Document.GetNumberParagraphs();
};

void Editor::Model::SetCursor(Editor::View& View, int position, int paragraph)
{
  _Builder.SetCursor(View, _Composer, position, paragraph);
};

void Editor::Model::SetValidPosition(Editor::View& View)
{
  int paragraph = GetParagraph(View),
    line = _Builder.GetParagraphOffset(_Composer, GetParagraph(View)),
    line_offset = 0;
  
  while(line + line_offset < View.GetCursorY())
    ++line_offset;
  
  View.SetCursorX(std::min(View.GetCursorX(), static_cast<int>(GetLine(line_offset, paragraph).size())));
};