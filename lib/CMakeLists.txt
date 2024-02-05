# 新增一個 CMake 目標，目標型態為靜態函式庫。
add_library(lib-s STATIC)

target_sources(lib-s
    PRIVATE
        "basis.cpp"
)
