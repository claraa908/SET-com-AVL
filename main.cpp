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
    return dif;
}

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

void mostrarAjuda(){
    cout << "=====================================================================================================" << endl;
    cout << "|COMANDOS DISPONIVEIS:                                                                              |" << endl;
    cout << "|===================================================================================================|" << endl;
    cout << "|sair ----------------------------------------------------------------------------- fecha o programa|" << endl;
    cout << "|criar ------------------------------------------------ cria um conjunto vazio e o adiciona na lista|" << endl;
    cout << "|criar x y z... ---------- cria um conjunto com os valores x y e z ja inclusos e o adiciona na lista|" << endl;
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
    cout << "Seja bem-vindo(a) ao sistema de conjunto dinamico!" << endl;
    cout << "Digite 'ajuda' para ver a lista de comandos disponiveis" << endl; 
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

        if(comando[0] == "criar" && comando.size() > 1){
            vector<int> val;

            for(int i = 1; i < comando.size(); i++){
                try{
                    val.push_back(stoi(comando[i]));
                }catch(const invalid_argument& e){
                    cout << "valor '" << comando[i] << "' eh invalido e por isso foi ignorado" << endl;
                }
            }

            Set novoConjunto(val);
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

                if(x >= 0 && x < listaSet.size()){
                    vector<int> val;
                    listaSet[x].inOrder(val);

                    if(val.empty()){
                        cout << "conjunto " << x <<": {}" << endl;
                        continue;
                    }
                    
                    cout << "conjunto " << x << ": {";
                    listaSet[x].print();
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
                listaSet[x].print();
                cout << "}" << endl;
            }
            continue;
        }
            

        if(comando[0] == "remover" && comando.size() == 2){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            if(x >= 0 && x < listaSet.size()){
                cout << "tem certeza que deseja apagar o conjunto " << x << " da sua lista? (s/n)" << endl;
                string conf;

                while(true){
                    cin >> conf;
                    if(conf == "s"){
                        listaSet.erase(listaSet.begin() + x);
                        cout << "conjunto na posicao " << x << " foi removida com sucesso!" << endl;
                        cin.ignore();
                        break;
                    }else if(conf == "n"){
                        cout << "remocao cancelada" << endl;
                        cin.ignore();
                        break;
                    }else{
                        cout << "entrada invalida, digite 's' para remover ou 'n' para cancelar remocao" << endl;
                    }
                }

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
                cin >> conf;
                if(conf == "s"){
                    listaSet.clear();
                    cout << "sua lista foi deletada com sucesso!" << endl;
                    cin.ignore();
                    break;
                }else if(conf == "n"){
                    cout << "remocao cancelada" << endl;
                    cin.ignore();
                    break;
                }else{
                    cout << "entrada invalida, digite 's' para remover tudo ou 'n' para cancelar remocao" << endl;
                }
            }
            continue;
        }

        if(comando[0] == "uniao" && comando.size() == 3){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            int y = stoi(comando[2]);

            if(x >= 0 && x < listaSet.size() && y >= 0 && y < listaSet.size()){
                Set uniao = union_set(listaSet[x], listaSet[y]);
                cout << "uniao dos conjuntos " << x << " e " << y << ": {";
                uniao.print();
                cout << "}" << endl;
                
                cout << "deseja salvar esse novo conjunto? (s/n)" << endl;
                string conf;

                while(true){
                    cin >> conf;
                    if(conf == "s"){
                        listaSet.push_back(uniao);
                        cout << "conjunto salvo na posicao " << listaSet.size()-1 << endl;
                        cin.ignore();
                        break;
                    }else if(conf == "n"){
                        uniao.clear();
                        cout << "conjunto deletado com sucesso!" << endl;
                        cin.ignore();
                        break;
                    }else{
                        cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar" << endl;
                    }
                }
                continue;
            }else{
                cout << "nao existe conjunto em uma dessas posicoes, insira uma posicao valida" << endl;
                continue;
            }
            continue;
        }

        if(comando[0] == "inter" && comando.size() == 3){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            int y = stoi(comando[2]);

            if(x >= 0 && x < listaSet.size() && y >= 0 && y < listaSet.size()){
                Set inter = intersection(listaSet[x], listaSet[y]);
                cout << "intersecao dos conjuntos " << x << " e " << y << ": {";
                inter.print();
                cout << "}" << endl;
                
                cout << "deseja salvar esse novo conjunto? (s/n)" << endl;
                string conf;

                while(true){
                    cin >> conf;
                    if(conf == "s"){
                        listaSet.push_back(inter);
                        cout << "conjunto salvo na posicao " << listaSet.size()-1 << endl;
                        cin.ignore();
                        break;
                    }else if(conf == "n"){
                        inter.clear();
                        cout << "conjunto deletado com sucesso!" << endl;
                        cin.ignore();
                        break;
                    }else{
                        cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar" << endl;
                    }
                }
                continue;
            }else{
                cout << "nao existe conjunto em uma dessas posicoes, insira uma posicao valida" << endl;
                continue;
            }
            continue;
        }

        if(comando[0] == "dif" && comando.size() == 3){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            int y = stoi(comando[2]);

            if(x >= 0 && x < listaSet.size() && y >= 0 && y < listaSet.size()){
                Set dif = difference(listaSet[x], listaSet[y]);
                cout << "diferenaa dos conjuntos " << x << " e " << y << ": {";
                dif.print();
                cout << "}" << endl;
                
                cout << "deseja salvar esse novo conjunto? (s/n)" << endl;
                string conf;

                while(true){
                    cin >> conf;
                    if(conf == "s"){
                        listaSet.push_back(dif);
                        cout << "conjunto salvo na posicao " << listaSet.size()-1 << endl;
                        cin.ignore();
                        break;
                    }else if(conf == "n"){
                        dif.clear();
                        cout << "conjunto deletado com sucesso!" << endl;
                        cin.ignore();
                        break;
                    }else{
                        cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar" << endl;
                    }
                }
                continue;
            }else{
                cout << "nao existe conjunto em uma dessas posicoes, insira uma posicao valida" << endl;
                continue;
            }
            continue;
        }

        if(comando[0] == "inserir" && comando.size() == 3){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            int y = stoi(comando[2]);
            if(y >= 0 && y < listaSet.size()){
                listaSet[y].insert(x);
                cout << x << " foi adicionado ao conjunto " << y << endl;
                continue;
            }else{
                cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                continue;
            }

            continue;
        }

        if(comando[0] == "apagar" && comando.size() == 3){
            try{
                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                    continue;
                }
    
                int x = stoi(comando[1]);
                int y = stoi(comando[2]);
                if(y >= 0 && y < listaSet.size()){
                    listaSet[y].erase(x);
                    cout << x << " foi removido do conjunto " << y << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                    continue;
                }
                continue;
            }catch(const invalid_argument& e){
                cout << "erro: esse valor nao esta contido na arvore para ser removido" << endl;
                continue;
            }
        }

        if(comando[0] == "contem" && comando.size() == 3){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            int y = stoi(comando[2]);
            if(y >= 0 && y < listaSet.size()){
                listaSet[y].contains(x) ? cout << x << " esta contido no conjunto " << y << endl :
                cout << x << " nao esta contido no conjunto " << y << endl;
                continue;
            }else{
                cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                continue;
            }
            continue;
        }

        if(comando[0] == "trocar" && comando.size() == 3){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            int y = stoi(comando[2]);
            if(x >= 0 && x < listaSet.size() && y >= 0 && y < listaSet.size()){
                listaSet[x].swapSet(listaSet[y]);
                cout << "conjuntos " << x << " e " << y << " foram trocados" << endl;
                continue;
            }else{
                cout << "nao existe conjunto em uma dessas posicoes, insira uma posicao valida" << endl;
                continue;
            }
            continue;
        }

        if(comando[0] == "min" && comando.size() == 2){
            try{
                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                    continue;
                }

                int x = stoi(comando[1]);
                if(x >= 0 && x < listaSet.size()){
                    cout << "o menor valor do conjunto " << x << " e: " << listaSet[x].minimum() << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                    continue;
                }
                continue;
            }catch(const runtime_error& e){
                cout << "erro: conjunto sem elementos, adicione um valor antes de buscar o minimo" << endl;
                continue;
            }
        }

        if(comando[0] == "max" && comando.size() == 2){
            try{
                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                    continue;
                }

                int x = stoi(comando[1]);
                if(x >= 0 && x < listaSet.size()){
                    cout << "o maior valor do conjunto " << x << " e: " << listaSet[x].maximum() << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                    continue;
                }
                continue;
            }catch(const runtime_error& e){
                cout << "erro: conjunto sem elementos, adicione um valor antes de buscar o maximo" << endl;
                continue;
            }
        }

        if(comando[0] == "suc" && comando.size() == 3){
            try{
                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                    continue;
                }
    
                int x = stoi(comando[1]);
                int y = stoi(comando[2]);
                if(y >= 0 && y < listaSet.size()){
                    cout << "o sucessor de " << x << " do conjunto " << y << " e: " << listaSet[y].sucessor(x) << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                    continue;
                }
                continue;
            }catch(const runtime_error& e){
                cout << "erro: nao ha sucessor para o valor fornecido" << endl;
                continue;
            }
        }

        if(comando[0] == "pre" && comando.size() == 3){
            try{
                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                    continue;
                }
    
                int x = stoi(comando[1]);
                int y = stoi(comando[2]);
                if(y >= 0 && y < listaSet.size()){
                    cout << "o predecessor de " << x << " do conjunto " << y << " e: " << listaSet[y].predecessor(x) << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                    continue;
                }
                continue;
            }catch(const runtime_error& e){
                cout << "erro: nao ha predecessor para o valor fornecido" << endl;
                continue;
            }
        }

        if(comando[0] == "tam" && comando.size() == 2){
            if(listaSet.empty()){
                cout << "sua lista de conjuntos esta vazia, crie um conjunto" << endl;
                continue;
            }

            int x = stoi(comando[1]);
            if(x >= 0 && x < listaSet.size()){
                cout << "o tamanho do conjunto " << x << " e: " << listaSet[x].size() << endl;
                continue;
            }else{
                cout << "nao existe conjunto nessa posicao, insira uma posicao valida" << endl;
                continue;
            }
            continue;
        }

        cout <<  "comando invalido. Cheque 'ajuda' para ver os comandos disponiveis" << endl;

    }

}