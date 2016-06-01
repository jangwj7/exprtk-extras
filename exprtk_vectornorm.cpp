/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * ExprTk L-Norm Of A Vector                                  *
 * Author: Arash Partow (1999-2016)                           *
 * URL: http://www.partow.net/programming/exprtk/index.html   *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the Common Public License.         *
 * http://www.opensource.org/licenses/cpl1.0.php              *
 *                                                            *
 **************************************************************
*/


#include <cstdio>
#include <iostream>
#include <string>

#include "exprtk.hpp"


template <typename T>
struct norm : public exprtk::igeneric_function<T>
{
   typedef typename exprtk::igeneric_function<T>::parameter_list_t
                                                  parameter_list_t;

   typedef typename exprtk::igeneric_function<T>::generic_type
                                                  generic_type;

   typedef typename generic_type::scalar_view scalar_t;
   typedef typename generic_type::vector_view vector_t;

   norm()
   : exprtk::igeneric_function<T>("V|VT")
   {}

   inline T operator()(const std::size_t& ps_index, parameter_list_t parameters)
   {
      unsigned int l = 2;

      if (1 == ps_index)
      {
         scalar_t scalar(parameters[1]);

         if (scalar() < T(1))
            return std::numeric_limits<T>::quiet_NaN();

         if (!exprtk::details::numeric::is_integer(scalar()))
            return std::numeric_limits<T>::quiet_NaN();

         l = static_cast<int>(scalar());
      }

      switch (l)
      {
         #define norm_def(N) case  N : return norm_impl<N>(vector_t(parameters[0]));
         norm_def( 1) norm_def( 2) norm_def( 3) norm_def( 4)
         norm_def( 5) norm_def( 6) norm_def( 7) norm_def( 8)
         norm_def( 9) norm_def(10) norm_def(11) norm_def(12)
         norm_def(13) norm_def(14) norm_def(15) norm_def(16)
         norm_def(17) norm_def(18) norm_def(19) norm_def(20)
         norm_def(21) norm_def(22) norm_def(23) norm_def(24)
         norm_def(25) norm_def(26) norm_def(27) norm_def(28)
         norm_def(29) norm_def(30) norm_def(31) norm_def(32)
         default : return norm_impl(vector_t(parameters[0]),l);
      }
   }

   template <unsigned int Pow>
   inline T norm_impl(const vector_t& vector)
   {
      T sum = T(0);

      for (std::size_t i = 0; i < vector.size(); ++i)
      {
         sum += exprtk::details::numeric::fast_exp<T,Pow>::result(vector[i]);
      }

      switch (Pow)
      {
         case 1  : return sum;
         case 2  : return exprtk::details::numeric::sqrt(sum);
         default : return exprtk::details::numeric::pow(sum, T(1) / Pow);
      }
   }

   inline T norm_impl(const vector_t& vector, unsigned int pow)
   {
      T sum = T(0);

      for (std::size_t i = 0; i < vector.size(); ++i)
      {
         sum += exprtk::details::numeric::pow(vector[i],T(pow));
      }

      return exprtk::details::numeric::pow(sum,T(1) / pow);
   }
};

template <typename T>
void norm_of_vector()
{
   typedef exprtk::symbol_table<T> symbol_table_t;
   typedef exprtk::expression<T>     expression_t;
   typedef exprtk::parser<T>             parser_t;

   symbol_table_t symbol_table;

   T x[] = { T(1), T(2), T(3) , T(4) };

   symbol_table.add_vector("x", x);

   norm<T> norm_;

   symbol_table.add_function("norm",norm_);

   std::string vector_norm_program[] =
               {
                  "norm(x)     ",
                  "norm(x,1)   ",
                  "norm(x,2)   ",
                  "norm(x,3)   ",
                  "norm(x,4)   ",
                  "norm(x,5)   ",
                  "norm(2x+1)  ",
                  "norm(2x+1,1)",
                  "norm(2x+1,2)",
                  "norm(2x+1,3)",
                  "norm(2x+1,4)",
                  "norm(2x+1,5)"
               };

   const std::size_t vecnorm_program_size = sizeof(vector_norm_program) / sizeof(std::string);

   parser_t parser;

   for (std::size_t i = 0; i < vecnorm_program_size; ++i)
   {
      expression_t expression;
      expression.register_symbol_table(symbol_table);

      parser.compile(vector_norm_program[i], expression);

      printf("%s = %15.8f\n",
             vector_norm_program[i].c_str(),
             expression.value());
   }
}

int main()
{
   norm_of_vector<double>();
   return 0;
}