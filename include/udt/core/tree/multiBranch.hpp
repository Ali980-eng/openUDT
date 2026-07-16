#include <iostream>
#include "cfrost/structure.h"
#include <stdexcept>

#pragma once
#ifndef OPENUDT___CORE___TREE_MULTIBRANCH_HPP
#define OPENUDT___CORE___TREE_MULTIBRANCH_HPP

namespace udt
{
    namespace tree
    {

        /// @brief Represents a tree where each node may have multiple named child branches.
        ///
        /// This container is useful for hierarchical data structures where each child is
        /// identified by a string name rather than by a fixed positional index.
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

            /// @brief Constructs a tree with the provided root element.
            ///
            /// @param element The initial value stored at the root node.
            multiBranch(const T &element) : root(new node{nullptr, {}, element}),
                                            current(root), nodeNumber(1) {}

            /// @brief Initializes the root node when the tree is still empty.
            ///
            /// @param element The value assigned to the root node.
            void set(const T &element) noexcept
            {
                if (root != nullptr)
                    return;
                root = new node{nullptr, {}, element};
                current = root;
                nodeNumber++;
            }

            /// @brief Adds a child node under the current node.
            ///
            /// @param name The name used to identify the child.
            /// @param element The value stored in the new child node.
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

            /// @brief Adds a child node whose subtree is copied from another multiBranch instance.
            ///
            /// @param name The name used to identify the child.
            /// @param other The tree whose root value is used to create the child subtree.
            void add(const std::string &name,
                     const multiBranch<T> &other) noexcept
            {
                add(name, other.root);
            }

            /// @brief Removes the current node from the tree and repositions the cursor to its parent.
            void remove() noexcept
            {
                node *temp = current;
                if (temp->parent == nullptr)
                    current = nullptr;
                else
                    current = current->parent;
                clear(temp);
            }

            /// @brief Removes a named child from the current node.
            ///
            /// @param name The child name to remove.
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

            /// @brief Clears the entire tree.
            void clear() noexcept { clear(root); }

            /// @brief Removes all children from the current node.
            void clear_childs() noexcept
            {
                if (current->childs.empty())
                    return;
                nodeNumber -= current->childs.size();
                current->childs.clear();
            }

            /// @brief Moves the current node to the root or to its parent.
            ///
            /// @param toRoot When true, moves to the root; otherwise moves to the parent.
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

            /// @brief Moves the current node to a child identified by name.
            ///
            /// @param name The name of the child node to select.
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

            /// @brief Prints the current node's child names and associated values.
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

            /// @brief Checks whether the current node is the root node.
            constexpr bool in_root() noexcept { return current == root ? true : false; }

            /// @brief Checks whether the current node has any children.
            constexpr bool has_childs() noexcept { return !(current->childs.empty()); }

            /// @brief Checks whether the current node has a parent node.
            constexpr bool has_parent() noexcept { return current->parent != nullptr; }

            /// @brief Checks whether the tree has no root node.
            constexpr bool empty() noexcept { return root == nullptr; }

            /// @brief Checks whether the current node contains a named child.
            ///
            /// @param name The child name to search for.
            bool contains_child(const std::string &name) { return current->childs.contains(name); }

            /// @brief Checks whether the specified value exists anywhere in the tree.
            ///
            /// @param element The value to search for.
            bool exist(const T &element) { return exist(root, element); }

            /// @brief Replaces every matching value in the tree with a new value.
            ///
            /// @param oldEle The old value to replace.
            /// @param newEle The new value used as a replacement.
            void replace(const T &oldEle, const T &newEle) { replace(root, oldEle, newEle); }

            /// @brief Assigns a set of named values to the tree by inserting them as children.
            ///
            /// @param list A mapping of child names to values.
            void operator=(const std::map<std::string, T> &list)
            {
                for (auto element : list)
                    add(element.first, element.second);
            }

            /// @brief Adds a value to the current node's stored element.
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

#endif // OPENUDT___CORE___TREE_MULTIBRANCH_HPP