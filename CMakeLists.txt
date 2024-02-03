cmake_minimum_required(VERSION 3.10)
project(classify VERSION 1.0)
set(CMAKE_VERBOSE_MAKEFILE ON)

# set(CMAKE_CXX_STANDARD 11) # 將 C++ 標準設定為 C++ 11
# set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++ 11 是強制要求，不會衰退至低版本
# flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_EXTENSIONS OFF) # 禁止使用編譯器特有擴充套件

# 新增一個 CMake 目標，目標型態為可執行檔。
add_executable(main)

# 指定建置該 CMake 目標時所使用的來源檔案，不必包含標頭檔。
# PRIVATE之後列出來的檔案路徑是從 CMakeLists.txt 所在的目錄起始的相對
# 路徑。以空格區隔即可，換行加縮排是為了可讀性和方便編輯。
target_sources(main
    PRIVATE
        "main.cpp"
)

# 新增有 Include 的目錄
target_include_directories(main
    PRIVATE
        "IO/"
        "LIBRARY/"
)
# 將指定資料夾的 CMake 專案（含有 CMakeLists.txt）一起加入建置。
add_subdirectory("IO/")
add_subdirectory("LIBRARY/")

# 新增目標所連結的函式庫。函式庫名稱為其他 CMake 專案的目標名稱。通常來自
# find_package 或 add_subdirectory。以這個範例來說，IO函式庫是來自
# add_subdirectory 指令所加入的 CMake 專案。
target_link_libraries(main
    PRIVATE
        IO
        LIBRARY
)

message("Processing CMakeLists.txt")
