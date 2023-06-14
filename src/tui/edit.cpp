#include <algorithm>
#include <exception>

#include <memory>
#include <string>

#include "data/record.hpp"
#include "db/database.hpp"
#include "tui/component/labeled_input.hpp"
#include "tui/edit.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

using namespace ftxui;
namespace {

std::vector<Component> labeledInputs = {
    LabeledInput("类型: ", "Type", borderEmpty),
    LabeledInput("型号: ", "Specification", borderEmpty),
    LabeledInput("归属: ", "Red/Blue", borderEmpty),
    LabeledInput("数量: ", "number", borderEmpty),
    LabeledInput("状态: ", "Destoryed/Captured", borderEmpty),
    LabeledInput("来源: ", "URL", borderEmpty),
};

Component deleteIdInput = LabeledInput("目标ID: ", "number", borderEmpty);

Component insertButton = Button(
    "执行",
    [] {
      static std::string inserts[6];
      std::transform(labeledInputs.begin(), labeledInputs.end(), inserts,
                     [](Component &input) {
                       return std::dynamic_pointer_cast<LabeledInputBase>(input)
                           ->GetInput();
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
    },
    ButtonOption::Ascii());

auto deleteButton = Button(
    "执行",
    [] {
      try {
        int id =
            std::stoi(std::dynamic_pointer_cast<LabeledInputBase>(deleteIdInput)
                          ->GetInput());
        Database::DeleteRecord(id);
      } catch (std::exception) {
        return;
      }
    },
    ButtonOption::Ascii());

auto quitButton1 = Button(
    "返回", [] { depth = 0; }, ButtonOption::Ascii());
auto quitButton2 = Button(
    "返回", [] { depth = 0; }, ButtonOption::Ascii());

Component labeledInputsComponent = Container::Vertical(labeledInputs);

Component insertComponent = Container::Horizontal({
    labeledInputsComponent,
    insertButton,
    quitButton1,
});

Component deleteComponenet = Container::Horizontal({
    deleteIdInput,
    deleteButton,
    quitButton2,
});

} // namespace
int depth = 0; // There are two layers. One at depth = 0 and the modal
               // window at depth = 1;
Component insertWindow = Renderer(insertComponent, [] {
  return vbox({
      window(text("添加记录"), vbox({
                                   labeledInputsComponent->Render(),
                                   hbox({
                                       filler(),
                                       insertButton->Render(),
                                       filler(),
                                       quitButton1->Render(),
                                       filler(),
                                   }),
                               })),
  });
});
Component deleteWindow = Renderer(deleteComponenet, [] {
  return vbox({
      window(text("删除记录"), vbox({
                                   deleteIdInput->Render() | vcenter,
                                   hbox({
                                       filler(),
                                       deleteButton->Render(),
                                       filler(),
                                       quitButton2->Render(),
                                       filler(),
                                   }),
                               })),
  });
});
