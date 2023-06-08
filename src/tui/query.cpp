#include "ftxui/dom/table.hpp"     // for Table, TableSelection
#include "ftxui/screen/screen.hpp" // for Screen
#include "include/operate.hpp"
#include <ftxui/dom/elements.hpp>
#include <string> // for basic_string, allocator, string
#include <vector> // for vector

#include "ftxui/component/component.hpp"
#include "ftxui/dom/node.hpp" // for Render
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui

using namespace ftxui;
//-------------------------------------------------------------------------
// ftxui::table is being improving
// ------------------------------------------------------------------------
std::string inputs[6];
Component input[6]{
    Input(&(inputs[0]), "Type"),
    Input(&(inputs[1]), "Specification"),
    Input(&(inputs[2]), "Red/Blue"),
    Input(&(inputs[3]), "Destoryed/Captured"),
};
class tables {
public:
  Database db;
  Table table = Table(db.LoadRecord());
  tables() {
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
  }
};

auto button = Button("查询", [] {});
auto compoment = Container::Horizontal({
    input[0],
    input[1],
    input[2],
    input[3],
    button,
});
auto records = Renderer(compoment, [] {
  tables table;
  return vbox(
      {hbox({
           window(text("条件"), hbox({
                                    hbox(text(" 型号  : "), input[0]->Render()),
                                    hbox(text(" 规格  : "), input[1]->Render()),
                                    hbox(text(" 归属  : "), input[2]->Render()),
                                    hbox(text(" 状态  : "), input[3]->Render()),
                                })),
           button->Render(),
       }) | hcenter,
       table.table.Render() | hcenter});
});
