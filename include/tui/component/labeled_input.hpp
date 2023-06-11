#ifndef _LABELED_INPUT_HPP
#define _LABELED_INPUT_HPP

#include <ftxui/component/component_base.hpp>

using namespace ftxui;

class LabeledInputBase : public ftxui::ComponentBase {
 public:
  const std::string& GetInput() const;
  ftxui::Element Render() override;
  LabeledInputBase(const std::string& label, const std::string& placeholder);

 private:
  std::string label;
  std::string input;
};

ftxui::Component LabeledInput(const std::string& label,
                              const std::string& placeholder);

#endif
