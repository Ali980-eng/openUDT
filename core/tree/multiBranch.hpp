#pragma once
#ifndef OPENUDT___CORE___TREE_MULTIBRANCH_HPP
#define OPENUDT___CORE___TREE_MULTIBRANCH_HPP

namespace udt
{
    namespace tree
    {

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

#endif // OPENUDT___CORE___TREE_MULTIBRANCH_HPP