#include "create_image.cpp"
#include "graph_algo.cpp"
#include "draw_graph.cpp"
#include "make_tests.cpp"
#include "..\\include\\libraries.hpp"
#include "..\\include\\bmp_structs.hpp"

void program(int V, int E, std::set <int> *graph, std::string outfilename, std::set <std::pair <int, int>> edges, int kae) {
    const int width = 800;
    const int height = 800;
    Pixel pixels[width][height];
    BMPHeader bmpHeader = {0x4D42, width * height * 3 + sizeof(BMPHeader) + sizeof(DIBHeader), 0, 0, sizeof(BMPHeader) + sizeof(DIBHeader)};
    DIBHeader dibHeader = {sizeof(DIBHeader), width, height, 1, 24, 0, width * height * 3, 2835, 2835, 0, 0};

    std::ofstream image(".\\output\\" + outfilename +".bmp", std::ios::binary);
    image.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));
    image.write(reinterpret_cast<char*>(&dibHeader), sizeof(DIBHeader));

    fill_field(pixels);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, (double)std::min(height, width));
    std::vector <Point> points;
    std::set <std::pair <double, double>> st;

    while (st.size() != V) {
        double l1 = distrib(gen), l2 = distrib(gen);
        st.insert(std::make_pair(l1, l2));
    }
    for (auto pt: st) {
        points.push_back((Point){pt.first, pt.second});
    }

    double L = sqrt((double)width * (double)height / V);
    fruchtermanReingold(points, graph, L, V, kae);
    scale_graph(points, V, height, width);
    for (int i = 0; i < V; ++i) {
        drawCircle(points[i].x, points[i].y, 5, pixels);
    }
    for (auto edge: edges) {
        drawLine(round(points[edge.first].x), round(points[edge.first].y), round(points[edge.second].x), round(points[edge.second].y), pixels);
    }
    // вписываем пиксели
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            image.write((char*)&pixels[x][y], sizeof(Pixel));
        }
    }
    image.close();
}

int main() {
    std::string path = ".\\input\\test_1.txt";
    std::ifstream inpfile(path, std::ios::in);
    if (!inpfile.is_open()) {
        std::cout << "File does not exist";
        return 0;
    }
    int V, E;
    inpfile >> V >> E;
    std::set <int> graph[V];
    std::set < std::pair <int, int> > edges;
    // инициализация графа
    for (int i = 0; i < E; ++i) {
        int a, b;
        inpfile >> a >> b;
        if (a != b) {
            graph[a].insert(b);
            graph[b].insert(a);
        }
    }
    std::string outfilename = "outtest1";
    program(V, E, graph, outfilename, edges, 100);
    inpfile.close();
    return 0;
}
