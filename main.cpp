#include <iostream>
#include <vector>
#include <sstream>
#include "Set.hpp"
using namespace std;

/*
* @authors 
* Clara Cruz Alves - 568563
*/
Set union_set(Set& A, Set& B){
    Set uniao = A;
    vector<int> var;
    B.inOrder(var);
    
    for(int x : var){
        uniao.insert(x);
    }
    
    return uniao;
}

Set intersection(Set& A, Set& B){
    Set inter;
    vector<int> valA, valB;
    A.inOrder(valA);
    B.inOrder(valB);

    for(int x : valA){
        for(int y : valB){
            if(x == y){
                inter.insert(x);
            }
        }
    }

    return inter;
}

Set difference(Set& A, Set& B){
    Set dif = A;
    Set interB = intersection(A, B);
    vector<int> valA, valB;
    dif.inOrder(valA);
    interB.inOrder(valB);

    for(int x : valA){
        for(int y : valB){
            if(x == y){
                dif.erase(x);
            }
        }
    }
}

// Função que transforma os comandos feitos no terminal em um vetor
vector<string> lerComando(){
    string frase;
    vector<string> comando;
    string aux;
    getline(cin, frase);

    stringstream ss(frase);
    while(ss >> aux){ 
        comando.push_back(aux);
    }

    return comando;
}

// funçao que exibe o cabeçalho dos comandos disponíveis
void mostrarAjuda(){
    cout << "=====================================================================================================" << endl;
    cout << "|COMANDOS DISPONIVEIS:                                                                              |" << endl;
    cout << "|===================================================================================================|" << endl;
    cout << "|sair ----------------------------------------------------------------------------- fecha o programa|" << endl;
    cout << "|criar ------------------------------------------------ cria um conjunto vazio e o adiciona na lista|" << endl;
    cout << "|mostrar i -------------------------------------------- mostra um conjunto na posicao i da sua lista|" << endl;
    cout << "|listar -------------------------------------------------- lista os conjuntos que estao na sua lista|" << endl;
    cout << "|remover i ------------------------------------------------------- remove um conjunto i da sua lista|" << endl;
    cout << "|removerTudo ------------------------------------------ remove todos os conjuntos atuais do programa|" << endl;
    cout << "|===================================================================================================|" << endl;
    cout << "|OPERACOES BINARIA ENTRE OS CONJUNTOS:                                                              |" << endl;
    cout << "|===================================================================================================|" << endl;
    cout << "|uniao i j -------------------------------- mostra o conjunto uniao dos conjuntos i e j da sua lista|" << endl;
    cout << "|inter i j ------------------------------------ mostra a intersecao dos conjuntos i e j da sua lista|" << endl;
    cout << "|dif i j -------------------------------- mostra o que esta no conjunto i que nao esta no conjunto j|" << endl;
    cout << "|===================================================================================================|" << endl;
    cout << "|MANIPULACAO DOS CONJUNTOS:                                                                         |" << endl;
    cout << "|===================================================================================================|" << endl;
    cout << "|inserir x i ------------------------------------------- insere o valor x no conjunto i da sua lista|" << endl;
    cout << "|apagar x i -------------------------------------------- remove o valor x do conjunto i da sua lista|" << endl;
    cout << "|contem x i -------------------------- verifica se o valor x esta contido no conjunto i da sua lista|" << endl;
    cout << "|trocar i j ---------------------------------- inverte os conteudos dos conjuntos i e j da sua lista|" << endl;
    cout << "|min i --------------------------------------------- mostra o menor valor do conjunto i da sua lista|" << endl;
    cout << "|max i --------------------------------------------- mostra o maior valor do conjunto i da sua lista|" << endl;
    cout << "|suc x i ----------------------------------- mostra o sucessor do valor x do conjunto i da sua lista|" << endl;
    cout << "|pre x i -------------------------------- mostra o predecessor do valor x do conjunto i da sua lista|" << endl;
    cout << "|tam i ------------------------------------------------- mostra o tamanho do conjunto i da sua lista|" << endl;
    cout << "=====================================================================================================" << endl;
}

int main(){
    vector<Set> listaSet;

    while(true){
   
        vector<string> comando = lerComando();

        if(comando.empty()){
            cout << "Escreva um comando valido." << endl;
            continue;
        }

        if(comando[0] == "ajuda" && comando.size() == 1){
            mostrarAjuda();
            continue;
        }

        if(comando[0] == "sair" && comando.size() == 1){
            cout << "Encerrando sistema..." << endl;
            break;
        }

        if(comando[0] == "criar" && comando.size() == 1){
            Set novoConjunto;
            listaSet.push_back(novoConjunto);
            cout << "seu conjunto " << listaSet.size() - 1 << " foi criado" << endl;
            continue;
        }

        if(comando[0] == "mostrar" && comando.size() == 2){
                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                    continue;
                }

                int x = stoi(comando[1]);
                
                if(x >= 0 || x < listaSet.size()){
                    vector<int> val;
                    listaSet[x].inOrder(val);

                    if(val.empty()){
                        cout << "conjunto " << x <<": {}" << endl;
                        continue;
                    }
                    
                    cout << "conjunto " << x << ": {";
                    for(int i : val){
                        cout << i;
                        if(i != val.size()) cout << ", ";
                    }
                    cout << "}" << endl;
                    continue;

                }else{
                    cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                    continue;
                }
        }

        if(comando[0] == "listar" && comando.size() == 1){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            for(int x = 0; x < listaSet.size(); x++){
                vector<int> val;
                listaSet[x].inOrder(val);

                if(val.empty()){
                    cout << "conjunto " << x <<": {}" << endl;
                    continue;
                }
                
                cout << "conjunto " << x << ": {";
                for(int i : val){
                    cout << i;
                    if(i != val.size()) cout << ", ";
                }
                cout << "}" << endl;
                continue;
            }
        }
            

        if(comando[0] == "remover" && comando.size() == 2){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            if(x >= 0 || x < listaSet.size()){
                listaSet.erase(listaSet.begin() + x);
                cout << "conjunto na posicao " << x << " foi removida com sucesso!" << endl;
                continue;
            }else{
                cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                continue;
            }

            continue;
        }

        if(comando[0] == "removerTudo" && comando.size() == 1){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            cout << "tem certeza que deseja apagar toda sua lista? (s/n)" << endl;
            string conf;
            while(true){
                if(conf == "s"){
                    listaSet.clear();
                    cout << "sua lista foi deletada com sucesso!" << endl;
                    break;
                }else if(conf == "n"){
                    break;
                }else{
                    cout << "digite um valor valido" << endl;
                }
            }
            continue;
        }

        if(comando[0] == "uniao" && comando.size() == 3){
            
            continue;
        }

        if(comando[0] == "inter" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "dif" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "inserir" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "apagar" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "contem" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "trocar" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "min" && comando.size() == 2){
            continue;
        }

        if(comando[0] == "max" && comando.size() == 2){
            continue;
        }

        if(comando[0] == "suc" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "pre" && comando.size() == 3){
            continue;
        }

        if(comando[0] == "tam" && comando.size() == 2){
            continue;
        }

        cout <<  "comando invalido. Cheque 'ajuda' para ver os comandos disponiveis" << endl;

    }

}