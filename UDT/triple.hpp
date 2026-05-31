/**
 * @file triple.hpp
 * @brief Defines the triple_t and triple_t3 classes for storing and manipulating triples of values.
 * This header provides two template classes:
 * - triple_t<T>: A class for storing three values of the same type T, with various member functions for accessing and modifying the elements.
 * - triple_t3<T1, T2, T3>: A class for storing three values of potentially different types (T1, T2, T3), with similar member functions for access and modification.
 * Both classes include constructors, getters/setters, element search, swapping, and various arithmetic operations. The member functions are designed to be constexpr and noexcept where appropriate, allowing for compile-time evaluation and guaranteeing no exceptions will be thrown.
 * The classes are defined within the 'udt' namespace and are intended for use in contexts where a simple grouping of three related values is needed, with convenient member functions for common operations on those values.
 * @note The implementation of some member functions (e.g., change_element) contains a bug where '==' is used instead of '=' for assignment, which should be addressed for correct functionality.
 * @see std::tuple for a more general-purpose alternative that can store an arbitrary number of elements of varying types.
 * @author Ali Lafi
 * @date 2025/9/25
 */

#include <iostream>
#include <cmath>
#include <stdexcept>

#pragma once
#ifndef OPENUDT___UDT_TRIPLE_HPP
#define OPENUDT___UDT_TRIPLE_HPP

namespace udt
{

    /// @brief A class representing a triple of values of type T.
    /// @tparam T The type of the elements in the triple.
    template <typename T>
    class triple_t
    {
    private:
        T first;
        T second;
        T third;

    public:
        /// @brief Default constructor that initializes all elements to their default values.
        constexpr triple_t() noexcept : first(T()), second(T()), third(T()) {}

        /// @brief Constructor that initializes the triple with the given values.
        /// @param first The first element.
        /// @param second The second element.
        /// @param third The third element.
        constexpr triple_t(const T &first, const T &second, const T &third) noexcept : first(first), second(second), third(third) {}

        /// @brief Copy constructor that initializes the triple with the values from another triple.
        /// @param other The other triple to copy from.
        constexpr triple_t(const triple_t &other) noexcept : first(other.first), second(other.second), third(other.third) {}

        /// @brief Get the first element of the triple.
        /// @return The first element.
        constexpr T get_first() const noexcept { return first; }

        /// @brief Get the second element of the triple.
        /// @return The second element.
        constexpr T get_second() const noexcept { return second; }

        /// @brief Get the third element of the triple.
        /// @return The third element.
        constexpr T get_third() const noexcept { return third; } /// @brief Set the first element of the triple.

        /// @param value The new value for the first element.
        constexpr void set_first(const T &value) noexcept { first = value; }

        /// @brief Set the second element of the triple.
        /// @param value The new value for the second element.
        constexpr void set_second(const T &value) noexcept { second = value; }

        /// @brief Set the third element of the triple.
        /// @param value The new value for the third element.
        constexpr void set_third(const T &value) noexcept { third = value; }

        /// @brief Set all three elements of the triple.
        /// @param first The new value for the first element.
        /// @param second The new value for the second element.
        /// @param third The new value for the third element.
        constexpr void set(const T &first, const T &second, const T &third) noexcept
        {
            this->first = first;
            this->second = second;
            this->third = third;
        }

        /// @brief Check if the triple contains the given element.
        /// @param element The element to search for.
        /// @return True if the element is found, false otherwise.
        constexpr bool element_search(const T &element) const noexcept
        {
            if (first == element)
                return true;
            else if (second == element)
                return true;
            else if (third == element)
                return true;
            else
                return false;
        }

        /**
         * @brief Change an element in the stored triple either by index or by value.
         *
         * Template parameter:
         * @tparam change_by_index If true, this call will change an element by its 1-based
         *                         index argument. If false, the function will search for
         *                         a matching element and replace it.
         *
         * Parameters:
         * @param element     The value used to locate the element to be replaced when
         *                    change_by_index is false. Ignored when change_by_index is true.
         * @param NewElement  The value that will replace the targeted element.
         * @param index       1-based index of the element to replace when change_by_index
         *                    is true. Default is -1 (invalid). If index <= -1, the function
         *                    returns without modifying anything.
         *
         * Behavior:
         * - When change_by_index == true:
         *   - If index <= -1: no change is performed.
         *   - If index == 1: the first element is set to NewElement.
         *   - If index == 2: the second element is set to NewElement.
         *   - If index == 3: the third element is set to NewElement.
         *   - If index is any other value: an error message is written to std::cerr and the
         *     third element is set to NewElement.
         *
         * - When change_by_index == false:
         *   - The function uses element_search(element) to determine if the element exists.
         *     If element_search(element) returns true, it will attempt to replace the first
         *     matching element in the order: first, second, third.
         *   - If first == element, first is set to NewElement.
         *   - Else if second == element, the code intends to set second to NewElement.
         *     NOTE: current implementation contains a bug using '==' (comparison) instead
         *     of '=' (assignment) for the second element; as written, second will not be
         *     modified even when it matches.
         *   - Else (fall-through) the third element is set to NewElement.
         *
         * Preconditions:
         * - The object must have members named first, second, third and a callable
         *   element_search(const T&) that returns a bool indicating presence.
         *
         * Postconditions:
         * - One element may be modified depending on the control path described above.
         *
         * Exceptions / noexcept:
         * - The function is declared noexcept and must not throw. It performs I/O via
         *   std::cerr for out-of-range index reporting.
         *
         * Side effects:
         * - Writes an error message to std::cerr for an out-of-range index when
         *   change_by_index == true.
         *
         * Notes:
         * - Indexing is 1-based (1 -> first, 2 -> second, 3 -> third).
         * - If multiple elements are equal to element, only the first matching element
         *   in evaluation order will be replaced.
         * - Consider fixing the assignment bug for the second element:
         *     second = NewElement;
         */
        template <bool change_by_index = false>
        constexpr void change_element(const T &element, const T &NewElement, int index = -1) noexcept
        {
            if (change_by_index)
            {
                if (index <= -1)
                    return;
                if (index == 1)
                    first = NewElement;
                else if (index == 2)
                    second = NewElement;
                else if (index == 3)
                    third = NewElement;
                else
                {
                    std::cerr << "The index is out of range.\n"
                              << "The program, by default, will set the "
                              << "value of the last element as a new element.\n";
                    third = NewElement;
                }
            }
            if (element_search(element))
            {
                if (first == element)
                    first = NewElement;
                else if (second == element)
                    second == NewElement;
                else
                    third = NewElement;
            }
        }

        /**
         * @brief Swap the contents of this triple with another.
         *
         * Exchanges the values of the three members (first, second, third) with those
         * of @p other by invoking std::swap on each member. After the call, this
         * object contains the former values of @p other and vice versa.
         *
         * @param other The triple to swap contents with.
         *
         * @note The function is declared noexcept. If any std::swap operation on the
         *       member types were to throw, the program will call std::terminate.
         * @note Complexity is constant: performs exactly three element swaps (O(1)).
         * @note Swapping an object with itself is safe and has no observable effect.
         */
        constexpr void swap(triple_t &other) noexcept
        {
            std::swap(first, other.first);
            std::swap(second, other.second);
            std::swap(third, other.third);
        }

        /// @brief Get the maximum element among the three.
        /// @return The maximum element.
        constexpr T max() const noexcept { return std::max({first, second, third}); }

        /// @brief Get the minimum element among the three.
        /// @return The minimum element.
        constexpr T min() const noexcept { return std::min({first, second, third}); }

        /// @brief Calculate the sum of the three elements, optionally starting from a given initial value.
        /// @param num the initial value to start the sum from.
        /// @return The sum of the three elements plus the initial value.
        constexpr T sum(int num = 0) const noexcept { return num + first + second + third; }

        /// @brief Calculate the product of the three elements, optionally starting from a given initial value.
        /// @param num the initial value to start the product from.
        /// @return The product of the three elements multiplied by the initial value.
        constexpr T product(int num = 1) const noexcept { return num * first * second * third; }

        /// @brief Calculate the average of the three elements.
        /// @return The average of the three elements.
        constexpr T average() const noexcept { return sum() / 3; }

        /**
         * @brief Clear the contents of the triple by resetting all elements to their default values.
         * This member function assigns the default-constructed value of type T to each of the three members (first, second, third), effectively resetting the triple to a "cleared" state. The function is declared constexpr and noexcept, allowing it to be used in constant expressions and guaranteeing that it will not throw exceptions.
         * @note The function does not take any parameters and does not return a value. After calling clear(), all members of the triple will be equal to T(), which is the default value for type T (e.g., 0 for numeric types, empty string for std::string, etc.).
         * @complexity Constant time O(1) since it performs a fixed number of assignments regardless of the state of the object.
         * @pre The type T must be default-constructible for this function to compile successfully, as it relies on T() to obtain the default value.
         * @post The members first, second, and third of this triple will be set to T(), effectively clearing the contents of the triple.
         * @exception This function is noexcept and does not throw exceptions. If T's default constructor were to throw, the program would call std::terminate due to the noexcept specification.
         * @note This function can be used to reset the state of the triple before reusing it or to clear sensitive data if T contains such information.
         * @example
         * triple_t<int> myTriple(1, 2, 3);
         * myTriple.clear(); // After this call, myTriple will contain (0, 0, 0).
         * triple_t<std::string> strTriple("Hello", "World", "!");
         * strTriple.clear(); // After this call, strTriple will contain ("", "", "").
         */
        constexpr void clear() noexcept
        {
            first = T();
            second = T();
            third = T();
        }

        /**
         * @brief Copy-assignment operator for triple_t.
         *
         * Copies the contained elements (first, second, third) from another
         * triple_t instance into this instance. A self-assignment check is
         * performed to avoid unnecessary work.
         *
         * @param other The triple_t to copy from.
         * @return Reference to this instance (*this) after assignment.
         *
         * @note This operator is noexcept.
         */
        constexpr triple_t &operator=(const triple_t &other) noexcept
        {
            if (this != &other)
            {
                first = other.first;
                second = other.second;
                third = other.third;
            }
            return *this;
        }

        /// @brief Check if this triple is equal to another.
        /// @param other The triple to compare with.
        /// @return True if all corresponding elements are equal, false otherwise.
        constexpr bool operator==(const triple_t &other) const noexcept { return first == other.first && second == other.second && third == other.third; }

        /// @brief Check if this triple is not equal to another.
        /// @param other The triple to compare with.
        /// @return True if any corresponding elements are not equal, false otherwise.
        constexpr bool operator!=(const triple_t &other) const noexcept { return !(*this == other); }

        /**
         * @brief Adds the given value to each of the object's three components.
         *
         * Adds value to first, second and third in-place.
         *
         * @param value The value to add to each component.
         *
         * @note This member function is constexpr and noexcept: it may be evaluated at compile time
         *       and guarantees not to throw exceptions.
         * @pre Each component (first, second, third) must support operator+=(const T&).
         * @complexity Constant time O(1).
         */
        constexpr void operator+=(const T &value) noexcept
        {
            first += value;
            second += value;
            third += value;
        }

        /**
         * @brief Adds another triple to this triple, component-wise.
         *
         * Performs element-wise addition:
         *   - first  += other.first
         *   - second += other.second
         *   - third  += other.third
         *
         * @param other The triple whose components will be added to this triple.
         *
         * @note This function is declared noexcept. If any underlying component's operator+= throws,
         *       std::terminate will be invoked.
         *
         * @post Each component of this triple is increased by the corresponding component of @p other.
         * @complexity Constant time.
         */
        constexpr void operator+=(const triple_t &other) noexcept
        {
            first += other.first;
            second += other.second;
            third += other.third;
        }

        /**
         * @brief Pre-increment the tuple-like object in-place.
         *
         * Increments each component (first, second, third) by one, in that order.
         *
         * This member function is constexpr and noexcept: it can be evaluated in a
         * constant expression and is guaranteed not to throw.
         *
         * @note The operator modifies the object and does not return a value.
         * @complexity Constant time O(1).
         */
        constexpr void operator++() noexcept
        {
            ++first;
            ++second;
            ++third;
        }

        /**
         * Subtracts the given value from each component of the triple.
         *
         * Performs element-wise subtraction assignment:
         * - first  -= value;
         * - second -= value;
         * - third  -= value;
         *
         * This function is constexpr and guaranteed not to throw (noexcept).
         *
         * Requirements:
         * - The element type T must be copy-assignable and must support operator-=(const T&).
         *
         * Complexity: O(1) — performs three subtraction assignments.
         *
         * @param value The value to subtract from each component.
         * @note No overflow/underflow or range checking is performed; behavior follows the underlying type T.
         */
        constexpr void operator-=(const T &value) noexcept
        {
            first -= value;
            second -= value;
            third -= value;
        }

        /**
         * Subtracts the components of another triple_t from this object.
         *
         * Performs element-wise subtraction:
         *   - first  -= other.first;
         *   - second -= other.second;
         *   - third  -= other.third;
         *
         * This is a mutating operator (modifies *this), marked constexpr so it
         * can be used in constant expressions and noexcept to indicate it will
         * not throw exceptions.
         *
         * @param other  The triple_t whose components are to be subtracted.
         * @note Does not return a value; operation completes in constant time.
         */
        constexpr void operator-=(const triple_t &other) noexcept
        {
            first -= other.first;
            second -= other.second;
            third -= other.third;
        }

        /**
         * @brief Prefix-decrements each element of the object.
         *
         * Applies the prefix decrement operator (--value) to the members `first`, `second`,
         * and `third` in that order, modifying the object in place.
         *
         * This function is constexpr and noexcept.
         *
         * @note Each member type must support the prefix decrement operation.
         * @warning This overload does not return a value; it performs the mutation only.
         */
        constexpr void operator--() noexcept
        {
            --first;
            --second;
            --third;
        }

        /**
         * Compound multiplication-assignment operator.
         *
         * Multiplies each component (first, second, third) by the provided scalar
         * value and stores the results in-place.
         *
         * Requirements:
         *  - The component types must support operator*=(const T&).
         *
         * @param value Scalar value to multiply each component by.
         * @note This function is constexpr and noexcept and therefore can be
         *       evaluated at compile time when used with constant expressions and
         *       is guaranteed not to throw.
         */
        constexpr void operator*=(const T &value) noexcept
        {
            first *= value;
            second *= value;
            third *= value;
        }

        /**
         * @brief Multiply-assign operator performing component-wise multiplication.
         *
         * Multiplies each member of this triple (first, second, third) by the
         * corresponding member of the provided triple, storing the results in this object.
         * The operation is performed in-place and is constexpr and noexcept.
         *
         * @param other The triple whose components are multiplied into this triple.
         */
        constexpr void operator*=(const triple_t &other) noexcept
        {
            first *= other.first;
            second *= other.second;
            third *= other.third;
        }

        /**
         * @brief In-place scalar division of the three components.
         *
         * Divides each component (first, second, third) by the provided scalar and
         * updates the object in-place.
         *
         * The operation is constexpr and noexcept.
         *
         * @param value The scalar divisor applied to all components.
         *
         * @pre The component type must support operator/=(const T&).
         * @pre For arithmetic component types, division by zero is undefined behavior.
         * @post The object's components have been divided by value.
         * @complexity Constant time.
         */
        constexpr void operator/=(const T &value) noexcept
        {
            first /= value;
            second /= value;
            third /= value;
        }

        /**
         * @brief Element-wise in-place division by another triple_t.
         *
         * Modifies this triple by dividing each of its components by the corresponding
         * component of the provided 'other' triple (i.e., each component performs an
         * in-place division by the matching component from 'other').
         *
         * @param other The triple whose components are used as divisors.
         *
         * @effects Modifies the members of *this.
         * @throws Nothing — marked noexcept.
         * @note The function is constexpr and may be evaluated in a constant expression
         *       when operands permit.
         * @pre The component type(s) must support operator/= for the type of the
         *      corresponding components of 'other'. For integral component types,
         *      dividing by zero is undefined behavior; for floating-point types,
         *      division by zero yields implementation-defined IEEE results (inf/nan).
         * @complexity Constant time (O(1)).
         */
        constexpr void operator/=(const triple_t &other) noexcept
        {
            first /= other.first;
            second /= other.second;
            third /= other.third;
        }

        /**
         * Applies an in-place exponentiation to each component.
         *
         * Raises each of the members (first, second, third) to the specified power using std::pow
         * and stores the results back into those members.
         *
         * @tparam T Type of the exponent. Must be compatible with std::pow for the component types.
         * @param value Exponent value to apply to each component.
         * @note This function is declared noexcept; if std::pow throws for the provided types, the
         *       program will call std::terminate.
         * @complexity Constant time (performs three pow operations).
         * @example
         * // Raises each component to the 2nd power (squares them):
         * // vec ^= 2.0;
         */
        constexpr void operator^=(const T &value) noexcept
        {
            first = std::pow(first, value);
            second = std::pow(second, value);
            third = std::pow(third, value);
        }

        /**
         * Element-wise exponentiation-assignment operator.
         *
         * Raises each component of this triple to the power of the corresponding
         * component from 'other' and stores the result back into this object.
         *
         * Effects:
         *  - first  = std::pow(first,  other.first)
         *  - second = std::pow(second, other.second)
         *  - third  = std::pow(third,  other.third)
         *
         * Parameters:
         *  - other: triple_t providing the exponents for each component.
         *
         * Exception safety:
         *  - Declared noexcept, but callers should be aware that std::pow can
         *    exhibit domain-related behavior (e.g., negative base with non-integer
         *    exponent) or produce +/-inf/NaN for invalid inputs. Ensure inputs are
         *    appropriate for std::pow when necessary.
         *
         * Notes:
         *  - This performs component-wise power assignment. Verify that the
         *    implementation uses the matching component from 'other' for each
         *    assignment (avoid reusing the same component by mistake).
         */
        constexpr void operator^=(const triple_t &other) noexcept
        {
            first = std::pow(first, other.first);
            second = std::pow(second, other.second);
            third = std::pow(second, other.second);
        }

        /**
         * Access element by 1-based index.
         *
         * @param i 1-based index of the element to retrieve:
         *          - 1: returns first
         *          - 2: returns second
         *          - 3: returns third
         *
         * @return A copy of the selected element of type T.
         *
         * @throws Nothing (function is marked noexcept).
         *
         * @notes
         * - If i is not 1, 2, or 3, the function writes "the index is out of range"
         *   to std::cerr and returns the third element. This out-of-range behavior may
         *   mask errors in callers that expect bounds-checked access.
         * - The function is declared constexpr; however, the out-of-range branch
         *   performs a runtime side-effect (writing to std::cerr) and thus that path
         *   cannot be evaluated in a constant expression.
         * - Complexity: O(1).
         */
        constexpr T operator[](unsigned int i) const noexcept
        {
            if (i == 1)
                return first;
            else if (i == 2)
                return second;
            else if (i == 3)
                return third;
            std::cerr << "the index is out of range" << std::endl;
            return third;
        }
    };

    /**
     * @brief A class representing a triple of values of potentially different types.
     * This class template allows for storing three values of types T1, T2, and T3, which may be different from each other. It provides member functions for accessing and modifying the elements, as well as various operations such as searching, swapping, and arithmetic operations. The member functions are designed to be constexpr and noexcept where appropriate, allowing for compile-time evaluation and guaranteeing no exceptions will be thrown.
     * @tparam T1 The type of the first element in the triple.
     * @tparam T2 The type of the second element in the triple.
     * @tparam T3 The type of the third element in the triple.
     * @note The implementation of some member functions (e.g., change_element) contains a bug where '==' is used instead of '=' for assignment, which should be addressed for correct functionality.
     * @see std::tuple for a more general-purpose alternative that can store an arbitrary number of elements of varying types.
     */
    template <typename T1, typename T2, typename T3>
    class triple_t3
    {
    private:
        T1 first;
        T2 second;
        T3 third;

    public:
        /// @brief Default constructor that initializes all elements to their default values.
        constexpr triple_t3() noexcept : first(T1()), second(T2()), third(T3()) {}

        /// @brief Constructor that initializes the triple with the given values.
        /// @param first The first element.
        /// @param second The second element.
        /// @param third The third element.
        constexpr triple_t3(const T1 &first, const T2 &second, const T3 &third) noexcept : first(first), second(second), third(third) {}

        /// @brief Copy constructor that initializes the triple with another triple.
        /// @param other The other triple to copy from.
        constexpr triple_t3(const triple_t3<T1, T2, T3> &other) noexcept : first(other.first), second(other.second), third(other.third) {}

        /// @brief Gets the first element of the triple.
        /// @return The first element.
        constexpr T1 get_first() const noexcept { return first; }

        /// @brief Gets the second element of the triple.
        /// @return The second element.
        constexpr T2 get_second() const noexcept { return second; }

        /// @brief Gets the third element of the triple.
        /// @return The third element.
        constexpr T3 get_third() const noexcept { return third; }

        /// @brief Sets the first element of the triple.
        /// @param value The new value for the first element.
        constexpr void set_first(const T1 &value) noexcept { first = value; }

        /// @brief Sets the second element of the triple.
        /// @param value The new value for the second element.
        constexpr void set_second(const T2 &value) noexcept { second = value; }

        /// @brief Sets the third element of the triple.
        /// @param value The new value for the third element.
        constexpr void set_third(const T3 &value) noexcept { third = value; }

        /**
         * Sets the object's elements from the provided values.
         *
         * Copies each argument into the corresponding data member:
         *   - this->first  = first
         *   - this->second = second
         *   - this->third  = third
         *
         * The function is constexpr and noexcept: it can be used in constant expressions
         * when the copy assignments are constexpr-capable, and it guarantees not to throw.
         *
         * @param first  Value to assign to the member 'first' (copied from const reference).
         * @param second Value to assign to the member 'second' (copied from const reference).
         * @param third  Value to assign to the member 'third' (copied from const reference).
         *
         * Complexity: O(1).
         */
        constexpr void set(const T1 &first, const T2 &second, const T3 &third) noexcept
        {
            this->first = first;
            this->second = second;
            this->third = third;
        }

        /// @brief Searches for an element in the triple.
        /// @param element the element to search for.
        /// @return a boolean indicating if the element was found.
        constexpr bool sarch(const T1 &element) const noexcept { return first == element; }

        /// @brief Searches for an element in the triple.
        /// @param element the element to search for.
        /// @return a boolean indicating if the element was found.
        constexpr bool sarch(const T2 &element) const noexcept { return second == element; }

        /// @brief Searches for an element in the triple.
        /// @param element the element to search for.
        /// @return a boolean indicating if the element was found.
        constexpr bool sarch(const T3 &element) const noexcept { return third == element; }

        /**
         * @brief Exchanges the contents of this triple with another.
         *
         * Swaps the values of the three members (first, second, third) with the corresponding
         * members of @p other by calling std::swap on each member in that order.
         *
         * @param other Reference to the triple whose contents will be exchanged with this object.
         *
         * @note This member function is declared constexpr and noexcept. It can be evaluated in
         *       a constant expression if std::swap for the element types is constexpr.
         *       Because the function is unconditionally noexcept, if any std::swap invocation
         *       would throw, std::terminate will be invoked.
         *
         * @complexity Performs exactly three calls to std::swap; overall complexity is the sum
         *             of the complexities of those three calls.
         *
         * @requirements T1, T2 and T3 must be Swappable (std::swap must be valid for each).
         */
        constexpr void swap(triple_t3<T1, T2, T3> &other) noexcept
        {
            std::swap(first, other.first);
            std::swap(second, other.second);
            std::swap(third, other.third);
        }

        /**
         * @brief Copy-assignment operator for triple_t3.
         *
         * Performs a memberwise copy assignment of the three elements (first, second, third).
         * A self-assignment check is performed to avoid unnecessary work. The function is
         * declared noexcept and returns a reference to the assigned object.
         *
         * @param other The triple to copy from.
         * @return Reference to this object after assignment.
         *
         * @pre The element types T1, T2 and T3 must be copy-assignable.
         * @exception This function is noexcept; if any element's assignment throws, std::terminate may be called.
         * @complexity Constant time (subject to the complexity of each element's assignment).
         */
        constexpr triple_t3 &operator=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            if (this != &other)
            {
                first = other.first;
                second = other.second;
                third = other.third;
            }
            return *this;
        }

        /// @brief Equality comparison operator for triple_t3.
        /// @param other the other triple to compare with.
        /// @return true if the triples are equal, false otherwise.
        constexpr bool operator==(const triple_t3<T1, T2, T3> &other) const noexcept { return first == other.first && second == other.second && third == other.third; }

        /// @brief Inequality comparison operator for triple_t3.
        /// @param other the other triple to compare with.
        /// @return true if the triples are not equal, false otherwise.
        constexpr bool operator!=(const triple_t3<T1, T2, T3> &other) const noexcept { return !(*this == other); }

        /// @brief Adds a value to the corresponding element.
        /// @param value sum value to add.
        constexpr void operator+=(const T1 &value) noexcept { first += value; }

        /// @brief Adds a value to the corresponding element.
        /// @param value sum value to add.
        constexpr void operator+=(const T2 &value) noexcept { second += value; }

        /// @brief Adds a value to the corresponding element.
        /// @param value sum value to add.
        constexpr void operator+=(const T3 &value) noexcept { third += value; }

        /**
         * Adds the elements of another triple to this triple, performing element-wise addition.
         *
         * This member function updates this->first by adding other.first, this->second by adding other.second,
         * and this->third by adding other.third using their respective operator+= implementations.
         *
         * Requirements:
         * - T1, T2, and T3 must support operator+=(const T&) (or a compatible overload) with the corresponding
         *   types stored in the provided other triple.
         * - For this function to be noexcept, each of the individual operator+= calls must be noexcept.
         *
         * Parameters:
         * @param other  The triple whose elements are added to this triple (passed by const reference).
         *
         * Effects:
         * - Modifies this object by performing element-wise addition with other.
         *
         * Return value:
         * - void
         *
         * Complexity:
         * - Constant time.
         *
         * Notes:
         * - constexpr-qualified: may be evaluated at compile time when operands are constexpr.
         * - Exception-safety: marked noexcept; actual noexcept-ness depends on the noexcept-specifications of the
         *   underlying operator+= implementations for T1, T2, and T3.
         */
        constexpr void operator+=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first += other.first;
            second += other.second;
            third += other.third;
        }

        /**
         * @brief Prefix increment operator that increments all three members.
         *
         * Invokes the prefix ++ operator on the members `first`, `second`, and `third`
         * in that order. The operation is performed in place and does not return a value.
         *
         * Requirements:
         * - The types of `first`, `second`, and `third` must support prefix ++.
         * - If evaluated in a constant expression, the member types' ++ must also be constexpr.
         *
         * Attributes:
         * - constexpr: Can be used in compile-time contexts when the member increments are constexpr.
         * - noexcept: Guaranteed not to throw.
         *
         * Complexity: Constant time.
         *
         * Example:
         * @code
         * // Given an object obj with integer-like members:
         * // obj.first == 1, obj.second == 2, obj.third == 3
         * ++obj; // obj.first == 2, obj.second == 3, obj.third == 4
         * @endcode
         */
        constexpr void operator++() noexcept
        {
            first++;
            second++;
            third++;
        }

        /// @brief Subtracts a value from the corresponding element.
        /// @param value the value to subtract.
        constexpr void operator-=(const T1 &value) noexcept { first -= value; }

        /// @brief Subtracts a value from the corresponding element.
        /// @param value the value to subtract.
        constexpr void operator-=(const T2 &value) noexcept { second -= value; }

        /// @brief Subtracts a value from the corresponding element.
        /// @param value the value to subtract.
        constexpr void operator-=(const T3 &value) noexcept { third -= value; }

        /// @brief Subtracts the elements of another triple from this triple.
        /// @param other the triple whose elements are to be subtracted.
        constexpr void operator-=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first -= other.first;
            second -= other.second;
            third -= other.third;
        }

        /**
         * @brief Pre-decrement operator that decrements all three elements.
         *
         * Performs a pre-decrement on each member in order: first, second, then third,
         * by invoking their respective pre-decrement operator (--).
         *
         * This function is constexpr and declared noexcept.
         *
         * Requirements:
         * - The types of first, second, and third must support pre-decrement.
         *
         * Complexity: Constant time.
         */
        constexpr void operator--() noexcept
        {
            first--;
            second--;
            third--;
        }

        /// @brief Multiplies the corresponding element by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T1 &value) noexcept { first *= value; }

        /// @brief Multiplies the corresponding element by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T2 &value) noexcept { second *= value; }

        /// @brief Multiplies the corresponding element by a value.
        /// @param value The value to multiply by.
        constexpr void operator*=(const T3 &value) noexcept { third *= value; }

        /// @brief Multiplies the corresponding element by the elements of another triple.
        /// @param other The triple whose elements are to be multiplied.
        constexpr void operator*=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first *= other.first;
            second *= other.second;
            third *= other.third;
        }

        /// @brief Divides the corresponding element by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T1 &value) noexcept { first /= value; }

        /// @brief Divides the corresponding element by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T2 &value) noexcept { second /= value; }

        /// @brief Divides the corresponding element by a value.
        /// @param value The value to divide by.
        constexpr void operator/=(const T3 &value) noexcept { third /= value; }

        /// @brief Divides the corresponding element by the elements of another triple.
        /// @param other The triple whose elements are to be divided.
        constexpr void operator/=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first /= other.first;
            second /= other.second;
            third /= other.third;
        }

        /// @brief Raises the corresponding element to the power of a value.
        /// @param value The exponent value.
        constexpr void operator^=(const T1 &value) noexcept { first = std::pow(first, value); }

        /// @brief Raises the corresponding element to the power of a value.
        /// @param value The exponent value.
        constexpr void operator^=(const T2 &value) noexcept { second = std::pow(second, value); }

        /// @brief Raises the corresponding element to the power of a value.
        /// @param value The exponent value.
        constexpr void operator^=(const T3 &value) noexcept { third = std::pow(third, value); }

        /// @brief Raises the elements to the powers of the elements of another triple.
        /// @param other The triple whose elements are the exponents.
        constexpr void operator^=(const triple_t3<T1, T2, T3> &other) noexcept
        {
            first = std::pow(first, other.first);
            second = std::pow(second, other.second);
            third = std::pow(third, other.third);
        }
    };
}

#endif // OPENUDT___UDT_TRIPLE_HPP