cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.1.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------
# --- Fetch SQLiteC++ ----------------------------------------------------------
FetchContent_Declare(SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
  GIT_TAG 3.3.0
)
FetchContent_MakeAvailable(SQLiteCpp)
# ------------------------------------------------------------------------------


project(osint)

# set(SRC_LIST src/tui/option/options.cpp src/tui/main.cpp src/tui/homescreen.cpp src/data/operate.cpp)
aux_source_directory(src/tui SRC_TUI_LIST)
aux_source_directory(src/tui/option SRC_TUI_OPTION_LIST)
aux_source_directory(src/tui/component SRC_TUI_COMPONENT_LIST)
aux_source_directory(src/db SRC_DB_LIST)
aux_source_directory(src/data SRC_DATA_LIST)

add_executable(${PROJECT_NAME} ${SRC_TUI_LIST} ${SRC_TUI_OPTION_LIST} ${SRC_TUI_COMPONENT_LIST} ${SRC_DB_LIST} ${SRC_DATA_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}   
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  SQLiteCpp
)

