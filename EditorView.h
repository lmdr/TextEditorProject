#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include "ECTextViewImp.h"

namespace Editor {

class View {
public:
  View();
  void Show();
  void Refresh();
  void Quit();
  void InitRows();
  void AddRow(const std::string &strRow);
  void ClearStatusRows();
  void AddStatusRow(const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground);
  int GetPressedKey();
  int GetRowNumInView() const;
  int GetColNumInView() const;
  int GetCursorX() const;
  int GetCursorY() const;
  void SetCursorX(int pos);
  void SetCursorY(int pos);
  void Attach(ECObserver*);
  void Detach(ECObserver*);
private:
  ECTextViewImp _TextViewImp;
};

}

#endif