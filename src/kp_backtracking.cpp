#include "utils.hpp"

double knapsack_backtracking(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs,
   double best,
   int index
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

   double best = 0;
   int index = 0;

   double result = knapsack_backtracking(maximum_capacity,
                                          amount_of_items,
                                          weight_value_pairs,
                                          best,
                                          index
                                       );
   auto end_program = std::chrono::steady_clock::now();
   auto diff = end_program - start_program;

   std::cout 
      << "result: " << result << " " 
      << "file: " << file_name << " "
      << "time: " << std::chrono::duration <double, std::milli>(diff).count() 
      << std::endl;

   return 0;
}

double knapsack_backtracking(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs,
   double best,
   int index
)
{
   // Se encher a mochila ou passar por todos os itens, chegamos a uma solução
   if (maximum_capacity == 0 || index == amount_of_items - 1)
   {
      // Pode existir o caso em que estamos no ultimo item e ele cabe na mochila, então atualizamos o melhor valor
      if (index == amount_of_items - 1 && maximum_capacity >= weight_value_pairs.at(index).weight)
      {
         best += weight_value_pairs.at(index).value;
      }
      return best;
   }

   // Se a mochila não suporta o peso do item, consideramos apenas o caso de não inserção
   else if (maximum_capacity < weight_value_pairs.at(index).weight)
   {
      return knapsack_backtracking(maximum_capacity, amount_of_items, weight_value_pairs, best, index + 1);
   }
   // Se a mochila suportar o item atual
   else
   {
      // Existem duas novas soluções parciais
      // Incluindo ou excluindo o item
      double max_capacity_after_add_item = maximum_capacity - weight_value_pairs.at(index).weight;
      double new_best_after_add_item_value = best + weight_value_pairs.at(index).value;
      return std::max(knapsack_backtracking(
                        max_capacity_after_add_item,
                        amount_of_items,
                        weight_value_pairs,
                        new_best_after_add_item_value,
                        index + 1
                     ),
                     knapsack_backtracking(
                        maximum_capacity,
                        amount_of_items,
                        weight_value_pairs,
                        best,
                        index + 1
                     )
                  );
   }
}
