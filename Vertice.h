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
        vector<Vertice*> neighbors; // Vertices adjacentes ou vizinhos
        bool visited;              // Campo booleano para identificar a visitação à esse vértice, utilizado para busca
        Vertice* predecessor;

    public: // Atributos públicos
        Vertice(string name, vector<Vertice*> neighbors) : name(name), neighbors(neighbors), visited(false), predecessor(nullptr)
        {
            // Testa a existência dos parâmetros
            if (name.empty() || neighbors.empty())
            {
                throw runtime_error("Parametros invalidos ou inexistentes");
            }
        }

        Vertice(string paramName) : name(paramName), neighbors({}), visited(false), predecessor(nullptr)
        {
            if (paramName.empty())
                throw runtime_error("Parametros invalidos ou inexistentes");
        }

        // Construtor sem parâmetros para a classe Vertice
        Vertice() : name(""), neighbors({}), visited(false), predecessor(nullptr)
        {
        }

        // Destrutor da classe Vertice
        ~Vertice()
        {
            name = nullptr;
            neighbors.clear();
            visited = false;
            predecessor = nullptr;
        }

        void printVertice()
        {
            cout << "Nome: " << name << endl;

            if (!neighbors.empty())
            {
                cout << "Vizinhos: ";
                for (int i = 0; i < neighbors.size(); i++)
                {
                    cout << neighbors[i]->getName();

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
            
            cout << "Antecessor: ";
            if(predecessor == nullptr){
                cout << "Vazio" << endl;
            }else{
                cout << predecessor->getName() << endl;
            }
        }

        void setNeighbor(Vertice* neighbor){
            if(!neighbor) throw runtime_error("Vizinho não informado");

            neighbors.push_back(neighbor);
            sort(neighbors.begin(), neighbors.end());
            neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
        }
        
        void setNeighbors(vector<Vertice*> neighborsVector){
            if(neighborsVector.empty()) throw runtime_error("Vizinhos não informados");

            neighbors = neighborsVector;
        }

        vector<Vertice*> getNeighbors(){return neighbors;}

        string getName(){
            return name;
        }

        void setVisited(bool vis){visited = vis;}
        bool getVisited(){return visited;}

        void setPredecessor(Vertice* pre){
            if(!pre) throw runtime_error("Vizinho não informado");

            predecessor = pre;
        }

        Vertice* getPredecessor(){return predecessor;}
};