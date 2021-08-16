#include "EditorKeyHandler.h"
#include "ECTextViewImp.h"
#include "EditorCommand.h"
#include "EditorController.h"
#include "EditorModel.h"
#include "EditorView.h"
#include <algorithm>

Editor::Request::Request(Editor::Controller& Controller, int key) :
  _Controller(Controller),
  _key(key)
{};

Editor::Controller& Editor::Request::GetController() const
{
  return _Controller;
};

int Editor::Request::GetKey() const
{
  return _key;
}

bool Editor::NullKeyHandler::Handle(Editor::Request& ActionRequest)
{
  return false;
};

bool Editor::EnterKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto cmd = new Editor::InsertParagraphCommand(ActionRequest.GetController());
  ActionRequest.GetController().ExecuteCommand(cmd);
  return true;
};

bool Editor::QuitKeyHandler::Handle(Editor::Request& ActionRequest)
{
  ActionRequest.GetController().GetView().Quit();
  return true;
};

bool Editor::SaveKeyHandler::Handle(Editor::Request& ActionRequest)
{
  ActionRequest.GetController().SaveToFile();
  return true;
};

bool Editor::RedoKeyHandler::Handle(Editor::Request& ActionRequest)
{
  return ActionRequest.GetController().Redo();
};

bool Editor::UndoKeyHandler::Handle(Editor::Request& ActionRequest)
{
  return ActionRequest.GetController().Undo();
};

bool Editor::BackspaceKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto& ctrl = ActionRequest.GetController();
  if(ctrl.GetView().GetCursorX() == 0 && ctrl.GetView().GetCursorY() == 0)
    return false;
  if(ctrl.GetView().GetCursorX() == 0)
  {
    auto cmd = new Editor::RemoveParagraphCommand(ctrl);
    ctrl.ExecuteCommand(cmd);
  }
  else
  {
    auto cmd = new Editor::RemoveCharacterCommand(ctrl);
    ctrl.ExecuteCommand(cmd);
  }
  return true;
};

bool Editor::LeftKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto& ctrl = ActionRequest.GetController();
  ctrl.SetCursor(std::max(ctrl.GetPosition() - 1, 0), ctrl.GetParagraph());
  return true;
};

bool Editor::RightKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto& ctrl = ActionRequest.GetController();
  ctrl.SetCursor(std::min(ctrl.GetPosition() + 1, static_cast<int>(ctrl.GetModel().GetParagraph(ctrl.GetParagraph()).size())), ctrl.GetParagraph());
  return true;
};

bool Editor::UpKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto& ctrl = ActionRequest.GetController();
  if(!ctrl.GetView().GetCursorY())
  {
    ctrl.PrevPage();
    ctrl.GetView().SetCursorY(ctrl.GetView().GetRowNumInView());
    ctrl.Draw();
  }
  else
    ctrl.GetView().SetCursorY(ctrl.GetView().GetCursorY() - 1);
  ctrl.SetValidPosition();
  return true;
};

bool Editor::DownKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto& ctrl = ActionRequest.GetController();
  if(!ctrl.GetView().GetRowNumInView() - ctrl.GetView().GetCursorY())
  {
    ctrl.NextPage();
    ctrl.GetView().SetCursorY(0);
    ctrl.Draw();
  }
  else
    ctrl.GetView().SetCursorY(ctrl.GetView().GetCursorY() + 1);
  ctrl.SetValidPosition();
  return true;
};

bool Editor::CharacterKeyHandler::Handle(Editor::Request& ActionRequest)
{
  auto& ctrl = ActionRequest.GetController();
  auto cmd = new Editor::InsertCharacterCommand(ctrl, static_cast<char>(ActionRequest.GetKey()));
  ctrl.ExecuteCommand(cmd);
  return true;
};

Editor::KeyHandlerDelegate::KeyHandlerDelegate() :
  _NullKeyHandler(),
  _EnterKeyHandler(),
  _QuitKeyHandler(),
  _SaveKeyHandler(),
  _RedoKeyHandler(),
  _UndoKeyHandler(),
  _BackspaceKeyHandler(),
  _LeftKeyHandler(),
  _RightKeyHandler(),
  _UpKeyHandler(),
  _DownKeyHandler(),
  _CharacterKeyHandler()
{};

bool Editor::KeyHandlerDelegate::Handle(Editor::Request& ActionRequest)
{
  bool handler_return = false;
  switch(ActionRequest.GetKey())
  {
    case KEY_NULL:
    {
      handler_return = _NullKeyHandler.Handle(ActionRequest);
      break;
    }
    case ENTER:
    {
      handler_return = _EnterKeyHandler.Handle(ActionRequest);
      break;
    }
    case CTRL_Q:
    {
      handler_return = _QuitKeyHandler.Handle(ActionRequest);
      break;
    }
    case CTRL_S:
    {
      handler_return = _SaveKeyHandler.Handle(ActionRequest);
      break;
    }
    case CTRL_Y:
    {
      handler_return = _RedoKeyHandler.Handle(ActionRequest);
      break;
    }
    case CTRL_Z:
    {
      handler_return = _UndoKeyHandler.Handle(ActionRequest);
      break;
    }
    case BACKSPACE:
    {
      handler_return = _BackspaceKeyHandler.Handle(ActionRequest);
      break;
    }
    case ARROW_LEFT:
    {
      handler_return = _LeftKeyHandler.Handle(ActionRequest);
      break;
    }
    case ARROW_RIGHT:
    {
      handler_return = _RightKeyHandler.Handle(ActionRequest);
      break;
    }
    case ARROW_UP:
    {
      handler_return = _UpKeyHandler.Handle(ActionRequest);
      break;
    }
    case ARROW_DOWN:
    {
      handler_return = _DownKeyHandler.Handle(ActionRequest);
      break;
    }
    default:
    {
      handler_return = _CharacterKeyHandler.Handle(ActionRequest);
      break;
    }
  }
  return handler_return;
};