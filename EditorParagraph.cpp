#include "EditorParagraph.h"

Editor::Paragraph::Paragraph(const std::string& paragraph) :
	_Paragraph(paragraph)
{};

void Editor::Paragraph::InsertCharacter(int position, char character)
{
	_Paragraph.insert(_Paragraph.begin() + position, character);
};

void Editor::Paragraph::RemoveCharacter(int position)
{
	_Paragraph.erase(_Paragraph.begin() + position);
};

std::string Editor::Paragraph::DivideParagraph(int position)
{
	auto new_paragraph = std::string(_Paragraph.begin() + position, _Paragraph.end());
	_Paragraph.erase(_Paragraph.begin() + position, _Paragraph.end());
	return new_paragraph;
};

void Editor::Paragraph::MergeParagraph(const std::string& paragraph)
{
	_Paragraph.append(paragraph);
};

const std::string& Editor::Paragraph::GetParagraph() const
{
	return _Paragraph;
};