#include "EditorDocument.h"

Editor::Document::Document() :
  _Paragraphs()
{};

void Editor::Document::InsertCharacter(int position, int paragraph, char character)
{
	(_Paragraphs.begin() + paragraph)->InsertCharacter(position, character);
};

void Editor::Document::RemoveCharacter(int position, int paragraph)
{
  (_Paragraphs.begin() + paragraph)->RemoveCharacter(position);
};

void Editor::Document::AddParagraph(const std::string& paragraph)
{
  _Paragraphs.push_back(Editor::Paragraph(paragraph));
};

void Editor::Document::InsertParagraph(int position, int paragraph)
{
  _Paragraphs.insert(_Paragraphs.begin() + paragraph + 1,
  	Editor::Paragraph((_Paragraphs.begin() + paragraph)->DivideParagraph(position)));
};

void Editor::Document::RemoveParagraph(int paragraph)
{
  (_Paragraphs.begin() + paragraph - 1)->MergeParagraph((_Paragraphs.begin() + paragraph)->GetParagraph());
  _Paragraphs.erase(_Paragraphs.begin() + paragraph);
};

const std::string& Editor::Document::GetParagraph(int paragraph) const
{
  return (_Paragraphs.begin() + paragraph)->GetParagraph();
};

const int Editor::Document::GetNumberParagraphs() const
{
  return _Paragraphs.size();
};