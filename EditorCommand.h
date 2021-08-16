#ifndef EDITORCOMMAND_H
#define EDITORCOMMAND_H

namespace Editor {

class Controller;

class Command {
public:
  virtual ~Command() {};
  virtual void Execute() = 0;
  virtual void UnExecute() = 0;
};

class InsertCharacterCommand : public Editor::Command {
public:
  InsertCharacterCommand(Editor::Controller&, char);
  void Execute();
  void UnExecute();
private:
  Editor::Controller& _Controller;
  int _position_x,
      _position_y;
  char _character;
};

class RemoveCharacterCommand : public Editor::Command {
public:
  RemoveCharacterCommand(Editor::Controller&);
  void Execute();
  void UnExecute();
private:
  Editor::Controller& _Controller;
  int _position_x,
      _position_y;
  char _character;
};

class InsertParagraphCommand : public Editor::Command {
public:
  InsertParagraphCommand(Editor::Controller&);
  void Execute();
  void UnExecute();
private:
  Editor::Controller& _Controller;
  int _position_x,
      _position_y;
};

class RemoveParagraphCommand : public Editor::Command {
public:
  RemoveParagraphCommand(Editor::Controller&);
  void Execute();
  void UnExecute();
private:
  Editor::Controller& _Controller;
  int _position_x,
      _position_y,
      _paragraph_size;
};

}

#endif