#include <chrono> // for operator""ms, literals
#include <thread> // for sleep_for, thread

#include "db/database.hpp"
#include "tui/tabs.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

int main(int argc, char *argv[]) {
  // 初始化数据库
  Database::Init();

  using namespace ftxui;
  // 设置为终端全屏
  auto screen = ScreenInteractive::Fullscreen();

  std::atomic<bool> refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      screen.Post(Event::Custom);
    }
  });

  // 设置快捷键
  main_renderer |= CatchEvent([&](ftxui::Event event) {
    if (event == Event::F1) {
      tab_index = 0;
      return true;
    };
    if (event == Event::F2) {
      tab_index = 1;
      return true;
    }
    if (event == Event::F3) {
      tab_index = 2;
      return true;
    }
    if (event == Event::Escape) {
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  screen.Loop(main_renderer | bgcolor(Color::Black));
  refresh_ui_continue = false;
  refresh_ui.join();

  return 0;
}
