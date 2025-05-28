#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <queue>
#include <limits>
#include <algorithm>
#include "Heap.h"

class Graph {
private:
    std::map<std::string, int> ipToIndex;
    std::vector<std::string> indexToIp;
    std::vector<std::vector<std::pair<int, int>>> adjList;

public:
    void loadGraph(std::istream& input) {
        int n, m;
        input >> n >> m;
        input.ignore();

        indexToIp.resize(n);
        for (int i = 0; i < n; ++i) {
            std::getline(input, indexToIp[i]);
            ipToIndex[indexToIp[i]] = i;
        }

        adjList.resize(n);
        for (int i = 0; i < m; ++i) {
            std::string mes, dia, hora, ipOrigen, ipDestino;
            int peso;
            std::string resto;

            input >> mes >> dia >> hora >> ipOrigen >> ipDestino >> peso;
            std::getline(input, resto);

            std::string ipO = ipOrigen.substr(0, ipOrigen.find(':'));
            std::string ipD = ipDestino.substr(0, ipDestino.find(':'));

            if (ipToIndex.count(ipO) && ipToIndex.count(ipD)) {
                int u = ipToIndex[ipO];
                int v = ipToIndex[ipD];
                adjList[u].push_back({v, peso});
            }
        }
    }

    void saveOutDegrees(const std::string& filename) {
        std::ofstream file(filename);
        for (size_t i = 0; i < adjList.size(); ++i) {
            file << indexToIp[i] << " " << adjList[i].size() << "\n";
        }
    }

    void saveTop5OutDegrees(const std::string& filename, std::string& botmaster) {
        Heap<std::pair<int, std::string>> heap;
        for (size_t i = 0; i < adjList.size(); ++i) {
            heap.push({(int)adjList[i].size(), indexToIp[i]});
        }

        std::ofstream file(filename);
        for (int i = 0; i < 5 && !heap.empty(); ++i) {
            auto top = heap.top();
            file << top.second << " " << top.first << "\n";
            if (i == 0) {
                botmaster = top.second;
            }
            heap.pop();
        }
    }

std::string findFirstConnection(std::istream& input, const std::string& botmaster) {
    int n, m;
    input >> n >> m;
    input.ignore();

    // Ignora la lista de IPs
    for (int i = 0; i < n; ++i) {
        std::string tmp;
        std::getline(input, tmp);
    }

    for (int i = 0; i < m; ++i) {
        std::string mes, dia, hora, ipOrigen, ipDestino;
        int peso;
        std::string resto;
        input >> mes >> dia >> hora >> ipOrigen >> ipDestino >> peso;
        std::getline(input, resto);  // Captura el resto por seguridad

        // Quita el puerto de la IP origen
        std::string ipSinPuerto = ipOrigen.substr(0, ipOrigen.find(':'));

        // Compara correctamente con el botmaster
        if (ipSinPuerto == botmaster) {
            return mes + " " + dia + " " + hora;
        }
    }

    return "No se encontro conexion";
}


    std::vector<int> dijkstra(const std::string& startIp) {
        int start = ipToIndex[startIp];
        std::vector<int> dist(adjList.size(), std::numeric_limits<int>::max());
        dist[start] = 0;

        std::set<std::pair<int, int>> pq;
        pq.insert({0, start});

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                if (dist[u] + w < dist[v]) {
                    pq.erase({dist[v], v});
                    dist[v] = dist[u] + w;
                    pq.insert({dist[v], v});
                }
            }
        }

        return dist;
    }

    void saveDistances(const std::string& filename, const std::vector<int>& dist) {
        std::ofstream file(filename);
        for (size_t i = 0; i < dist.size(); ++i) {
            if (dist[i] != std::numeric_limits<int>::max()) {
                file << indexToIp[i] << " " << dist[i] << "\n";
            }
        }
    }

    int findFarthestIp(const std::vector<int>& dist) {
        int maxDist = -1;
        int idx = -1;
        for (size_t i = 0; i < dist.size(); ++i) {
            if (dist[i] != std::numeric_limits<int>::max() && dist[i] > maxDist) {
                maxDist = dist[i];
                idx = i;
            }
        }
        return idx;
    }

    void savePath(const std::string& filename, const std::string& startIp, const std::string& endIp) {
        int start = ipToIndex[startIp];
        int end = ipToIndex[endIp];
        std::vector<int> dist(adjList.size(), std::numeric_limits<int>::max());
        std::vector<int> prev(adjList.size(), -1);
        dist[start] = 0;

        std::set<std::pair<int, int>> pq;
        pq.insert({0, start});

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                if (dist[u] + w < dist[v]) {
                    pq.erase({dist[v], v});
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.insert({dist[v], v});
                }
            }
        }

        std::vector<std::string> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(indexToIp[at]);
        }
        std::reverse(path.begin(), path.end());

        std::ofstream file(filename);
        for (const auto& ip : path) {
            file << ip << "\n";
        }
    }

    std::string getIpFromIndex(int index) const {
        return indexToIp[index];
    }
};

#endif
