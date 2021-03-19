#include "utils.hpp"

void open_and_extract_file_info(
   std::string file_name,
   std::vector<Item> &info_vector,
   int *amount_of_items,
   double *maximum_capacity
)
{
   std::ifstream FILE;
   FILE.open(file_name, std::ios::in);

   std::string read_buffer;

   FILE >> read_buffer;
   *amount_of_items = atoi(read_buffer.c_str());

   FILE >> read_buffer;
   *maximum_capacity = ::atof(read_buffer.c_str());

   double value;
   double weight;
   for (int i = 0; i < *amount_of_items; ++i)
   {
      FILE >> read_buffer;
      value = ::atof(read_buffer.c_str());
      FILE >> read_buffer;
      weight = ::atof(read_buffer.c_str());

      Item new_item;
      new_item.value = value;
      new_item.weight = weight;
      new_item.ratio = (double)value / weight;

      info_vector.push_back(new_item);
   }

   FILE.close();
};