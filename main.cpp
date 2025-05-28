#include <fstream>
#include <iostream>
#include "Graph.h"

int main() {
    std::ifstream bitacora("bitacoraGrafos.txt");
    Graph g;
    g.loadGraph(bitacora);

    g.saveOutDegrees("grados_ips.txt");

    std::string botmaster;
    g.saveTop5OutDegrees("mayores_grados_ips.txt", botmaster);
    std::cout << "Botmaster sospechoso: " << botmaster << "\n";

    // Nueva lectura para reinicializar el grafo y encontrar la conexión
    std::ifstream bitacora2("bitacoraGrafos.txt");
    Graph g2;
    g2.loadGraph(bitacora2);
    std::ifstream bitacora3("bitacoraGrafos.txt");
    std::string primeraConexion = g2.findFirstConnection(bitacora3, botmaster);
    std::cout << "Primera conexión del botmaster: " << primeraConexion << "\n";

    std::vector<int> distancias = g.dijkstra(botmaster);
    g.saveDistances("distancia_botmaster.txt", distancias);

    int idxLejano = g.findFarthestIp(distancias);
    std::string ipLejana = g.getIpFromIndex(idxLejano);
    std::cout << "IP más difícil de atacar: " << ipLejana << "\n";

    g.savePath("ataque_botmaster.txt", botmaster, ipLejana);

    return 0;
}
