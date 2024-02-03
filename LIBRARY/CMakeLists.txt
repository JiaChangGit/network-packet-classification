# 新增一個 CMake 目標，目標型態為靜態函式庫。
add_library(LIBRARY STATIC)

target_sources(LIBRARY
    PRIVATE
        "basis.cpp"
)
