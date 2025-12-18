
#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
        //miembros privados
	int nelem;
	BSNode<T> *root;
	
	BSNode<T>* search(BSNode<T>* n, T e) const{
		if(n == nullptr) {throw runtime_error("Elemento no encontrado");}
		else if(n->elem > e) { return search(n->left, e);}
		else if(n->elem < e) { return search(n->right, e);}
		else {return n;}
	}
	
	BSNode<T>* insert(BSNode<T>* n, T e){
		if(n == nullptr){
			return new BSNode<T>(e, nullptr, nullptr);	
		}
		else if(n->elem == e) { throw runtime_error("El elemento e ya existe");}
        else if(n->elem > e) { n->left = insert(n->left, e);}
        else if(n->elem < e) { n->right = insert(n->right, e);}
		return n;
	}
	
	void print_inorder(std::ostream &out, BSNode<T>* n) const{
		if(n == nullptr){
			return;
		}
		print_inorder(out, n->left);
		out << n->elem << " ";
		print_inorder(out, n->right);
	}

	BSNode<T>* remove(BSNode<T>* n, T e){
        if (n == nullptr){
            throw runtime_error("Elemento no encontrado");
        }
		else if(n->elem > e) { n->left = remove(n->left, e);}
        else if(n->elem < e) { n->right = remove(n->right, e);}
		else {
			if(n->left != nullptr && n->right != nullptr){ // 2 hijos
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			}
			else{
				BSNode<T>* aux = n;
				n = (n->left != nullptr) ? n->left : n ->right;
				delete aux;
			}
		}
		return n;	
	}

	T max(BSNode<T>* n) const {
		if(n == nullptr){
			throw runtime_error("Elemento no encontrado");
		}
		else if(n->right != nullptr){return max(n->right);}
		else{return n->elem;}
	}
	//funcion para obtener el arbol binario minimo 2 examen practicas
	T min(BSNode<T>* node) const {
            if (node == nullptr) {
                throw std::runtime_error("Elemento no encontrado");
            }
            
            if (node->left == nullptr) {
                return node->elem; 
            }
            return min(node->left);
        }
	BSNode<T>* remove_max(BSNode<T>* n){
		if (n->right == nullptr){
			BSNode<T>* aux = n->left;
        	delete n;
			return aux;
		}
    	else{
        	n->right = remove_max(n->right);
       		return n;
		}
	}
	
	void delete_cascade(BSNode<T>* n){	
		if(n == nullptr){return;}
		delete_cascade(n->left);
		delete_cascade(n->right);
		delete n;
	}

    public:
        // miembros públicos
   	BSTree(){
		this->root = nullptr;
		this->nelem = 0;
		//en public hay q declarar t()min
		
	}
	int size() const{
		return nelem;
	}
	T search(T e) const{
		BSNode<T>* aux = search(root, e);
		return aux->elem;
	}
	T operator[](T e) const{
		return search(e);
	}
	void insert(T e){
		root = insert(root, e);
		nelem++;
	}
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out, bst.root);
		return out;
	}
//funcion de prune 2 examen de practicas 
void prune_N(int nTimes, bool pMAX) {
            for (int i = 0; i < nTimes; i++) {
                if (isEmpty()) {
                    break; 
                }
                try {
                    T valueToRemove;
                    if (pMAX) {
                        valueToRemove = max(root);
                    } else { 
                        valueToRemove = min(root);
                    }
                    remove(valueToRemove);
                } catch (const std::runtime_error&) {
                    break;
                }
            }
        }
	void remove(T e){
		root = remove(root, e);
		nelem--;
	}
	~BSTree(){
		delete_cascade(root);
		nelem = 0;
	}
	
};

#endif
