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
auto quitButton1 = Button(
    "返回", [] { depth = 0; }, ButtonOption::Ascii());
auto quitButton2 = Button(
    "返回", [] { depth = 0; }, ButtonOption::Ascii());
auto quitButton3 = Button(
    "返回", [] { depth = 0; }, ButtonOption::Ascii());

std::vector<Component> insertLabeledInputs = {
    LabeledInput("类型: ", "Type", borderEmpty),
    LabeledInput("型号: ", "Specification", borderEmpty),
    LabeledInput("归属: ", "Red/Blue", borderEmpty),
    LabeledInput("数量: ", "number", borderEmpty),
    LabeledInput("状态: ", "Destoryed/Captured", borderEmpty),
    LabeledInput("来源: ", "URL", borderEmpty),
};
Component insertLabeledInputsComponent =
    Container::Vertical(insertLabeledInputs);

Component insertButton = Button(
    "插入",
    [] {
      static std::string inserts[6];
      std::transform(insertLabeledInputs.begin(), insertLabeledInputs.end(),
                     inserts, [](Component &input) {
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

Component insertComponent = Container::Horizontal({
    insertLabeledInputsComponent,
    insertButton,
    quitButton1,
});

Component deleteIdInput = LabeledInput("目标ID: ", "number", borderEmpty);

auto deleteButton = Button(
    "删除",
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

Component deleteComponenet = Container::Horizontal({
    deleteIdInput,
    deleteButton,
    quitButton2,
});
std::vector<Component> updateLabeledInputs = {
    LabeledInput("类型: ", "Type", borderEmpty),
    LabeledInput("型号: ", "Specification", borderEmpty),
    LabeledInput("归属: ", "Red/Blue", borderEmpty),
    LabeledInput("数量: ", "number", borderEmpty),
    LabeledInput("状态: ", "Destoryed/Captured", borderEmpty),
    LabeledInput("来源: ", "URL", borderEmpty),
};
Component updateLabeledInputsComponent =
    Container::Vertical(updateLabeledInputs);

Component updateButton = Button(
    "插入",
    [] {
      static std::string inserts[6];
      std::transform(updateLabeledInputs.begin(), updateLabeledInputs.end(),
                     inserts, [](Component &input) {
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

Component updateComponent = Container::Horizontal({
    updateLabeledInputsComponent,
    updateButton,
    quitButton3,
});
} // namespace
int depth = 0;
Component insertWindow = Renderer(insertComponent, [] {
  return vbox({
      window(text("添加记录"), vbox({
                                   insertLabeledInputsComponent->Render(),
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
                                   deleteIdInput->Render(),
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
Component updateWindow = Renderer(updateComponent, [] {
  return vbox({
      window(text("编辑记录"), vbox({
                                   updateLabeledInputsComponent->Render(),
                                   hbox({
                                       filler(),
                                       updateButton->Render(),
                                       filler(),
                                       quitButton3->Render(),
                                       filler(),
                                   }),
                               })),
  });
});
