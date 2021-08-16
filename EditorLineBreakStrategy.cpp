#include "EditorLineBreakStrategy.h"
#include <algorithm>
#include <iterator>

std::string::iterator Editor::WholeWordLineBreak::Compose(const std::string& Paragraph, std::string::iterator Start, int width)
{
  std::string delimiter(" ");
  
  return (std::distance(Start, const_cast<std::string&>(Paragraph).end()) <= width) ?
    const_cast<std::string&>(Paragraph).end() :
    std::find_end(Start, Start + width, delimiter.begin(), delimiter.end()) + 1;
};