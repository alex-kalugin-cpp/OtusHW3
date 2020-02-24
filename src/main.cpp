#include <iostream>
#include <map>
#include <vector>

#include "../include/allocator.h"
#include "../include/SimpleVector.h"

//simple factorial
size_t factorial(size_t n){
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;

}

int main()
{

        {
        //part 1 map with custom allocator
            std::map<std::size_t, std::size_t, std::less<std::size_t>, HW3::I_rob_this_allocator<std::pair<const int, std::size_t>,10>> mymap;

            for(std::size_t i = 0; i < 10; ++i){
                mymap[i]= factorial(i);
            }
            //отличный тест для проверки расширяемости:
            // mymap[10] = 10;
            for(auto& [key, value] : mymap){
                std::cout << key << " " << value << std::endl;
            }

     }

    {
        //part 2 custom container with std allocator
             SimpleVector<int,std::allocator<int>> vec1;
            for(int i = 0; i < 10; ++i){
                vec1.push_back(i);
            }

            for(const auto &i : vec1){
                std::cout << i << " ";
            }
             std::cout << std::endl;

            //part 3 custom container with custom allocator
            // 2 * size - потому что вектор
            SimpleVector<int, HW3::I_rob_this_allocator<int,2*10>> vec2;
            for(int i = 0; i < 10; ++i){
                vec2.push_back(i);
            }
            for(const auto &i : vec2){
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }

    return 0;
}
