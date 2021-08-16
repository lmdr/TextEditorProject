#ifndef EDITORKEYHANDLER_H
#define EDITORKEYHANDLER_H

namespace Editor {

class Controller;

class Request {
public:
  Request(Editor::Controller&, int);
  Editor::Controller& GetController() const;
  int GetKey() const;
private:
  Editor::Controller& _Controller;
  int _key;
};

class KeyHandler {
public:
  virtual ~KeyHandler() {};
  virtual bool Handle(Editor::Request&) = 0;
};

class NullKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class EnterKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class QuitKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class SaveKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class RedoKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class UndoKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class BackspaceKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class LeftKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class RightKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class UpKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class DownKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class CharacterKeyHandler : public Editor::KeyHandler {
public:
  bool Handle(Editor::Request&);
};

class KeyHandlerDelegate {
public:
  KeyHandlerDelegate();
  bool Handle(Editor::Request&);
private:
  Editor::NullKeyHandler _NullKeyHandler;
  Editor::EnterKeyHandler _EnterKeyHandler;
  Editor::QuitKeyHandler _QuitKeyHandler;
  Editor::SaveKeyHandler _SaveKeyHandler;
  Editor::RedoKeyHandler _RedoKeyHandler;
  Editor::UndoKeyHandler _UndoKeyHandler;
  Editor::BackspaceKeyHandler _BackspaceKeyHandler;
  Editor::LeftKeyHandler _LeftKeyHandler;
  Editor::RightKeyHandler _RightKeyHandler;
  Editor::UpKeyHandler _UpKeyHandler;
  Editor::DownKeyHandler _DownKeyHandler;
  Editor::CharacterKeyHandler _CharacterKeyHandler;
};

}

#endif