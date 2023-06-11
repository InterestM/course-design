#include "tui/component/labeled_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>

const std::string& LabeledInputBase::GetInput() const { return input; }

ftxui::Element LabeledInputBase::Render() {
  return hbox(text(label), children_[0]->Render());
}

LabeledInputBase::LabeledInputBase(const std::string& label,
                                   const std::string& placeholder)
    : label{label}, input{""} {
  this->ComponentBase::Add(ftxui::Input(&input, placeholder));
}

ftxui::Component LabeledInput(const std::string& label,
                              const std::string& placeholder) {
  return Make<LabeledInputBase>(std::move(label), std::move(placeholder));
}
