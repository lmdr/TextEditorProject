#include "EditorPage.h"

Editor::Page::Page(int start_line, int start_paragraph, int stop_line, int stop_paragraph) :
	_Start(start_line, start_paragraph),
	_Stop(stop_line, stop_paragraph)
{};

bool Editor::Page::IsLineIn(int line, int paragraph)
{
	return !(paragraph < GetStartParagraph() || GetStopParagraph() < paragraph || 
		(paragraph == GetStartParagraph() && line < GetStartLine()) ||
		(paragraph == GetStopParagraph() && GetStopLine() < line));
};

int Editor::Page::GetStartParagraph() const
{
	return _Start.second;
};

int Editor::Page::GetStopParagraph() const
{
	return _Stop.second;
};

int Editor::Page::GetStartLine() const
{
	return _Start.first;
};

int Editor::Page::GetStopLine() const
{
	return _Stop.first;
};