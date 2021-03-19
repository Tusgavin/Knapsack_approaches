#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include <queue>
#include <chrono>

typedef struct TreeNode {
   int level;
   double accumulated_value;
   double accumulated_weight;
   double bound; 
} TreeNode;

typedef struct Item {
   double value;
   double weight;
   double ratio;
} Item;

void open_and_extract_file_info(
   std::string file_name,
   std::vector<Item> &info_vector,
   int *amount_of_items,
   double *maximum_capacity
);

#endif  // UTILS_HPP