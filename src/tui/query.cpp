#include <algorithm>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>  // for basic_string, allocator, string
#include <vector>  // for vector

#include "db/database.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/node.hpp"   // for Render
#include "ftxui/dom/table.hpp"  // for Table, TableSelection
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include "ftxui/screen/screen.hpp"  // for Screen
#include "tui/component/labeled_input.hpp"

using namespace ftxui;

namespace {

std::vector<ftxui::Component> labeledInputs = {
    LabeledInput("类型: ", "Type"),
    LabeledInput("型号: ", "Specification"),
    LabeledInput("归属: ", "Red/Blue"),
    LabeledInput("状态: ", "Destoryed/Captured"),
};

static ftxui::Table GetTable() {
  std::vector<std::vector<std::string>> recordRows = {
      {"ID", "类型", "型号", "归属", "数量", "状态", "来源"}};
  auto records = Database::QueryRecord();

  std::transform(records.begin(), records.end(), std::back_inserter(recordRows),
                 [](const Record& record) -> std::vector<std::string> {
                   return {std::to_string(record.getId()),
                           record.getType(),
                           record.getSpecification(),
                           record.getAdscription(),
                           std::to_string(record.getAmount()),
                           record.getStatus(),
                           record.getSource()};
                 });

  ftxui::Table table(recordRows);

  // data = ftxui::Table(Database::LoadRecord());
  table.SelectAll().Border(LIGHT);

  // Add border around the first column.
  table.SelectColumn(0).Border(LIGHT);

  // Make first row bold with a double border.
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);

  // Align right the "Release date" column.
  table.SelectColumn(2).DecorateCells(center);
  table.SelectColumn(5).DecorateCells(center);

  // Select row from the second to the last.
  auto content = table.SelectRows(1, -1);
  // Alternate in between 3 colors.
  content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
  content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
  content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

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

auto labeledInputsComponent = Container::Horizontal(labeledInputs);
auto queryComponent =
    Container::Horizontal({labeledInputsComponent, queryButton});

}  // namespace

auto records = Renderer(queryComponent, [] {
  return vbox({hbox({window(text("条件"), labeledInputsComponent->Render()),
                     queryButton->Render()}) |
                   hcenter,
               GetTable().Render() | hcenter});
});
