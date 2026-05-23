#include <memory>
#include <ostream>
#include <cmath>

#pragma once
#ifndef OPENUDT___UDT_DYNAMIC__DYANMIC_U__HPP
#define OPENUDT___UDT_DYNAMIC__DYANMIC_U__HPP

namespace udt
{
    /**
     * @class dynamic_u
     * @brief Dynamic type holder with unique pointer semantics for owned value storage.
     *
     * @details This class provides a unique-ownership variant of the dynamic type family.
     * Values are stored as std::unique_ptr<T>, meaning this object maintains exclusive
     * ownership of any allocated values. This is useful for managing dynamically allocated
     * primitive type values with automatic cleanup and move semantics.
     *
     * Storage Model:
     * - std::unique_ptr<bool> d_bool: nullable boolean pointer
     * - std::unique_ptr<int> d_int: nullable integer pointer
     * - std::unique_ptr<char> d_char: nullable character pointer
     * - std::unique_ptr<float> d_float: nullable float pointer
     * - std::unique_ptr<double> d_double: nullable double pointer
     * - bool complextype: flag indicating complex multi-value mode
     *
     * Unique Features:
     * - Automatic memory management with RAII semantics
     * - Support for complex mode storing multiple types simultaneously
     * - Move-only semantics (no copy constructor by default)
     * - Nullable values (nullptr indicates value is not set)
     *
     * Usage Patterns:
     * 1. Simple mode: Store a single value of one type
     * 2. Complex mode: Store multiple values of different types simultaneously
     *
     * @warning This class uses manual dynamic allocation via std::make_unique.
     * Objects cannot be copied; they must be moved.
     *
     * @note All pointer members start as nullptr and must be explicitly initialized.
     * @note Call complex() to enable multi-value storage mode.
     * @note Not thread-safe. External synchronization required for concurrent access.
     *
     * @see dynamic - Type-discriminated variant
     * @see dynamic_r - Raw pointer variant (non-owning)
     * @see dynamic_t - All-types-at-once variant
     */
    class dynamic_u
    {
    private:
        /// @brief Pointer to boolean value (nullptr if not set)
        std::unique_ptr<bool> d_bool = nullptr;
        /// @brief Pointer to integer value (nullptr if not set)
        std::unique_ptr<int> d_int = nullptr;
        /// @brief Pointer to character value (nullptr if not set)
        std::unique_ptr<char> d_char = nullptr;
        /// @brief Pointer to float value (nullptr if not set)
        std::unique_ptr<float> d_float = nullptr;
        /// @brief Pointer to double value (nullptr if not set)
        std::unique_ptr<double> d_double = nullptr;
        /// @brief Flag indicating if object is in complex (multi-value) mode
        bool complextype = false;

    public:
        /**
         * @brief Default constructor - creates empty dynamic_u.
         *
         * Initializes a new dynamic_u with all smart pointers set to nullptr
         * and complextype set to false. The object is ready to accept values.
         *
         * @note This is a defaulted constructor with implicit generation by the compiler
         */
        dynamic_u() = default;

        /**
         * @brief Move constructor - transfers ownership from another dynamic_u.
         *
         * Implements move semantics for dynamic_u, allowing efficient transfer
         * of ownership from a temporary or explicitly moved source. The moved-from
         * object is left in a valid but unspecified state.
         *
         * @note This is a defaulted move constructor
         */
        // Move Constructor
        dynamic_u(dynamic_u &&) = default;
        /**
         * @brief Constructs a dynamic_u and initializes its contained scalar values.
         *
         * Initializes the object's internal complex representation and then assigns the
         * provided values to the integer, float, double, and character members.
         *
         * @param intval Initial value for the integer member.
         * @param fval   Initial value for the float member.
         * @param dval   Initial value for the double member.
         * @param cval   Initial value for the char member.
         *
         * Notes:
         * - This constructor prepares any required internal state prior to performing
         *   the member assignments.
         */
        dynamic_u(int intval, float fval, double dval, char cval)
        {
            complex();
            set_int(intval);
            set_float(fval);
            set_double(dval);
            set_char(cval);
        }
        /// @brief Constructs a dynamic_u with an integer value.
        /// @param val The integer value to initialize the dynamic_u.
        dynamic_u(int val) noexcept { d_int = std::make_unique<int>(val); }
        /// @brief Constructs a dynamic_u with a char value.
        /// @param val The char value to initialize the dynamic_u.
        dynamic_u(char val) noexcept { d_char = std::make_unique<char>(val); }
        /// @brief Constructs a dynamic_u with a float or double value.
        /// @param val The float value to initialize the dynamic_u.
        dynamic_u(float val) noexcept { d_float = std::make_unique<float>(val); }
        /// @brief Constructs a dynamic_u with a double value.
        /// @param val The double value to initialize the dynamic_u.
        dynamic_u(double val) noexcept { d_double = std::make_unique<double>(val); }
        /// @brief Constructs a dynamic_u with a boolean value.
        /// @param val The boolean value to initialize the dynamic_u.
        dynamic_u(bool val) { d_bool = std::make_unique<bool>(val); }
        /**
         * @brief Copy constructor for dynamic_u class
         *
         * Performs a deep copy of another dynamic_u object by copying all its pointer-managed values
         * and the complex type indicator. Only copies values that are actually present (non-null) in
         * the source object.
         *
         * @param other The source dynamic_u object to copy from
         *
         * @details Copies the following members if they exist in the source object:
         *          - Integer value (d_int)
         *          - Character value (d_char)
         *          - Float value (d_float)
         *          - Double value (d_double)
         *          - Boolean value (d_bool)
         *          - Complex type indicator (complextype)
         */
        dynamic_u(const dynamic_u &other)
        {
            if (other.d_int)
                d_int = std::make_unique<int>(*other.d_int);
            if (other.d_char)
                d_char = std::make_unique<char>(*other.d_char);
            if (other.d_float)
                d_float = std::make_unique<float>(*other.d_float);
            if (other.d_double)
                d_double = std::make_unique<double>(*other.d_double);
            if (other.d_bool)
                d_bool = std::make_unique<bool>(*other.d_bool);
            complextype = other.complextype;
        }
        /// @brief Sets the dynamic_u to complex type mode.
        constexpr void complex() noexcept { complextype = true; }
        /**
         * @brief Sets the dynamic_u to simple type mode by removing specified types.
         *
         * This function switches the object from complex type mode to simple type mode
         * by removing the specified data types. At least four types must be removed
         * to ensure that only one type remains.
         *
         * @param reint    If true, removes the integer type.
         * @param rechar   If true, removes the char type.
         * @param refloat  If true, removes the float type.
         * @param redouble If true, removes the double type.
         * @param rebool   If true, removes the boolean type.
         *
         * @throws std::invalid_argument if fewer than four types are removed.
         */
        void uncomplex(bool reint = true,
                       bool rechar = true,
                       bool refloat = true,
                       bool redouble = true,
                       bool rebool = true)
        {
            int boolcheck = reint + refloat + rechar + redouble + rebool;
            if (boolcheck < 4)
                throw std::invalid_argument("to many data to hold for the uncomplex type");
            complextype = false;
            if (d_int != nullptr && reint)
                d_int = nullptr;
            if (d_float != nullptr && refloat)
                d_float = nullptr;
            if (d_double != nullptr && redouble)
                d_double = nullptr;
            if (d_char != nullptr && rechar)
                d_char = nullptr;
            if (d_bool != nullptr && rebool)
                d_bool = nullptr;
        }
        /**
         * @brief Sets the boolean value of the data type
         *
         * @param val The boolean value to set
         * @throws std::invalid_argument If the type is not complex and changes are not allowed
         *
         * Sets the internal boolean value if either:
         * - Changes are allowed for the given value
         * - The type is marked as complex
         */
        void set_bool(bool val)
        {
            if (change_allowed(val) || complextype)
                d_bool = std::make_unique<bool>(val);
            throw std::invalid_argument("not complextype nor allowed changes");
        }
        /**
         * @brief Sets the integer value of the data type
         * @param val The integer value to set
         * @throws std::invalid_argument If the type is not complex and changes are not allowed
         */
        void set_int(int val)
        {
            if (change_allowed(val) || complextype)
                d_int = std::make_unique<int>(val);
            else
                throw std::invalid_argument("Change not allowed");
        }
        /**
         * @brief Sets the character value stored in the data member
         *
         * @param val The character value to be set
         * @throws std::invalid_argument if the change is not allowed and complextype is false
         *
         * This method attempts to set the internal character value. The change is permitted
         * if either change_allowed() returns true or if complextype is true.
         * If neither condition is met, an exception is thrown.
         */
        void set_char(char val)
        {
            if (change_allowed(val) || complextype)
                d_char = std::make_unique<char>(val);
            else
                throw std::invalid_argument("Change not allowed");
        }
        /**
         * Set the stored floating-point value.
         *
         * Attempts to store the given value in the object's internal floating-point
         * storage. If change_allowed(val) returns true or the complextype flag is set,
         * the function allocates a new float (via std::make_unique<float>) and replaces
         * the previous stored value. If neither condition holds, the function throws
         * std::invalid_argument("Change not allowed").
         *
         * @param val The floating-point value to assign.
         *
         * @throws std::invalid_argument if change_allowed(val) is false and complextype
         *         is false.
         * @throws std::bad_alloc if allocation for the new float fails.
         *
         * Postconditions:
         * - On success, d_float points to a new float holding val (previous value is
         *   replaced).
         * - On failure (exception), the previous state is unchanged.
         *
         * Notes:
         * - Behavior depends on the semantics of change_allowed(float) and the
         *   complextype flag.
         * - Not guaranteed to be thread-safe; concurrent access to the object may
         *   require external synchronization.
         */
        void set_float(float val)
        {
            if (change_allowed(val) || complextype)
                d_float = std::make_unique<float>(val);
            else
                throw std::invalid_argument("Change not allowed");
        }
        /**
         * @brief Sets the value of the double field
         *
         * @param val The double value to be set
         * @throws std::invalid_argument if the change is not allowed and complextype is false
         *
         * Sets the internal double value if either:
         * - The change is allowed based on change_allowed() check
         * - The complextype flag is true
         */
        void set_double(double val)
        {
            if (change_allowed(val) || complextype)
                d_double = std::make_unique<double>(val);
            else
                throw std::invalid_argument("Change not allowed");
        }
        /// @brief Sets the value of the boolean field
        /// @param val The boolean value to be set
        void set_value(bool val) { set_bool(val); }
        /// @brief Sets the value of the integer field
        /// @param val The integer value to be set
        void set_value(int val) { set_int(val); }
        /// @brief Sets the value of the float or double field
        /// @param val The float value to be set
        void set_value(float val) { set_float(val); }
        /// @brief Sets the value of the double field
        /// @param val The double value to be set
        void set_value(double val) { set_double(val); }
        /// @brief Sets the value of the character field
        /// @param val The character value to be set
        void set_value(char val) { set_char(val); }
        /**
         * @brief Retrieves the boolean value stored in the data structure
         * @return Boolean value stored in d_bool
         * @throws std::invalid_argument if d_bool is null and complextype is true
         * @throws std::invalid_argument if the stored value is not of boolean type
         */
        bool get_bool() const
        {
            if (d_bool != nullptr)
                return *d_bool;
            else if (complextype && d_bool == nullptr)
                throw std::invalid_argument("no set declaration for d_bool");
            else
                throw std::invalid_argument("Getting not allowed: the value is not boolean");
        }
        /**
         * @brief Retrieve the stored integer value.
         *
         * Returns the integer value referenced by d_int.
         *
         * Behavior:
         * - If d_int != nullptr: returns *d_int.
         * - If complextype is true and d_int == nullptr: throws std::invalid_argument("no set declaration for d_int").
         * - Otherwise: throws std::invalid_argument("Getting not allowed: the value is not integer").
         *
         * @return int The integer value stored in this object.
         * @throws std::invalid_argument If no integer value is available or retrieving is not allowed.
         * @note This member function is const and does not modify object state.
         */
        int get_int() const
        {
            if (d_int != nullptr)
                return *d_int;
            else if (complextype && d_int == nullptr)
                throw std::invalid_argument("no set declaration for d_int");
            else
                throw std::invalid_argument("Getting not allowed: the value is not integer");
            return 0;
        }
        /**
         * Retrieve the stored character value.
         *
         * If a character has been set (d_char != nullptr), returns the character referred to by d_char.
         *
         * @return The character stored in this object.
         *
         * @throws std::invalid_argument if no character is available:
         *         - If complextype is true and d_char is nullptr, throws with message "no set declaration for d_char".
         *         - Otherwise, when the value is not a character (d_char == nullptr), throws with message "Getting not allowed: the value is not character".
         *
         * @note This method is const-qualified and expects d_char to point to a valid character when present.
         */
        char get_char() const
        {
            if (d_char != nullptr)
                return *d_char;
            else if (complextype && d_char == nullptr)
                throw std::invalid_argument("no set declaration for d_char");
            else
                throw std::invalid_argument("Getting not allowed: the value is not character");
            throw std::runtime_error("");
        }
        /**
         * @brief Retrieves the stored float value
         * @return float The stored float value
         * @throws std::invalid_argument If attempting to access float when value is not float type
         * @throws std::invalid_argument If complex type is set but float value is not declared
         */
        float get_float() const
        {
            if (d_float != nullptr)
                return *d_float;
            else if (complextype && d_float != nullptr)
                throw std::invalid_argument("no set declaration for d_float");
            else
                throw std::invalid_argument("Getting not allowed: the value is not float");
            return 0;
        }
        /**
         * @brief Retrieve the stored double value.
         *
         * Returns the value pointed to by the internal pointer d_double.
         *
         * Behavior:
         * - If d_double is non-null, returns *d_double.
         * - If d_double is null and complextype is true, throws std::invalid_argument
         *   indicating that there is "no set declaration for d_double".
         * - If d_double is null and complextype is false, throws std::invalid_argument
         *   indicating that getting is not allowed because the value is not a double.
         *
         * @throws std::invalid_argument If the value is not present or retrieval is not allowed.
         * @return double The stored double value.
         * @note This function is const and does not modify object state.
         */
        double get_double() const
        {
            if (d_double != nullptr)
                return *d_double;
            else if (complextype && d_double == nullptr)
                throw std::invalid_argument("no set declaration for d_double");
            else
                throw std::invalid_argument("Getting not allowed: the value is not double");
            return 0;
        }
        /**
         * @brief Retrieves the stored value as a dynamic_u type
         * @throws std::invalid_argument If the stored value is a complex type
         * @throws std::runtime_error If no value has been set
         * @return dynamic_u The stored value converted to dynamic_u type
         *
         * This method returns the internally stored value as a dynamic_u type.
         * It checks various internal pointers (d_int, d_char, d_float, d_double, d_bool)
         * and returns the first non-null value found. If the value is a complex type
         * or if no value has been set, appropriate exceptions are thrown.
         */
        dynamic_u get_value() const
        {
            if (complextype)
                throw std::invalid_argument("complex type don't return specific standard data type automatically");
            if (d_int != nullptr)
                return dynamic_u(*d_int);
            else if (d_char != nullptr)
                return dynamic_u(*d_char);
            else if (d_float != nullptr)
                return dynamic_u(*d_float);
            else if (d_double != nullptr)
                return dynamic_u(*d_double);
            else if (d_bool != nullptr)
                return dynamic_u(*d_bool);
            throw std::runtime_error("no value set");
        }
        /// @brief Checks if the stored value is of complex type.
        /// @return True if the value is complex, false otherwise.
        constexpr bool is_complex() const noexcept { return complextype; }
        /// @brief Checks if the stored value is empty.
        /// @return True if the value is empty, false otherwise.
        bool empty() const noexcept
        {
            return d_int == nullptr &&
                   d_char == nullptr &&
                   d_float == nullptr &&
                   d_double == nullptr &&
                   d_bool == nullptr;
        }
        /// @brief Clears all stored values.
        void clear_all() noexcept
        {
            d_int = nullptr;
            d_char = nullptr;
            d_float = nullptr;
            d_double = nullptr;
            d_bool = nullptr;
        }
        /// @brief Clears the boolean value.
        void clear_bool() noexcept
        {
            if ((!change_allowed() || complextype) && d_bool != nullptr)
                d_bool = nullptr;
        }
        /// @brief Clears the integer value.
        void clear_int() noexcept
        {
            if ((!change_allowed() || complextype) && d_int != nullptr)
                d_int = nullptr;
        }
        /// @brief Clears the float value.
        void clear_float() noexcept
        {
            if ((!change_allowed() || complextype) && d_float != nullptr)
                d_float = nullptr;
        }
        /// @brief Clears the double value.
        void clear_double() noexcept
        {
            if ((!change_allowed() || complextype) && d_double != nullptr)
                d_double = nullptr;
        }
        /// @brief Clears the character value.
        void clear_char() noexcept
        {
            if ((!change_allowed() || complextype) && d_char != nullptr)
                d_char = nullptr;
        }
        /// @brief Checks if the stored value is a boolean.
        /// @return True if the value is boolean, false otherwise.
        bool has_bool() const noexcept
        {
            if (d_bool != nullptr)
                return true;
            return false;
        }
        /// @brief Checks if the stored value is an integer.
        /// @return True if the value is integer, false otherwise.
        bool has_int() const noexcept
        {
            if (d_int != nullptr)
                return true;
            return false;
        }
        /// @brief Checks if the stored value is a float.
        /// @return True if the value is float, false otherwise.
        bool has_float() const noexcept
        {
            if (d_float != nullptr)
                return true;
            return false;
        }
        /// @brief Checks if the stored value is a double.
        /// @return True if the value is double, false otherwise.
        bool has_double() const noexcept
        {
            if (d_double != nullptr)
                return true;
            return false;
        }
        /// @brief Checks if the stored value is a character.
        /// @return True if the value is char, false otherwise.
        bool has_char() const noexcept
        {
            if (d_char != nullptr)
                return true;
            return false;
        }
        /**
         * @brief Checks if a specific data type exists in the container
         * @param type String representation of the data type to check for
         * @return true if the specified type exists, false otherwise
         *
         * Supported type strings:
         * - "int"     - Checks for integer type
         * - "float"   - Checks for float type
         * - "double"  - Checks for double type
         * - "char"    - Checks for character type
         * - "boolean" - Checks for boolean type
         */
        bool has(const std::string &type) const
        {
            if (type == "int")
                return has_int();
            if (type == "float")
                return has_float();
            if (type == "double")
                return has_double();
            if (type == "char")
                return has_char();
            if (type == "boolean")
                return has_bool();
            return false;
        }
        /**
         * @brief Checks if a given value has the same type as the current dynamic object
         *
         * @tparam T The type parameter for the input value
         * @param value Reference to the value being compared
         * @return true If the type of the input value matches the current object's type
         * @return false If the types do not match
         *
         * This template method converts the input value to a dynamic_u object and compares
         * its type with the current object's type using the type() method.
         */
        template <typename T>
        bool same_type(T &value)
        {
            dynamic_u d = value;
            if (d.type() == type())
                return true;
            return false;
        }
        /// @brief Checks if the current dynamic object can change its type
        /// @return True if the type can be changed, false otherwise
        bool change_allowed()
        {
            if (is_complex())
                return true;
            return !(has_int() || has_float() || has_double() || has_char() || has_bool());
        }
        /// @brief Checks if the current dynamic object can change its type based on the input value
        /// @return True if the type can be changed, false otherwise
        template <typename T>
        bool change_allowed(T &value)
        {
            if (is_complex())
                return true;
            if (same_type(value))
                return true;
            return !(has_int() || has_float() || has_double() || has_char() || has_bool());
        }
        /**
         * @brief Returns the type of the stored value as a string.
         * @return A string representing the type of the stored value.
         * If the type is complex, returns "complex".
         */
        std::string type() const noexcept
        {
            if (complextype)
                return "complex";
            if (d_int != nullptr)
                return "int";
            if (d_float != nullptr)
                return "float";
            if (d_double != nullptr)
                return "double";
            if (d_char != nullptr)
                return "char";
            if (d_bool != nullptr)
                return "boolean";
            return "undefined";
        }
        /**
         * @brief Checks if the stored value is purely numeric (int, float, double)
         * @return True if the value is purely numeric, false otherwise.
         * A purely numeric value means it does not contain char or bool types.
         */
        bool is_pure_numeric()
        {
            if (complextype)
            {
                if (d_char == nullptr && d_bool == nullptr && (d_int != nullptr || d_float != nullptr || d_double != nullptr))
                    return true;
                else
                    return false;
            }
            else
            {
                if (d_char == nullptr && d_bool == nullptr)
                    return true;
                else
                    return false;
            }
            throw std::runtime_error("the function run beyond expected");
        }
        /**
         * @brief Overloads the stream insertion operator for dynamic_u
         * @param os The output stream
         * @param d The dynamic_u object to be printed
         * @return The output stream with the dynamic_u representation
         * This operator prints the contents of the dynamic_u object.
         * If the object is of complex type, it prints all non-null members in a structured format.
         * If the object is of simple type, it prints the single stored value.
         */
        friend std::ostream &operator<<(std::ostream &os, const dynamic_u &d)
        {
            if (d.complextype)
            {
                bool printed = false;
                os << "{ ";
                if (d.d_int != nullptr)
                {
                    os << "int: " << *d.d_int;
                    printed = true;
                }
                if (d.d_float != nullptr)
                {
                    if (printed)
                        os << ", ";
                    os << "float: " << *d.d_float;
                    printed = true;
                }
                if (d.d_double != nullptr)
                {
                    if (printed)
                        os << ", ";
                    os << "double: " << *d.d_double;
                    printed = true;
                }
                if (d.d_char)
                {
                    if (printed)
                        os << ", ";
                    os << "char: '" << *d.d_char << "'";
                }
                if (d.d_bool)
                {
                    if (printed)
                        os << ", ";
                    os << "bool: '" << *d.d_bool << "'";
                }
                os << " }";
                return os;
            }
            else if (d.d_int != nullptr)
                return os << *d.d_int;
            else if (d.d_float != nullptr)
                return os << *d.d_float;
            else if (d.d_double != nullptr)
                return os << *d.d_double;
            else if (d.d_char != nullptr)
                return os << *d.d_char;
            else if (d.d_bool != nullptr)
                return os << *d.d_bool;
            else
                return os << "[undefined dynamic]";
        }
        // Move Assignment Operator
        dynamic_u &operator=(dynamic_u &&) = default;
        /**
         * @brief Assignment operator for integer values
         * @param val The integer value to assign
         * @throws std::invalid_argument if the type is not complex and changes are not allowed
         * This operator assigns an integer value to the dynamic_u object.
         * If the object is in complex mode or if changing to this type is allowed,
         * it sets the internal integer pointer to the new value.
         * Otherwise, it throws an exception.
         */
        void operator=(int val)
        {
            if (change_allowed(val) || complextype)
                d_int = std::make_unique<int>(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }
        /**
         * @brief Assignment operator for float values
         * @param val The float value to assign
         * @throws std::invalid_argument if the type is not complex and changes are not allowed
         * This operator assigns a float value to the dynamic_u object.
         * If the object is in complex mode or if changing to this type is allowed,
         * it sets the internal float pointer to the new value.
         * Otherwise, it throws an exception.
         */
        void operator=(float val)
        {
            if (change_allowed(val) || complextype)
                d_float = std::make_unique<float>(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }
        /**
         * @brief Assignment operator for double values
         * @param val The double value to assign
         * @throws std::invalid_argument if the type is not complex and changes are not allowed
         * This operator assigns a double value to the dynamic_u object.
         * If the object is in complex mode or if changing to this type is allowed,
         * it sets the internal double pointer to the new value.
         * Otherwise, it throws an exception.
         */
        void operator=(double val)
        {
            if (change_allowed(val) || complextype)
                d_double = std::make_unique<double>(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }
        /**
         * @brief Assignment operator for char values
         * @param val The char value to assign
         * @throws std::invalid_argument if the type is not complex and changes are not allowed
         * This operator assigns a char value to the dynamic_u object.
         * If the object is in complex mode or if changing to this type is allowed,
         * it sets the internal char pointer to the new value.
         * Otherwise, it throws an exception.
         */
        void operator=(char val)
        {
            if (change_allowed(val) || complextype)
                d_char = std::make_unique<char>(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }
        /**
         * @brief Assignment operator for boolean values
         * @param val The boolean value to assign
         * @throws std::invalid_argument if the type is not complex and changes are not allowed
         * This operator assigns a boolean value to the dynamic_u object.
         * If the object is in complex mode or if changing to this type is allowed,
         * it sets the internal boolean pointer to the new value.
         * Otherwise, it throws an exception.
         */
        void operator=(bool val)
        {
            if (change_allowed(val) || complextype)
                d_bool = std::make_unique<bool>(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }
        /**
         * @brief Copy assignment operator for dynamic_u class
         * @param other The source dynamic_u object to copy from
         * @return Reference to the assigned dynamic_u object
         * @details Performs a deep copy of another dynamic_u object by copying all its pointer-managed values
         * and the complex type indicator. Only copies values that are actually present (non-null) in
         * the source object.
         */
        dynamic_u &operator=(const dynamic_u &other)
        {
            if (this != &other)
            {
                clear_all();
                if (other.d_int)
                    d_int = std::make_unique<int>(*other.d_int);
                if (other.d_char)
                    d_char = std::make_unique<char>(*other.d_char);
                if (other.d_float)
                    d_float = std::make_unique<float>(*other.d_float);
                if (other.d_double)
                    d_double = std::make_unique<double>(*other.d_double);
                if (other.d_bool)
                    d_bool = std::make_unique<bool>(*other.d_bool);
                complextype = other.complextype;
            }
            return *this;
        }
        /**
         * @brief Equality operator for dynamic_u class
         * @param other The other dynamic_u object to compare with
         * @return true if both dynamic_u objects are equal, false otherwise
         * @details Compares two dynamic_u objects for equality by checking their complex type indicators
         * and the values of their pointer-managed members. Two dynamic_u objects are considered equal
         * if they have the same complex type status and all corresponding non-null members are equal.
         * If one member is null in one object and non-null in the other, they are considered not equal.
         */
        bool operator==(const dynamic_u &other) const noexcept
        {
            if (complextype != other.complextype)
                return false;
            if (d_int != nullptr && other.d_int != nullptr)
            {
                if (*d_int != *other.d_int)
                    return false;
            }
            else if (d_int != nullptr || other.d_int != nullptr)
                return false;
            if (d_float != nullptr && other.d_float != nullptr)
            {
                if (*d_float != *other.d_float)
                    return false;
            }
            else if (d_float != nullptr || other.d_float != nullptr)
                return false;
            if (d_double != nullptr && other.d_double != nullptr)
            {
                if (*d_double != *other.d_double)
                    return false;
            }
            else if (d_double != nullptr || other.d_double != nullptr)
                return false;
            if (d_char != nullptr && other.d_char != nullptr)
            {
                if (*d_char != *other.d_char)
                    return false;
            }
            else if (d_char != nullptr || other.d_char != nullptr)
                return false;
            if (d_bool != nullptr && other.d_bool != nullptr)
            {
                if (*d_bool != *other.d_bool)
                    return false;
            }
            else if (d_bool != nullptr || other.d_bool != nullptr)
                return false;
            return true;
        }
        /**
         * @brief Inequality operator for dynamic_u class
         * @param other The other dynamic_u object to compare with
         * @return true if both dynamic_u objects are not equal, false otherwise
         * @details Compares two dynamic_u objects for inequality by checking their complex type indicators
         * and the values of their pointer-managed members. Two dynamic_u objects are considered not equal
         * if they have different complex type status or any corresponding non-null members are not equal.
         * If one member is null in one object and non-null in the other, they are considered not equal.
         */
        bool operator!=(const dynamic_u &other) const noexcept
        {
            if (complextype != other.complextype)
                return true;
            if (d_int != nullptr && other.d_int != nullptr)
            {
                if (*d_int != *other.d_int)
                    return true;
            }
            else if (d_int != nullptr || other.d_int != nullptr)
                return true;
            if (d_float != nullptr && other.d_float != nullptr)
            {
                if (*d_float != *other.d_float)
                    return true;
            }
            else if (d_float != nullptr || other.d_float != nullptr)
                return true;
            if (d_double != nullptr && other.d_double != nullptr)
            {
                if (*d_double != *other.d_double)
                    return true;
            }
            else if (d_double != nullptr || other.d_double != nullptr)
                return true;
            if (d_char != nullptr && other.d_char != nullptr)
            {
                if (*d_char != *other.d_char)
                    return true;
            }
            else if (d_char != nullptr || other.d_char != nullptr)
                return true;
            if (d_bool != nullptr && other.d_bool != nullptr)
            {
                if (*d_bool != *other.d_bool)
                    return true;
            }
            else if (d_bool != nullptr || other.d_bool != nullptr)
                return true;
            return false;
        }
        /**
         * @brief Equality operator for comparing with primitive types
         * @param val The primitive value to compare with
         * @return true if the stored value equals the primitive value, false otherwise
         * @details Compares the stored value in the dynamic_u object with a primitive type value.
         * Returns true if the stored value matches the primitive value for the corresponding type.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator==(int val) const noexcept
        {
            if (d_int != nullptr && val == *d_int)
                return true;
            return false;
        }
        /**
         * @brief Inequality operator for comparing with primitive types
         * @param val The primitive value to compare with
         * @return true if the stored value does not equal the primitive value, false otherwise
         * @details Compares the stored value in the dynamic_u object with a primitive type value.
         * Returns true if the stored value does not match the primitive value for the corresponding type.
         * If the stored value is null or of a different type, returns true.
         */
        bool operator!=(int val) const noexcept
        {
            if (d_int != nullptr && val == *d_int)
                return false;
            return true;
        }
        /**
         * @brief Equality operator for comparing with float values
         * @param val The float value to compare with
         * @return true if the stored float value equals the given value, false otherwise
         * @details Compares the stored float value in the dynamic_u object with a given float value.
         * Returns true if they are equal, false otherwise.
         */
        bool operator==(float val) const noexcept
        {
            if (d_float != nullptr && val == *d_float)
                return true;
            return false;
        }
        /**
         * @brief Inequality operator for comparing with float values
         * @param val The float value to compare with
         * @return true if the stored float value does not equal the given value, false otherwise
         * @details Compares the stored float value in the dynamic_u object with a given float value.
         * Returns true if they are not equal, false otherwise.
         * If the stored value is null or of a different type, returns true.
         */
        bool operator!=(float val) const noexcept
        {
            if (d_float != nullptr && val == *d_float)
                return false;
            return true;
        }
        /**
         * @brief Equality operator for comparing with double values
         * @param val The double value to compare with
         * @return true if the stored double value equals the given value, false otherwise
         * @details Compares the stored double value in the dynamic_u object with a given double value.
         * Returns true if they are equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator==(double val) const noexcept
        {
            if (d_double != nullptr && val == *d_double)
                return true;
            return false;
        }
        /**
         * @brief Inequality operator for comparing with double values
         * @param val The double value to compare with
         * @return true if the stored double value does not equal the given value, false otherwise
         * @details Compares the stored double value in the dynamic_u object with a given double value.
         * Returns true if they are not equal, false otherwise.
         * If the stored value is null or of a different type, returns true.
         */
        bool operator!=(double val) const noexcept
        {
            if (d_double != nullptr && val == *d_double)
                return false;
            return true;
        }
        /**
         * @brief Equality operator for comparing with char values
         * @param val The char value to compare with
         * @return true if the stored char value equals the given value, false otherwise
         * @details Compares the stored char value in the dynamic_u object with a given char value.
         * Returns true if they are equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator==(char val) const noexcept
        {
            if (d_char != nullptr && val == *d_char)
                return true;
            return false;
        }
        /**
         * @brief Inequality operator for comparing with char values
         * @param val The char value to compare with
         * @return true if the stored char value does not equal the given value, false otherwise
         * @details Compares the stored char value in the dynamic_u object with a given char value.
         * Returns true if they are not equal, false otherwise.
         * If the stored value is null or of a different type, returns true.
         */
        bool operator!=(char val) const noexcept
        {
            if (d_char != nullptr && val == *d_char)
                return false;
            return true;
        }
        /**
         * @brief Equality operator for comparing with boolean values
         * @param val The boolean value to compare with
         * @return true if the stored boolean value equals the given value, false otherwise
         * @details Compares the stored boolean value in the dynamic_u object with a given boolean value.
         * Returns true if they are equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator==(bool val) const noexcept
        {
            if (d_bool != nullptr && *d_bool == val)
                return true;
            return false;
        }
        /**
         * @brief Inequality operator for comparing with boolean values
         * @param val The boolean value to compare with
         * @return true if the stored boolean value does not equal the given value, false otherwise
         * @details Compares the stored boolean value in the dynamic_u object with a given boolean value.
         * Returns true if they are not equal, false otherwise.
         * If the stored value is null or of a different type, returns true.
         */
        bool operator!=(bool val) const noexcept
        {
            if (d_bool != nullptr && *d_bool == val)
                return false;
            return true;
        }
        /**
         * @brief Greater-than operator overloads for various types
         * @param c The value to compare against
         * @return true if the stored value is greater than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>(char c) const noexcept
        {
            if (d_char != nullptr)
            {
                if (*d_char > c)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is greater than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>(int value) const noexcept
        {
            if (d_int != nullptr)
            {
                if (*d_int > value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is greater than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>(float value) const noexcept
        {
            if (d_float != nullptr)
            {
                if (*d_float > value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is greater than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>(double value) const noexcept
        {
            if (d_double != nullptr)
            {
                if (*d_double > value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than-or-equal-to operator overloads for various types
         *  @param c The value to compare against
         * @return true if the stored value is greater than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>=(char c) const noexcept
        {
            if (d_char != nullptr)
            {
                if (*d_char >= c)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than-or-equal-to operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is greater than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>=(int value) const noexcept
        {
            if (d_int != nullptr)
            {
                if (*d_int >= value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than-or-equal-to operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is greater than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>=(float value) const noexcept
        {
            if (d_float != nullptr)
            {
                if (*d_float >= value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Greater-than-or-equal-to operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is greater than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is greater than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator>=(double value) const noexcept
        {
            if (d_double != nullptr)
            {
                if (*d_double >= value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than operator overloads for various types
         * @param c The value to compare against
         * @return true if the stored value is less than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<(char c) const noexcept
        {
            if (d_char != nullptr)
            {
                if (*d_char < c)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is less than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<(int value) const noexcept
        {
            if (d_int != nullptr)
            {
                if (*d_int < value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is less than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<(float value) const noexcept
        {
            if (d_float != nullptr)
            {
                if (*d_float < value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is less than the given value, false otherwise
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<(double value) const noexcept
        {
            if (d_double != nullptr)
            {
                if (*d_double < value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than-or-equal-to operator overloads for various types
         * @param c The value to compare against
         * @return true if the stored value is less than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<=(char c) const noexcept
        {
            if (d_char != nullptr)
            {
                if (*d_char <= c)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than-or-equal-to operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is less than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<=(int value) const noexcept
        {
            if (d_int != nullptr)
            {
                if (*d_int <= value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than-or-equal-to operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is less than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<=(float value) const noexcept
        {
            if (d_float != nullptr)
            {
                if (*d_float <= value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Less-than-or-equal-to operator overloads for various types
         * @param value The value to compare against
         * @return true if the stored value is less than or equal to the given value, false otherwise.
         * @details Compares the stored value in the dynamic_u object with the provided value.
         * Returns true if the stored value is less than or equal, false otherwise.
         * If the stored value is null or of a different type, returns false.
         */
        bool operator<=(double value) const noexcept
        {
            if (d_double != nullptr)
            {
                if (*d_double <= value)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        /**
         * @brief Summation operator for dynamic_u objects
         * @param val The dynamic_u object to add
         * @return A new dynamic_u object representing the sum
         * @throws std::invalid_argument if either object contains a boolean value
         * @details This operator performs summation between two dynamic_u objects.
         * If either object contains a boolean value, an exception is thrown.
         * The operator checks the types of both objects and performs the appropriate addition.
         * If both objects have the same type, their values are added directly.
         */
        dynamic_u operator+(dynamic_u &val)
        {
            if (val.type() == "bool")
                throw std::invalid_argument("A bool value does not support the summation operator");
            dynamic_u temp;
            if (val.type() == "int" && d_int != nullptr && val.d_int != nullptr)
                temp = *d_int + *val.d_int;
            else if (val.type() == "float" && d_float != nullptr && val.d_float != nullptr)
                temp = *d_float + *val.d_float;
            else if (val.type() == "double" && d_double != nullptr && val.d_double != nullptr)
                temp = *d_double + *val.d_double;
            else if (val.type() == "char" && d_char != nullptr && val.d_char != nullptr)
                temp = *d_char + *val.d_char;
            else
            {
                temp.complex();
                if (d_int != nullptr && val.d_int != nullptr)
                    temp = *d_int + *val.d_int;
                if (d_float != nullptr && val.d_float != nullptr)
                    temp = *d_float + *val.d_float;
                if (d_double != nullptr && val.d_double != nullptr)
                    temp = *d_double + *val.d_double;
                if (d_char != nullptr && val.d_char != nullptr)
                    temp = *d_char + *val.d_char;
            }
            return temp;
        }
        /**
         * @brief Summation assignment operator for dynamic_u objects
         * @param val The dynamic_u object to add
         * @throws std::invalid_argument if either object contains a boolean value
         * @details This operator performs summation assignment between two dynamic_u objects.
         * If either object contains a boolean value, an exception is thrown.
         * The operator checks the types of both objects and performs the appropriate addition.
         * If both objects have the same type, their values are added directly.
         * Otherwise, it attempts to add compatible types by converting as necessary.
         * If the types are not compatible, the operation is not performed.
         * The result is stored in the left-hand operand.
         */
        void operator+=(dynamic_u &val)
        {
            if (val.type() == "int")
            {
                if (d_int != nullptr)
                    *d_int += *val.d_int;
                else if (d_float != nullptr)
                    *d_float += static_cast<float>(*val.d_int);
                else if (d_double != nullptr)
                    *d_double += static_cast<double>(*val.d_int);
                else if (d_char != nullptr)
                    *d_char += static_cast<char>(*val.d_int);
            }
            else if (val.type() == "float")
            {
                if (d_float != nullptr)
                    *d_float += *val.d_float;
                else if (d_double != nullptr)
                    *d_double += static_cast<double>(*val.d_float);
                else if (d_int != nullptr)
                    *d_int += static_cast<int>(*val.d_float);
                else if (d_char != nullptr)
                    *d_char += static_cast<char>(*val.d_float);
            }
            else if (val.type() == "double")
            {
                if (d_double != nullptr)
                    *d_double += *val.d_double;
                else if (d_float != nullptr)
                    *d_float += static_cast<float>(*val.d_double);
                else if (d_int != nullptr)
                    *d_int += static_cast<int>(*val.d_double);
                else if (d_char != nullptr)
                    *d_char += static_cast<char>(*val.d_double);
            }
            else if (val.type() == "char")
            {
                if (d_char != nullptr)
                    *d_char += *val.d_char;
                else if (d_int != nullptr)
                    *d_int += static_cast<int>(*val.d_char);
                else if (d_float != nullptr)
                    *d_float += static_cast<float>(*val.d_char);
                else if (d_double != nullptr)
                    *d_double += static_cast<double>(*val.d_char);
            }
            else
            {
                if (d_int != nullptr && val.d_int != nullptr)
                    *d_int += *val.d_int;
                if (d_float != nullptr && val.d_float != nullptr)
                    *d_float += *val.d_float;
                if (d_double != nullptr && val.d_double != nullptr)
                    *d_double += *val.d_double;
                if (d_char != nullptr && val.d_char != nullptr)
                    *d_char += *val.d_char;
            }
        }
        /**
         * @brief Adds an integer value to the dynamic value stored in this object.
         *
         * @param val The integer value to add.
         * @return The result of adding val to the stored value, converted to int if necessary.
         *
         * @throw std::invalid_argument If the stored value is of boolean type, which does not support this operation.
         *
         * @details This operator supports addition with int, float, double, and char types.
         * Non-integer types are implicitly cast to int before performing the addition.
         * Boolean types are not supported and will raise an exception.
         */
        int operator+(int val)
        {
            if (d_int != nullptr)
                return *d_int + val;
            else if (d_float != nullptr)
                return static_cast<int>(*d_float) + val;
            else if (d_double != nullptr)
                return static_cast<int>(*d_double) + val;
            else if (d_char != nullptr)
                return static_cast<int>(*d_char) + val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }
        /// @brief Adds an integer value to the dynamic variable in-place
        /// @param val The integer value to add
        /// @details Performs addition based on the underlying data type:
        ///          - For int: adds the value directly
        ///          - For float/double: casts val to the appropriate type and adds
        ///          - For char: casts val to char and adds
        /// @throws std::invalid_argument If the dynamic variable holds a boolean type,
        ///         as the += operator is not supported for boolean values
        /// @note This operator modifies the current dynamic variable in-place
        void operator+=(int val)
        {
            if (d_int != nullptr)
                *d_int += val;
            else if (d_float != nullptr)
                *d_float += static_cast<float>(val);
            else if (d_double != nullptr)
                *d_double += static_cast<double>(val);
            else if (d_char != nullptr)
                *d_char += static_cast<char>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }
        /// @brief Adds a float value to the dynamic type.
        ///
        /// @param val The float value to add.
        /// @return The result of the addition as a float.
        ///
        /// @throws std::invalid_argument If the dynamic type holds a boolean value,
        ///         as arithmetic operations are not supported for boolean types.
        ///
        /// @details This operator performs addition between the internal numeric value
        ///          and the provided float parameter. If the internal value is stored as
        ///          a different numeric type (int, double, or char), it is implicitly
        ///          cast to float before addition.
        float operator+(float val)
        {
            if (d_float != nullptr)
                return *d_float + val;
            else if (d_int != nullptr)
                return static_cast<float>(*d_int) + val;
            else if (d_double != nullptr)
                return static_cast<float>(*d_double) + val;
            else if (d_char != nullptr)
                return static_cast<float>(*d_char) + val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }
        /**
         * @brief Adds a float value to the dynamic variable in-place
         * @param val The float value to add
         * @details Performs addition based on the underlying data type:
         *         - For float: adds the value directly
         *        - For int/double: casts val to the appropriate type and adds
         *       - For char: casts val to char and adds
         * @throws std::invalid_argument If the dynamic variable holds a boolean type,
         *         as the += operator is not supported for boolean values
         */
        void operator+=(float val)
        {
            if (d_float != nullptr)
                *d_float += val;
            else if (d_int != nullptr)
                *d_int += static_cast<int>(val);
            else if (d_double != nullptr)
                *d_double += static_cast<double>(val);
            else if (d_char != nullptr)
                *d_char += static_cast<char>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief Adds a double value to the dynamic variable.
         * @param val The double value to add.
         * @return The result of the addition as a double.
         * @throws std::invalid_argument If the dynamic variable holds a boolean type,
         *        as arithmetic operations are not supported for boolean types.
         * @details This operator performs addition between the internal numeric value
         *         and the provided double parameter. If the internal value is stored as
         *         a different numeric type (int, float, or char), it is implicitly
         *         cast to double before addition.
         */
        double operator+(double val)
        {
            if (d_double != nullptr)
                return *d_double + val;
            else if (d_int != nullptr)
                return static_cast<double>(*d_int) + val;
            else if (d_float != nullptr)
                return static_cast<double>(*d_float) + val;
            else if (d_char != nullptr)
                return static_cast<double>(*d_char) + val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }
        /**
         * @brief Adds a double value to the dynamic variable in-place
         * @param val The double value to add
         * @details Performs addition based on the underlying data type:
         *        - For double: adds the value directly
         *       - For int/float: casts val to the appropriate type and adds
         *      - For char: casts val to char and adds
         * @throws std::invalid_argument If the dynamic variable holds a boolean type,
         *        as the += operator is not supported for boolean values
         */
        void operator+=(double val)
        {
            if (d_double != nullptr)
                *d_double += val;
            else if (d_int != nullptr)
                *d_int += static_cast<int>(val);
            else if (d_float != nullptr)
                *d_float += static_cast<float>(val);
            else if (d_char != nullptr)
                *d_char += static_cast<char>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }
        /**
         * @brief Subtraction operator between two dynamic_u objects.
         *
         * @param val The dynamic_u object to subtract from this object
         * @return A new dynamic_u object representing the difference
         *
         * @throws std::invalid_argument If the types are incompatible or not supported
         *
         * @details Performs subtraction between two dynamic_u objects. The operation
         * checks the type of the argument and performs the appropriate subtraction:
         * - If val is an integer, subtracts its integer value
         * - If val is a float, subtracts its float value
         * - If val is a double, subtracts its double value
         * - If val is a character, subtracts its character value
         *
         * @note A temporary dynamic_u is created and returned (copy)
         * @note This operation does not modify the current object
         */
        dynamic_u operator-(dynamic_u &val)
        {
            dynamic_u temp;
            if (val.type() == "int")
                temp = *d_int - *val.d_int;
            else if (val.type() == "float")
                temp = *d_float - *val.d_float;
            else if (val.type() == "double")
                temp = *d_double - *val.d_double;
            else if (val.type() == "char")
                temp = *d_char - *val.d_char;
            else
                throw std::invalid_argument("Subtraction not allowed in to different types");
        }

        /**
         * @brief In-place subtraction operator with another dynamic_u object.
         *
         * @param val The dynamic_u object to subtract from this object (modifies this object)
         *
         * @throws std::invalid_argument If the types are incompatible or not supported
         *
         * @details Modifies this object by subtracting another dynamic_u's value.
         * The operation checks the type of the argument:
         * - If val is an integer, subtracts its value from d_int
         * - If val is a float, subtracts its value from d_float
         * - If val is a double, subtracts its value from d_double
         *
         * @warning This operation modifies the current object in-place
         * @note Type must match for the operation to succeed
         */
        void operator-=(dynamic_u &val)
        {
            if (val.type() == "int")
                *d_int -= *val.d_int;
            else if (val.type() == "float")
                *d_float -= *val.d_float;
            else if (val.type() == "double")
                *d_double -= *val.d_double;
            else
                throw std::invalid_argument("Subtraction not allowed in to different types");
        }

        /**
         * @brief Subtraction operator with integer value.
         *
         * @param val The integer value to subtract
         * @return The result of subtraction as an integer
         *
         * @throws std::invalid_argument If the stored value is of boolean type,
         *         which does not support this operation
         *
         * @details Performs subtraction with an integer value:
         * - For integers: subtracts directly
         * - For float/double: casts to int before subtraction
         * - For char: casts to int before subtraction
         *
         * @note Boolean types are not supported
         */
        int operator-(int val)
        {
            if (d_int != nullptr)
                return *d_int - val;
            else if (d_float != nullptr)
                return static_cast<int>(*d_float) - val;
            else if (d_double != nullptr)
                return static_cast<int>(*d_double) - val;
            else if (d_char != nullptr)
                return static_cast<int>(*d_char) - val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief In-place subtraction assignment with integer value.
         *
         * @param val The integer value to subtract
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *
         * @details Modifies this object by subtracting an integer value:
         * - For integers: subtracts directly
         * - For float/double: casts val to appropriate type and subtracts
         * - For char: casts val to char and subtracts
         *
         * @warning Modifies this object in-place
         */
        void operator-=(int val)
        {
            if (d_int != nullptr)
                *d_int -= val;
            else if (d_float != nullptr)
                *d_float -= static_cast<float>(val);
            else if (d_double != nullptr)
                *d_double -= static_cast<double>(val);
            else if (d_char != nullptr)
                *d_char -= static_cast<char>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief Subtraction operator with float value.
         *
         * @param val The float value to subtract
         * @return The result of subtraction as a float
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *
         * @details Performs subtraction with a float value:
         * - For floats: subtracts directly
         * - For int/double: casts to float before subtraction
         * - For char: casts to float before subtraction
         *
         * @note Boolean types are not supported
         */
        float operator-(float val)
        {
            if (d_float != nullptr)
                return *d_float - val;
            else if (d_int != nullptr)
                return static_cast<float>(*d_int) - val;
            else if (d_double != nullptr)
                return static_cast<float>(*d_double) - val;
            else if (d_char != nullptr)
                return static_cast<float>(*d_char) + val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief In-place subtraction assignment with float value.
         *
         * @param val The float value to subtract
         *
         * @throws std::invalid_argument If the subtraction is not allowed
         *
         * @details Modifies this object by subtracting a float value.
         * Only performs operation if not in complex mode or if floats can be converted.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-float types
         */
        void operator-=(float val)
        {
            if (d_float != nullptr)
                *d_float -= val;
            else if (d_int != nullptr && !complextype)
                *d_int -= static_cast<int>(val);
            else if (d_double != nullptr && !complextype)
                *d_double -= static_cast<double>(val);
            else
                throw std::invalid_argument("Subtraction not allowed in to different types");
        }

        /**
         * @brief Subtraction operator with double value.
         *
         * @param val The double value to subtract
         * @return The result of subtraction as a double
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *
         * @details Performs subtraction with a double value:
         * - For doubles: subtracts directly
         * - For int/float/char: casts to double before subtraction
         *
         * @note Boolean types are not supported
         */
        double operator-(double val)
        {
            if (d_double != nullptr)
                return *d_double - val;
            else if (d_int != nullptr)
                return static_cast<double>(*d_int) - val;
            else if (d_float != nullptr)
                return static_cast<double>(*d_float) - val;
            else if (d_char != nullptr)
                return static_cast<double>(*d_char) - val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief In-place subtraction assignment with double value.
         *
         * @param val The double value to subtract
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *
         * @details Modifies this object by subtracting a double value:
         * - For doubles: subtracts directly
         * - For int/float/char: casts val to appropriate type and subtracts
         *
         * @warning Modifies this object in-place
         */
        void operator-=(double val)
        {
            if (d_double != nullptr)
                *d_double -= val;
            else if (d_int != nullptr)
                *d_int -= static_cast<int>(val);
            else if (d_float != nullptr)
                *d_float -= static_cast<float>(val);
            else if (d_char != nullptr)
                *d_char -= static_cast<char>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief Subtraction operator with character value.
         *
         * @param val The character value to subtract
         * @return The result of subtraction as a character
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *
         * @details Performs subtraction with a character value:
         * - For chars: subtracts directly (uses ASCII values)
         * - For int/float/double: casts to char before subtraction
         *
         * @note Character subtraction uses ASCII numeric values
         */
        char operator-(char val)
        {
            if (d_char != nullptr)
                return *d_char - val;
            else if (d_int != nullptr)
                return static_cast<char>(*d_int) - val;
            else if (d_float != nullptr)
                return static_cast<char>(*d_float) - val;
            else if (d_double != nullptr)
                return static_cast<char>(*d_double) - val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief In-place subtraction assignment with character value (const member function).
         *
         * @param val The character value to subtract
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *
         * @details Modifies this object by subtracting a character value:
         * - For chars: subtracts directly
         * - For int/float/double: casts val to appropriate type and subtracts
         *
         * @warning Modifies this object in-place despite being const (implementation detail)
         * @note This is marked const but performs mutable operations (design issue)
         */
        void operator-=(char val) const
        {
            if (d_char != nullptr)
                *d_char -= val;
            else if (d_int != nullptr)
                *d_int -= static_cast<int>(val);
            else if (d_float != nullptr)
                *d_float -= static_cast<float>(val);
            else if (d_double != nullptr)
                *d_double -= static_cast<double>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        /**
         * @brief Multiplication operator between two dynamic_u objects.
         *
         * @param val The dynamic_u object to multiply with this object
         * @return A new dynamic_u object representing the product
         *
         * @throws std::invalid_argument If the types are incompatible
         *
         * @details Performs multiplication between two dynamic_u objects:
         * - If val is an integer, multiplies integer values
         * - If val is a float, multiplies float values
         * - If val is a double, multiplies double values
         * - If val is complex type, enters complex mode and multiplies all components
         *
         * @note Returns a temporary dynamic_u object
         * @note This operation does not modify the current object
         */
        dynamic_u operator*(dynamic_u &val)
        {
            dynamic_u temp;
            if (val.type() == "int")
                temp = (*d_int) * (*val.d_int);
            else if (val.type() == "float")
                temp = (*d_float) * (*val.d_float);
            else if (val.type() == "double")
                temp = (*d_double) * (*val.d_double);
            else if (val.type() == "complex")
            {
                temp.complex();
                temp = (*d_int) * (*val.d_int);
                temp = (*d_float) * (*val.d_float);
                temp = (*d_double) * (*val.d_double);
            }
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
            return temp;
        }

        /**
         * @brief In-place multiplication operator with another dynamic_u object.
         *
         * @param val The dynamic_u object to multiply with
         *
         * @throws std::invalid_argument If the types are incompatible
         *
         * @details Modifies this object by multiplying it with another dynamic_u's value.
         * Type of val must match one of the stored types for operation to succeed.
         *
         * @warning This operation modifies the current object in-place
         */
        void operator*=(dynamic_u &val)
        {
            if (val.type() == "int")
                *d_int *= *val.d_int;
            else if (val.type() == "float")
                *d_float *= *val.d_float;
            else if (val.type() == "double")
                *d_double *= *val.d_double;
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief Multiplication operator with integer value.
         *
         * @param val The integer value to multiply with
         * @return The result of multiplication as a double
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *         or in complex mode
         *
         * @details Performs multiplication with an integer value:
         * - For integers: multiplies directly
         * - For float/double: casts val to appropriate type and multiplies
         * - Only works in simple (non-complex) mode for non-integer types
         */
        double operator*(int val)
        {
            if (d_int != nullptr)
                return *d_int * val;
            else if (d_float != nullptr && !complextype)
                return *d_float * static_cast<float>(val);
            else if (d_double != nullptr && !complextype)
                return *d_double * static_cast<double>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief In-place multiplication assignment with integer value.
         *
         * @param val The integer value to multiply with
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *         or operation is not allowed
         *
         * @details Modifies this object by multiplying it with an integer value.
         * Works on all numeric types (int, float, double).
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-integer types
         */
        void operator*=(int val)
        {
            if (d_int != nullptr)
                *d_int *= val;
            else if (d_float != nullptr && !complextype)
                *d_float *= static_cast<float>(val);
            else if (d_double != nullptr && !complextype)
                *d_double *= static_cast<double>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief Multiplication operator with float value.
         *
         * @param val The float value to multiply with
         * @return The result of multiplication as a double
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *         or in complex mode (for non-float types)
         *
         * @details Performs multiplication with a float value:
         * - For floats: multiplies directly
         * - For int/double: casts val to appropriate type and multiplies
         * - Only works in simple mode for non-float types
         */
        double operator*(float val)
        {
            if (d_float != nullptr)
                return *d_float * val;
            else if (d_int != nullptr && !complextype)
                return *d_int * static_cast<int>(val);
            else if (d_double != nullptr && !complextype)
                return *d_double * static_cast<double>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief In-place multiplication assignment with float value.
         *
         * @param val The float value to multiply with
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object by multiplying it with a float value.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-float types
         */
        void operator*=(float val)
        {
            if (d_float != nullptr)
                *d_float *= val;
            else if (d_int != nullptr && !complextype)
                *d_int *= static_cast<int>(val);
            else if (d_double != nullptr && !complextype)
                *d_double *= static_cast<double>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief Multiplication operator with double value.
         *
         * @param val The double value to multiply with
         * @return The result of multiplication as a double
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *         or in complex mode (for non-double types)
         *
         * @details Performs multiplication with a double value:
         * - For doubles: multiplies directly
         * - For int/float: casts to appropriate type and multiplies
         * - Only works in simple mode for non-double types
         */
        double operator*(double val)
        {
            if (d_double != nullptr)
                return *d_double * val;
            else if (d_int != nullptr && !complextype)
                return *d_int * static_cast<int>(val);
            else if (d_float != nullptr && !complextype)
                return *d_float * static_cast<float>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief In-place multiplication assignment with double value.
         *
         * @param val The double value to multiply with
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object by multiplying it with a double value.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-double types
         */
        void operator*=(double val)
        {
            if (d_double != nullptr)
                *d_double *= val;
            else if (d_int != nullptr && !complextype)
                *d_int *= static_cast<int>(val);
            else if (d_float != nullptr && !complextype)
                *d_float *= static_cast<float>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in to different types");
        }

        /**
         * @brief Multiplication operator with character value (const member function).
         *
         * @param val The character value to multiply with
         * @return The result of multiplication as a double
         *
         * @throws std::invalid_argument If the stored value is of boolean type
         *         or character type is not supported
         *
         * @details Performs multiplication with a character value:
         * - For int/float/double: casts val to appropriate type and multiplies
         * - Character multiplication uses ASCII numeric values
         */
        double operator*(char val) const
        {
            if (d_int != nullptr)
                return (*d_int) * static_cast<int>(val);
            else if (d_float != nullptr)
                return (*d_float) * static_cast<float>(val);
            else if (d_double != nullptr)
                return (*d_double) * static_cast<double>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in char type");
        }

        /**
         * @brief In-place multiplication assignment with character value (const).
         *
         * @param val The character value to multiply with
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs in-place multiplication with a character value.
         *
         * @warning Marked const but performs mutable operations (design issue)
         * @note Character multiplication uses ASCII numeric values
         */
        void operator*=(char val) const
        {
            if (d_int != nullptr)
                *d_int *= static_cast<int>(val);
            else if (d_float != nullptr)
                *d_float *= static_cast<float>(val);
            else if (d_double != nullptr)
                *d_double *= static_cast<double>(val);
            else
                throw std::invalid_argument("Multiplication not allowed in char type");
        }

        /**
         * @brief Division operator with another dynamic_u object.
         *
         * @param val The dynamic_u object to divide by
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs division with another dynamic_u object.
         * @note This function does not return a value (void)
         *
         * @warning Be careful with division by zero
         */
        void operator/(dynamic_u &val)
        {
            if (val.type() == "int")
                *d_int / *val.d_int;
            else if (val.type() == "float")
                *d_float / *val.d_float;
            else if (val.type() == "double")
                *d_double / *val.d_double;
            else
                throw std::invalid_argument("Subtraction not allowed in to different types");
        }

        /**
         * @brief In-place division assignment with another dynamic_u object (rvalue).
         *
         * @param val The dynamic_u rvalue object to divide by
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs in-place division with an rvalue dynamic_u object.
         *
         * @warning Modifies this object in-place
         * @warning Be careful with division by zero
         */
        void operator/=(dynamic_u &&val)
        {
            if (val.type() == "int")
                *d_int /= *val.d_int;
            else if (val.type() == "float")
                *d_float /= *val.d_float;
            else if (val.type() == "double")
                *d_double /= *val.d_double;
            else
                throw std::invalid_argument("Subtraction not allowed in to different types");
        }

        /**
         * @brief Division operator with integer value.
         *
         * @param val The integer value to divide by
         * @return The result of division as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs division with an integer value:
         * - For integers: divides directly
         * - For float/double: casts val to appropriate type and divides
         *
         * @warning Be careful with division by zero - may result in infinity or NaN
         */
        double operator/(int val)
        {
            if (d_int != nullptr)
                return *d_int / val;
            else if (d_float != nullptr)
                return *d_float / static_cast<float>(val);
            else if (d_double != nullptr)
                return *d_double / static_cast<double>(val);
            else
                throw std::invalid_argument("Division not allowed in to different types");
        }

        /**
         * @brief In-place division assignment with integer value.
         *
         * @param val The integer value to divide by
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object by dividing it by an integer value.
         *
         * @warning Modifies this object in-place
         * @warning Division by zero behavior depends on numeric type
         */
        void operator/=(int val)
        {
            if (d_int != nullptr)
                *d_int /= val;
            else if (d_float != nullptr)
                *d_float /= static_cast<float>(val);
            else if (d_double != nullptr)
                *d_double /= static_cast<double>(val);
            else
                throw std::invalid_argument("Division not allowed in to different types");
        }

        /**
         * @brief Division operator with float value.
         *
         * @param val The float value to divide by
         * @return The result of division as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs division with a float value.
         * Only works in simple (non-complex) mode for non-float types.
         *
         * @warning Be careful with division by zero
         */
        double operator/(float val)
        {
            if (d_float != nullptr)
                return *d_float / val;
            else if (d_int != nullptr && !complextype)
                return *d_int / static_cast<int>(val);
            else if (d_double != nullptr && !complextype)
                return *d_double / static_cast<double>(val);
            else
                throw std::invalid_argument("Division not allowed in to different types");
        }

        /**
         * @brief In-place division assignment with float value.
         *
         * @param val The float value to divide by
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object by dividing it by a float value.
         * Only works in simple (non-complex) mode for non-float types.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-float types
         */
        void operator/=(float val)
        {
            if (d_float != nullptr)
                *d_float /= val;
            else if (d_int != nullptr && !complextype)
                *d_int /= static_cast<int>(val);
            else if (d_double != nullptr && !complextype)
                *d_double /= static_cast<double>(val);
            else
                throw std::invalid_argument("Division not allowed in to different types");
        }

        /**
         * @brief Division operator with double value.
         *
         * @param val The double value to divide by
         * @return The result of division as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs division with a double value.
         * Only works in simple (non-complex) mode for non-double types.
         *
         * @warning Be careful with division by zero
         */
        double operator/(double val)
        {
            if (d_double != nullptr)
                return *d_double / val;
            else if (d_int != nullptr && !complextype)
                return *d_int / static_cast<int>(val);
            else if (d_float != nullptr && !complextype)
                return *d_float / static_cast<float>(val);
            else
                throw std::invalid_argument("Division not allowed in to different types");
        }

        /**
         * @brief In-place division assignment with double value.
         *
         * @param val The double value to divide by
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object by dividing it by a double value.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-double types
         */
        void operator/=(double val)
        {
            if (d_double != nullptr)
                *d_double /= val;
            else if (d_int != nullptr && !complextype)
                *d_int /= static_cast<int>(val);
            else if (d_float != nullptr && !complextype)
                *d_float /= static_cast<float>(val);
            else
                throw std::invalid_argument("Division not allowed in to different types");
        }

        /**
         * @brief Division operator with character value.
         *
         * @param val The character value to divide by
         * @return The result of division as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Performs division with a character value.
         * Only works in simple (non-complex) mode.
         *
         * @warning Be careful with division by zero
         * @note Character division uses ASCII numeric values
         */
        double operator/(char val)
        {
            if (d_int != nullptr && !complextype)
                return *d_int / static_cast<int>(val);
            else if (d_float != nullptr && !complextype)
                return *d_float / static_cast<float>(val);
            else if (d_double != nullptr && !complextype)
                return *d_double / static_cast<double>(val);
            else
                throw std::invalid_argument("Division not allowed in char type");
        }

        /**
         * @brief In-place division assignment with character value.
         *
         * @param val The character value to divide by
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object by dividing it by a character value.
         * Only works in simple (non-complex) mode.
         *
         * @warning Modifies this object in-place
         * @warning Be careful with division by zero
         */
        void operator/=(char val)
        {
            if (d_int != nullptr && !complextype)
                *d_int /= static_cast<int>(val);
            else if (d_float != nullptr && !complextype)
                *d_float /= static_cast<float>(val);
            else if (d_double != nullptr && !complextype)
                *d_double /= static_cast<double>(val);
            else
                throw std::invalid_argument("Division not allowed in char type");
        }

        /**
         * @brief Modulus operator with integer value.
         *
         * @param val The integer divisor
         * @return The remainder of the division as an integer
         *
         * @throws std::invalid_argument If the stored value is not an integer
         *
         * @details Performs modulus operation on integer values only.
         * Returns remainder when this->d_int is divided by val.
         *
         * @warning Only valid for integer types
         * @warning Undefined behavior if val is zero
         */
        int operator%(int val)
        {
            if (d_int != nullptr)
                return *d_int % val;
            else
                throw std::invalid_argument("Modulus not allowed in to different types");
        }

        /**
         * @brief In-place modulus assignment operator with integer value.
         *
         * @param val The integer divisor
         *
         * @throws std::invalid_argument If the stored value is not an integer
         *
         * @details Modifies this object by assigning the modulus remainder to it.
         * Only valid for integer stored values.
         *
         * @warning Modifies this object in-place
         * @warning Only valid for integer types
         * @warning Undefined behavior if val is zero
         */
        void operator%=(int val)
        {
            if (d_int != nullptr)
                *d_int %= val;
            else
                throw std::invalid_argument("Modulus not allowed in to different types");
        }

        /**
         * @brief Power operator with integer exponent.
         *
         * @param val The integer exponent
         * @return The result of exponentiation as a double (base^exponent)
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Computes base^exponent using std::pow:
         * - For integers: uses integer exponentiation
         * - For float/double: casts exponent to appropriate type
         * - Only works in simple (non-complex) mode for non-integer types
         *
         * @note Uses std::pow function which returns double
         */
        double operator^(int val)
        {
            if (d_int != nullptr)
                return pow(*d_int, val);
            else if (d_float != nullptr && !complextype)
                return pow(*d_float, static_cast<float>(val));
            else if (d_double != nullptr && !complextype)
                return pow(*d_double, static_cast<double>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in to different types");
        }

        /**
         * @brief In-place power assignment operator with integer exponent.
         *
         * @param val The integer exponent
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object to hold base^exponent.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-integer types
         */
        void operator^=(int val)
        {
            if (d_int != nullptr)
                *d_int = pow(*d_int, val);
            else if (d_float != nullptr && !complextype)
                *d_float = pow(*d_float, static_cast<float>(val));
            else if (d_double != nullptr && !complextype)
                *d_double = pow(*d_double, static_cast<double>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in char type or boolean values");
        }

        /**
         * @brief Power operator with float exponent.
         *
         * @param val The float exponent
         * @return The result of exponentiation as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Computes base^exponent using std::pow with float exponent.
         * Only works in simple (non-complex) mode for non-float types.
         *
         * @note Uses std::pow function which returns double
         */
        double operator^(float val)
        {
            if (d_float != nullptr)
                return pow(*d_float, val);
            else if (d_int != nullptr && !complextype)
                return pow(*d_int, static_cast<int>(val));
            else if (d_double != nullptr && !complextype)
                return pow(*d_double, static_cast<double>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in char type or boolean values");
        }

        /**
         * @brief In-place power assignment operator with float exponent.
         *
         * @param val The float exponent
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object to hold base^exponent.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-float types
         */
        void operator^=(float val)
        {
            if (d_float != nullptr)
                *d_float = pow(*d_float, val);
            else if (d_int != nullptr && !complextype)
                *d_int = pow(*d_int, static_cast<int>(val));
            else if (d_double != nullptr && !complextype)
                *d_double = pow(*d_double, static_cast<double>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in char type or boolean values");
        }

        /**
         * @brief Power operator with double exponent.
         *
         * @param val The double exponent
         * @return The result of exponentiation as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Computes base^exponent using std::pow with double exponent.
         * Only works in simple (non-complex) mode for non-double types.
         *
         * @note Uses std::pow function which returns double
         */
        double operator^(double val)
        {
            if (d_double != nullptr)
                return pow(*d_double, val);
            else if (d_int != nullptr && !complextype)
                return pow(*d_int, static_cast<int>(val));
            else if (d_float != nullptr && !complextype)
                return pow(*d_float, static_cast<float>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in char type or boolean values");
        }

        /**
         * @brief In-place power assignment operator with double exponent.
         *
         * @param val The double exponent
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object to hold base^exponent.
         *
         * @warning Modifies this object in-place
         * @note Only works in simple (non-complex) mode for non-double types
         */
        void operator^=(double val)
        {
            if (d_double != nullptr)
                *d_double = pow(*d_double, val);
            else if (d_int != nullptr && !complextype)
                *d_int = pow(*d_int, static_cast<int>(val));
            else if (d_float != nullptr && !complextype)
                *d_float = pow(*d_float, static_cast<float>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in to different types");
        }

        /**
         * @brief Power operator with character exponent (const).
         *
         * @param val The character exponent
         * @return The result of exponentiation as a double
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Computes base^exponent using std::pow with character exponent.
         * Character value is cast to its numeric ASCII value.
         * Only works in simple (non-complex) mode.
         *
         * @note Uses std::pow function
         * @note Character exponent uses ASCII numeric values
         */
        double operator^(char val) const
        {
            if (d_int != nullptr && !complextype)
                return pow(*d_int, static_cast<int>(val));
            else if (d_float != nullptr && !complextype)
                return pow(*d_float, static_cast<float>(val));
            else if (d_double != nullptr && !complextype)
                return pow(*d_double, static_cast<double>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in char type or boolean values");
        }

        /**
         * @brief In-place power assignment operator with character exponent (const).
         *
         * @param val The character exponent
         *
         * @throws std::invalid_argument If the operation is not allowed
         *
         * @details Modifies this object to hold base^exponent.
         * Only works in simple (non-complex) mode.
         *
         * @warning Marked const but performs mutable operations (design issue)
         * @note Character exponent uses ASCII numeric values
         */
        void operator^=(char val) const
        {
            if (d_int != nullptr && !complextype)
                *d_int = pow(*d_int, static_cast<int>(val));
            else if (d_float != nullptr && !complextype)
                *d_float = pow(*d_float, static_cast<float>(val));
            else if (d_double != nullptr && !complextype)
                *d_double = pow(*d_double, static_cast<double>(val));
            else
                throw std::invalid_argument("Exponentiation not allowed in char type or boolean values");
        }

        /**
         * @brief Logical AND operator.
         *
         * @param val The boolean value to AND with the stored boolean
         * @return The result of logical AND operation
         *
         * @throws std::invalid_argument If the stored boolean pointer is null
         *
         * @details Performs logical AND between the stored boolean value and the provided parameter.
         * Returns true only if both operands are true.
         *
         * @warning Throws if d_bool is not initialized (nullptr)
         */
        bool operator&&(bool val)
        {
            if (d_bool != nullptr)
                return *d_bool && val;
            else
                throw std::invalid_argument("The boolean value is null ptr");
        }

        /**
         * @brief Logical OR operator.
         *
         * @param val The boolean value to OR with the stored boolean
         * @return The result of logical OR operation
         *
         * @throws std::invalid_argument If the stored boolean pointer is null
         *
         * @details Performs logical OR between the stored boolean value and the provided parameter.
         * Returns true if either operand is true.
         *
         * @warning Throws if d_bool is not initialized (nullptr)
         */
        bool operator||(bool val)
        {
            if (d_bool != nullptr)
                return *d_bool || val;
            else
                throw std::invalid_argument("The boolean value is null ptr");
        }
        ~dynamic_u() = default;
    };
}

#endif // OPENUDT___UDT_DYNAMIC__DYANMIC_R__HPP