#ifndef EDITORPAGECOMPOSER_H
#define EDITORPAGECOMPOSER_H

#include <vector>

namespace Editor {

class Controller;
class LineBreakStrategy;

struct Page {
  Page(int, int);
  int _paragraph,
      _position;
};

class PageComposer {
public:
  PageComposer(Editor::Controller&);
  ~PageComposer();
  void Init();
  void ComposePage();
  void NextPage();
  void PrevPage();
  void SetPage(int, int);
  int GetParagraph() const;
  int GetPosition() const;
  void SetCursor(int, int);
private:
  void RecalculatePages();
  void AddPage(int, int);
  Editor::Controller& _Controller;
  Editor::LineBreakStrategy* _LineBreakStrategy;
  std::vector<Editor::Page> _Pages;
  std::vector<Editor::Page>::iterator _CurrentPage;
};

}

#endif