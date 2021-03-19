#include "utils.hpp"

double knapsack_branch_and_bound(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs
);

double get_node_bound(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs,
   TreeNode current
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

   // Ordenar vetor pelo valor relativo
   std::sort(weight_value_pairs.begin(), weight_value_pairs.end(), [](Item a, Item b) {
      return (a.ratio > b.ratio);
   });

   double result = knapsack_branch_and_bound(maximum_capacity, amount_of_items, weight_value_pairs);
   auto end_program = std::chrono::steady_clock::now();
   auto diff = end_program - start_program;

   std::cout 
      << "result: " << result << " " 
      << "file: " << file_name << " "
      << "time: " << std::chrono::duration <double, std::milli>(diff).count() 
      << std::endl;

   return 0;
}

double knapsack_branch_and_bound(
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

      // Se o peso estiver inferior à capacidade maxima e o melhor valor é superado, atualizamos melhor valor encontrado
      if (node_aux_2.accumulated_weight <= maximum_capacity && node_aux_2.accumulated_value > best)
      {
         best = node_aux_2.accumulated_value;
      }

      // Se peso atual maior ou igual à capacidade maxima, não há possibilidade de inserção de mais itens na mochila
      if (node_aux_2.accumulated_weight < maximum_capacity)
      {
         // Se conseguimos adicionar mais itens, fazemos estimativa do lucro máximo
         node_aux_2.bound = get_node_bound(maximum_capacity, amount_of_items, weight_value_pairs, node_aux_2);
         if (node_aux_2.bound > best)
         {
            Tree.push(node_aux_2);
         }
      }

      // Situação 2: Não colocando o item atual na mochila
      // Peso permanece o mesmo
      node_aux_2.accumulated_weight = node_aux_1.accumulated_weight;
      // Valor permanece o mesmo
      node_aux_2.accumulated_value = node_aux_1.accumulated_value;

      // Como não adicionamos nenhum item, o melhor valor encontrado não sofre alteração

      // Se peso atual maior ou igual à capacidade maxima, não há possibilidade de inserção de mais itens na mochila
      if (node_aux_2.accumulated_weight < maximum_capacity)
      {
         // Se conseguimos adicionar mais itens, fazemos estimativa do lucro máximo
         node_aux_2.bound = get_node_bound(maximum_capacity, amount_of_items, weight_value_pairs, node_aux_2);
         if (node_aux_2.bound > best)
         {
            Tree.push(node_aux_2);
         }
      }
   }

   return best;
}

// Função de estimativa de lucro
double get_node_bound(
   double maximum_capacity,
   int amount_of_items,
   std::vector<Item> weight_value_pairs,
   TreeNode current
)
{
   double upper_bound = current.accumulated_value;
   int next_item_index = current.level + 1;
   double total_weight = current.accumulated_weight;

   // Estimamos o lucro a partir do item i calculando (peso_maximo - peso_atual) frações do item (i + 1) que podemos adicionar
   if (next_item_index < amount_of_items)
   {
      upper_bound += 
         (maximum_capacity - total_weight) * 
         (weight_value_pairs.at(next_item_index).value /
         weight_value_pairs.at(next_item_index).weight);
   }

   return upper_bound;
}
