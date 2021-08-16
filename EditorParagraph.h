#ifndef EDITORPARAGRAPH_H
#define EDITORPARAGRAPH_H

#include <string>

namespace Editor {

class Paragraph {
public:
  Paragraph(const std::string&);
  void InsertCharacter(int, char);
  void RemoveCharacter(int);
  std::string DivideParagraph(int);
  void MergeParagraph(const std::string&);
  const std::string& GetParagraph() const;
private:
  std::string _Paragraph;
};

}

#endif