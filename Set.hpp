#ifndef SET_HPP
#define SET_HPP
#include "Node.hpp"
using namespace std;

class Set{
    public:
        Set() {
            root = nullptr;
        }

        void add( int key ){
            root = add(root, key);
        }

        void show(){
            bshow(root, "");
        }

        bool contains(int key){
            return contains(key, root) == key ? true : false;
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

        Node* add(Node *p , int key){
            if(p == nullptr){
                return new Node{key, 1, nullptr, nullptr};
            }
            if(key == p->key){
                return p;
            }
            if(key < p->key){
                add(p->left, key);
            }
            else if(key>p->key){
                add(p->right, key);
            }
            p = fixup_node(p, key);
            return p;
        }

        Node* fixup_node ( Node *p , int key ){
            int bal = balance(p);
            if(bal < -1 && key < p->left->key){
                return rightRotation(p);
            }
            if(bal < -1 && key > p->left->key){
                p->left = leftRotation(p);
                return rightRotation(p);
            }
            if(bal < -1 && key > p->right->key){
                return leftRotation(p);
            }
            if(bal < -1 && key < p->right->key){
                p->right = rightRotation(p);
                return leftRotation(p);
            }
            p->height = 1 + max(height(p->left), height(p->right));
            return p;
        }

        void bshow(Node *node, std::string heranca) const {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

        //contains
        int contains(int key, Node* p){
            if(p == nullptr){
                return 0;
            }else{
                if(key == p->key){
                    return key;
                }else if(key < p->key){
                    contains(key, p->left);
                }else{
                    contains(key, p->right);
                }
            }
        }
};
#endif