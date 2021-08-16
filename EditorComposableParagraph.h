#ifndef EDITORCOMPOSABLEPARAGRAPH_H
#define EDITORCOMPOSABLEPARAGRAPH_H

#include "EditorLine.h"
#include <vector>

namespace Editor {

class ComposableParagraph {
public:
	ComposableParagraph();
	ComposableParagraph(const ComposableParagraph&);
	ComposableParagraph& operator=(const ComposableParagraph&);
	void AddLine(const Editor::Line);
	bool IsPositionIn(int, int) const;
	const Editor::Line& GetLine(int) const;
	int GetNumberLines() const;
	int GetPositionOffset(int, int) const;
	int GetStartPosition(int) const;
private:
	std::vector<Editor::Line> _Lines;
};

}

#endif