#include "Vertice.h"

//Declaração da classe Grafo
class Grafo{
    private: //atributos privados da classe Grafo
        vector<Vertice*> vertices; //Conjunto de vertices do grafo

    public: //atributos públicos da classe Grafo
        Grafo(vector<Vertice*> vertices) : vertices(vertices) {
            //Testa existência de parâmetros
            if(vertices.empty()) throw runtime_error("Parametros invalidos ou inexistentes");
        }

        //Construtor da classe sem parâmetros
        Grafo() : vertices({}){

        }

        //Destrutor da classe 
        ~Grafo(){
            vertices.clear(); //limpa conjunto de vertices
        }

        void printGrafo(){
            for(Vertice* i : vertices){
                i->printVertice();
                cout << endl;
            }
        }

        void organize(){
            vector<string> neighbors;
            for(Vertice* vertice : vertices){
                neighbors = vertice->getNeighbors();

                for(string neighbor : neighbors){
                    for(Vertice* vert : vertices){
                        if(neighbor == vert->getName()){
                            vert->setNeighbor(vertice->getName());
                        }
                    }
                }
                
                // vertice->setNeighbors(neighbors);
            }
        }

};
