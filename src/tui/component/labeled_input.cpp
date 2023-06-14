#include "tui/component/labeled_input.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
////输入框
const std::string &LabeledInputBase::GetInput() const { return input; }

ftxui::Element LabeledInputBase::Render() {
  return ftxui::hbox(ftxui::text(label),
                     this->ftxui::ComponentBase::children_[0]->Render()) |
         this->decorator;
}

LabeledInputBase::LabeledInputBase(const std::string &label,
                                   const std::string &placeholder,
                                   ftxui::Decorator decorator)
    : label{label}, input{""}, decorator{decorator} {
  this->ftxui::ComponentBase::Add(ftxui::Input(&input, placeholder));
}

ftxui::Component
LabeledInput(const std::string &label, const std::string &placeholder,
             std::function<ftxui::Element(ftxui::Element)> decorator) {
  return ftxui::Make<LabeledInputBase>(std::move(label), std::move(placeholder),
                                       std::move(decorator));
}
