#include "ftxui/component/component.hpp"
#include "ftxui/screen/color.hpp" // for Color, Color::Blue, Color::Cyan, Color::White, ftxui
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include "data/database.hpp"
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
std::string deleted;
Component deleting = Input(&deleted, "number");
auto insertButton = Button("执行", [] {
  Database::InsertRecord(inserts);
  Database::QueryRecord();
});
auto deleteButton = Button("执行", [] {
  Database::DeleteRecord(deleted);
  Database::QueryRecord();
});
auto editComponent = Container::Horizontal({
    insert[0],
    insert[1],
    insert[2],
    insert[3],
    insert[4],
    insert[5],
    insertButton,
    deleting,
    deleteButton,
});

auto edits = Renderer(editComponent, [] {
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
      hbox({
          window(text("删除记录"),
                 hbox({
                     hbox(text(" 目标ID  : "), deleting->Render()),
                 })),
          deleteButton->Render(),
      }) | hcenter,
  });
});
