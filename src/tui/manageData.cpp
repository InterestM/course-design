#include <algorithm>
#include <string> // for basic_string, allocator, string
#include <vector> // for vector

#include "db/database.hpp"
#include "tui/component/labeled_input.hpp"
#include "tui/edit.hpp"
#include "tui/manageData.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"  //for Render
#include "ftxui/dom/table.hpp" // for Table, TableSelection
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include "ftxui/screen/screen.hpp" // for Screen

using namespace ftxui;

namespace {
// At depth=0, Data Browser
std::vector<ftxui::Component> labeledInputs = {
    LabeledInput(" 类型: ", "Type"),
    LabeledInput(" 型号: ", "Specification"),
    LabeledInput(" 归属: ", "Red/Blue"),
    LabeledInput(" 状态: ", "Destoryed/Captured"),
};

static ftxui::Table GetTable() {
  std::vector<std::vector<std::string>> recordRows = {
      {"ID", "类型", "型号", "归属", "数量", "状态", "来源"}};
  auto records = Database::QueryRecord();
  std::transform(records.begin(), records.end(), std::back_inserter(recordRows),
                 [](const Record &record) -> std::vector<std::string> {
                   return {std::to_string(record.getId()),
                           record.getType(),
                           record.getSpecification(),
                           record.getAdscription(),
                           std::to_string(record.getAmount()),
                           record.getStatus(),
                           record.getSource()};
                 });
  ftxui::Table table(recordRows);

  table.SelectAll().Border(LIGHT);

  // Add border around the first column.
  table.SelectColumn(0).Border(LIGHT);

  // Make first row bold with a double border.
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);

  // Align right the "Release date" column.
  table.SelectColumn(5).DecorateCells(center);

  // Select row from the second to the last.
  auto content = table.SelectColumns(1, -1);
  // Alternate in between 3 colors.
  content.DecorateCellsAlternateColumn(color(Color::NavajoWhite1), 3, 0);
  content.DecorateCellsAlternateColumn(color(Color::RedLight), 3, 1);
  content.DecorateCellsAlternateColumn(color(Color::Blue), 3, 2);

  return table;
};
auto queryButton = Button("查询", [] {
  Database::QueryRecord(
      std::dynamic_pointer_cast<LabeledInputBase>(labeledInputs[0])->GetInput(),
      std::dynamic_pointer_cast<LabeledInputBase>(labeledInputs[1])->GetInput(),
      std::dynamic_pointer_cast<LabeledInputBase>(labeledInputs[2])->GetInput(),
      std::dynamic_pointer_cast<LabeledInputBase>(labeledInputs[3])
          ->GetInput());
});

auto button_open_insert = Button(
    "新增记录", [] { depth = 1; }, ButtonOption::Ascii());
auto button_open_delete = Button(
    "删除记录", [] { depth = 2; }, ButtonOption::Ascii());

auto labeledInputsComponent = Container::Horizontal(labeledInputs);
auto queryComponent =
    Container::Horizontal({button_open_insert, button_open_delete,
                           labeledInputsComponent, queryButton});

Component depth_0_renderer = Renderer(queryComponent, [] {
  return vbox({
             hbox({window(text("条件"), labeledInputsComponent->Render()),
                   queryButton->Render()}) |
                 hcenter,
             hbox({
                 filler(),
                 button_open_insert->Render(),
                 filler(),
                 button_open_delete->Render(),
                 filler(),
             }),
             GetTable().Render(),
         }) |
         vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 60) | hcenter;
});

// At depth=1, open insertWindow(see at edit.cpp)
// At depth=2,open deleteWindow(see at edit.cpp)

// contain depth 0&1
auto main_container =
    Container::Tab({depth_0_renderer, insertWindow, deleteWindow}, &depth);
} // namespace

Component dataManager = Renderer(main_container, [] {
  Element document = depth_0_renderer->Render();

  if (depth == 1) {
    document = dbox({
        document,
        insertWindow->Render() | bgcolor(Color::Black) | clear_under | center,
    });
  }
  if (depth == 2) {
    document = dbox({
        document,
        deleteWindow->Render() | bgcolor(Color::Black) | clear_under | center,
    });
  }
  return document;
});
