#include "ftxui/dom/table.hpp"     // for Table, TableSelection
#include "ftxui/screen/screen.hpp" // for Screen
#include "include/database.hpp"
#include <ftxui/dom/elements.hpp>
#include <string> // for basic_string, allocator, string
#include <vector> // for vector

#include "ftxui/component/component.hpp"
#include "ftxui/dom/node.hpp" // for Render
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui

using namespace ftxui;

namespace {


std::string inputs[4];
Component input[4] = {
    Input(&(inputs[0]), "Type"),
    Input(&(inputs[1]), "Specification"),
    Input(&(inputs[2]), "Red/Blue"),
    Input(&(inputs[3]), "Destoryed/Captured"),
};
class Tables {
public:
  static inline Table data;
  Tables() {
    Database::QueryRecord();
    load();
  }
  void load() {
    data = Table(Database::LoadRecord());
    data.SelectAll().Border(LIGHT);

    // Add border around the first column.
    data.SelectColumn(0).Border(LIGHT);

    // Make first row bold with a double border.
    data.SelectRow(0).Decorate(bold);
    data.SelectRow(0).SeparatorVertical(LIGHT);
    data.SelectRow(0).Border(DOUBLE);

    // Align right the "Release date" column.
    data.SelectColumn(2).DecorateCells(center);
    data.SelectColumn(5).DecorateCells(center);

    // Select row from the second to the last.
    auto content = data.SelectRows(1, -1);
    // Alternate in between 3 colors.
    content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
    content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
    content.DecorateCellsAlternateRow(color(Color::White), 3, 2);
  };
} table;

auto queryButton = Button("查询", [] {
  Database::QueryRecord(inputs[0], inputs[1], inputs[2], inputs[3]);
});
auto queryComponent = Container::Horizontal({
    input[0],
    input[1],
    input[2],
    input[3],
    queryButton,
});

}
auto records = Renderer(queryComponent, [] {

  table.load();
  return vbox(
      {hbox({
           window(text("条件"), hbox({
                                    hbox(text(" 类型  : "), input[0]->Render()),
                                    hbox(text(" 型号  : "), input[1]->Render()),
                                    hbox(text(" 归属  : "), input[2]->Render()),
                                    hbox(text(" 状态  : "), input[3]->Render()),
                                })),
           queryButton->Render(),
       }) | hcenter,
       table.data.Render() | hcenter});
});
