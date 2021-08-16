#include "EditorController.h"
#include "EditorModel.h"
#include "EditorView.h"
#include <fstream>
#include <iostream>

Editor::Controller::Controller(Editor::Model& Model, Editor::View& View, const std::string& Filename) :
  _CommandHistory(),
  _KeyHandlerDelegate(),
  _Model(Model),
  _View(View),
  _filename(Filename)
{
  std::cerr << "Before Init()\n";
  GetModel().Init(GetView().GetColNumInView(), GetView().GetRowNumInView());
  std::cerr << "After Init()\n";
  LoadFromFile();
  GetView().Attach(this);
  GetView().Show();
  Draw();
  SaveToFile();
};

void Editor::Controller::Draw()
{
  GetModel().Draw(GetView());
};

void Editor::Controller::ExecuteCommand(Editor::Command* cmd)
{
  _CommandHistory.ExecuteCommand(cmd);
};

bool Editor::Controller::Redo()
{
  return _CommandHistory.Redo();
};

bool Editor::Controller::Undo()
{
  return _CommandHistory.Undo();
};

void Editor::Controller::Update()
{
  Editor::Request ActionRequest(*this, GetView().GetPressedKey());
  _KeyHandlerDelegate.Handle(ActionRequest);
  GetView().Refresh();
};

void Editor::Controller::LoadFromFile()
{
  std::ifstream filestream(_filename);
  
  std::string line;
  while(std::getline(filestream, line))
    GetModel().AddParagraph(line);
  
  filestream.close();
  
  if(!GetModel().GetNumberParagraphs())
    GetModel().AddParagraph(std::string());
};

void Editor::Controller::SaveToFile()
{
  std::ofstream filestream(_filename, std::ios_base::trunc);
  
  for(int i = 0; i < GetModel().GetNumberParagraphs(); ++i)
    filestream << GetModel().GetParagraph(i) << '\n';
  
  filestream.close();
};

void Editor::Controller::NextPage()
{
  GetModel().NextPage();
};

void Editor::Controller::PrevPage()
{
  GetModel().PrevPage();
};

int Editor::Controller::GetParagraph() const
{
  return GetModel().GetParagraph(GetView());
};

int Editor::Controller::GetPosition() const
{
 return GetModel().GetPosition(GetView()); 
};

Editor::Model& Editor::Controller::GetModel() const
{
  return _Model;
};

Editor::View& Editor::Controller::GetView() const
{
  return _View;
};

void Editor::Controller::SetCursor(int position, int paragraph)
{
  GetModel().SetCursor(GetView(), position, paragraph);
};

void Editor::Controller::SetValidPosition()
{
  GetModel().SetValidPosition(GetView());
};