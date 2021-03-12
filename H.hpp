#pragma once
#include <vector>
#include "element.hpp"

void H2(Element* e, std::vector<std::vector<double>>& H_, std::vector<std::vector<double>>& C_, std::vector<double>& P_);
void H3(Element* e, std::vector<std::vector<double>>& H_, std::vector<std::vector<double>>& C_, std::vector<double>& P_);
void integrated_H(std::vector<Element*> elements, std::vector<std::vector<double>>& H_, std::vector<std::vector<double>>& C_, std::vector<double>& P_);