cmake_minimum_required(VERSION 3.30.5)
project(Jogo LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Adiciona o diretório include ao caminho de busca dos headers
include_directories(include)

# Define o PROJECT_ROOT como variável global
add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Procura de forma recursiva os arquivos .cpp na pasta src e salva em sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)

add_executable(main ${sources})
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
