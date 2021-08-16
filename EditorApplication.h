#ifndef EDITORAPPLICATION_H
#define EDITORAPPLICATION_H

#include "EditorController.h"
#include "EditorModel.h"
#include "EditorView.h"
#include <string>

namespace Editor {

class Application {
public:
  Application(const std::string&);
private:
  Editor::Model _Model;
  Editor::View _View;
  Editor::Controller _Controller;
};

}

#endif