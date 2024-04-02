// Dependências
#include "Vertice.h"
#include <stack>
#include <queue>
#include <sstream>
#include <set>
#include <list>

// Declaração da classe Grafo
class Grafo
{
private:                        // atributos privados da classe Grafo
    vector<Vertice *> vertices; // Conjunto de vertices do grafo
    int cicles;                 // Variável que indica número de ciclos no grafp

public: // atributos públicos da classe Grafo
    // Construtor tendo o vetor de vértices como parâmetro, número de ciclos é igual a zero, por padrão
    Grafo(vector<Vertice *> vertices) : vertices(vertices), cicles(0)
    {
        // Testa existência de parâmetros, se não houver lança exceção
        if (vertices.empty())
            throw runtime_error("Parametros invalidos ou inexistentes");
    }

    // Construtor da classe sem parâmetros, passando valores padrões para classe
    Grafo() : vertices({}), cicles(0)
    {
    }

    // Destrutor da classe
    ~Grafo()
    {
        vertices.clear(); // limpa conjunto de vertices
        cicles = 0;
    }

    // Método para obter os vértices do grafo
    vector<Vertice *> getVertices() { return vertices; }

    // Método para printar grafo
    void printGrafo()
    {
        // Print no número de ciclos de um grafo
        cout << "Ciclos: " << cicles << endl;
        cout << endl;

        cout << "Vizinhos" << endl;
        // Printa os valores de cada vértice de um grafo
        for (Vertice *i : vertices)
        {
            i->printVertice();
            cout << endl;
        }
    }

    // Método para adicionar os vizinhos necessários em cada vértice, considerando que o grafo é não direcionado
    void organize()
    {
        vector<Vertice *> neighbors;

        // Para cada vértice, procura seus vizinhos, e se ele não tiver na lista de vizinhos do seu vizinho, ele é adicionado
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

    //Método para setar todos os vertices que foram visitados como não visitados, para não afetar buscas futuras
    void cleanVertices(Vertice* notVertice){
        for(int i = 0; i < vertices.size(); i++){
            if(vertices[i] == notVertice) continue;
            
            if(vertices[i]->getVisited()){
                vertices[i]->setVisited(false);
            }

            if(vertices[i]->getPredecessor()){
                vertices[i]->setPredecessor(nullptr);
            }
        }
    }

    // Método de busca em largura, utilizando fila
    // Parâmetro: vértice de início da busca
    void wfs(Vertice *start, int recur = 0)
    {
        //Teste de parâmetros
        if(!start) throw runtime_error("Parametro nao informado");

        // Inicia fila e variável de auxílio
        queue<Vertice *> queue;
        Vertice *aux = new Vertice();
        cicles = 0;

        // Adiciona vértice do início da busca a fila e o define como visitado
        start->setVisited(true);
        queue.push(start);

        // Enquanto a fila não estiver vazia, continua buscando
        do
        {
            // Obtem valor do primeiro vertice da fila e o retira
            aux = queue.front();
            // cout << aux->getName() << endl;
            queue.pop();

            // Para cada vizinho do primeiro da fila
            for (Vertice *vert : aux->getNeighbors())
            {
                // Testa se o vizinho já foi visitado, se não o define como visitado e adiciona na fila
                if (!vert->getVisited())
                {
                    vert->setVisited(true);
                    queue.push(vert);
                }else if(vert == start){
                    cicles++;
                }
            }

        } while (!queue.empty());

        // Verificando se todos os vértices do grafo foram visitados
        for (int i = 0; i < vertices.size(); i++)
        {
            if(!vertices[i]->getVisited()){
                wfs(vertices[i]);
            }
        }
    }
    
    // Método de busca em profundidade, contando ciclos, utilizando pilha
    // Parâmetros: vértice de início da busca
    void dfs(Vertice *start, bool recur = true)
    {
        //Teste de parâmetros
        if(!start) throw runtime_error("Parametro nao informado");
        
        // Inicialização da pilha e variáveis auxiliares
        stack<Vertice *> stack;
        Vertice *aux = new Vertice();
        vector<Vertice *> neighbors;

        // Adiciona vértice do início da busca a pilha e o define como visitado
        start->setVisited(true);
        stack.push(start);

        // Enquanto a pilha não estiver vazia, continua buscando
        do
        {
            // Obtem valor do vertice do topo da pilha e o retira
            aux = stack.top();
            aux->setVisited(true);
            stack.pop();

            // Obtem vizinhos do vértice do topo da pilha
            neighbors = aux->getNeighbors();

            // Para cada vizinho (Iteração está sendo feita inversa para manter ordem alfabética dos vizinhos)
            for (int i = (neighbors.size() - 1); i >= 0; i--)
            {
                // Testa se vizinho foi visitado
                if (!neighbors[i]->getVisited())
                {
                    // Se não foi, coloca o topo da pilha como seu antecessor e adiciona na pilha
                    neighbors[i]->setPredecessor(aux);
                    stack.push(neighbors[i]);
                }
                else if (neighbors[i] == start && neighbors[i] != aux->getPredecessor()) // Se foi visitado e antecessor for diferente do topo da pilha
                {
                    // Adiciona 1 no número de ciclos
                    cicles++;
                }
            }
        } while (!stack.empty());

        // Verificando se todos os vértices do grafo foram visitados
        for (int i = 0; i < vertices.size(); i++)
        {
            if(!vertices[i]->getVisited() && recur){
                dfs(vertices[i]);
            }
        }
    }

    int countCicles(string mode){
        if(mode.empty()) throw runtime_error("Parametros vazios");

        if(mode == "dfs"){
            cicles = 0;
            for(int i = 0; i < vertices.size(); i++){
                dfs(vertices[i], false);
                cleanVertices(vertices[i]);
            }
            cicles = cicles / 2;
        }else if(mode == "wfs"){
            cicles = 0;
            for(int i = 0; i < vertices.size(); i++){
                wfs(vertices[i]);
                cleanVertices(vertices[i]);
            }
            cicles = cicles / 2;
        }

        return cicles;
    }

    void permutacao(Vertice *start)
    {
        // Função auxiliar para verificar se uma permutação representa um caminho válido
        auto verificarCaminho = [&](const string &caminho)
        {
            vector<string> verticesDoCaminho;
            stringstream ss(caminho);
            string token;

            // Divide a string caminho em tokens separados por espaço
            while (getline(ss, token, ' '))
            {
                verticesDoCaminho.push_back(token);
            }

            // Verifica os vizinhos entre cada par de vértices consecutivos no caminho
            for (int i = 0; i < verticesDoCaminho.size() - 1; ++i)
            {
                Vertice *verticeAtual = nullptr;
                Vertice *proxVertice = nullptr;

                // Encontra os vértices correspondentes na lista de vértices
                for (Vertice *v : vertices)
                {
                    if (v->getName() == verticesDoCaminho[i])
                    {
                        verticeAtual = v;
                    }
                    if (v->getName() == verticesDoCaminho[i + 1])
                    {
                        proxVertice = v;
                    }
                }

                // Verifica se o próximo vértice é um vizinho do vértice atual
                if (verticeAtual && proxVertice)
                {
                    bool encontrado = false;
                    for (Vertice *vizinho : verticeAtual->getNeighbors())
                    {
                        if (vizinho == proxVertice)
                        {
                            encontrado = true;
                            break;
                        }
                    }
                    // Se o próximo vértice não for vizinho do vértice atual, o caminho não é válido
                    if (!encontrado)
                    {
                        return false;
                    }
                }
                else
                {
                    // Se não encontrar algum dos vértices na permutação, o caminho não é válido
                    return false;
                }
            }
            return true;
        };

        int numVertices = vertices.size();
        list<string> ciclosValidos;

        // Gerar e imprimir permutações de todos os comprimentos possíveis
        for (int comprimento = 3; comprimento <= numVertices; ++comprimento)
        { // erro possivel aqui, precisa chegar ao ultimo vertice e a possivel e contada no comprimento
            string caminhoAtual;
            string caminhoAntigo;

            do
            {
                caminhoAtual = "";
                for (int i = 0; i < comprimento; ++i)
                {
                    caminhoAtual += vertices[i]->getName();
                }
                // caminhoAtual += caminhoAtual[0];
                //  Verifica se a permutação representa um caminho válido
                if (verificarCaminho(caminhoAtual) && caminhoAntigo.substr(0, comprimento - 1) != caminhoAtual.substr(0, comprimento - 1))
                {
                    // cout << caminhoAntigo.substr(0,comprimento-1) <<"\n" << caminhoAtual.substr(0,comprimento-1) << "\n\n";
                    // cout << "Caminho valido"<< caminhoAtual << endl;
                    sort(caminhoAtual.begin(), caminhoAtual.end());

                    // Verifica se o ciclo já foi contado
                    bool cicloJaContado = false;
                    for (const auto &ciclo : ciclosValidos)
                    {
                        if (ciclo == caminhoAtual)
                        {
                            cicloJaContado = true;
                            break;
                        }
                    }

                    // Se o ciclo não foi contado antes, adiciona à lista de ciclos válidos e incrementa a contagem
                    if (!cicloJaContado)
                    {
                        ciclosValidos.push_back(caminhoAtual);
                    }

                    caminhoAntigo = caminhoAtual;
                }
            } while (next_permutation(vertices.begin(), vertices.end(), [](Vertice *a, Vertice *b)
                                      { return a->getName() < b->getName(); }));
        }

        for (const auto &str : ciclosValidos)
        {
            cout << str << str[0] << endl;
        }

        // Print no número de ciclos de um grafo
        cout << "CiclosV: " << ciclosValidos.size() << endl;
    }
};
