//Dependências
#include "Grafo.h"
#include <sstream>

using namespace std;

//Método para dividir string
vector<string> splitString(string text, char token){
    //Testa existência de parâmetros, se não houver lança exceção
    if(text.empty() || token == '\0') throw runtime_error("Texto ou token não foram informados");

    //Inicializa "leitor" da string, variável de retorno e auxiliar
    istringstream iss(text);
    vector<string> retorno;
    string item;

    //Para cada "split" feito, adiciona na variável de retorno
    while(getline(iss, item, token)){
        retorno.push_back(item);
    }

    //Retorno da função
    return retorno;
}

//Função principal
int main()
{
    //Inicialização de variáveis
    string name = "";
    string neighbors = "";
    vector<string> neighborsNames;
    vector<Vertice*> vertices;

    //Introdução ao programa
    cout << "Ola! Por favor digite o nome dos vertices que deseja criar. Quando desejar parar digite 'PARE'!" << endl;
    
    //Enquanto entrada for diferente de 'PARE', lê o nome dos vértices
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

    //Se não foi informado nenhum vértice, programa é finalizado
    if (vertices.empty())
    {
        cout << "Fim do programa!" << endl;
        return 0;
    }

    //Instruções para introdução de vizinhos a cada vértice
    cout << endl;
    cout << "Agora informe o(s) vizinho(s) de cada vertice." << endl;
    cout << "Exemplos:" << endl;
    cout << "1 vizinho: 'Vizinho(s) de A: B'" << endl;
    cout << "Mais de 1 vizinho: 'Vizinho(s) de A: B,C,D'" << endl;
    cout << "Nenhum vizinho: 'Vizinho(s) de A: []'" << endl;
    cout << endl;

    //Para cada vértice, inclui os vizinhos em sua lista
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

    //Quebra de linha
    cout << endl;

    //Inicializa grafo e o organiza, considerando que é um grafo não direcionado
    Grafo *grafo = new Grafo(vertices);
    grafo->organize();

    //Contagem de ciclos usando busca em profundidade
    // grafo->countCicles("dfs");

    grafo->permutacao(grafo->getVertices()[0]);

    //Printa o grafo
    // grafo->printGrafo();

    //Quebra de linha e saída indicando fim do programa
    cout << endl;
    cout << "Fim do programa!" << endl;

    //Fim da função principal
    return 0;
}