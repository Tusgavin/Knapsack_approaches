#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include <queue>
#include <chrono>

#include "utils.hpp"

double knapsack_backtracking(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs
);

int main(int argc, char *argv[])
{
   std::vector<Item> weight_value_pairs;
   
   std::string file_name = std::string(argv[1]);
   int amount_of_items;
   double maximum_capacity;

   // Abrir e extrair informações do arquivo
   open_and_extract_file_info(file_name, weight_value_pairs, &amount_of_items, &maximum_capacity);

   auto start_program = std::chrono::steady_clock::now();

   double result = knapsack_backtracking(maximum_capacity, amount_of_items, weight_value_pairs);
   auto end_program = std::chrono::steady_clock::now();
   auto diff = end_program - start_program;

   std::cout << "Result is: " << result << std::endl;
   std::cout 
      << "The test '" 
      << file_name 
      << "' took " 
      << std::chrono::duration <double, std::milli>(diff).count() 
      << " milliseconds." 
      << std::endl;

   return 0;
}

double knapsack_backtracking(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs
)
{
   std::queue<TreeNode> Tree;
   TreeNode head;
   TreeNode node_aux_1;
   TreeNode node_aux_2;

   head.level = -1;
   head.accumulated_value = 0;
   head.accumulated_weight = 0;

   Tree.push(head);

   double best = 0;
   while (!Tree.empty())
   {
      node_aux_1 = Tree.front();
      Tree.pop();

      if (node_aux_1.level == amount_of_items - 1)
      {
         continue;
      }

      // Situação 1: Colocando o item atual na mochila
      // Atualizamos o level / item
      node_aux_2.level = node_aux_1.level + 1;
      // Atualizamos o peso com o item adicionado
      node_aux_2.accumulated_weight = node_aux_1.accumulated_weight + weight_value_pairs.at(node_aux_2.level).weight;
      // Atualizamos o valor com o item adicionado
      node_aux_2.accumulated_value = node_aux_1.accumulated_value + weight_value_pairs.at(node_aux_2.level).value;

      if (node_aux_2.accumulated_weight <= maximum_capacity && node_aux_2.accumulated_value > best)
      {
         best = node_aux_2.accumulated_value;
      }

      if (node_aux_2.accumulated_weight <= maximum_capacity) 
      {
         Tree.push(node_aux_2);
      }

      // Situação 2: Não colocando o item atual na mochila
      // Peso permanece o mesmo
      node_aux_2.accumulated_weight = node_aux_1.accumulated_weight;
      // Valor permanece o mesmo
      node_aux_2.accumulated_value = node_aux_1.accumulated_value;


      if (node_aux_2.accumulated_weight <= maximum_capacity) 
      {
         Tree.push(node_aux_2);
      }

   }

   return best;
}
