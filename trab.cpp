#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// Definição da estrutura Registro
struct Registro {
    string data;
    map<string, int> ocorrencias;
};

// Definição da estrutura Ocorrencia
struct Ocorrencia {
    string crianca;
    vector<string> datas;
    vector<int> quantidades;
};

void lerArquivoCSV(string nomeArquivo, map<string, vector<Registro>>& registros) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        cout << "Linha lida: " << linha << endl;
        stringstream ss(linha);
        string nome;
        getline(ss, nome, ',');
        Registro registro;
        string chave;
        int valor; // Adicionado
        string entrada;
         while (getline(ss, chave, ',')) {
            if (!getline(ss, entrada, ',')) {
             break;
            }
        stringstream ssEntrada(entrada);
        ssEntrada >> valor;
        registro.ocorrencias[chave] = valor;
}
        registros[nome].push_back(registro);
    }

    cout << "Arquivo " << nomeArquivo << " lido com sucesso." << endl;
}


// Função para gerar relatório por criança
void gerarRelatorioPorCrianca(map<string, vector<Registro>>& registros) {
    string nome;
    cout << "Digite o nome da criança: ";
    cin.ignore();
    getline(cin, nome);

    auto it = registros.find(nome);
    if (it == registros.end()) {
        cout << "Crianca não encontrada." << endl;
        return;
    }

    vector<Registro>& registrosCrianca = it->second;
    cout << "Relatorio para a crianca " << nome << ":";
    for (const Registro& registro : registrosCrianca) {
        cout << registro.data << ": ";
        for (const auto& ocorrencia : registro.ocorrencias) {
            cout << ocorrencia.first << "=" << ocorrencia.second << " ";
        }
        cout << endl;
    }
}

// IMPRIMIR REGISTROS

void imprimirRegistros(const map<string, vector<Registro>>& registros) {
    for (const auto& par : registros) {
        const string& nome = par.first;
        const vector<Registro>& listaRegistros = par.second;

        cout << "Registros de " << nome << ":" << endl;
        for (const Registro& registro : listaRegistros) {
            cout << "- Data: " << registro.data << endl;
            for (const auto& parOcorrencia : registro.ocorrencias) {
                const string& chave = parOcorrencia.first;
                int valor = parOcorrencia.second;
                cout << "  - " << chave << ": " << valor << endl;
            }
        }
        cout << endl;
    }
}

int main() {
    map<string, vector<Registro>> registros;
    
    string nomeArquivo;

    cout << "Digite o nome do arquivo a ser lido: ";
    cin >> nomeArquivo;

    lerArquivoCSV(nomeArquivo , registros);
    imprimirRegistros(registros);
    gerarRelatorioPorCrianca(registros);
    return 0;
}