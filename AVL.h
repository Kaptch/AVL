//
// Created by kaptch on 3/18/18.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#define DEBUG

#include <functional>
#include <stack>
#include <fstream>

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
        int balance;

        AVL_Node(T x) : _data(x), balance(0) {}

        AVL_Node(T x, AVL_ptr p, AVL_ptr l, AVL_ptr r) : _data(x), Base_Node(l, r, p), balance(0) {}

        AVL_Node(T x, AVL_ptr p, AVL_ptr l, AVL_ptr r, int b) : _data(x), Base_Node(l, r, p), balance(b) {}
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
#ifdef DEBUG
    unsigned int rotations;
#endif

    AVL_ptr rotateLeft(AVL_ptr a) {
        AVL_ptr b = a->_right;
        b->_parent = a->_parent;
        a->_right = b->_left;

        if (a->_right != nullptr)
            a->_right->_parent = a;

        b->_left = a;
        a->_parent = b;

        if (b->_parent != _sentient) {
            if (b->_parent->_right == a) {
                b->_parent->_right = b;
            } else {
                b->_parent->_left = b;
            }
        }

        setBalance(a);
        setBalance(b);

#ifdef DEBUG
        ++rotations;
#endif

        return b;
    }

    AVL_ptr rotateRight(AVL_ptr a) {
        AVL_ptr b = a->_left;
        b->_parent = a->_parent;
        a->_left = b->_right;

        if (a->_left != nullptr)
            a->_left->_parent = a;

        b->_right = a;
        a->_parent = b;

        if (b->_parent != _sentient) {
            if (b->_parent->_right == a) {
                b->_parent->_right = b;
            } else {
                b->_parent->_left = b;
            }
        }

        setBalance(a);
        setBalance(b);

#ifdef DEBUG
        ++rotations;
#endif

        return b;
    }

    AVL_ptr rotateLeftThenRight(AVL_ptr n) {
        n->_left = rotateLeft(n->_left);
        return rotateRight(n);
    }

    AVL_ptr rotateRightThenLeft(AVL_ptr n) {
        n->_right = rotateRight(n->_right);
        return rotateLeft(n);
    }

    void rebalance(AVL_ptr n) {
        setBalance(n);

        if (n->balance == -2) {
            if (height(n->_left->_left) >= height(n->_left->_right))
                n = rotateRight(n);
            else
                n = rotateLeftThenRight(n);
        } else if (n->balance == 2) {
            if (height(n->_right->_right) >= height(n->_right->_left))
                n = rotateLeft(n);
            else
                n = rotateRightThenLeft(n);
        }

        if (n->_parent != _sentient) {
            rebalance(n->_parent);
        } else {
            _root = n;
            _sentient->_parent = n;
        }
    }

    int height(AVL_ptr n) {
        if (n == nullptr)
            return -1;
        return 1 + std::max(height(n->_left), height(n->_right));
    }

    void setBalance(AVL_ptr n) {
        n->balance = height(n->_right) - height(n->_left);
    }

    AVL_ptr increment(AVL_ptr ptr) {
        if (ptr->_right) {
            ptr = ptr->_right;
            while (ptr->_left)
                ptr = ptr->_left;
        } else {
            AVL_ptr y = ptr->_parent;
            while (ptr == y->_right) {
                //if (y->_parent == y)
                //return;
                ptr = y;
                if (!ptr->_parent)
                    return _sentient;
                y = y->_parent;
            }
            if (ptr->_right != y)
                ptr = y;
        }
        return ptr;
    }

    AVL_ptr decrement(AVL_ptr ptr) {
        if (!ptr->_parent) {
            ptr = ptr->_right;
            return _sentient;
        }
        if (ptr->_left) {
            AVL_ptr y = ptr->_left;
            while (y->_right)
                y = y->_right;
            ptr = y;
        } else {
            AVL_ptr y = ptr->_parent;
            while (ptr == y->_left) {
                ptr = y;
                y = y->_parent;
            }
            ptr = y;
        }
        return ptr;
    }

    AVL_ptr upper_bound(AVL_ptr ptr, const T &x) {
        if (!ptr)
            return nullptr;

        if (!comp(x, ptr->_data))
            return upper_bound(ptr->_right, x);
        else {
            if (!ptr->_left)
                return ptr;
            AVL_ptr temp = upper_bound(ptr->_left, x);
            if (temp)
                return comp(temp->_data, ptr->_data) ? temp : ptr;
            else
                return ptr;
        }
    }

    AVL_ptr lower_bound(AVL_ptr ptr, const T &x) {
        if (!ptr)
            return nullptr;

        if (!comp(x, ptr->_data) && !comp(ptr->_data, x))
            return ptr;

        if (comp(ptr->_data, x))
            return lower_bound(ptr->_right, x);
        else {
            if (!ptr->_left)
                return ptr;
            AVL_ptr temp = lower_bound(ptr->_left, x);
            if (temp)
                return comp(temp->_data, ptr->_data) ? temp : ptr;
            else
                return ptr;
        }
    }

    void print_offset(std::ostream &stream, int offset) {
        int i;
        for (i = 0; i < offset; ++i) {
            stream << "-";
        }
    }

    void bst_print_ascii(AVL_ptr tree, std::ostream &stream) {
        static int offset = 0;

        print_offset(stream, offset);

        if (tree == nullptr) {
            stream << "+" << std::endl;
            return;
        }
        stream << tree->_data << std::endl;

        offset += 3;
        bst_print_ascii(tree->_left, stream);
        bst_print_ascii(tree->_right, stream);
        offset -= 3;
    }
public:
    AVL_tree() : _empty(true), _root(nullptr) {
        _sentient = (AVL_ptr)(new Base_Node());
#ifdef DEBUG
        rotations = 0;
#endif
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

    iterator max() { return iterator(_root ? _sentient->_left : _sentient); }

    iterator min() { return iterator(_root ? _sentient->_right : _sentient); }
    void clear() { if (!empty()) _root->_flush(); }

    iterator find(const T &x) {
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

    iterator insert(const T &x) {
        if (_empty) {
            _root = new AVL_Node(x);
            _root->_parent = _sentient;
            _sentient->_left = _root;
            _sentient->_right = _root;
            //_sentient->_parent = _root;
            _empty = false;
            return iterator(_root);
        } else {
            AVL_ptr n = _root, parent, ans;

            while (true) {
                if (!comp(n->_data, x) && !comp(x, n->_data))
                    return iterator(n);

                parent = n;

                bool goLeft = comp(x, n->_data);
                n = goLeft ? n->_left : n->_right;

                if (n == nullptr) {
                    if (goLeft) {
                        parent->_left = new AVL_Node(x, parent, nullptr, nullptr);
                        if (parent == _sentient->_right)
                            _sentient->_right = parent->_left;
                        ans = parent->_left;
                    } else {
                        parent->_right = new AVL_Node(x, parent, nullptr, nullptr);
                        if (parent == _sentient->_left)
                            _sentient->_left = parent->_right;
                        ans = parent->_right;
                    }

                    rebalance(parent);
                    break;
                }
            }
            return iterator(ans);
        }
    }
    void erase(iterator it) {
        erase(*it);
    }

    void erase(const T &x) {
        if (_root == nullptr)
            return;

        AVL_ptr n = _root, parent = _root, delNode = nullptr, child = _root;

        while (child != nullptr) {
            parent = n;
            n = child;
            child = !comp(x, n->_data) ? n->_right : n->_left;
            if (!comp(x, n->_data) && !comp(n->_data, x))
                delNode = n;
        }

        if (delNode != nullptr) {
            delNode->_data = n->_data;

            if (delNode == _root && !_root->_right && !_root->_left) {
                _root = nullptr;
                _sentient->_left = nullptr;
                _sentient->_right = nullptr;
                _sentient->_parent = nullptr;
                _empty = true;
            }

            if (delNode == _sentient->_right)
                _sentient->_right = increment(delNode);

            if (delNode == _sentient->_left)
                _sentient->_left = decrement(delNode);

            child = n->_left != nullptr ? n->_left : n->_right;

            if (!comp(_root->_data, x) && !comp(x, _root->_data)) {
                _root = child;
            } else {
                if (parent->_left == n) {
                    parent->_left = child;
                } else {
                    parent->_right = child;
                }

                rebalance(parent);
            }
        }
    }

    iterator upper_bound(const T &x) {
        AVL_ptr t = upper_bound(_root, x);
        if (t)
            return iterator(t);
        else
            return end();
    }

    iterator lower_bound(const T &x) {
        AVL_ptr t = lower_bound(_root, x);
        if (t)
            return iterator(t);
        else
            return end();
    }

    void printTree() {
        bst_print_ascii(_root, std::cout);
    }

#ifdef DEBUG

    unsigned int get_rotations() {
        return rotations;
    }

    void nullify_rotation() {
        rotations = 0;
    }

#endif

    void write(const std::string &fn) {
        std::ofstream ofs;
        ofs.open(fn);
        std::for_each(begin(), end(), [&ofs](T x) { ofs << x << " "; });
        ofs.close();
    }

    void read(const std::string &fn) {
        std::ifstream ifs;
        ifs.open(fn);
        T temp;
        while (ifs) {
            ifs >> temp;
            insert(temp);
        }
        ifs.close();
    }
};


#endif //AVL_TREE_H
