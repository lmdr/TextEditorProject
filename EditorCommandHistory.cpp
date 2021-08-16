#include "EditorCommandHistory.h"
#include "EditorCommand.h"

Editor::CommandHistory::CommandHistory() :
  _ExecutedCommands(),
  _ExecutedCommandsIterator(_ExecutedCommands.begin())
{};

void Editor::CommandHistory::ExecuteCommand(Editor::Command* cmd)
{
  cmd->Execute();
  if(!_ExecutedCommands.empty() &&
     _ExecutedCommandsIterator + 1 != _ExecutedCommands.end())
    _ExecutedCommands.erase(_ExecutedCommandsIterator + 1, _ExecutedCommands.end());
  _ExecutedCommands.push_back(cmd);
  _ExecutedCommandsIterator = _ExecutedCommands.end() - 1;
};

bool Editor::CommandHistory::Redo()
{
  if(_ExecutedCommands.empty() ||
  	 _ExecutedCommandsIterator + 1 == _ExecutedCommands.end())
    return false;
  ++_ExecutedCommandsIterator;
  (*_ExecutedCommandsIterator)->Execute();
  return true;
};

bool Editor::CommandHistory::Undo()
{
  if(_ExecutedCommands.empty() ||
     std::vector<Editor::Command*>::reverse_iterator(_ExecutedCommandsIterator + 1) == _ExecutedCommands.rend())
    return false;
  (*_ExecutedCommandsIterator)->UnExecute();
  --_ExecutedCommandsIterator;
  return true;
};