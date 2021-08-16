#ifndef EDITORMODEL_H
#define EDITORMODEL_H

#include "EditorBuilder.h"
#include "EditorComposer.h"
#include "EditorDocument.h"
#include <string>

namespace Editor {

class View;

class Model {
public:
  Model();
  void Init(int, int);
  void Draw(Editor::View&);
  void InsertCharacter(int, int, char);
  void RemoveCharacter(int, int);
  void AddParagraph(const std::string&);
  void InsertParagraph(int, int);
  void RemoveParagraph(int);
  void NextPage();
  void PrevPage();
  const std::string GetLine(int, int) const;
  const std::string& GetParagraph(int) const;
  int GetParagraph(const View&) const;
  int GetPosition(const View&) const;
  int GetNumberLines(int) const;
  int GetNumberParagraphs() const;
  void SetCursor(Editor::View&, int, int);
  void SetValidPosition(Editor::View&);
private:
  Editor::Builder _Builder;
  Editor::Composer _Composer;
  Editor::Document _Document;
};

}

#endif