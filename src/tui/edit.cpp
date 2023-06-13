#include <algorithm>
#include <exception>
#include <memory>
#include <string>

#include "data/record.hpp"
#include "db/database.hpp"
#include "tui/component/labeled_input.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui

using namespace ftxui;
namespace {
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
  try {
    Database::InsertRecord({
        -1,
        inserts[0],
        inserts[1],
        inserts[2],
        std::stoi(inserts[3]),
        inserts[4],
        inserts[5],
    });
  } catch (std::exception) {
    return;
  }
});

auto deleteButton = Button("执行", [] {
  try {
    int id = std::stoi(
        std::dynamic_pointer_cast<LabeledInputBase>(deleteIdInput)->GetInput());
    Database::DeleteRecord(id);
  } catch (std::exception) {
    return;
  }
});

auto labeledInputsComponent = Container::Vertical(labeledInputs);

auto editComponent = Container::Horizontal({
    labeledInputsComponent,
    insertButton,
    deleteIdInput,
    deleteButton,
});
} // namespace

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
