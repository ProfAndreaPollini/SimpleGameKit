cmake_minimum_required(VERSION 3.27)
project(SimpleGameKit CXX)
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG 5.0
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/ProfAndreaPollini/raylib-cpp.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

FetchContent_Declare(
        RlImGui
        GIT_REPOSITORY https://github.com/ProfAndreaPollini/rlImGui.git
        GIT_TAG 2c0df9e55a94a9f6991770fd2c11e5a67d40255d
)
FetchContent_MakeAvailable(RlImGui)

FetchContent_Declare(
        LDtkLoader
        GIT_REPOSITORY https://github.com/Madour/LDtkLoader.git
        GIT_TAG master
)
FetchContent_MakeAvailable(ldtkloader)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG main
)
FetchContent_MakeAvailable(box2d)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(plog URL https://github.com/SergiusTheBest/plog/archive/refs/tags/1.1.10.tar.gz)
FetchContent_MakeAvailable(plog)

####### MACRO #######

macro(myproject_enable_cppcheck TARG WARNINGS_AS_ERRORS CPPCHECK_OPTIONS)
    find_program(CPPCHECK cppcheck)
    if (CPPCHECK)

        if (CMAKE_GENERATOR MATCHES ".*Visual Studio.*")
            set(CPPCHECK_TEMPLATE "vs")
        else ()
            set(CPPCHECK_TEMPLATE "gcc")
        endif ()

        if ("${CPPCHECK_OPTIONS}" STREQUAL "")
            # Enable all warnings that are actionable by the user of this toolset
            # style should enable the other 3, but we'll be explicit just in case
            set_target_properties( "${TARG}" PROPERTIES CMAKE_CXX_CPPCHECK
                    ${CPPCHECK}
                    --template=${CPPCHECK_TEMPLATE}
                    --enable=style,performance,warning,portability
                    --inline-suppr
                    # We cannot act on a bug/missing feature of cppcheck
                    --suppress=cppcheckError
                    --suppress=internalAstError
                    # if a file does not have an internalAstError, we get an unmatchedSuppression error
                    --suppress=unmatchedSuppression
                    # noisy and incorrect sometimes
                    --suppress=passedByValue
                    # ignores code that cppcheck thinks is invalid C++
                    --suppress=syntaxError
                    --suppress=preprocessorErrorDirective
                    --inconclusive)
        else ()
            # if the user provides a CPPCHECK_OPTIONS with a template specified, it will override this template
            set_target_properties( "${TARG}" PROPERTIES CMAKE_CXX_CPPCHECK ${CPPCHECK} --template=${CPPCHECK_TEMPLATE}
            ${CPPCHECK_OPTIONS})
        endif ()

        if (NOT
                "${CMAKE_CXX_STANDARD}"
                STREQUAL
                "")
            set_target_properties( "${TARG}" PROPERTIES CMAKE_CXX_CPPCHECK ${CMAKE_CXX_CPPCHECK} --std=c++${CMAKE_CXX_STANDARD})
        endif ()
        if (${WARNINGS_AS_ERRORS})
            list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
        endif ()
    else ()
        message(${WARNING_MESSAGE} "cppcheck requested but executable not found")
    endif ()
endmacro()

######## MACRO END ########


##### TESTING #####
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(tests
    tests/core.cpp
    tests/entity.cpp)
target_link_libraries(tests GTest::gtest_main SimpleGameKit)
include(GoogleTest)
gtest_discover_tests(tests)
##### TESTING END #####


set(MODULE_FILES
    src/SimpleGameKit.cpp
    src/Core/Game.cpp
    src/Core/InputManager.cpp
    src/Core/AssetManager.cpp
    src/Core/Scene.cpp
    src/Core/Renderer.cpp
    src/Core/Entity.cpp
    src/Core/EntityManager.cpp
)


add_library(${PROJECT_NAME} STATIC ${MODULE_FILES})
myproject_enable_cppcheck(${PROJECT_NAME} WARNINGS_AS_ERRORS "")

target_link_libraries(${PROJECT_NAME} PUBLIC plog raylib raylib_cpp RlImGui imgui nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC include)