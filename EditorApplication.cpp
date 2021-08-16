#include "EditorApplication.h"

Editor::Application::Application(const std::string& filename) :
  _Model(),
  _View(),
  _Controller(_Model, _View, filename)
{};