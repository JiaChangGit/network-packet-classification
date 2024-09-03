# 新增一個 CMake 目標，目標型態為靜態函式庫。
add_library(lib-s STATIC)

# 定義一個編譯標誌，用於條件編譯
#add_definitions(-DCOVERCHECKER_MANY)

target_sources(lib-s
    PRIVATE
        "equivalentPri.cpp"
        "checkCovered_one.cpp"
        "hyperrectangleCoverChecker.cpp"
)
