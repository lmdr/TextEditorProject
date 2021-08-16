#ifndef EDITORCONTROLLER_H
#define EDITORCONTROLLER_H

#include "ECObserver.h"
#include "EditorCommandHistory.h"
#include "EditorKeyHandler.h"
#include <string>

namespace Editor {

class Command;
class Model;
class View;

class Controller : public ECObserver {
public:
  Controller(Editor::Model&, Editor::View&, const std::string&);
  void Draw();
  void ExecuteCommand(Editor::Command*);
  bool Redo();
  bool Undo();
  void Update();
  void LoadFromFile();
  void SaveToFile();
  void NextPage();
  void PrevPage();
  int GetParagraph() const;
  int GetPosition() const;
  Editor::Model& GetModel() const;
  Editor::View& GetView() const;
  void SetCursor(int, int);
  void SetValidPosition();
private:
  Editor::CommandHistory _CommandHistory;
  Editor::KeyHandlerDelegate _KeyHandlerDelegate;
  Editor::Model& _Model;
  Editor::View& _View;
  const std::string& _filename;
};

}

#endif