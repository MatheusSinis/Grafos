// Dependências
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Declaração da classe Vertice do Grafo
class Vertice
{
    private:                        // Atributos privados
        string name;                // Nome ou rótulo
        vector<Vertice*> neighbors; // Vertices adjacentes ou vizinhos
        bool visited;               // Campo booleano para identificar a visitação à esse vértice, utilizado para busca
        Vertice* predecessor;       // Campo referência para um vertice, que indica a partir de qual vizinho que a busca o encontrou, utilizado para busca

    public: // Atributos públicos
        
        //Construtor utilizando nome e vizinhos como parâmetro, variáveis usadas para busca, inicializadas de forma padrão
        Vertice(string name, vector<Vertice*> neighbors) : name(name), neighbors(neighbors), visited(false), predecessor(nullptr)
        {
            // Testa a existência dos parâmetros
            if (name.empty() || neighbors.empty())
            {
                throw runtime_error("Parametros invalidos ou inexistentes");
            }
        }

        //Construtor utilizando nome como parâmetro, variáveis usadas para busca, inicializadas de forma padrão
        Vertice(string paramName) : name(paramName), neighbors({}), visited(false), predecessor(nullptr)
        {
            if (paramName.empty())
                throw runtime_error("Parametros invalidos ou inexistentes");
        }

        // Construtor sem parâmetros para a classe Vertice, inicialização padrão para todas as variáveis
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

        //Método para printar os valores do vértice, exceto as variáveis que são utilizadas apenas para busca
        void printVertice()
        {
            //Print nome do vértice
            cout << "Nome: " << name << endl;

            //Se houver vizinhos, printar o nome de cada um deles
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
            else //Se não houver printar "[]"
            {
                cout << "Vizinhos: []" << endl;
            }

            //Código comentado para usar em testes
            // cout << "Visitado: " << visited << endl;
            
            // cout << "Antecessor: ";
            // if(predecessor == nullptr){
            //     cout << "Vazio" << endl;
            // }else{
            //     cout << predecessor->getName() << endl;
            // }
        }

        //Método para adicionar um vizinho na lista de vizinhos 
        void setNeighbor(Vertice* neighbor){
            //Se parâmetro não informado, lançar exceção
            if(!neighbor) throw runtime_error("Vizinho não informado");

            //Adicionar vizinho e organizar vetor de vizinhos
            neighbors.push_back(neighbor);
            sort(neighbors.begin(), neighbors.end());
            neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
        }
        
        //Método para incluir vetor de vizinhos no vértice
        void setNeighbors(vector<Vertice*> neighborsVector){
            //Teste para existência do parâmetro, se não houver, lançar erro
            if(neighborsVector.empty()) throw runtime_error("Vizinhos não informados");

            //Variável neighbors recebe vetor de vizinhos
            neighbors = neighborsVector;
        }

        //Obter vizinhos do vértice
        vector<Vertice*> getNeighbors(){return neighbors;}

        //Obter nome
        string getName(){
            return name;
        }

        //Incluir valor para variável "visited", utilizado na busca
        void setVisited(bool vis){visited = vis;}
        
        //Obter valor da variável "visited"
        bool getVisited(){return visited;}

        //Alterar valor do predecessor
        void setPredecessor(Vertice* pre){
            //variável "predecessor" recebe parâmetro
            predecessor = pre;
        }

        //Obter predecessor
        Vertice* getPredecessor(){return predecessor;}
};