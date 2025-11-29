#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <cstdint>


int heidic_main();
float add(float a, float b);
float multiply(float a, float b);

int heidic_main() {
        std::cout << "Hello, HEIDIC v2!\n" << std::endl;
        float x = 10;
        float y = 20;
        float result = (x + y);
        std::cout << "10.0 + 20.0 = " << std::endl;
        std::cout << result << std::endl;
        std::cout << "\n" << std::endl;
        float health = 100;
        float damage = 25;
        float new_health = (health - damage);
        std::cout << "Health: " << std::endl;
        std::cout << health << std::endl;
        std::cout << " - Damage: " << std::endl;
        std::cout << damage << std::endl;
        std::cout << " = New Health: " << std::endl;
        std::cout << new_health << std::endl;
        std::cout << "\n" << std::endl;
        if ((new_health > 0)) {
            std::cout << "Player is alive!\n" << std::endl;
        } else {
            std::cout << "Player is dead!\n" << std::endl;
        }
        std::cout << "Counting from 1 to 5:\n" << std::endl;
        int32_t counter = 1;
        while ((counter <= 5)) {
            std::cout << "  Count: " << std::endl;
            std::cout << counter << std::endl;
            std::cout << "\n" << std::endl;
            counter = (counter + 1);
        }
        float sum = add(15, 25);
        std::cout << "add(15.0, 25.0) = " << std::endl;
        std::cout << sum << std::endl;
        std::cout << "\n" << std::endl;
        float product = multiply(3, 7);
        std::cout << "multiply(3.0, 7.0) = " << std::endl;
        std::cout << product << std::endl;
        std::cout << "\n" << std::endl;
        std::cout << "Program complete!\n" << std::endl;
        return 0;
}

float add(float a, float b) {
        return (a + b);
}

float multiply(float a, float b) {
        return (a * b);
}

int main(int argc, char* argv[]) {
    heidic_main();
    return 0;
}
