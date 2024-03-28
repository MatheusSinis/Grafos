// Dependências
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Declaração da classe Vertice do Grafo
class Vertice
{
    private:                       // Atributos privados
        string name;               // Nome ou rótulo
        vector<string> neighbors; // Vertices adjacentes ou vizinhos
        bool visited;              // Campo booleano para identificar a visitação à esse vértice, utilizado para busca

    public: // Atributos públicos
        Vertice(string name, vector<string> neighbors) : name(name), neighbors(neighbors), visited(false)
        {
            // Testa a existência dos parâmetros
            if (name.empty() || neighbors.empty())
            {
                throw runtime_error("Parametros invalidos ou inexistentes");
            }
        }

        Vertice(string paramName) : name(paramName), neighbors({}), visited(false)
        {
            if (paramName.empty())
                throw runtime_error("Parametros invalidos ou inexistentes");
        }

        // Construtor sem parâmetros para a classe Vertice
        Vertice() : name(""), neighbors({}), visited(false)
        {
        }

        // Destrutor da classe Vertice
        ~Vertice()
        {
            name = nullptr;
            neighbors.clear();
            visited = false;
        }

        void printVertice()
        {
            cout << "Nome: " << name << endl;

            if (!neighbors.empty())
            {
                cout << "Vizinhos: ";
                for (int i = 0; i < neighbors.size(); i++)
                {
                    cout << neighbors[i];

                    if(i != (neighbors.size()-1)){
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            else
            {
                cout << "Vizinhos: []" << endl;
            }

            cout << "Visitado: " << visited << endl;
        }

        void setNeighbor(string neighbor){
            if(neighbor.empty()) throw runtime_error("Vizinho não informado");

            if(neighbor != "[]"){
                neighbors.push_back(neighbor);
                sort(neighbors.begin(), neighbors.end());
                neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
            }
        }
        
        void setNeighbors(vector<string> neighborsVector){
            if(neighborsVector.empty()) throw runtime_error("Vizinho não informado");

            neighbors = neighborsVector;
        }

        vector<string> getNeighbors(){return neighbors;}

        string getName(){
            return name;
        }
};