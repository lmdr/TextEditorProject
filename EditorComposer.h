#ifndef EDITORCOMPOSER_H
#define EDITORCOMPOSER_H

#include "EditorComposableParagraph.h"
#include <string>
#include <vector>

namespace Editor {

class Document;
class LineBreakStrategy;

class Composer {
public:
  Composer();
  void Init(const Editor::Document&, int);
  void Compose(const Editor::Document&, int, bool = false);
  void RemoveParagraph(int);
	bool IsPositionIn(int, int, int) const;
  const std::string GetLine(const std::string&, int, int) const;
  int GetNumberLines(int) const;
  int GetNumberParagraphs() const;
  int GetPositionOffset(int, int, int) const;
  int GetStartPosition(int, int) const;
private:
  Editor::LineBreakStrategy* _LineBreakStrategy;
  std::vector<Editor::ComposableParagraph> _ComposableParagraphs;
  int _Width;
};

}

#endif