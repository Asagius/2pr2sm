#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Header.h"

int main() {
    int choice;
    List vect, vect2, vect3;

    vect.add_first(1);
    vect.add_last(2);
    vect.add_last(2);
    vect.add_last(2);
    vect.add_last(2);
    
    while (1) {
        std::cin >> choice;
        switch (choice) {
            case 1: // List showing
                vect.show();
                break;
            case 2: // Data adding
                vect.add_first(5);
                break;
            case 3: // Data deleting
                int a, b;
                std::cout << "Choose min limit: " << std::endl;
                std::cin >> a;
                std::cout << "Choose max limit: " << std::endl;
                std::cin >> b;
                vect.del(a, b);
                break;
            case 4: // List size
                std::cout << vect.getsize() << std::endl;
                break;
            case 5: // Lists copying
                vect2 = vect;
                break;
            case 6: // List comparison
                if (vect == vect2)
                    std::cout << "Lists are equal." << std::endl;
                if (vect > vect2)
                    std::cout << "The first list is bigger than the second one." << std::endl;;
                if (vect2 < vect)
                    std::cout << "The first list is smaller than the second one." << std::endl;
                break;
            case 7: // List sum
                vect + vect2;
                break;
            case 8: // Deleting iterative values
                vect.del_repeat();
                break;
            case 13: {
                return (0);
            }

        }
    }
}