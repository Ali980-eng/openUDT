#include "using_keys.hpp"

#pragma once
#ifndef OPENUDT___CORE___TREE_TERNARY_HPP
#define OPENUDT___CORE___TREE_TERNARY_HPP

namespace udt
{
    namespace tree
    {
        /// @brief Represents a ternary tree where each node may have up to three children.
        ///
        /// The class supports navigation through left, middle, right, and parent links,
        /// and provides basic insertion and lookup helpers for tree traversal.
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

            /// @brief Constructs a ternary tree with the provided root element.
            ///
            /// @param element The value assigned to the root node.
            Ternary(const T &element)
            {
                root = new node{nullptr, nullptr, nullptr, nullptr, element};
                current = root;
            }

            /// @brief Sets or resets the root node to the supplied value.
            ///
            /// @param element The value stored in the root node.
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

            /// @brief Inserts an element into the current node according to BST-style ordering.
            ///
            /// @param element The value to insert.
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

            /// @brief Inserts an element into a specific child slot in non-BST mode.
            ///
            /// @param element The value to insert.
            /// @param left Selects the left branch when true.
            /// @param right Selects the right branch when true.
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

            /// @brief Checks whether the current node is the root node.
            constexpr bool in_root() noexcept { return current == root; }

            /// @brief Moves the current pointer to a child or back to the parent.
            ///
            /// @param left Selects the left branch when true.
            /// @param right Selects the right branch when true.
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

            /// @brief Returns the value stored at the current node.
            ///
            /// @return The current node's value.
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

            /// @brief Checks whether the supplied value exists somewhere in the tree.
            ///
            /// @param element The value to locate.
            bool exsit(const T &element)
            {
                return exsit(root, element);
            }

            /// @brief Replaces the value of every matching node in the tree.
            ///
            /// @param element The replacement value.
            void replace(const T &element) noexcept
            {
                replace(root, element);
            }

            /// @brief Assigns a new value to the current node.
            ///
            /// @param element The value to assign.
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

            /// @brief Compares the current node value with another value for equality.
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

            /// @brief Compares the current node value with another value for inequality.
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
    }
}

#endif // OPENUDT___CORE___TREE_TERNARY_HPP