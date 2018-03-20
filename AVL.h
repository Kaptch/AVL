//
// Created by kaptch on 3/18/18.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <functional>
#include <stack>

template <typename T, typename Compare = std::less<T>> //, typename Alloc = allocator<T>
class AVL_tree {
private:
    Compare comp = Compare();
    class Base_Node;
    class AVL_Node;
    class Base_Node {
        using Base_ptr = Base_Node *;
        using AVL_ptr = AVL_Node *;
    public:
        AVL_ptr _left;
        AVL_ptr _right;
        AVL_ptr _parent;
        void _flush() {
            if (_left) {
                _left->_flush();
                delete _left;
            }
            if (_right) {
                _right->_flush();
                delete _right;
            }
            delete this;
        }
        virtual ~Base_Node() {}
        Base_Node() : _left(nullptr), _right(nullptr), _parent(nullptr) {}
        Base_Node(AVL_ptr l, AVL_ptr r) : _left(l), _right(r), _parent(nullptr) {}
        Base_Node(AVL_ptr l, AVL_ptr r, AVL_ptr p) : _left(l), _right(r), _parent(p) {}
    };
    class AVL_Node : public Base_Node {
        using Base_ptr = Base_Node *;
        using AVL_ptr = AVL_Node *;
    public:
        T _data;
        unsigned int _height;
        AVL_Node(T x) : _data(x), _height(1) {}
        AVL_Node(T x, AVL_ptr p, AVL_ptr l, AVL_ptr r) :
                _data(x), Base_Node(l, r, p), _height(1) {}
        AVL_Node(T x, AVL_ptr p, AVL_ptr l, AVL_ptr r, unsigned int h) :
                _data(x), Base_Node(l, r, p), _height(h) {}
        static AVL_ptr _S_minimum(AVL_ptr p) {
            while (p->_left)
                p = p->_left;
            return p;
        }
        static AVL_ptr _S_maximum(AVL_ptr p) {
            while (p->_right)
                p = p->_right;
            return p;
        }
    };
    using Base_ptr = Base_Node *;
    using AVL_ptr = AVL_Node *;
    AVL_ptr _sentient;
    AVL_ptr _root;
    bool _empty;
    unsigned int height(AVL_ptr p) { return p ? p->_height : 0; }
    unsigned int bfactor(AVL_ptr p) { return height(p->_right)-height(p->_left); }
    void fixheight(AVL_ptr p) {
        unsigned int hl = height(p->_left);
        unsigned int hr = height(p->_right);
        p->_height = (hl > hr ? hl : hr) + 1;
    }
    AVL_ptr rotateRight(AVL_ptr p) {
        AVL_ptr q = p->_left;
        if (p == _root) {
            _root = q;
            q->_parent = _sentient;
            //_sentient->_parent = q;
        }
        p->_left = q->_right;
        if (p->_left)
            p->_left->_parent = p;
        q->_right = p;
        p->_parent = q;
        fixheight(p);
        fixheight(q);
        return q;
    }
    AVL_ptr rotateLeft(AVL_ptr q) {
        AVL_ptr p = q->_right;
        if (q == _root) {
            _root = p;
            p->_parent = _sentient;
            //_sentient->_parent = p;
        }
        q->_right = p->_left;
        if (q->_right)
            q->_right->_parent = q;
        p->_left = q;
        q->_parent = p;
        fixheight(q);
        fixheight(p);
        return p;
    }
    AVL_ptr balance(AVL_ptr p) {
        fixheight(p);
        if( bfactor(p) == 2 ) {
            if( bfactor(p->_right) < 0 )
                p->_right = rotateRight(p->_right);
            return rotateLeft(p);
        }
        if( bfactor(p) == -2 ) {
            if( bfactor(p->_left) > 0  )
                p->_left = rotateLeft(p->_left);
            return rotateRight(p);
        }
        return p;
    }
    AVL_ptr insert(AVL_ptr proot, T x) {
        std::stack<AVL_ptr> st;
        AVL_ptr ans;
        while (proot) {
            st.push(proot);
            if (!comp(x, proot->_data) && !comp(proot->_data, x))
                return proot;
            if (comp(x, proot->_data)) {
                if (proot->_left)
                    proot = proot->_left;
                else {
                    proot->_left = new AVL_Node(x, proot, nullptr, nullptr);
                    if (proot == _sentient->_right)
                        _sentient->_right = proot->_left;
                    ans = proot->_left;
                    break;
                }
            }
            else {
                if (proot->_right)
                    proot = proot->_right;
                else {
                    proot->_right = new AVL_Node(x, proot, nullptr, nullptr);
                    if (proot == _sentient->_left)
                        _sentient->_left = proot->_right;
                    ans = proot->_right;
                    break;
                }
            }
        }
        while (!st.empty()) {
            AVL_ptr temp = st.top();
            fixheight(temp);
            if (bfactor(temp) == 2 || bfactor(temp) == -2)
                st.push(balance(temp));
            st.pop();
        }
        return ans;
    }
public:
    AVL_tree() : _empty(true), _root(nullptr) {
        _sentient = (AVL_ptr)(new Base_Node());
    }
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    private:
        AVL_ptr ptr;
        void increment() {
            if (ptr->_right) {
                ptr = ptr->_right;
                while (ptr->_left)
                    ptr = ptr->_left;
            }
            else {
                AVL_ptr y = ptr->_parent;
                while (ptr == y->_right) {
                    //if (y->_parent == y)
                        //return;
                    ptr = y;
                    if (!ptr->_parent)
                        return;
                    y = y->_parent;
                }
                if (ptr->_right != y)
                    ptr = y;
            }
        }
        void decrement() {
            if (!ptr->_parent) {
                ptr = ptr->_right;
                return;
            }
            if (ptr->_left) {
                AVL_ptr y = ptr->_left;
                while (y->_right)
                    y = y->_right;
                ptr = y;
            }
            else {
                AVL_ptr y = ptr->_parent;
                while (ptr == y->_left) {
                    ptr = y;
                    y = y->_parent;
                }
                ptr = y;
            }
        }
    public:
        iterator(AVL_ptr x) : ptr(x) {}
        iterator(const iterator &mit) : ptr(mit.ptr) {}
        iterator &operator++() {
            increment();
            return *this;
        }
        iterator &operator--() {
            decrement();
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            operator++();
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            operator--();
            return tmp;
        }
        bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }
        bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }

        const T &operator*() {
            auto *q = this->ptr;
            if (q)
                return q->_data;
        }
    };
    iterator begin() { return iterator(_root ? _sentient->_right : _sentient); }
    iterator end() { return iterator(_sentient); }
    bool empty() { return _empty; }
    iterator max() { return iterator(_root ? AVL_Node::_S_maximum(_root) : _sentient); }
    iterator min() { return iterator(_root ? AVL_Node::_S_minimum(_root) : _sentient); }
    void clear() { if (!empty()) _root->_flush(); }
    iterator find(T x) {
        if (_empty) return end();
        auto p = _root;
        while (true) {
            if (!comp(p->_data, x) && !comp(x, p->_data))
                return iterator(_root);
            if (comp(p->_data, x)) {
                if (p->_left)
                    p = p->_left;
                else
                    return end();
            } else {
                if (p->_right)
                    p = p->_right;
                else
                    return end();
            }
        }
    }
    iterator insert(T x) {
        if (_empty) {
            _root = new AVL_Node(x, _sentient, nullptr, nullptr);
            _sentient->_left = _root;
            _sentient->_right = _root;
            _sentient->_parent = _root; //hmmmmm
            _empty = false;
            return iterator(_root);
        } else {
            return iterator(insert(_root, x));
        }
    }
    void erase(iterator it) {
        //TODO
    }
    void erase(T x) { erase(iterator(find(x))); }
};


#endif //AVL_TREE_H
