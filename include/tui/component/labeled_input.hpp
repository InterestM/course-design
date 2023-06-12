#ifndef _LABELED_INPUT_HPP
#define _LABELED_INPUT_HPP

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

class LabeledInputBase : public ftxui::ComponentBase {
 public:
  const std::string& GetInput() const;
  ftxui::Element Render() override;
  LabeledInputBase(const std::string& label, const std::string& placeholder,
                   ftxui::Decorator decorator);

 private:
  std::string label;
  std::string input;
  ftxui::Decorator decorator;
};

ftxui::Component LabeledInput(const std::string& label,
                              const std::string& placeholder,
                              ftxui::Decorator decorator = ftxui::nothing);

#endif
