#pragma once

template <typename T> class TreeNode {
    T value;
    bool is_terminal;
public:
    Array<TreeNode<T>> children;
    TreeNode<T>* parent;
    TreeNode(T& value, bool is_terminal);
    TreeNode();
    T& getValue();
    bool isTerminal() ;
    size_t addChild(T& value, bool is_terminal) ;
    TreeNode<T>* removeChild(T& value) ;
    TreeNode<T>* removeChild(size_t f);
    TreeNode<T>* getNode(Array<T>& path) ;
    Array<Array<T>>* search(T& value)  ;
    TreeNode<T>* nthchild(size_t n)  ;
    size_t findChild(T& value)  ;
    size_t childCount()  ;
    bool operator ==(TreeNode<T>& second)  ;
    bool operator !=(TreeNode<T>& second)  ;
};

template<typename T> TreeNode<T>::TreeNode() : value(T()), is_terminal(false) {};
template<typename T> TreeNode<T>::TreeNode(T& value, bool is_terminal) {
    this->value = value; this->is_terminal = is_terminal;
    };
    template<typename T> T& TreeNode<T>::getValue() {
        return this->value;
    }
    
    template<typename T>bool TreeNode<T>::isTerminal()  {return is_terminal;};
    template<typename T>size_t TreeNode<T>::addChild(T& value, bool is_terminal) {
        if (findChild(value) != children.length()) {return children.length();}
        else if (this->is_terminal) {return children.length();}
        else {TreeNode<T> node = TreeNode<T>(value,is_terminal);node.parent=this;size_t c = children.add(node); return c;}
    }
    template<typename T>TreeNode<T>* TreeNode<T>::removeChild(T& value) {
        size_t f = findChild(value);
        return removeChild(f);
    };
    template<typename T>TreeNode<T>* TreeNode<T>::removeChild(size_t f) {
        if (f == children.length()){return nullptr;}
        if (is_terminal) {return nullptr;}
        else {
            children.remove(f);
            return this+f;
        }
    };
    template<typename T> TreeNode<T>* TreeNode<T>::getNode(Array<T>& path)  {
        if (path[0] != value) {return nullptr;}
        if (is_terminal) {return nullptr;}
        TreeNode* current = this;
        for (T* i = path.begin()+1; i < path.end(); i++) {
            size_t ind = current->findChild(*i);
            TreeNode<T>* node = current->nthchild(ind);
            if (node) current = node;
            else return nullptr;
        }
        return current;
    };
    template<typename T>Array<Array<T>>* TreeNode<T>::search(T& value)  {
        if (is_terminal) return nullptr;
        Array<Array<T>>* ptr = new Array<Array<T>>();
        TreeNode* t = this->nthchild(findChild(value));
        Array<T> base;
        base.add(this->value);
        if (t) {
            Array<T> arr;
            arr = base;
            arr.add(t->getValue());
            ptr->add(arr);
        }
        
        for (TreeNode* i = children.begin(); i < children.end(); i++) {
            Array<Array<T>>* paths_ = i->search(value);
            if (!paths_) continue;
            for (Array<T>* j = paths_->begin(); j < (paths_->end()); j++) {
                Array<T> arr;
                arr = base;
                for (T* k = j->begin(); k < (j->end()); k++) {
                    arr.add(*k);
                }
                ptr->add(arr);
            }
            delete paths_;
        }
        return ptr;
    }
    template<typename T>TreeNode<T>* TreeNode<T>::nthchild(size_t n)  {
        if (n < childCount()) return children.begin()+n; else return nullptr;
    }
    template<typename T>size_t TreeNode<T>::findChild(T& value)  {return children.find([&value](TreeNode& node) {return node.value == value;});}
    template<typename T>size_t TreeNode<T>::childCount()  {return children.length();}
    template <typename T> bool TreeNode<T>::operator ==(TreeNode<T>& second) {
        return second.getValue() == this->getValue();
    }
    template <typename T> bool TreeNode<T>::operator !=(TreeNode<T>& second)  {
        return !(*this == second);
    }
