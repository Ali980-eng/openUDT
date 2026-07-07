#include "using_keys.hpp"

#pragma once
#ifndef OPENUDT___CORE___TREE_BINARY_HPP
#define OPENUDT___CORE___TREE_BINARY_HPP

namespace udt
{
    namespace tree
    {
        /// @brief Represents a binary tree with optional binary-search-tree semantics.
        ///
        /// The tree stores nodes with left and right links and tracks the current node
        /// for navigation and manipulation.
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

            /// @brief Constructs a tree with the provided root element.
            ///
            /// @param rootEle The value stored in the initial root node.
            binary(const T &rootEle)
                : root(new Node{rootEle, nullptr, nullptr, nullptr}),
                  current(root),
                  node_number(1)
            {
            }

            binary(const binary &) = delete;
            binary &operator=(const binary &) = delete;

            /// @brief Checks whether the tree contains any nodes.
            ///
            /// @return true if the tree is empty, false otherwise.
            constexpr bool empty() noexcept { return root == nullptr; }

            /// @brief Inserts an element into the current tree position for BST mode.
            ///
            /// @param element The value to insert.
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

            /// @brief Inserts an element into the left or right child position in non-BST mode.
            ///
            /// @param left Selects the left child when true, otherwise the right child.
            /// @param element The value to insert.
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

            /// @brief Removes the current node and its subtree from the tree.
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

            /// @brief Removes the node matching the specified value in BST mode.
            ///
            /// @param element The value to remove.
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

            /// @brief Removes the left or right child of the current node.
            ///
            /// @param left Removes the left child when true, otherwise the right child.
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

            /// @brief Moves the current pointer to the parent node.
            constexpr void move_back() noexcept
            {
                current = current->prev;
            }

            /// @brief Resets the current pointer to the root node.
            constexpr void move() noexcept
            {
                current = root;
            }

            /// @brief Moves the current pointer to the left or right child.
            ///
            /// @param left Moves to the left child when true, otherwise the right child.
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

            /// @brief Returns the number of nodes currently stored in the tree.
            ///
            /// @return The node count.
            constexpr size_t nodeNumber() noexcept { return node_number; }

            /// @brief Prints the current node and its immediate children.
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

            /// @brief Checks whether the current node has a child on the specified side.
            ///
            /// @param left Checks the left child when true, otherwise the right child.
            /// @return true if the target child exists, false otherwise.
            bool has_item(bool left) noexcept
            {
                if (left)
                    return current->left != nullptr;
                else
                    return current->right != nullptr;
            }

            /// @brief Checks whether the current node is a leaf.
            ///
            /// @return true if the node has no children, false otherwise.
            constexpr bool is_leaf() noexcept
            {
                return current->left == nullptr &&
                       current->right == nullptr;
            }

            /// @brief Checks whether the current node is the root node.
            ///
            /// @return true if the current node is the root, false otherwise.
            constexpr bool in_root() noexcept { return current == root; }

            /// @brief Returns the root element.
            ///
            /// @return The stored root value.
            constexpr T get_root() noexcept { return root->item; }

            /// @brief Returns the current node element.
            ///
            /// @return The stored value of the current node.
            constexpr T get() noexcept { return current->item; }

            /// @brief Returns the left or right child element of the current node.
            ///
            /// @param left Selects the left child when true, otherwise the right child.
            /// @return The child value, or a default-constructed value if it is missing.
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

            /// @brief Removes every node in the tree and resets the traversal state.
            void clear() noexcept
            {
                clear(root);
                root = nullptr;
                current = nullptr;
                node_number = size_t();
            }

            /// @brief Checks whether the specified element exists in the tree.
            ///
            /// @param element The value to search for.
            /// @return true if the element is present, false otherwise.
            bool exist(const T &element)
            {
                if constexpr (!BST)
                    return exist(root, element);
                else
                    return exist(element);
            }

            /// @brief Replaces all matching values in the tree with a new value.
            ///
            /// @param oldEle The value to replace.
            /// @param newEle The replacement value.
            void replace(const T &oldEle, const T &newEle)
            {
                if constexpr (!BST)
                    replace(root, oldEle, newEle);
                else
                    replace(oldEle, newEle);
            }

            /// @brief Applies an in-place addition to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator+=(const T &element) noexcept { current->item += element; }

            /// @brief Applies an in-place subtraction to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator-=(const T &element) noexcept { current->item -= element; }

            /// @brief Applies an in-place multiplication to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator*=(const T &element) noexcept { current->item *= element; }

            /// @brief Applies an in-place division to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator/=(const T &element) noexcept { current->item /= element; }

            /// @brief Returns the result of adding the given value to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator+(const T &element) noexcept { return current->item + element; }

            /// @brief Returns the result of subtracting the given value from the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator-(const T &element) noexcept { return current->item - element; }

            /// @brief Returns the result of multiplying the current node value by the given value.
            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator*(const T &element) noexcept { return current->item * element; }

            /// @brief Returns the result of dividing the current node value by the given value.
            template <typename U = T>
            constexpr arithmetic_condition<U, T>
            operator/(const T &element) noexcept { return current->item / element; }

            /// @brief Applies a bitwise AND to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator&=(const T &element) noexcept { current->item &= element; }

            /// @brief Applies a bitwise OR to the current node value.
            template <typename U = T>
            constexpr arithmetic_condition<U, void>
            operator|=(const T &element) noexcept { current->item |= element; }

            /// @brief Applies a bitwise XOR to the current node value.
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

            /// @brief Compares the current node value with another value for equality.
            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator==(const T &element) noexcept { return current->item == element; }

            /// @brief Compares the current node value with another value for inequality.
            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator!=(const T &element) noexcept { return current->item != element; }

            /// @brief Compares the current node value with another value for greater-than.
            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator>(const T &element) noexcept { return current->item > element; }

            /// @brief Compares the current node value with another value for less-than.
            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator<(const T &element) noexcept { return current->item < element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator>=(const T &element) noexcept { return current->item >= element; }

            template <typename U = T>
            constexpr arithmetic_condition<U, bool>
            operator<=(const T &element) noexcept { return current->item <= element; }

            /// @brief Returns the child value selected by the given direction.
            ///
            /// @param left Selects the left child when true, otherwise the right child.
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