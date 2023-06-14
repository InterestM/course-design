#include <chrono> // for operator""ms, literals
#include <thread> // for sleep_for, thread

#include "db/database.hpp"
#include "tui/tabs.hpp"

#include "ftxui/component/component.hpp" // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include <ftxui/dom/elements.hpp>

int main(int argc, char *argv[]) {
  Database::Init();

  using namespace ftxui;
  auto screen = ScreenInteractive::Fullscreen();

  std::atomic<bool> refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      screen.Post(Event::Custom);
    }
  });

  screen.Loop(main_renderer | bgcolor(Color::Black));
  refresh_ui_continue = false;
  refresh_ui.join();

  return 0;
}
