#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip> // Adicionado para usar std::setw

using namespace std;

struct Registro {
    string data;
    map<string, int> ocorrencias;
};

void lerArquivoCSV(string nomeArquivo, map<string, vector<Registro>>& registros) {
    if (nomeArquivo.find(".csv") == string::npos) {
        nomeArquivo += ".csv";
    }

    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return;
    }

    // Extrair a data do nome do arquivo
    size_t pos = nomeArquivo.find_last_of("/");
    string dataArquivo = nomeArquivo.substr(pos + 1, 8); // Assume que o formato do nome do arquivo é DDMMYYYY

    string linha;
    while (getline(arquivo, linha)) {
        cout << "Linha lida: " << linha << endl;
        stringstream ss(linha);
        string nome;
        getline(ss, nome, ',');
        Registro registro;
        registro.data = dataArquivo;
        string chave;
        string valor;
        while (getline(ss, chave, ',')) {
            if (!getline(ss, valor, ',')) {
                break;
            }
            registro.ocorrencias[chave] = stoi(valor);
        }
        registros[nome].push_back(registro);
    }

    cout << "Arquivo " << nomeArquivo << " lido com sucesso." << endl;
}

void gerarRelatorioPorCrianca(map<string, vector<Registro>>& registros) {
    string nome;
    cout << "Digite o nome da criança: ";
    cin.ignore();
    getline(cin, nome);

    auto it = registros.find(nome);
    if (it == registros.end()) {
        cout << "Criança não encontrada." << endl;
        return;
    }

    vector<Registro>& registrosCrianca = it->second;
    cout << "Relatório para a criança " << nome << ":" << endl;
    for (const Registro& registro : registrosCrianca) {
        // Formatar a data como DD/MM/YYYY
        string dataFormatada = registro.data.substr(0, 2) + "/" + registro.data.substr(2, 2) + "/" + registro.data.substr(4, 4);
        cout << "Data: " << dataFormatada << endl << endl;
        for (const auto& ocorrencia : registro.ocorrencias) {
            cout << "  - " << ocorrencia.first << ": " << ocorrencia.second << endl;
        }
        cout << endl;
    }
}
void gerarRelatorioGeral(const map<string, vector<Registro>>& registros, int op) {

    string quesito;

    switch(op){
        case 1:
          quesito = "penalti";
          break;
        case 2:
          quesito = "falta";
          break;
        case 3:
          quesito = "escanteio";
          break;
        case 4:
          quesito = "gol";
          break;
        case 5:
          quesito = "cruzamento";
          break;
        case 6:
          quesito = "cartao amarelo";
          break;
        case 7:
          quesito = "cartao vermelho";
          break;
        case 8:
          quesito = "drible";
          break;
        case 9:
          quesito = "desarme";
          break;
        case 10:
          quesito = "cabeceio";
          break;
        case 11: 
          quesito = "assistencia";
          break;
    }
    cout << "Relatório de " + quesito + " por criança:" << endl;

    bool encontrado = false; // Verificar se há registros do quesito escolhido para alguma criança

    for (const auto& par : registros) {
        const string& nome = par.first;
        const vector<Registro>& registrosCrianca = par.second;

        for (const Registro& registro : registrosCrianca) {
            auto itQuesito = registro.ocorrencias.find(quesito);
            if (itQuesito != registro.ocorrencias.end()) {
                if (!encontrado) {
                    encontrado = true;
                }

                // Formatar a data como DD/MM/YYYY
                string dataFormatada = registro.data.substr(0, 2) + "/" + registro.data.substr(2, 2) + "/" + registro.data.substr(4, 4);
                cout << "Criança: " << nome << endl;
                cout << "Data: " << dataFormatada << endl;
                cout << "  - " + quesito + ": " << itQuesito->second << endl;
                cout << endl;
            }
        }
    }

    if (!encontrado) {
        cout << "Não foram encontrados registros de " + quesito + " para nenhuma criança." << endl;
    }
}

void gerarRelatorioPorDrible(const map<string, vector<Registro>>& registros) {

}

void imprimirRegistros(const map<string, vector<Registro>>& registros) {
    for (const auto& par : registros) {
        const string& nome = par.first;
        const vector<Registro>& listaRegistros = par.second;

        cout << "Registros de " << nome << ":" << endl;
        for (const Registro& registro : listaRegistros) {
            // Formatar a data como DD/MM/YYYY
            string dataFormatada = registro.data.substr(0, 2) + "/" + registro.data.substr(2, 2) + "/" + registro.data.substr(4, 4);
            cout << "- Data: " << dataFormatada << endl;
            for (const auto& parOcorrencia : registro.ocorrencias) {
                const string& chave = parOcorrencia.first;
                cout << "  - " << chave << endl;
            }
        }
        cout << endl;
    }
}

int main() {
    int ver, op = 9, check;
    map<string, vector<Registro>> registros;
    string nomeArquivo;

    do {
        cout << "ESCOLHA A OPÇÃO ABAIXO:\n[1]LER ARQUIVO\n[2]GERAR RELATÓRIO POR CRIANÇA\n[3]GERAR RELATÓRIO POR QUESITO\n[0]SAIR\n[->]";
        cin >> op;

        switch(op) {
            case 1:
                cout << "Digite o nome do arquivo a ser lido: ";
                cin >> nomeArquivo;
                lerArquivoCSV(nomeArquivo, registros);
                op = 8;
                break;
            case 2:
                gerarRelatorioPorCrianca(registros);
                break;
            case 3:
                {
                    op = 8;
                    cout << "ESCOLHA A OPÇÃO PARA GERAR O RELATÓRIO:\n[1]penalti [2]falta [3]escanteio [4]gol [5] cruzamento [6]cartao armarelo [7] cartao vermelho [8]drible [9]desarme [10]cabeceio [11] assistencia \n[->]";
                    cin >> op;
                    gerarRelatorioGeral(registros, op);
                }
            case 0:
                break;
            default:
                cout << "\nOPÇÃO INVÁLIDA\n";
                op = 8;
                break;
        }
    } while(op != 0);

    return 0;
}