#ifndef SET_HPP
#define SET_HPP
#include "Node.hpp"
using namespace std;

class Set{
    //publicas são as que passam chaves ou nada
    //privadas as que passam o root como parametro
    public:
        Set() {
            root = nullptr;
        }

        void insert(int key){
            root = _insert(root, key);
        }

        void show(){
            bshow(root, "");
        }

        bool contains(int key){
            return _contains(key, root);
        }

        void clear(){
            root = _clear(root);
        }

        int maximum(){
            return _maximum(root);
        }

        int minimum(){
            return _minimum(root);
        }

        bool empty(){
            return _empty(root);
        }

    private:
        Node * root;

        int height ( Node * node ){
            return (node == nullptr) ? 0 : node->height;
        }

        int balance ( Node * node ){
            return height(node->right) - height(node->left);
        }

        Node * rightRotation (Node *p){
            Node* u = p->left;
            p->left = u->right;
            u->right = p;

            u->height = 1 +  max(height(u->left), height(u->right));
            p->height = 1 +  max(height(p->left), height(p->right));
            return u;
        }

        Node * leftRotation (Node *p){
            Node* u = p->right;
            p->right = u->left;
            u->left = p;

            u->height = 1 +  max(height(u->left), height(u->right));
            p->height = 1 +  max(height(p->left), height(p->right));
            return u;
        }

        //insert
        Node* _insert(Node *p , int key){
            if(p == nullptr){
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
                p->left = leftRotation(p);
                return rightRotation(p);
            }
            if(bal > 1 && key > p->right->key){
                return leftRotation(p);
            }
            if(bal > 1 && key < p->right->key){
                p->right = rightRotation(p);
                return leftRotation(p);
            }
            p->height = 1 + max(height(p->left), height(p->right));
            return p;
        }

        void bshow(Node *node, string heranca) const {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            cout << "#" << endl;
            return;
        }
        cout << node->key << endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
        }


        //contains
        //função booleana que recebe o primeiro nó da árvore e um determinado valor e verifica se este está na árvore
        bool _contains(int key, Node* p){
            if(p == nullptr){
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
            if(p == nullptr){
                throw runtime_error("árvore vazia") ;
            }
            
            while(p->left != nullptr){
                p = p->left;
            }
            return p->key;
        }

        //maximum
        //função que busca o nó mais a direita da árvore e retorna o seu valor
        int _maximum(Node *p){
            if(p == nullptr){
                throw runtime_error("árvore vazia") ;
            }
            
            while(p->right != nullptr){
                p = p->right;
            }
            return p->key;
        }

        //empty
        bool _empty(Node *p){
            return (p == nullptr) ? true : false;
        }

};
#endif