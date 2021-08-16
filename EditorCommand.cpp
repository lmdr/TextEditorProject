#include "EditorCommand.h"
#include "EditorController.h"
#include "EditorModel.h"

Editor::InsertCharacterCommand::InsertCharacterCommand(Editor::Controller& Controller, char character) :
  _Controller(Controller),
  _position_x(_Controller.GetPosition()),
  _position_y(_Controller.GetParagraph()),
  _character(character)
{};

void Editor::InsertCharacterCommand::Execute()
{
  _Controller.GetModel().InsertCharacter(_position_x, _position_y, _character);
  _Controller.SetCursor(_position_x + 1, _position_y);
  _Controller.Draw();
};

void Editor::InsertCharacterCommand::UnExecute()
{
  _Controller.GetModel().RemoveCharacter(_position_x, _position_y);
  _Controller.SetCursor(_position_x, _position_y);
  _Controller.Draw();
};

Editor::RemoveCharacterCommand::RemoveCharacterCommand(Editor::Controller& Controller) :
  _Controller(Controller),
  _position_x(_Controller.GetPosition()),
  _position_y(_Controller.GetParagraph()),
  _character(_Controller.GetModel().GetParagraph(_position_y)[_position_x - 1])
{};

void Editor::RemoveCharacterCommand::Execute()
{
  _Controller.GetModel().RemoveCharacter(_position_x - 1, _position_y);
  _Controller.SetCursor(_position_x - 1, _position_y);
  _Controller.Draw();
};

void Editor::RemoveCharacterCommand::UnExecute()
{
  _Controller.GetModel().InsertCharacter(_position_x - 1, _position_y, _character);
  _Controller.SetCursor(_position_x, _position_y);
  _Controller.Draw();
};

Editor::InsertParagraphCommand::InsertParagraphCommand(Editor::Controller& Controller) :
  _Controller(Controller),
  _position_x(_Controller.GetPosition()),
  _position_y(_Controller.GetParagraph())
{};

void Editor::InsertParagraphCommand::Execute()
{
  _Controller.GetModel().InsertParagraph(_position_x, _position_y);
  _Controller.SetCursor(0, _position_y + 1);
  _Controller.Draw();
};

void Editor::InsertParagraphCommand::UnExecute()
{
  _Controller.GetModel().RemoveParagraph(_position_y + 1);
  _Controller.SetCursor(_position_x, _position_y);
  _Controller.Draw();
};

Editor::RemoveParagraphCommand::RemoveParagraphCommand(Editor::Controller& Controller) :
  _Controller(Controller),
  _position_x(_Controller.GetPosition()),
  _position_y(_Controller.GetParagraph()),
  _paragraph_size(_Controller.GetModel().GetParagraph(_position_y).size())
{};

void Editor::RemoveParagraphCommand::Execute()
{
  _Controller.GetModel().RemoveParagraph(_position_y);
  _Controller.SetCursor(_Controller.GetModel().GetParagraph(_position_y - 1).size(), _position_y - 1);
  _Controller.Draw();
};

void Editor::RemoveParagraphCommand::UnExecute()
{
  _Controller.GetModel().InsertParagraph(_Controller.GetModel().GetParagraph(_position_y).size() - _paragraph_size, _position_y);
  _Controller.SetCursor(0, _position_y);
  _Controller.Draw();
};