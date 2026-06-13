#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <initializer_list>

#pragma once
#ifndef OPENUDT___CORE_TREE_HPP
#define OPENUDT___CORE_TREE_HPP

namespace udt
{
    namespace tree
    {
        template <typename T1, typename T2>
        using arithmetic_condition = typename std::enable_if<std::is_arithmetic<T1>::value, T2>::type;
        template <bool T1, typename T2>
        using enableIF = typename std::enable_if_t<T1, T2>;
        template <typename T, bool BST>
        class binary
        {
        private:
            struct Node
            {
                T item;
                Node *prev;
                Node *left;
                Node *right;
            };

            Node *root = nullptr;
            Node *current = nullptr;
            size_t node_number = size_t();

        protected:
            static void clear(Node *node) noexcept
            {
                if (node == nullptr)
                    return;
                clear(node->left);
                clear(node->right);
                delete node;
                node_number--;
            }

            void remove(Node *node) { clear(node); }

            template <bool B = BST>
            static enableIF<B, bool> exist(const T &element) noexcept
            {
                if (root == nullptr)
                {
                    throw std::invalid_argument("searching in empty tree is invalid.\n" + "use the set(const T&) to solve the problem.\n");
                }
                Node *temp = root;
                while (temp != nullptr)
                {
                    if (temp->item > element)
                        temp = temp->left;
                    else if (temp->item < element)
                        temp = temp->right;
                    else
                        return true;
                }
                return false;
            }

            template <bool B = BST>
            static enableIF<!B, bool> exist(Node *node, const T &element) noexcept
            {
                if (node == nullptr)
                    return false;
                if (node->item == element)
                    return true;
                return exist(node->left, element) || exist(node->right, element);
            }

            template <bool B = BST>
            static enableIF<B, void> replace(const T &oldEle, const T &newEle) noexcept
            {
                if (root == nullptr)
                {
                    std::cerr << "null value allocation: the root is point to nullptr.\n"
                              << "use set(const T&) to set the root at least.\n";
                    return;
                }
                Node *temp = root;
                while (temp != nullptr)
                {
                    if (temp->item > oldEle)
                        temp = temp->left;
                    else if (temp->item < oldEle)
                        temp = temp->right;
                    else
                        temp->item = newEle;
                }
            }

            template <bool B = BST>
            static enableIF<!B, void> replace(Node *node, const T &oldEle, const T &newEle) noexcept
            {
                if (node == nullptr)
                    return;
                if (node->item == oldEle)
                {
                    node->item = newEle;
                }
                replace(node->left, oldEle, newEle);
                replace(node->right, oldEle, newEle);
            }

        public:
            binary() = default;

            binary(const T &rootEle)
                : root(new Node{rootEle, nullptr, nullptr, nullptr}),
                  current(root),
                  node_number(1)
            {
            }

            binary(const binary &) = delete;
            binary &operator=(const binary &) = delete;

            constexpr bool empty() noexcept { return root == nullptr; }

            template <bool B = BST>
            enableIF<B, void> add(const T &element) noexcept
            {
                if (current == nullptr)
                {
                    std::cerr << "Error: current is null\n";
                    return;
                }
                if (current == nullptr && root == nullptr)
                {
                    root = new Node{element, nullptr, nullptr, nullptr};
                    current = root;
                    node_number++;
                    return;
                }
                if (current->item > element)
                {
                    current->left = new Node{element, current, nullptr, nullptr};
                    node_number++;
                }
                else if (current->item < element)
                {
                    current->right = new Node{element, current, nullptr, nullptr};
                    node_number++;
                }
                else
                {
                    std::cerr << "Error: position already occupied\n";
                }
            }

            template <bool B = BST>
            enableIF<!B, void> add(bool left, const T &element) noexcept
            {
                if (current == nullptr)
                {
                    std::cerr << "Error: current is null\n";
                    return;
                }
                if (current == nullptr && root == nullptr)
                {
                    root = new Node{element, nullptr, nullptr, nullptr};
                    current = root;
                    node_number++;
                    return;
                }
                if (left && current->left == nullptr)
                {
                    current->left = new Node{element, current, nullptr, nullptr};
                    node_number++;
                }
                else if (!left && current->right == nullptr)
                {
                    current->right = new Node{element, current, nullptr, nullptr};
                    node_number++;
                }
                else
                {
                    std::cerr << "Error: position already occupied\n";
                }
            }

            void remove() noexcept
            {
                if (current == nullptr)
                    return;
                if (current == root)
                {
                    remove(root);
                    root = current = nullptr;
                    node_number = 0;
                    return;
                }
                Node *parent = current->prev;
                if (parent->left == current)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                remove(current);
                current = parent;
            }

            template <bool B = BST>
            enableIF<B, void> remove(const T &element) noexcept
            {
                if (root == nullptr)
                    return;
                Node *temp = root;
                while (temp != nullptr)
                {
                    if (element < temp->item)
                        temp = temp->left;
                    else if (element > temp->item)
                        temp = temp->right;
                    else
                        remove(temp);
                }
            }

            void remove(bool left) noexcept
            {
                if (current == nullptr)
                    return;
                if (left)
                {
                    remove(current->left);
                    current->left = nullptr;
                }
                else
                {
                    remove(current->right);
                    current->right = nullptr;
                }
            }

            constexpr void move_back() noexcept
            {
                current = current->prev;
            }

            constexpr void move() noexcept
            {
                current = root;
            }

            void move(bool left) noexcept
            {
                if (left && current->left != nullptr)
                {
                    current = current->left;
                }
                else if (!left && current->right != nullptr)
                {
                    current = current->right;
                }
                else
                {
                    std::cerr << "invalid argument: The target is null.\n";
                }
            }

            constexpr size_t nodeNumber() noexcept { return node_number; }

            void list() noexcept
            {
                if (current->left == nullptr && current->right != nullptr)
                {
                    std::cout << "current item: " << current->item << "\nleft item: null\n"
                              << "right item: " << current->right->item << "\n";
                }
                else if (current->right == nullptr && current->left != nullptr)
                {
                    std::cout << "current item: " << current->item << "\nright item: null\n"
                              << "left item: " << current->left->item << "\n";
                }
                else if (current->right != nullptr && current->left != nullptr)
                {
                    std::cout << "current item: " << current->item
                              << "\nright item: " << current->right->item << "\n"
                              << "left item: " << current->left->item << "\n";
                }
                else
                {
                    std::cout << "current item: " << current->item << "\nright item: null\nleft item: null\n";
                }
            }

            bool has_item(bool left) noexcept
            {
                if (left)
                    return current->left != nullptr;
                else
                    return current->right != nullptr;
            }

            constexpr bool is_leaf() noexcept
            {
                return current->left == nullptr &&
                       current->right == nullptr;
            }

            constexpr bool in_root() noexcept { return current == root; }
            constexpr T get_root() noexcept { return root->item; }
            constexpr T get() noexcept { return current->item; }

            T get(bool left) noexcept
            {
                if (left && current->left == nullptr)
                {
                    std::cerr << "Null Value Error\n";
                    return T();
                }
                else if (!left && current->right == nullptr)
                {
                    std::cerr << "Null Value Error\n";
                    return T();
                }
                if (left)
                    return current->left->item;
                else
                    return current->right->item;
            }

            void clear() noexcept
            {
                clear(root);
                root = nullptr;
                current = nullptr;
                node_number = size_t();
            }

            bool exist(const T &element)
            {
                if constexpr (!BST)
                    return exist(root, element);
                else
                    return exist(element);
            }

            void replace(const T &oldEle, const T &newEle)
            {
                if constexpr (!BST)
                    replace(root, oldEle, newEle);
                else
                    replace(oldEle, newEle);
            }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator+=(const T &element) noexcept { current->item += element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator-=(const T &element) noexcept { current->item -= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator*=(const T &element) noexcept { current->item *= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator/=(const T &element) noexcept { current->item /= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator+(const T &element) noexcept { return current->item + element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator-(const T &element) noexcept { return current->item - element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator*(const T &element) noexcept { return current->item * element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator/(const T &element) noexcept { return current->item / element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator&=(const T &element) noexcept { current->item &= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator|=(const T &element) noexcept { current->item |= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator^=(const T &element) noexcept { current->item ^= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator&&(const T &element) noexcept { return current->item && element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator||(const T &element) noexcept { return current->item || element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator^(const T &element) noexcept { return current->item ^ element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator==(const T &element) noexcept { return current->item == element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator!=(const T &element) noexcept { return current->item != element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator>(const T &element) noexcept { return current->item > element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator<(const T &element) noexcept { return current->item < element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator>=(const T &element) noexcept { return current->item >= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator<=(const T &element) noexcept { return current->item <= element; }

            constexpr T operator[](bool left) noexcept
            {
                Node *temp;
                if (left)
                    temp = current->left;
                else
                    temp = current->right;
                return temp->item;
            }

            ~binary()
            {
                clear(root);
            }
        };

        template <typename T, bool BTT>
        class Ternary
        {
        private:
            struct node
            {
                node *prev = nullptr;
                node *right = nullptr;
                node *middle = nullptr;
                node *left = nullptr;
                T item = T();
            };
            node *root = nullptr;
            node *current = nullptr;

        protected:
            constexpr char place(bool left, bool right) noexcept
            {
                if (left && right)
                    return 'm';
                else if (left && (!right))
                    return 'l';
                else if (right && (!left))
                    return 'r';
                else
                    return 'p';
            }

            constexpr bool is_middle(bool left, bool right) noexcept
            {
                return right && left;
            }

            constexpr bool is_right(bool left, bool right) noexcept
            {
                return right && (!left);
            }

            constexpr bool is_left(bool left, bool right) noexcept
            {
                return left && (!right);
            }

            constexpr bool is_prev(bool left, bool right) noexcept
            {
                return (!left) && (!right);
            }

            bool exist(node *n, const T &element) noexcept
            {
                if (n == nullptr)
                    return false;
                if (element == n->item)
                    return true;
                return exist(n->left, element) ||
                       exist(n->middle, element) ||
                       exist(n->right, element);
            }

            void replace(node *n, const T &element) noexcept
            {
                if (n == nullptr)
                    return;
                if (element == n->item)
                    n->item = element;
                replace(n->left, element);
                replace(n->middle, element);
                replace(n->right, element);
            }

        public:
            Ternary() = default;
            Ternary(const T &element)
            {
                root = new node{nullptr, nullptr, nullptr, nullptr, element};
                current = root;
            }

            void set(const T &element) noexcept
            {
                if (root != nullptr &&
                    (root->left != nullptr ||
                     root->middle != nullptr ||
                     root->right != nullptr))
                {
                    current = root;
                    root = new node{current->prev, current->right,
                                    current->middle, current->left, element};
                    current = root;
                }
                root = new node{nullptr, nullptr, nullptr, nullptr, element};
                current = root;
            }

            template <bool B = BTT>
            enableIF<B, void> add(const T &element) noexcept
            {
                if (root == nullptr)
                    set(element);
                else if (current->left == nullptr && current->item > element)
                    current->left = new node{current, nullptr, nullptr, nullptr, element};
                else if (current->middle == nullptr)
                    current->middle = new node{current, nullptr, nullptr, nullptr, element};
                else if (current->right == nullptr)
                    current->right = new node{current, nullptr, nullptr, nullptr, element};
                else
                    std::cerr << "invalid argumant: no empty node to but the value of the element.\n";
            }

            template <bool B = BTT>
            enableIF<!B, void> add(const T &element, bool left, bool right) noexcept
            {
                if (root == nullptr)
                {
                    std::cerr << "Empty Error: can't add on empty tree at lest you have to set the root.\n"
                              << "use set to allocate the root of the tree.\n"
                              << "set(const T&);\n";
                    return;
                }
                if (current == nullptr)
                {
                    std::cerr << "internal Error(null value allocation): the current node points to nullptr.\n"
                              << "use move with out prameters.\n"
                              << "move(false, false);\n";
                    return;
                }
                if (is_middle(left, right) && current->middle == nullptr)
                    current->middle = new node{current, nullptr, nullptr, nullptr, element};
                else if (is_left(left, right) && current->left == nullptr)
                    current->left = new node{current, nullptr, nullptr, nullptr, element};
                else if (is_right(left, right) && current->right == nullptr)
                    current->right = new node{current, nullptr, nullptr, nullptr, element};
                else if (is_prev(left, right) && current->prev == nullptr)
                {
                    current->prev = new node{nullptr, nullptr, current, nullptr, element};
                    if (current == root)
                        root = current->prev;
                }
            }

            constexpr bool in_root() noexcept { return current == root; }

            void move(bool left = true, bool right = false) noexcept
            {
                if (is_middle(left, right))
                    current = current->middle;
                else if (is_left(left, right))
                    current = current->left;
                else if (is_right(left, right))
                    current = current->right;
                else
                    current = current->prev;
            }

            T get() const noexcept
            {
                if (current == nullptr)
                {
                    std::cerr << "internal Error(null value allocation): the current node points to nullptr.\n"
                              << "use move with out prameters.\n"
                              << "move(false, false);\n";
                    return T();
                }
                return current->item;
            }

            bool exsit(const T &element)
            {
                return exsit(root, element);
            }

            void replace(const T &element) noexcept
            {
                replace(root, element);
            }

            void operator=(const T &element)
            {
                if (current == nullptr)
                {
                    std::cerr << "internal logic error(null value allocation)," << " use move(false, false) to return to the root if the root has been set.\n"
                              << "if the root has not been set, use set(const T&).\n";
                    return;
                }
                current->item = element;
            }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool> operator==(const T &item)
            {
                if (current == nullptr)
                    throw std::invalid_argument(
                        "internal logic error(null value allocation)," +
                        " use move(false, false) to return to the root if the root has been set.\n" +
                        "if the root has not been set, use set(const T&).\n");
                return current->item == item;
            }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool> operator!=(const T &item)
            {
                if (current == nullptr)
                    throw std::invalid_argument(
                        "internal logic error(null value allocation)," +
                        " use move(false, false) to return to the root if the root has been set.\n" +
                        "if the root has not been set, use set(const T&).\n");
                return current->item != item;
            }

            template <typename U = T>
            constexpr arithmetic_condition<U, T> operator+(const T &item);
            template <typename U = T>
            constexpr arithmetic_condition<U, T> operator-(const T &item);
            template <typename U = T>
            constexpr arithmetic_condition<U, T> operator*(const T &item);
            template <typename U = T>
            constexpr arithmetic_condition<U, T> operator/(const T &item);
            template <typename U = T>
            constexpr arithmetic_condition<U, T> operator%(const T &item);

            template <typename U = T>
            constexpr arithmetic_condition<U, void> operator+=(const T &item) noexcept;
            constexpr arithmetic_condition<U, void> operator-=(const T &item) noexcept;
            constexpr arithmetic_condition<U, void> operator*=(const T &item) noexcept;
            constexpr arithmetic_condition<U, void> operator/=(const T &item) noexcept;
            constexpr arithmetic_condition<U, void> operator%=(const T &item) noexcept;

            template <typename U = T>
            constexpr arithmetic_condition<U, bool> operator&&(const T &item);

            template <typename U = T>
            constexpr arithmetic_condition<U, bool> operator||(const T &item);

            template <typename U = T>
            constexpr arithmetic_condition<U, bool> operator^(const T &item);

            template <typename U = T>
            constexpr arithmetic_condition<U, void> operator&=(const T &item) noexcept;

            template <typename U = T>
            constexpr arithmetic_condition<U, void> operator|=(const T &item) noexcept;

            template <typename U = T>
            constexpr arithmetic_condition<U, void> operator^=(const T &item) noexcept;
        };

        template <typename T>
        class multiBranch
        {
        private:
            struct node
            {
                node *parent = nullptr;
                std::map<std::string, node *> childs = std::map<std::string, node *>();
                T element = T();
            };
            node *root = nullptr;
            node *current = nullptr;
            size_t nodeNumber = size_t();

        protected:
            void clear(node *n) noexcept
            {
                if (n == nullptr)
                    return;
                if (n->childs.empty())
                    return;
                for (auto p : n->childs)
                    clear(p.second);
                delete n;
                nodeNumber--;
            }

            static bool exist(node *n, const T &element) noexcept
            {
                if (n == nullptr)
                    return false;
                if (n->element == element)
                    return true;
                bool result = bool();
                for (auto l : n->childs)
                    result |= exist(l.second, element);
                return result;
            }

            static void replace(node *n, const T &oldEle, const T &newEle) noexcept
            {
                if (n == nullptr)
                    return;
                if (n->childs.empty())
                    return;
                if (n->element == oldEle)
                    n->element = newEle;
                for (auto l : n->childs)
                    replace(l.second, oldEle, newEle);
            }

        public:
            multiBranch() = default;
            ~multiBranch() { clear(root); }
            multiBranch(const T &element) : root(new node{nullptr, {}, element}),
                                            current(root), nodeNumber(1) {}

            void set(const T &element) noexcept
            {
                if (root != nullptr)
                    return;
                root = new node{nullptr, {}, element};
                current = root;
                nodeNumber++;
            }

            void add(const std::string &name, const T &element) noexcept
            {
                if (root == nullptr)
                {
                    std::cerr << "Empty Error: can't add on empty tree at least you have to set the root of the tree.\n"
                              << "use set(const T& element) to solve the error.\n";
                    return;
                }
                if (current == nullptr)
                {
                    std::cerr << "internal Error(null value allocation): the current node points to nullptr.\n"
                              << "use move(true) to solve the error.\n";
                    return;
                }
                current->childs[name] = new node{current, {}, element};
                nodeNumber++;
            }

            void add(const std::string &name,
                     const multiBranch<T> &other) noexcept
            {
                add(name, other.root);
            }

            void remove() noexcept
            {
                node *temp = current;
                if (temp->parent == nullptr)
                    current = nullptr;
                else
                    current = current->parent;
                clear(temp);
            }

            void remove_child(const std::string &name)
            {
                if (root != nullptr)
                {
                    current->childs.erase(name);
                    nodeNumber--;
                }
                else if (root == nullptr)
                {
                    std::cerr << "empty error: the tree is empty,"
                              << " can't remove.\n";
                }
                else if (current->childs.empty())
                {
                    std::cerr << "empty error: no childs for the current"
                              << " element, can't remove.\n";
                }
            }

            void clear() noexcept { clear(root); }

            void clear_childs() noexcept
            {
                if (current->childs.empty())
                    return;
                nodeNumber -= current->childs.size();
                current->childs.clear();
            }

            void move(bool toRoot)
            {
                if (root != nullptr && toRoot)
                    current = root;
                else if (current->parent != nullptr && !toRoot)
                    current = current->parent;
                else
                {
                    std::cerr << "nullptr error: the current"
                              << " node don't have parent node.\n";
                }
            }

            void move(const std::string &name)
            {
                if (current->childs.contains(name))
                {
                    current = current->childs[name];
                }
                else
                {
                    std::cerr << "no element in current childs"
                              << " have this name: " << name << ".\n";
                }
            }

            void list() noexcept
            {
                if (root == nullptr || current == nullptr)
                    return;
                for (auto p : current->childs)
                {
                    std::cout << "The name: "
                              << p.first
                              << ", value: "
                              << p.second;
                }
            }

            constexpr bool in_root() noexcept { return current == root ? true : false; }
            constexpr bool has_childs() noexcept { return !(current->childs.empty()); }
            constexpr bool has_parent() noexcept { return current->parent != nullptr; }
            constexpr bool empty() noexcept { return root == nullptr; }
            bool contains_child(const std::string &name) { return current->childs.contains(name); }
            bool exist(const T &element) { return exist(root, element); }
            void replace(const T &oldEle, const T &newEle) { replace(root, oldEle, newEle); }

            void operator=(const std::map<std::string, T> &list)
            {
                for (auto element : list)
                    add(element.first, element.second);
            }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator+=(const T &element) noexcept { current->element += element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator-=(const T &element) noexcept { current->element -= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator*=(const T &element) noexcept { current->element *= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator/=(const T &element) noexcept { current->element /= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator+(const T &element) noexcept { return current->element + element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator-(const T &element) noexcept { return current->element - element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator*(const T &element) noexcept { return current->element * element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator/(const T &element) noexcept { return current->element / element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator&=(const T &element) noexcept { current->element &= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator|=(const T &element) noexcept { current->element |= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator^=(const T &element) noexcept { current->element ^= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator&&(const T &element) noexcept { return current->element && element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator||(const T &element) noexcept { return current->element || element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator^(const T &element) noexcept { return current->element ^ element; }

            constexpr T operator[](const std::string &name)
            {
                if (name.empty())
                {
                    throw std::invalid_argument("empty string parameter.");
                }
                else if (!contains_child(name))
                {
                    throw std::invalid_argument("no child has this name: " + name + ". ");
                }
                node *temp = current->childs[name];
                return temp->element;
            }
        };
    }
}

#endif // OPENUDT___CORE_TREE_HPP