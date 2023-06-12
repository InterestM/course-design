#include <algorithm>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>

#include "db/database.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include "tui/component/labeled_input.hpp"
using namespace ftxui;

std::vector<Component> labeledInputs = {
    LabeledInput("类型: ", "Type", borderLight),
    LabeledInput("型号: ", "Specification", borderLight),
    LabeledInput("归属: ", "Red/Blue", borderLight),
    LabeledInput("数量: ", "number", borderLight),
    LabeledInput("状态: ", "Destoryed/Captured", borderLight),
    LabeledInput("来源: ", "URL", borderLight),
};

Component deleteIdInput = LabeledInput("目标ID: ", "number");

auto insertButton = Button("执行", [] {
  static std::string inserts[6];
  std::transform(
      labeledInputs.begin(), labeledInputs.end(), inserts,
      [](Component &input) {
        return std::dynamic_pointer_cast<LabeledInputBase>(input)->GetInput();
      });
  Database::InsertRecord(inserts);
  Database::QueryRecord();
});

auto deleteButton = Button("执行", [] {
  Database::DeleteRecord(
      std::dynamic_pointer_cast<LabeledInputBase>(deleteIdInput)->GetInput());
  Database::QueryRecord();
});

auto labeledInputsComponent = Container::Vertical(labeledInputs);

auto editComponent = Container::Horizontal({
    labeledInputsComponent,
    insertButton,
    deleteIdInput,
    deleteButton,
});

auto edits = Renderer(editComponent, [] {
  return vbox({
      vbox({window(text("添加记录"), labeledInputsComponent->Render()),
            insertButton->Render()}) |
          hcenter,
      hbox({
          window(text("删除记录"), deleteIdInput->Render()),
          deleteButton->Render(),
      }) | hcenter,
  });
});
