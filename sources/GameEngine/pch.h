#pragma once

// STL
#include<set>
#include<random>
#include<limits>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>
#include<sstream>
#include<istream>
#include<fstream>
#include<assert.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<map>
#include<stack>

//External
#include "raylib.h"

#ifdef _DEBUG || DEBUG
#define LOG(level, message,...)\
        fprintf(stderr, "[%s] ", level);\
        fprintf(stderr, message, ##__VA_ARGS__);\
        fprintf(stderr, "\n")

#define LOG_INFO(message, ...) LOG("Info", message, ##__VA_ARGS__)
#define LOG_ERROR(message, ...) LOG("Error", message, ##__VA_ARGS__)
#define LOG_WARNING(message, ...) LOG("Warning", message, ##__VA_ARGS__)
#else
#define LOG_INFO
#define LOG_ERROR
#define LOG_WARNING
#endif

#define FREE_MEMORY(memory) if (memory) { delete memory; memory = nullptr; }

namespace Engine
{
    template<typename T> using Shared = std::shared_ptr<T>;
    template<typename T> using Unique = std::unique_ptr<T>;
}

#define GetDeltaTime() GetTime()
#define GetDeltaTime() GetTime() * 1000
#define MAX_FPS 60