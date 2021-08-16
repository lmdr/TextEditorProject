#ifndef EDITORCOMMANDHISTORY_H
#define EDITORCOMMANDHISTORY_H

#include <vector>

namespace Editor {

class Command;

class CommandHistory {
public:
  CommandHistory();
  void ExecuteCommand(Editor::Command*);
  bool Redo();
  bool Undo();
private:
  std::vector<Editor::Command*> _ExecutedCommands;
  std::vector<Editor::Command*>::iterator _ExecutedCommandsIterator;
};

}

#endif