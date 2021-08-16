#ifndef EDITORDOCUMENT_H
#define EDITORDOCUMENT_H

#include "EditorParagraph.h"
#include <string>
#include <vector>

namespace Editor {

class Document {
public:
  Document();
  void InsertCharacter(int, int, char);
  void RemoveCharacter(int, int);
  void AddParagraph(const std::string&);
  void InsertParagraph(int, int);
  void RemoveParagraph(int);
  const std::string& GetParagraph(int) const;
  const int GetNumberParagraphs() const;
private:
  std::vector<Editor::Paragraph> _Paragraphs;
};

}

#endif