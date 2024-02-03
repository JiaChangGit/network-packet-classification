# 新增一個 CMake 目標，目標型態為靜態函式庫。
add_library(IO STATIC)

target_sources(IO
    PRIVATE
        "input.cpp"
        "inputFile_test.cpp"
)
