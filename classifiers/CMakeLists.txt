# 新增一個 CMake 目標，目標型態為靜態函式庫。
add_library(classifiers-s STATIC)

target_sources(classifiers-s
    PRIVATE
    "linearSearch.cpp"
    "tSearch.cpp"

)
