#include <ftxui/dom/elements.hpp> // for color, Fit, LIGHT, align_right, bold, DOUBLE
#include <ftxui/dom/table.hpp>     // for Table, TableSelection
#include <ftxui/screen/screen.hpp> // for Screen
#include <string>                  // for basic_string, allocator, string
#include <vector>                  // for vector

#include "ftxui/dom/node.hpp" // for Render
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui

#include <ftxui/component/component.hpp>

#include "include/operate.hpp"
using namespace ftxui;
//-------------------------------------------------------------------------
// ftxui::table is inappropriate and stupid,these codes will be refactoring
// ------------------------------------------------------------------------
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
auto records = Renderer([] {
  tables table;
  return vbox({table.table.Render() | hcenter});
});
