#include "using_keys.hpp"

#pragma once
#ifndef OPENUDT___CORE___TREE_BINARY_HPP
#define OPENUDT___CORE___TREE_BINARY_HPP

namespace udt
{
    namespace tree
    {
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
    }
}

#endif // OPENUDT___CORE___TREE_BINARY_HPP