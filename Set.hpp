#ifndef SET_HPP
#define SET_HPP
#include "Node.hpp"
#include <vector>
using namespace std;

class Set{
    public:
        //construtor
        Set() {
            root = nullptr;
        }

        //construtor de cópia
        Set(const Set& copia){
            root = copy(copia.root);
        }

        Set(vector<int>& v){
            root = nullptr;
            for(int x : v){
                insert(x);
            }
        }

        //destrutor
        ~Set(){
            root = _clear(root);
        }

        void insert(int key){
            root = _insert(root, key);
        }

        void erase(int key){
            if(!contains(key)){
                throw invalid_argument("esse valor nao existe na arvore para remocao");
            }
            root = _erase(root, key);
        }

        bool contains(int key){
            return _contains(key, root);
        }

        void clear(){
            if(_empty(root)){
                throw runtime_error("nao ha o que limpar");
            }
            root = _clear(root);
        }

        void swapSet(Set& t){
            swap(root, t.root);
        }

        int minimum(){
            if(_empty(root)){
                throw runtime_error("conjunto sem elementos");
            }
            return _minimum(root);
        }

        int maximum(){
            if(_empty(root)){
                throw runtime_error("conjunto sem elementos");
            }
            return _maximum(root);
        }

        int sucessor(int key){
            Node* aux = _sucessor(key, root, nullptr);

            if(_empty(aux)){
                throw runtime_error("nao ha sucessor para a chave fornecida");
            }

            return aux->key; 
        }

        int predecessor(int key){
            Node* aux = _predecessor(key, root, nullptr);

            if(_empty(aux)){
                throw runtime_error("nao ha predecessor para a chave fornecida");
            }

            return aux->key;
        }

        bool empty(){
            return _empty(root);
        }

        int size(){
            return _empty(root) ? 0 : _size(root);
        }

        Set& operator=(const Set& var){
            if(this != &var){
                this->_clear(root);
                root = copy(var.root);
            }

            return *this;
        }

        void inOrder(vector<int>& v){
            _inOrder(root, v);
        }
        
        void print(){
            vector<int> val;
            this->inOrder(val);

            for (size_t i = 0; i < val.size(); ++i) {
                cout << val[i];
                if (i + 1 < val.size()) cout << ", ";
            }
        }

    private:
        Node * root;

        int height ( Node * node ){
            return (_empty(node)) ? 0 : node->height;
        }

        int balance ( Node * node ){
            return height(node->right) - height(node->left);
        }

        Node * rightRotation (Node *p){
            Node* u = p->left;
            p->left = u->right;
            u->right = p;

            p->height = 1 +  max(height(p->left), height(p->right));
            u->height = 1 +  max(height(u->left), height(u->right));
            return u;
        }

        Node * leftRotation (Node *p){
            Node* u = p->right;
            p->right = u->left;
            u->left = p;

            p->height = 1 +  max(height(p->left), height(p->right));
            u->height = 1 +  max(height(u->left), height(u->right));
            return u;
        }

        //insert
        Node* _insert(Node *p , int key){
            if(_empty(p)){
                return new Node{key, 1, nullptr, nullptr};
            }
            if(key == p->key){
                return p;
            }
            if(key < p->key){
                p->left = _insert(p->left, key);
            }
            else if(key>p->key){
                p->right = _insert(p->right, key);
            }
            p = fixup_insertion(p, key);
            return p;
        }
        
        Node* fixup_insertion( Node *p , int key ){
            int bal = balance(p);
            if(bal < -1 && key < p->left->key){
                return rightRotation(p);
            }
            if(bal < -1 && key > p->left->key){
                p->left = leftRotation(p->left);
                return rightRotation(p);
            }
            if(bal > 1 && key > p->right->key){
                return leftRotation(p);
            }
            if(bal > 1 && key < p->right->key){
                p->right = rightRotation(p->right);
                return leftRotation(p);
            }
            p->height = 1 + max(height(p->left), height(p->right));
            return p;
        }

        //erase
        Node* _erase(Node* p, int key){
            if(_empty(p)){
                return nullptr;
            }
            if(key < p->key){
                p->left = _erase(p->left, key);
            }else if(key > p->key){
                p->right = _erase(p->right, key);
            }else if(p->right == nullptr){
                Node* aux = p->left;
                delete p;
                return aux;
            }else{
                p->right = remove_successor(p, p->right);
            }

            p = fixup_erase(p);
            return p;
        }

        Node* remove_successor(Node* node, Node* p){
            if(!_empty(p->left)){
                p = remove_successor(node, p->left);
            }else{
                node->key = p->key;
                Node* aux = p->right;
                delete p;
                return aux;
            }
            p = fixup_erase(p);
            return p;
        }

        Node* fixup_erase(Node* p){
            int bal = balance(p);
            if(bal < -1 && balance(p->left) <= 0){
                return rightRotation(p);
            }
            if(bal < -1 && balance(p->left) > 0){
                p->left = leftRotation(p);
                return rightRotation(p);
            }
            if(bal > 1 && balance(p->right) >= 0){
                return leftRotation(p);
            }
            if(bal > 1 && balance(p->right) < 0){
                p->right = rightRotation(p);
                return leftRotation(p);
            }
            p->height = 1 + max(height(p->left), height(p->right));
            return p;
        }

        //contains
        //função booleana que recebe o primeiro nó da árvore e um determinado valor e verifica se este está na árvore
        bool _contains(int key, Node* p){
            if(_empty(p)){
                return false;
            }
            if(key == p->key){
                return true;
            }

            if(key < p->key){
                return _contains(key, p->left);
            }else{
                return _contains(key, p->right);
            }
        }

        //clear
        Node* _clear(Node* p){
            if(p != nullptr){
                p->left = _clear(p->left);
                p->right = _clear(p->right);
                delete p;
            }
            return nullptr;
        }

        //minimum
        //função que procura o nó mais a esquerda da árvore e retorna o seu valor
        int _minimum(Node *p){
            if(_empty(p)){
                throw runtime_error("árvore vazia");
            }
            
            while(p->left != nullptr){
                p = p->left;
            }
            return p->key;
        }

        //maximum
        //função que busca o nó mais a direita da árvore e retorna o seu valor
        int _maximum(Node *p){
            if(_empty(p)){
                throw runtime_error("árvore vazia");
            }
            
            while(p->right != nullptr){
                p = p->right;
            }
            return p->key;
        }

        //successor
        Node* _sucessor(int key, Node* p, Node* f){
            if(_empty(p)){
                return nullptr;
            }

            if(p->key == key){
                if(p->right != nullptr){
                    Node* aux = p->right;
                    while(aux->left != nullptr){
                        aux = aux->left;
                    }
                    return aux;
                }
                return f;
            }

            if(p->key > key){
                return _sucessor(key, p->left, p);
            }
            if(p->key < key){
                return _sucessor(key, p->right, f);
            }

            //fazer um throw depois
            return nullptr;
        }

        //predecessor
        Node* _predecessor(int key, Node* p, Node* f){
            if(_empty(p)){
                return nullptr;
            }

            if(p->key == key){
                if(p->left != nullptr){
                    return p->left;
                }
                return f;
            }

            if(p->key > key){
                return _predecessor(key, p->left, f);
            }
            if(p->key < key){
                return _predecessor(key, p->right, p);
            }
            return nullptr;
        }

        //empty
        bool _empty(Node *p){
            return (p == nullptr) ? true : false;
        }
        
        //função que copia árvore
        Node* copy(Node* p){
            if(_empty(p))return nullptr;

            Node* left = copy(p->left);
            Node* right = copy(p->right);
            int novaAltura = 1 + max(height(left), height(right));

            Node* node = new Node(p->key, novaAltura, left, right);
            return node;
        }

        //size
        int _size(Node *p){
            if(_empty(p)){
                return 0;
            }

            return 1 + _size(p->left) + _size(p->right);
        }
        
        void _inOrder(Node* p, vector<int>& v){
            if(p != nullptr){
            _inOrder(p->left, v);
            v.push_back(p->key);
            _inOrder(p->right, v);
            }
        }

};
#endif