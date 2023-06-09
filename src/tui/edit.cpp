#include "ftxui/component/component.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include "include/operate.hpp"
using namespace ftxui;
// this file will include some interface for user to edit data.
std::string inserts[6];
Component insert[6] = {
    Input(&(inserts[0]), "Type"),
    Input(&(inserts[1]), "Specification"),
    Input(&(inserts[2]), "Red/Blue"),
    Input(&(inserts[3]), "number"),
    Input(&(inserts[4]), "Destoryed/Captured"),
    Input(&(inserts[5]), "URL"),
};

auto insertButton = Button("执行", [] {
  Database::InsertRecord(inserts);
  Database::QueryRecord();
});
auto insertComponent = Container::Horizontal({
    insert[0],
    insert[1],
    insert[2],
    insert[3],
    insert[4],
    insert[5],
    insertButton,
});
auto edits = Renderer(insertComponent, [] {
  return vbox({
      hbox({
          window(text("添加记录"),
                 hbox({
                     hbox(text(" 类型  : "), insert[0]->Render()),
                     hbox(text(" 型号  : "), insert[1]->Render()),
                     hbox(text(" 归属  : "), insert[2]->Render()),
                     hbox(text(" 数量  : "), insert[3]->Render()),
                     hbox(text(" 状态  : "), insert[4]->Render()),
                     hbox(text(" 来源  : "), insert[5]->Render()),
                 })),
          insertButton->Render(),
      }) | hcenter,
  });
});
