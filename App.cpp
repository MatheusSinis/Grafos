#include "Grafo.h"
#include <sstream>

using namespace std;

vector<string> splitString(string text, char token){
    if(text.empty() || token == '\0') throw runtime_error("Texto ou token não foram informados");

    istringstream iss(text);
    vector<string> retorno;
    string item;

    while(getline(iss, item, token)){
        retorno.push_back(item);
    }

    return retorno;
}

int main()
{
    string name = "";
    string neighbors = "";
    vector<string> neighborsNames;
    vector<Vertice*> vertices;

    cout << "Ola! Por favor digite o nome dos vertices que deseja criar. Quando desejar parar digite 'PARE'!" << endl;
    do
    {
        cout << "Nome ou PARE: ";
        cin >> name;

        if (name != "PARE")
        {
            Vertice *obj = new Vertice(name);
            vertices.push_back(obj);
        }
    } while (name != "PARE");

    if (vertices.empty())
    {
        cout << "Fim do programa!" << endl;
        return 0;
    }

    cout << endl;
    cout << "Agora informe o(s) vizinho(s) de cada vertice." << endl;
    cout << "Exemplos:" << endl;
    cout << "1 vizinho: 'Vizinho(s) de A: B'" << endl;
    cout << "Mais de 1 vizinho: 'Vizinho(s) de A: B,C,D'" << endl;
    cout << "Nenhum vizinho: 'Vizinho(s) de A: []'" << endl;
    cout << endl;

    for(Vertice* vertice : vertices){
        cout << "Vizinho(s) de " << vertice->getName() << " : ";
        cin >> neighbors;
        
        neighborsNames = splitString(neighbors, ',');

        for(string name : neighborsNames){
            for(Vertice* vert : vertices){
                if(name == vert->getName()){
                    vertice->setNeighbor(vert);
                }
            }
        }
    }

    cout << endl;

    Grafo *grafo = new Grafo(vertices);
    grafo->organize();
    grafo->printGrafo();

    cout << endl;

    cout << "Fim do programa!" << endl;

    return 0;
}