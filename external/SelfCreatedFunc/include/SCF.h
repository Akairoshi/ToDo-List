#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <type_traits>

namespace scf
{
    template <typename Type>
    
    // функция безопасного ввода. работает со int, double, float, long, string
    Type safeInput(const std::string &prompt)
    {
        Type value;
        while (true)
        {
            std::cout << prompt;

            // проверка при int, long, float, double на то что бы в них вводилось число
            if constexpr (std::is_integral_v<Type> || std::is_floating_point_v<Type>)
            {
                if (!(std::cin >> value))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "! Enter number" << "\n";
                }
                else
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return value;
                }
            }

            // проверка при string на то что бы строка не была пустая
            else if constexpr (std::is_same_v<Type, std::string>)
            {
                std::getline(std::cin >> std::ws, value);
                if (value.empty())
                {
                    std::cout << "! String cannot bee empty" << "\n";
                }
                else
                {
                    return value;
                }
            }
        }
    };
}