cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(bare_keyboard C CXX)

add_bare_module(bare_keyboard)

if(WIN32)
  target_sources(${bare_keyboard} PRIVATE
    binding.c
    src/keyboard.cpp
  )
elseif(APPLE)
  target_sources(${bare_keyboard} PRIVATE
    binding.c
    src/macos.cpp
  )
  target_link_libraries(${bare_keyboard} PRIVATE
    "-framework ApplicationServices"
  )
elseif(UNIX)
  find_package(X11 REQUIRED)
  target_sources(${bare_keyboard} PRIVATE
    binding.c
    src/linux.cpp
  )
  target_include_directories(${bare_keyboard} PRIVATE ${X11_INCLUDE_DIR})
  target_link_libraries(${bare_keyboard} PRIVATE
    ${X11_LIBRARIES}
    ${X11_XTest_LIB}
  )
endif()