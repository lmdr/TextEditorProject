#ifndef EDITORBUILDER_H
#define EDITORBUILDER_H

#include "EditorPage.h"
#include <utility>
#include <vector>

namespace Editor {

class Composer;
class View;

class Builder {
public:
  Builder();
  void Init(const Editor::Composer&, int);
  void Build(const Editor::Composer&, int, int);
  void NextPage(const Editor::Composer&);
  void PrevPage();
  const Editor::Page& GetPage() const;
  int GetParagraph(const Editor::Composer&, int, int) const;
  int GetParagraphOffset(const Editor::Composer&, int) const;
  int GetPosition(const Editor::Composer&, int, int) const;
  void SetCursor(Editor::View&, const Editor::Composer&, int, int);
private:
  Editor::Page CreatePage(const Editor::Composer&, int, int);
  std::pair<int, int> FindStart(const Editor::Composer&, int);
  std::vector<Editor::Page> _Pages;
  int _CurrentPage,
      _Height;
};

}

#endif