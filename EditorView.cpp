#include "EditorView.h"
#include "EditorLineBreakStrategy.h"

Editor::View::View() :
  _TextViewImp()
{
  _TextViewImp.Init();
  _TextViewImp.AddStatusRow("Status", "Bar", false);
};

void Editor::View::Show()
{
  _TextViewImp.Show();
};

void Editor::View::Refresh()
{
  _TextViewImp.Refresh();
};

void Editor::View::Quit()
{
  _TextViewImp.Quit();
};

void Editor::View::InitRows()
{
  _TextViewImp.InitRows();
};

void Editor::View::AddRow(const std::string &strRow)
{
  _TextViewImp.AddRow(strRow);
};

void Editor::View::ClearStatusRows()
{
  _TextViewImp.ClearStatusRows();
};

void Editor::View::AddStatusRow(const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground)
{
  _TextViewImp.AddStatusRow(statusMsgLeft, statusMsgRight, fBlackBackground);
};

int Editor::View::GetPressedKey()
{
  return _TextViewImp.GetPressedKey();
};

int Editor::View::GetRowNumInView() const
{
  return _TextViewImp.GetRowNumInView();
};

int Editor::View::GetColNumInView() const
{
  return _TextViewImp.GetColNumInView();
};

int Editor::View::GetCursorX() const
{
  return _TextViewImp.GetCursorX();
};

int Editor::View::GetCursorY() const
{
  return _TextViewImp.GetCursorY();
};

void Editor::View::SetCursorX(int pos)
{
  _TextViewImp.SetCursorX(pos);
};

void Editor::View::SetCursorY(int pos)
{
  _TextViewImp.SetCursorY(pos);
};

void Editor::View::Attach(ECObserver* Observer)
{
  _TextViewImp.Attach(Observer);
};

void Editor::View::Detach(ECObserver* Observer)
{
  _TextViewImp.Detach(Observer);
};