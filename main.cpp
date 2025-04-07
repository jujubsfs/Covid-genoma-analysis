#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Estrutura de dados para representar um nó na lista ligada
// Usada para tratar colisões na tabela hash (encadeamento externo)
struct NoHash {
    string bloco;       // Bloco de 6 bases (ex: ATTAAA)
    int contagem;       // Quantidade de vezes que esse bloco apareceu
    NoHash* proximo;    // Ponteiro para o próximo nó na lista (caso de colisão)

    // Construtor: inicializa com o bloco recebido e contagem 1
    NoHash(string b) : bloco(b), contagem(1), proximo(nullptr) {}
};

// Classe que representa a tabela de espalhamento (hash table)
class TabelaHash {
    static const int TAMANHO = 100003; // Tamanho fixo da tabela hash (deve ser primo)
    vector<NoHash*> tabela;            // Vetor de ponteiros para listas ligadas

public:
    // Construtor: inicializa a tabela com ponteiros nulos
    TabelaHash() {
        tabela.resize(TAMANHO, nullptr);
    }

    // Função hash: converte uma string em um índice inteiro da tabela
    // Utiliza uma função de espalhamento simples baseada em multiplicação por 31
    int hashFunction(const string& chave) {
        unsigned long hash = 0;
        for (char c : chave) {
            hash = hash * 31 + c; // Acumula o valor hash com base nos caracteres
        }
        return hash % TAMANHO; // Garante que o índice fique dentro do tamanho da tabela
    }

    // Insere um bloco na tabela hash ou incrementa sua contagem se já existir
    void inserir(const string& bloco) {
        int indice = hashFunction(bloco);    // Calcula o índice baseado no bloco
        NoHash* atual = tabela[indice];      // Pega o início da lista encadeada nesse índice

        // Procura o bloco na lista
        while (atual) {
            if (atual->bloco == bloco) {     // Bloco já existe, apenas incrementa
                atual->contagem++;
                return;
            }
            atual = atual->proximo;
        }

        // Se não encontrou o bloco, cria um novo nó e insere no início da lista
        NoHash* novo = new NoHash(bloco);
        novo->proximo = tabela[indice];
        tabela[indice] = novo;
    }

    // Salva os resultados (bloco + contagem) em um arquivo de saída
    void salvarEmArquivo(const string& nomeArquivo) {
        ofstream out(nomeArquivo);
        for (int i = 0; i < TAMANHO; i++) {
            NoHash* atual = tabela[i];
            while (atual) {
                out << atual->bloco << " " << atual->contagem << "\n";
                atual = atual->proximo;
            }
        }
        out.close();
    }

    // Destrutor: libera a memória alocada para as listas encadeadas
    ~TabelaHash() {
        for (int i = 0; i < TAMANHO; i++) {
            NoHash* atual = tabela[i];
            while (atual) {
                NoHash* temp = atual;
                atual = atual->proximo;
                delete temp; // Libera cada nó da lista
            }
        }
    }
};

// Função que processa um arquivo de genoma e preenche a tabela hash com os blocos
void processarArquivo(const string& nomeEntrada, const string& nomeSaida) {
    ifstream arquivo(nomeEntrada); // Abre o arquivo de entrada
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo: " << nomeEntrada << "\n";
        return;
    }

    TabelaHash hash;  // Instancia uma nova tabela hash
    string linha;

    // Lê o arquivo linha por linha
    while (getline(arquivo, linha)) {
        if (linha.size() < 60) continue; // Ignora linhas menores que 60 caracteres

        // Percorre a linha pegando blocos de 6 em 6 caracteres (sem sobreposição)
        for (int i = 0; i + 6 <= 60; i += 6) {
            string bloco = linha.substr(i, 6); // Extrai o bloco
            hash.inserir(bloco);               // Insere na tabela hash
        }
    }

    arquivo.close();               // Fecha o arquivo de entrada
    hash.salvarEmArquivo(nomeSaida); // Salva os resultados no arquivo de saída
}

// Função principal: processa dois arquivos de entrada e gera dois arquivos de saída
int main() {
    // Processa o primeiro arquivo
    processarArquivo("sequences.fasta1.txt", "saida_blocos_1.txt");

    // Processa o segundo arquivo
    processarArquivo("sequences.fasta2.txt", "saida_blocos_2.txt");

    cout << "Contagem de blocos concluída.\n";
    cout << "Resultados salvos em 'saida_blocos_1.txt' e 'saida_blocos_2.txt'.\n";
    return 0;
}
