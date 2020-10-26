#pragma once
#include <vector>
#include <map>
#include <memory>

class Figure;

extern std::vector<std::vector<int>> board;

extern std::map<int, std::shared_ptr<Figure>> figures;

enum class FIGURES;