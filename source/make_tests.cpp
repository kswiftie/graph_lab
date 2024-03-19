#include "..\\include\\make_tests.hpp"

void create(int V, int test_name) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, V);
    std::uniform_int_distribution<> E_rand(0, 2000);
    std::ofstream file(".\\input\\test_" + std::to_string(test_name) + ".txt");
    file << V << " " << E_rand(gen) << "\n";
    for (int i = 0; i < V; ++i) {
        file << distrib(gen) << " " << distrib(gen) << "\n";
    }
    file.close();
}

/*
int main() {
    int vertexes[8] = {10, 50, 100, 200, 300, 500, 700, 1000};
    for (int t = 0; t < 8; ++t) {
        create(vertexes[t], t + 1);
    }
    return 0;
}
*/