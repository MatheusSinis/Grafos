#include "Vertice.h"
#include <stack>
#include <queue>

// Declaração da classe Grafo
class Grafo
{
private:                        // atributos privados da classe Grafo
    vector<Vertice *> vertices; // Conjunto de vertices do grafo
    int cicles;

public: // atributos públicos da classe Grafo
    Grafo(vector<Vertice *> vertices) : vertices(vertices), cicles(0)
    {
        // Testa existência de parâmetros
        if (vertices.empty())
            throw runtime_error("Parametros invalidos ou inexistentes");
    }

    // Construtor da classe sem parâmetros
    Grafo() : vertices({}), cicles(0)
    {
    }

    // Destrutor da classe
    ~Grafo()
    {
        vertices.clear(); // limpa conjunto de vertices
        cicles = 0;
    }

    void printGrafo()
    {
        cout << "Ciclos: " << cicles << endl;
        cout << endl;
        for (Vertice *i : vertices)
        {
            i->printVertice();
            cout << endl;
        }
    }

    void organize()
    {
        vector<Vertice *> neighbors;
        for (Vertice *vertice : vertices)
        {
            neighbors = vertice->getNeighbors();

            for (Vertice *neighbor : neighbors)
            {
                for (Vertice *vert : vertices)
                {
                    if (neighbor->getName() == vert->getName())
                    {
                        vert->setNeighbor(vertice);
                    }
                }
            }
        }
    }

    void buscaLargura(Vertice *start)
    {
        queue<Vertice *> queue;
        Vertice* aux = new Vertice();
        
        start->setVisited(true);
        queue.push(start);

        do
        {
            aux = queue.front();
            // cout << aux->getName() << endl;
            queue.pop();

            for(Vertice* vert : aux->getNeighbors()){
                if(!vert->getVisited()){
                    vert->setVisited(true);
                    queue.push(vert);
                }
            }

        } while (!queue.empty());
    }

    vector<Vertice*> getVertices(){return vertices;}

    void buscaProfundidade(Vertice* start){
        stack<Vertice *> stack;
        Vertice* aux = new Vertice();
        vector<Vertice*> neighbors;
        
        start->setVisited(true);
        stack.push(start);

        do
        {
            aux = stack.top();
            // cout << aux->getName() << endl;
            stack.pop();

            neighbors = aux->getNeighbors();
            for (int i = (neighbors.size()-1); i >= 0; i--) {
                if(!neighbors[i]->getVisited()){
                    neighbors[i]->setVisited(true);
                    neighbors[i]->setPredecessor(aux);
                    stack.push(neighbors[i]);
                }else if(neighbors[i] != aux->getPredecessor()){
                    cicles++;
                }
            }

        } while (!stack.empty());

        cicles = cicles/2;
    }
};
