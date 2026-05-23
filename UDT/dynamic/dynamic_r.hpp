#include "dynamic_u.hpp"
#include <ostream>
#include <cmath>

#pragma once
#ifndef OPENUDT___UDT_DYNAMIC__DYANMIC_R__HPP
#define OPENUDT___UDT_DYNAMIC__DYANMIC_R__HPP

namespace udt
{
    /**
     * @class dynamic_r
     * @brief Dynamic type holder with raw pointer semantics for referenced value storage.
     *
     * @details This class provides a non-owning reference variant of the dynamic type family.
     * Values are stored as raw pointers (int*, char*, float*, double*, bool*), meaning this
     * object does NOT own the memory it references. The caller is responsible for managing
     * the lifetime of pointed-to objects.
     *
     * Storage Model:
     * - int* d_int: non-owning reference to integer value
     * - char* d_char: non-owning reference to character value
     * - float* d_float: non-owning reference to float value
     * - double* d_double: non-owning reference to double value
     * - bool* d_bool: non-owning reference to boolean value
     * - bool complextype: flag indicating complex multi-reference mode
     *
     * Key Characteristics:
     * - Non-owning (does not delete pointed-to values)
     * - Move semantics supported
     * - Nullable references (nullptr indicates reference is not set)
     * - Support for complex mode storing multiple types simultaneously
     *
     * Memory Safety Considerations:
     * @warning This class holds non-owning raw pointers. The caller must ensure that:
     * 1. All pointed-to objects remain valid for the lifetime of the dynamic_r object
     * 2. Destruction order is managed properly to avoid dangling pointers
     * 3. The dynamic_r object is not used after pointed-to objects are deleted
     *
     * Usage Patterns:
     * 1. Create references to existing stack or heap objects
     * 2. Pass references without transferring ownership
     * 3. Use for temporary views into other containers
     *
     * @note All pointer members start as nullptr and must be explicitly initialized.
     * @note Call complex() to enable multi-reference storage mode.
     * @note Not thread-safe. External synchronization required for concurrent access.
     * @note Predefined copy constructor available - performs shallow copy of pointers.
     *
     * @see dynamic - Type-discriminated variant
     * @see dynamic_u - Unique pointer (owning) variant
     * @see dynamic_t - All-types-at-once variant
     */
    class dynamic_r
    {
    private:
        /// @brief Non-owning pointer to integer value (nullptr if not set)
        int *d_int = nullptr;
        /// @brief Non-owning pointer to character value (nullptr if not set)
        char *d_char = nullptr;
        /// @brief Non-owning pointer to float value (nullptr if not set)
        float *d_float = nullptr;
        /// @brief Non-owning pointer to double value (nullptr if not set)
        double *d_double = nullptr;
        /// @brief Non-owning pointer to boolean value (nullptr if not set)
        bool *d_bool = nullptr;
        /// @brief Flag indicating if object is in complex (multi-reference) mode
        bool complextype = false;

    public:
        /**
         * @brief Default constructor - creates empty dynamic_r.
         *
         * Initializes a new dynamic_r with all raw pointers set to nullptr
         * and complextype set to false. The object is ready to accept references.
         *
         * @note This is a defaulted constructor
         */
        dynamic_r() = default;

        /**
         * @brief Move constructor - transfers reference ownership from another dynamic_r.
         *
         * Implements move semantics for dynamic_r. Note that since pointers are not owning,
         * the move semantics simply transfer pointer values and complex mode flag.
         *
         * @warning The moved-from object will have nullptr values unless reassigned.
         * @note This is a defaulted move constructor
         */
        // Move Constructor
        dynamic_r(dynamic_r &&) = default;

        /**
         * @brief Constructor initializing a complex dynamic_r with all four numeric types.
         * @param intval The integer value to store
         * @param fval The float value to store
         * @param dval The double value to store
         * @param cval The char value to store
         * @details This constructor creates a complex dynamic_r object that holds multiple values simultaneously.
         * It initializes the object in complex mode and sets all four numeric types at once.
         * @note Creates new dynamic allocations for each pointer member
         */
        dynamic_r(int intval, float fval, double dval, char cval)
        {
            complex();
            set_int(intval);
            set_float(fval);
            set_double(dval);
            set_char(cval);
        }

        /**
         * @brief Constructor from an integer value (noexcept).
         * @param val The integer value to store
         * @details Creates a dynamic_r object holding a single integer value.
         * The object is in simple (non-complex) mode and only the d_int pointer is allocated.
         */
        dynamic_r(int val) noexcept { d_int = new int(val); }

        /**
         * @brief Constructor from a character value (noexcept).
         * @param val The char value to store
         * @details Creates a dynamic_r object holding a single character value.
         * The object is in simple (non-complex) mode and only the d_char pointer is allocated.
         */
        dynamic_r(char val) noexcept { d_char = new char(val); }

        /**
         * @brief Constructor from a float value (noexcept).
         * @param val The float value to store
         * @details Creates a dynamic_r object holding a single float value.
         * The object is in simple (non-complex) mode and only the d_float pointer is allocated.
         */
        dynamic_r(float val) noexcept { d_float = new float(val); }

        /**
         * @brief Constructor from a double value (noexcept).
         * @param val The double value to store
         * @details Creates a dynamic_r object holding a single double value.
         * The object is in simple (non-complex) mode and only the d_double pointer is allocated.
         */
        dynamic_r(double val) noexcept { d_double = new double(val); }

        /**
         * @brief Constructor from a boolean value.
         * @param val The bool value to store
         * @details Creates a dynamic_r object holding a single boolean value.
         * The object is in simple (non-complex) mode and only the d_bool pointer is allocated.
         */
        dynamic_r(bool val) { d_bool = new bool(val); }

        /**
         * @brief Copy constructor.
         * @param other The dynamic_r object to copy from
         * @details Creates a new dynamic_r object by deep copying all allocated pointers from the source object.
         * Preserves the complex mode flag and duplicates all non-null pointer values.
         * All member pointers of the source are independently copied to the new object.
         * @note Performs deep copy of all member pointers; original and copy are independent
         */
        dynamic_r(const dynamic_r &other)
        {
            if (other.d_int)
                d_int = new int(*other.d_int);
            if (other.d_char)
                d_char = new char(*other.d_char);
            if (other.d_float)
                d_float = new float(*other.d_float);
            if (other.d_double)
                d_double = new double(*other.d_double);
            if (other.d_bool)
                d_bool = new bool(*other.d_bool);
            complextype = other.complextype;
        }

        /**
         * @brief Enables complex mode for storing multiple simultaneous values.
         * @details Sets the complextype flag to true, allowing this object to hold multiple data values
         * (int, float, double, char, bool) simultaneously. In complex mode, type restrictions are relaxed.
         * @note This is a constexpr noexcept function
         */
        constexpr void complex() noexcept { complextype = true; }

        /**
         * @brief Disables complex mode and clears selected data members.
         * @param reint Whether to clear the integer pointer (default: true)
         * @param rechar Whether to clear the char pointer (default: true)
         * @param refloat Whether to clear the float pointer (default: true)
         * @param redouble Whether to clear the double pointer (default: true)
         * @param rebool Whether to clear the bool pointer (default: true)
         * @throws std::invalid_argument If fewer than 4 of the 5 parameters are true
         * @details Transitions the object from complex mode to simple mode by setting complextype to false
         * and selectively clearing (setting to nullptr) the specified member pointers.
         * At least 4 of the 5 type flags must be true to pass validation.
         * @warning Clearing pointers without proper deallocation may cause memory leaks if the pointers hold allocated memory
         * @note After successful uncomplex, the object will be in simple mode with only the retained pointer(s) active
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
         * @brief Sets a boolean value if allowed by the current mode.
         * @param val The boolean value to set
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new boolean value and stores it at d_bool.
         * In simple mode, can only set bool if no other type is already set or complextype is true.
         * In complex mode, can always set bool regardless of other values.
         * @note Creates a new dynamic allocation; existing value (if any) is overwritten without deallocation
         */
        void set_bool(bool val)
        {
            if (change_allowed(val) || complextype)
                d_bool = new bool(val);
            throw std::invalid_argument("not complextype nor allowed changes");
        }

        /**
         * @brief Sets an integer value if allowed by the current mode.
         * @param val The integer value to set
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new integer value and stores it at d_int.
         * In simple mode, can only set int if no other type is already set or complextype is true.
         * In complex mode, can always set int regardless of other values.
         * @note Creates a new dynamic allocation; existing value (if any) is overwritten without deallocation
         */
        void set_int(int val)
        {
            if (change_allowed(val) || complextype)
                d_int = new int(val);
            else
                throw std::invalid_argument("Change not allowed");
        }

        /**
         * @brief Sets a character value if allowed by the current mode.
         * @param val The char value to set
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new char value and stores it at d_char.
         * In simple mode, can only set char if no other type is already set or complextype is true.
         * In complex mode, can always set char regardless of other values.
         * @note Creates a new dynamic allocation; existing value (if any) is overwritten without deallocation
         */
        void set_char(char val)
        {
            if (change_allowed(val) || complextype)
                d_char = new char(val);
            else
                throw std::invalid_argument("Change not allowed");
        }

        /**
         * @brief Sets a float value if allowed by the current mode.
         * @param val The float value to set
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new float value and stores it at d_float.
         * In simple mode, can only set float if no other type is already set or complextype is true.
         * In complex mode, can always set float regardless of other values.
         * @note Creates a new dynamic allocation; existing value (if any) is overwritten without deallocation
         */
        void set_float(float val)
        {
            if (change_allowed(val) || complextype)
                d_float = new float(val);
            else
                throw std::invalid_argument("Change not allowed");
        }

        /**
         * @brief Sets a double value if allowed by the current mode.
         * @param val The double value to set
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new double value and stores it at d_double.
         * In simple mode, can only set double if no other type is already set or complextype is true.
         * In complex mode, can always set double regardless of other values.
         * @note Creates a new dynamic allocation; existing value (if any) is overwritten without deallocation
         */
        void set_double(double val)
        {
            if (change_allowed(val) || complextype)
                d_double = new double(val);
            else
                throw std::invalid_argument("Change not allowed");
        }

        /**
         * @brief Template setter methods for different data types.
         * @details Overloaded set_value methods that delegate to the specific type setters.
         * Allows setting values using a common interface regardless of type.
         * Each overload calls the corresponding set_* method (set_bool, set_int, set_char, set_float, set_double).
         */
        void set_value(bool val) { set_bool(val); }

        /**
         * @brief Template setter methods for different data types.
         * @details Overloaded set_value methods that delegate to the specific type setters.
         * Allows setting values using a common interface regardless of type.
         * Each overload calls the corresponding set_* method (set_bool, set_int, set_char, set_float, set_double).
         *
         */
        void set_value(int val) { set_int(val); }

        /**
         * @brief Template setter methods for different data types.
         * @details Overloaded set_value methods that delegate to the specific type setters.
         * Allows setting values using a common interface regardless of type.
         * Each overload calls the corresponding set_* method (set_bool, set_int, set_char, set_float, set_double).
         */
        void set_value(float val) { set_float(val); }

        /**
         * @brief Template setter methods for different data types.
         * @details Overloaded set_value methods that delegate to the specific type setters.
         * Allows setting values using a common interface regardless of type.
         * Each overload calls the corresponding set_* method (set_bool, set_int, set_char, set_float, set_double).
         */
        void set_value(double val) { set_double(val); }

        /**
         * @brief Template setter methods for different data types.
         * @details Overloaded set_value methods that delegate to the specific type setters.
         * Allows setting values using a common interface regardless of type.
         * Each overload calls the corresponding set_* method (set_bool, set_int, set_char, set_float, set_double).
         */
        void set_value(char val) { set_char(val); }

        /**
         * @brief Gets the stored boolean value.
         * @return The boolean value from d_bool
         * @throws std::invalid_argument If d_bool is nullptr (value not set), or if in complex mode and d_bool is not set,
         * or if the type is not boolean
         * @details Retrieves the stored boolean value by dereferencing d_bool.
         * Validates that d_bool is non-null before dereferencing.
         * @warning Throws exception if value has not been set with a boolean type
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
         * @brief Gets the stored integer value.
         * @return The integer value from d_int
         * @throws std::invalid_argument If d_int is nullptr (value not set), or if getting not allowed
         * @details Retrieves the stored integer value by dereferencing d_int.
         * Validates that d_int is non-null before dereferencing.
         * @warning Throws exception if value has not been set with an integer type
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
         * @brief Gets the stored character value.
         * @return The character value from d_char
         * @throws std::invalid_argument If d_char is nullptr (value not set), or if getting not allowed
         * @details Retrieves the stored character value by dereferencing d_char.
         * Validates that d_char is non-null before dereferencing.
         * @warning Throws exception if value has not been set with a character type
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
         * @brief Gets the stored float value.
         * @return The float value from d_float
         * @throws std::invalid_argument If d_float is nullptr (value not set), or if getting not allowed
         * @details Retrieves the stored float value by dereferencing d_float.
         * Validates that d_float is non-null before dereferencing.
         * @warning Throws exception if value has not been set with a float type
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
         * @brief Gets the stored double value.
         * @return The double value from d_double
         * @throws std::invalid_argument If d_double is nullptr (value not set), or if getting not allowed
         * @details Retrieves the stored double value by dereferencing d_double.
         * Validates that d_double is non-null before dereferencing.
         * @warning Throws exception if value has not been set with a double type
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
         * @brief Gets any stored value as a dynamic_u object.
         * @return A dynamic_u object containing the value (only in simple mode)
         * @throws std::invalid_argument If in complex mode (complex type doesn't return specific standard data type automatically)
         * @throws std::runtime_error If no value has been set
         * @details Converts the stored value to a dynamic_u object.
         * Only works in simple mode where exactly one type is stored.
         * Checks all member pointers in order (int, char, float, double, bool) and returns the first non-null value.
         * @warning Cannot be used in complex mode; must use specific getters instead
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

        /**
         * @brief Checks if the object is in complex mode.
         * @return True if in complex mode, false otherwise
         * @details Returns the value of the complextype flag, indicating whether this object is currently in complex mode (holding multiple values simultaneously) or simple mode (holding at most one value).
         * @note This is a constexpr noexcept function
         */
        constexpr bool is_complex() const noexcept { return complextype; }

        /**
         * @brief Checks if the object is empty (no values set).
         * @return True if all member pointers are nullptr, false otherwise
         * @details Returns true if all member pointers (d_int, d_char, d_float, d_double, d_bool) are nullptr, indicating that no value is currently stored in this object.
         * @note This is a constexpr noexcept function
         * @warning An object in complex mode can still be considered empty if all pointers are nullptr
         */
        bool empty() const noexcept
        {
            return d_int == nullptr &&
                   d_char == nullptr &&
                   d_float == nullptr &&
                   d_double == nullptr &&
                   d_bool == nullptr;
        }

        /**
         * @brief Clears all stored values by setting all member pointers to nullptr.
         * @details Sets d_int, d_char, d_float, d_double, and d_bool to nullptr, effectively clearing any stored values. This does not change the complex mode flag.
         * @warning This method does not deallocate memory if the pointers hold allocated values, which may lead to memory leaks if not used carefully.
         * @note This is a noexcept function
         * @warning Use with caution: does not manage memory of pointed-to values, may cause leaks if used on allocated pointers
         */
        void clear_all() noexcept
        {
            d_int = nullptr;
            d_char = nullptr;
            d_float = nullptr;
            d_double = nullptr;
            d_bool = nullptr;
        }

        /**
         * @brief Clears the stored boolean value by setting d_bool to nullptr if allowed by the current mode.
         * @details Sets d_bool to nullptr if the current mode allows changes (not complex mode or same type) and if d_bool is currently non-null. In complex mode, clearing is allowed regardless of other values.
         * @warning This method does not deallocate memory if d_bool holds an allocated value, which may lead to memory leaks if not used carefully.
         * @note This is a noexcept function
         * @warning Use with caution: does not manage memory of pointed-to values, may cause leaks if used on allocated pointers
         */
        void clear_bool() noexcept
        {
            if ((!change_allowed() || complextype) && d_bool != nullptr)
                d_bool = nullptr;
        }

        /**
         * @brief Clears the stored integer value by setting d_int to nullptr if allowed by the current mode.
         * @details Sets d_int to nullptr if the current mode allows changes (not complex mode or same type) and if d_int is currently non-null. In complex mode, clearing is allowed regardless of other values.
         * @warning This method does not deallocate memory if d_int holds an allocated value, which may lead to memory leaks if not used carefully.
         */
        void clear_int() noexcept
        {
            if ((!change_allowed() || complextype) && d_int != nullptr)
                d_int = nullptr;
        }

        /**
         * @brief Clears the stored float value by setting d_float to nullptr if allowed by the current mode.
         * @details Sets d_float to nullptr if the current mode allows changes (not complex mode or same type) and if d_float is currently non-null. In complex mode, clearing is allowed regardless of other values.
         * @warning This method does not deallocate memory if d_float holds an allocated value,
         * which may lead to memory leaks if not used carefully. Use with caution.
         * @note This is a noexcept function
         * @warning Use with caution: does not manage memory of pointed-to values, may cause leaks if used on allocated pointers
         */
        void clear_float() noexcept
        {
            if ((!change_allowed() || complextype) && d_float != nullptr)
                d_float = nullptr;
        }

        /**
         * @brief Clears the stored double value by setting d_double to nullptr if allowed by the current mode.
         * @details Sets d_double to nullptr if the current mode allows changes (not complex mode or same type) and if d_double is currently non-null. In complex mode, clearing is allowed regardless of other values.
         * @warning This method does not deallocate memory if d_double holds an allocated value,
         * which may lead to memory leaks if not used carefully. Use with caution.
         * @note This is a noexcept function
         * @warning Use with caution: does not manage memory of pointed-to values, may cause
         */
        void clear_double() noexcept
        {
            if ((!change_allowed() || complextype) && d_double != nullptr)
                d_double = nullptr;
        }

        /**
         * @brief Clears the stored character value by setting d_char to nullptr if allowed by the current mode.
         * @details Sets d_char to nullptr if the current mode allows changes (not complex mode or same type) and if d_char is currently non-null. In complex mode, clearing is allowed regardless of other values.
         * @warning This method does not deallocate memory if d_char holds an allocated value,
         * which may lead to memory leaks if not used carefully. Use with caution.
         * @note This is a noexcept function
         * @warning Use with caution: does not manage memory of pointed-to values, may cause
         */
        void clear_char() noexcept
        {
            if ((!change_allowed() || complextype) && d_char != nullptr)
                d_char = nullptr;
        }

        /**
         * @brief Checks if a boolean value is currently stored.
         * @return True if d_bool is non-null, false otherwise
         * @details Returns true if d_bool is currently pointing to a boolean value (non-null), indicating that a boolean value is stored in this object. Returns false if d_bool is nullptr, indicating that no boolean value is currently stored.
         * @note This is a noexcept function
         * @warning An object in complex mode can have multiple values; this only checks for the presence of a boolean value
         */
        bool has_bool() const noexcept
        {
            if (d_bool != nullptr)
                return true;
            return false;
        }

        /**
         * @brief Checks if an integer value is currently stored.
         * @return True if d_int is non-null, false otherwise
         * @details Returns true if d_int is currently pointing to an integer value (non-null), indicating that an integer value is stored in this object. Returns false if d_int is nullptr, indicating that no integer value is currently stored.
         * @note This is a noexcept function
         * @warning An object in complex mode can have multiple values; this only checks for the presence of an integer value
         */
        bool has_int() const noexcept
        {
            if (d_int != nullptr)
                return true;
            return false;
        }

        /**
         * @brief Checks if a float value is currently stored.
         * @return True if d_float is non-null, false otherwise
         * @details Returns true if d_float is currently pointing to a float value (non-null), indicating that a float value is stored in this object. Returns false if d_float is nullptr, indicating that no float value is currently stored.
         * @note This is a noexcept function
         * @warning An object in complex mode can have multiple values; this only checks for the presence of a float value
         */
        bool has_float() const noexcept
        {
            if (d_float != nullptr)
                return true;
            return false;
        }

        /**
         * @brief Checks if a double value is currently stored.
         * @return True if d_double is non-null, false otherwise
         * @details Returns true if d_double is currently pointing to a double value (non-null), indicating that a double value is stored in this object. Returns false if d_double is nullptr, indicating that no double value is currently stored.
         * @note This is a noexcept function
         * @warning An object in complex mode can have multiple values; this only checks for the presence of a double value
         */
        bool has_double() const noexcept
        {
            if (d_double != nullptr)
                return true;
            return false;
        }

        /**
         * @brief Checks if a character value is currently stored.
         * @return True if d_char is non-null, false otherwise
         * @details Returns true if d_char is currently pointing to a character value (non-null), indicating that a character value is stored in this object. Returns false if d_char is nullptr, indicating that no character value is currently stored.
         * @note This is a noexcept function
         * @warning An object in complex mode can have multiple values; this only checks for the presence of a character value
         */
        bool has_char() const noexcept
        {
            if (d_char != nullptr)
                return true;
            return false;
        }

        /**
         * @brief Checks if a value of the specified type is currently stored.
         * @param type The type to check for ("int", "float", "double", "char", "boolean")
         * @return True if a value of the specified type is stored, false otherwise
         */
        bool has(const std::string &type) const noexcept
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
         * @brief Checks if the stored value is of the same type as the provided value.
         * @param value The value to compare against
         * @return True if the stored value is of the same type as the provided value, false otherwise
         */
        template <typename T>
        bool same_type(T &value) noexcept
        {
            dynamic_u d = value;
            if (d.type() == type())
                return true;
            return false;
        }

        /**
         * @brief Checks if changing the stored value to a new type is allowed based on the current mode and existing values.
         * @return True if changing the type is allowed, false otherwise
         * @details In simple mode (not complex), changing the type is only allowed if no other type is currently set. In complex mode, changing the type is always allowed regardless of existing values.
         */
        bool change_allowed()
        {
            if (is_complex())
                return true;
            return !(has_int() || has_float() || has_double() || has_char() || has_bool());
        }

        /**
         * @brief Checks if changing the stored value to a new type is allowed based on the current mode and existing values, considering the type of the new value.
         * @param value The new value to be set
         * @return True if changing the type is allowed, false otherwise
         * @details In simple mode (not complex), changing the type is allowed if no other type is currently set or if the new value is of the same type as the existing value. In complex mode, changing the type is always allowed regardless of existing values.
         */
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
         * @brief Returns a string representation of the type of value currently stored in this object.
         * @return A string indicating the type of the stored value ("complex", "int",
         * "float", "double", "char", "boolean", or "undefined")
         * @details Checks the member pointers in order (complex mode first, then int, float, double, char, bool) and returns a string indicating the type of value currently stored. If in complex mode, returns "complex". If a specific type pointer is non-null, returns the corresponding type name. If no value is set, returns "undefined".
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
         * @brief Checks if the stored value(s) are purely numeric (int, float, double) with no char or bool values.
         * @return True if the stored value(s) are purely numeric, false otherwise
         * @details In complex mode, returns true if d_char and d_bool are nullptr and at least one of d_int, d_float, or d_double is non-null.
         * In simple mode, returns true if d_char and d_bool are nullptr regardless of other values.
         * Returns false if any char or bool value is stored.
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

        friend std::ostream &operator<<(std::ostream &os, const dynamic_r &d)
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
        dynamic_r &operator=(dynamic_r &&) = default;

        /**
         * @brief Overloaded assignment operators for different data types.
         * @details Allows assigning values of different types directly to a dynamic_r object using the assignment operator. Each overload checks if changing the type is allowed based on the current mode and existing values, and if so, allocates a new value of the corresponding type. If changing the type is not allowed in simple mode, an exception is thrown.
         * @warning These operators do not manage memory of existing values; assigning a new value will overwrite the pointer without deallocating any previously allocated memory, which may lead to memory leaks if not used carefully.
         * @note In complex mode, these operators will always allow changing the type and will simply set the new value. In simple mode, they will only allow changing the type if no other type is currently set or if the new value is of the same type as the existing value.
         */
        void operator=(int val)
        {
            if (change_allowed(val) || complextype)
                d_int = new int(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }

        /**
         * @brief Overloaded assignment operator for float type.
         * @param val The float value to assign
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new float value and stores it at d_float if changing the type is allowed based on the current mode and existing values. In simple mode, changing the type is only allowed if no other type is currently set or if the new value is of the same type as the existing value. In complex mode, changing the type is always allowed regardless of existing values. If changing the type is not allowed in simple mode, an exception is thrown.
         */
        void operator=(float val)
        {
            if (change_allowed(val) || complextype)
                d_float = new float(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }

        /**
         * @brief Overloaded assignment operator for double type.
         * @param val The double value to assign
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new double value and stores it at d_double if changing the type is allowed based on the current mode and existing values. In simple mode, changing the type is only allowed if no other type is currently set or if the new value is of the same type as the existing value. In complex mode, changing the type is always allowed regardless of existing values. If changing the type is not allowed in simple mode, an exception is thrown.
         */
        void operator=(double val)
        {
            if (change_allowed(val) || complextype)
                d_double = new double(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }

        /**
         * @brief Overloaded assignment operator for char type.
         * @param val The char value to assign
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new char value and stores it at d_char if changing the type is allowed based on the current mode and existing values. In simple mode, changing the type is only allowed if no other type is currently set or if the new value is of the same type as the existing value. In complex mode, changing the type is always allowed regardless of existing values. If changing the type is not allowed in simple mode, an exception is thrown.
         */
        void operator=(char val)
        {
            if (change_allowed(val) || complextype)
                d_char = new char(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }

        /**
         * @brief Overloaded assignment operator for bool type.
         * @param val The bool value to assign
         * @throws std::invalid_argument If the type cannot be changed (not complex mode and other types already set)
         * @details Allocates a new bool value and stores it at d_bool if changing the type is allowed based on the current mode and existing values. In simple mode, changing the type is only allowed if no other type is currently set or if the new value is of the same type as the existing value. In complex mode, changing the type is always allowed regardless of existing values. If changing the type is not allowed in simple mode, an exception is thrown.
         */
        void operator=(bool val)
        {
            if (change_allowed(val) || complextype)
                d_bool = new bool(val);
            else
                throw std::invalid_argument("uncomplex type can not have more than one value");
        }

        /**
         * @brief Copy assignment operator for dynamic_r.
         * @param other The dynamic_r object to copy from
         * @return A reference to this dynamic_r object after assignment
         * @details Performs a deep copy of the other dynamic_r object. First
         */
        dynamic_r &operator=(const dynamic_r &other)
        {
            if (this != &other)
            {
                clear_all();
                if (other.d_int)
                    d_int = new int(*other.d_int);
                if (other.d_char)
                    d_char = new char(*other.d_char);
                if (other.d_float)
                    d_float = new float(*other.d_float);
                if (other.d_double)
                    d_double = new double(*other.d_double);
                if (other.d_bool)
                    d_bool = new bool(*other.d_bool);
                complextype = other.complextype;
            }
            return *this;
        }

        /**
         * @brief Equality operator to compare two dynamic_r objects.
         * @param other The dynamic_r object to compare with
         * @return True if the two objects are considered equal, false otherwise
         * @details Compares the current object with another dynamic_r object for equality. First checks if the complex mode flags are the same. Then compares each member pointer (d_int, d_char, d_float, d_double, d_bool) for equality. If both pointers are non-null, their values are compared. If one pointer is null and the other is not, they are considered not equal. If all checks pass, the objects are considered equal.
         */
        bool operator==(const dynamic_r &other) const noexcept
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
         * @brief Inequality operator to compare two dynamic_r objects.
         * @param other The dynamic_r object to compare with
         * @return True if the two objects are considered not equal, false otherwise
         * @details Compares the current object with another dynamic_r object for inequality.
         * First checks if the complex mode flags are different.
         * Then compares each member pointer (d_int, d_char, d_float, d_double, d_bool) for inequality.
         * If both pointers are non-null, their values are compared.
         * If one pointer is null and the other is not, they are considered not equal.
         * If all checks pass, the objects are considered equal, so this operator returns false.
         */
        bool operator!=(const dynamic_r &other) const noexcept
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
         * @brief Equality operator to compare the stored value with a specific type value.
         * @param val The value to compare with (int, float, double, char, bool)
         * @return True if the stored value is equal to the provided value, false otherwise
         * @details Compares the stored value in this object with a provided value of a specific type.
         * Each overload checks if the corresponding member pointer is non-null and if its value is equal to the provided value.
         * If the pointer is null or the values are not equal, it returns false.
         * If the pointer is non-null and the values are equal, it returns true.
         */
        bool operator==(int val) const noexcept
        {
            if (d_int != nullptr && val == *d_int)
                return true;
            return false;
        }

        /**
         * @brief Inequality operator to compare the stored value with a specific type value.
         * @param val The value to compare with (int, float, double, char, bool)
         * @return True if the stored value is not equal to the provided value, false otherwise
         * @details Compares the stored value in this object with a provided value of a specific type for inequality.
         * Each overload checks if the corresponding member pointer is non-null and if its value is equal to the provided value.
         * If the pointer is non-null and the values are equal, it returns false (not unequal).
         * If the pointer is null or the values are not equal, it returns true (unequal).
         */
        bool operator!=(int val) const noexcept
        {
            if (d_int != nullptr && val == *d_int)
                return false;
            return true;
        }

        /**
         * @brief Equality and inequality operators to compare the stored value with a specific type value (float, double, char, bool).
         * @param val The value to compare with (float, double, char, bool)
         * @return True if the stored value is equal to the provided value, false otherwise (for operator==) or true if not equal, false otherwise (for operator!=)
         * @details Compares the stored value in this object with a provided value of a specific type for equality and inequality.
         * Each overload checks if the corresponding member pointer is non-null and if its value is equal to the provided value.
         * For operator==: If the pointer is non-null and the values are equal, it returns true; otherwise, it returns false.
         * For operator!=: If the pointer is non-null and the values are equal, it
         */
        bool operator==(float val) const noexcept
        {
            if (d_float != nullptr && val == *d_float)
                return true;
            return false;
        }

        /**
         * @brief Inequality operator to compare the stored float value with a provided float value.
         * @param val The float value to compare with
         * @return True if the stored float value is not equal to the provided value, false otherwise
         * @details Compares the stored float value in this object with a provided float value for inequality.
         * Checks if d_float is non-null and if its value is equal to the provided value
         * If d_float is non-null and the values are equal, it returns false (not unequal).
         * If d_float is null or the values are not equal, it returns true (unequal).
         */
        bool operator!=(float val) const noexcept
        {
            if (d_float != nullptr && val == *d_float)
                return false;
            return true;
        }

        /**
         * @brief Equality and inequality operators to compare the stored double value with a provided double value.
         * @param val The double value to compare with
         * @return True if the stored double value is equal to the provided value, false otherwise (for operator==) or true if not equal, false otherwise (for operator!=)
         * @details Compares the stored double value in this object with a provided double value for equality and inequality.
         * Each overload checks if the corresponding member pointer is non-null and if its value is equal to the provided value.
         * For operator==: If the pointer is non-null and the values are equal, it returns true; otherwise, it returns false.
         * For operator!=: If the pointer is non-null and the values are equal, it returns false; otherwise, it returns true.
         */
        bool operator==(double val) const noexcept
        {
            if (d_double != nullptr && val == *d_double)
                return true;
            return false;
        }

        /**
         * @brief Inequality operator to compare the stored double value with a provided double value.
         * @param val The double value to compare with
         * @return True if the stored double value is not equal to the provided value, false otherwise
         * @details Compares the stored double value in this object with a provided double value for inequality.
         * Checks if d_double is non-null and if its value is equal to the provided value
         * If d_double is non-null and the values are equal, it returns false (not unequal).
         * If d_double is null or the values are not equal, it returns true (unequal).
         */
        bool operator!=(double val) const noexcept
        {
            if (d_double != nullptr && val == *d_double)
                return false;
            return true;
        }

        /**
         * @brief Equality operator to compare the stored char value with a provided char value.
         * @param val The char value to compare with
         * @return True if the stored char value is equal to the provided value, false otherwise
         * @details Compares the stored char value in this object with a provided char value for equality.
         * Checks if d_char is non-null and if its value is equal to the provided value
         * If d_char is non-null and the values are equal, it returns true (equal).
         * If d_char is null or the values are not equal, it returns false (not equal).
         */
        bool operator==(char val) const noexcept
        {
            if (d_char != nullptr && val == *d_char)
                return true;
            return false;
        }

        /**
         * @brief Inequality operator to compare the stored char value with a provided char value.
         * @param val The char value to compare with
         * @return True if the stored char value is not equal to the provided value, false otherwise
         * @details Compares the stored char value in this object with a provided char value for inequality.
         * Checks if d_char is non-null and if its value is equal to the provided value
         * If d_char is non-null and the values are equal, it returns false (not unequal).
         * If d_char is null or the values are not equal, it returns true (unequal).
         */
        bool operator!=(char val) const noexcept
        {
            if (d_char != nullptr && val == *d_char)
                return false;
            return true;
        }

        /**
         * @brief Equality operator to compare the stored bool value with a provided bool value.
         * @param val The bool value to compare with
         * @return True if the stored bool value is equal to the provided value, false otherwise
         * @details Compares the stored bool value in this object with a provided bool value for equality.
         * Checks if d_bool is non-null and if its value is equal to the provided value
         * If d_bool is non-null and the values are equal, it returns true (equal).
         * If d_bool is null or the values are not equal, it returns false (not equal).
         */
        bool operator==(bool val) const noexcept
        {
            if (d_bool != nullptr && *d_bool == val)
                return true;
            return false;
        }

        /**
         * @brief Inequality operator to compare the stored bool value with a provided bool value.
         * @param val The bool value to compare with
         * @return True if the stored bool value is not equal to the provided value, false otherwise
         * @details Compares the stored bool value in this object with a provided bool value for inequality.
         * Checks if d_bool is non-null and if its value is equal to the provided value
         * If d_bool is non-null and the values are equal, it returns false (not unequal).
         * If d_bool is null or the values are not equal, it returns true (unequal).
         */
        bool operator!=(bool val) const noexcept
        {
            if (d_bool != nullptr && *d_bool == val)
                return false;
            return true;
        }

        /**
         * @brief Comparison operators to compare the stored value with a specific type value (char, int, float, double) for greater than, less than, greater than or equal to, and less than or equal to.
         * @param val The value to compare with (char, int, float, double)
         * @return True if the comparison condition is satisfied, false otherwise
         * @details Compares the stored value in this object with a provided value of a specific
         * type for greater than, less than, greater than or equal to, and less than or equal to.
         * Each overload checks if the corresponding member pointer is non-null and if its value satisfies the comparison condition with the provided value.
         * If the pointer is null, an exception is thrown indicating that no value of that type has been set.
         * If the pointer is non-null, the comparison is performed and the result is returned.
         */
        bool operator>(char c) const
        {
            if (d_char != nullptr)
            {
                if (*d_char > c)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No char value have been set");
        }

        /**
         * @brief Comparison operator to compare the stored int value with a provided int value for greater than.
         * @param value The int value to compare with
         * @return True if the stored int value is greater than the provided value, false otherwise
         * @details Compares the stored int value in this object with a provided int value for greater than.
         * Checks if d_int is non-null and if its value is greater than the provided value
         * If d_int is non-null and its value is greater than the provided value, it returns true; otherwise, it returns false.
         * If d_int is null, an exception is thrown indicating that no int value has been set.
         * @warning This operator only checks the int value; if the object is in complex mode and has multiple values, it does not consider those other values in the comparison.
         */
        bool operator>(int value) const
        {
            if (d_int != nullptr)
            {
                if (*d_int > value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No int value have been set");
        }

        /**
         * @brief Comparison operator to compare the stored float value with a provided float value for greater than.
         * @param value The float value to compare with
         * @return True if the stored float value is greater than the provided value, false otherwise
         * @details Compares the stored float value in this object with a provided float value for greater than.
         * Checks if d_float is non-null and if its value is greater than the provided value
         * If d_float is non-null and its value is greater than the provided value, it returns true; otherwise, it returns false.
         * If d_float is null, an exception is thrown indicating that no float value has been set.
         * @warning This operator only checks the float value; if the object is in complex mode and has multiple values, it does not consider those other values in the comparison.
         */
        bool operator>(float value) const
        {
            if (d_float != nullptr)
            {
                if (*d_float > value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No float value have been set");
        }

        /**
         * @brief Comparison operator to compare the stored double value with a provided double value for greater than.
         * @param value The double value to compare with
         * @return True if the stored double value is greater than the provided value, false otherwise
         * @details Compares the stored double value in this object with a provided double value for greater than.
         * Checks if d_double is non-null and if its value is greater than the provided value
         * If d_double is non-null and its value is greater than the provided value, it returns true; otherwise, it returns false.
         * If d_double is null, an exception is thrown indicating that no double value has been set.
         * @warning This operator only checks the double value; if the object is in complex mode and has multiple values, it does not consider those other values in the comparison.
         */
        bool operator>(double value) const
        {
            if (d_double != nullptr)
            {
                if (*d_double > value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No double value have been set");
        }

        /**
         * @brief Comparison operators to compare the stored value with a specific type value (char, int, float, double) for greater than or equal to and less than or equal to.
         * @param val The value to compare with (char, int, float, double)
         * @return True if the comparison condition is satisfied, false otherwise
         * @details Compares the stored value in this object with a provided value of a specific type for greater than or equal to and less than or equal to.
         * Each overload checks if the corresponding member pointer is non-null and if its value satisfies the comparison condition with the provided value.
         * If the pointer is null, an exception is thrown indicating that no value of that type has been set.
         * If the pointer is non-null, the comparison is performed and the result is returned.
         */
        bool operator>=(char c) const
        {
            if (d_char != nullptr)
            {
                if (*d_char >= c)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No char value have been set");
        }

        /**
         * @brief Comparison operator to compare the stored int value with a provided int value for greater than or equal to.
         * @param value The int value to compare with
         * @return True if the stored int value is greater than or equal to the provided value, false otherwise
         * @details Compares the stored int value in this object with a provided int value for greater than or equal to.
         * Checks if d_int is non-null and if its value is greater than or equal to the provided value
         * If d_int is non-null and its value is greater than or equal to the provided value, it returns true; otherwise, it returns false.
         * If d_int is null, an exception is thrown indicating that no int value has been set.
         * @warning This operator only checks the int value; if the object is in complex mode and has multiple values, it does not consider those other values in the comparison.
         */
        bool operator>=(int value) const
        {
            if (d_int != nullptr)
            {
                if (*d_int >= value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No int value have been set");
        }

        /**
         * @brief Comparison operator to compare the stored float value with a provided float value for greater than or equal to.
         * @param value The float value to compare with
         * @return True if the stored float value is greater than or equal to the provided value, false otherwise
         * @details Compares the stored float value in this object with a provided float value for greater than or equal to.
         * Checks if d_float is non-null and if its value is greater than or equal to the provided value
         * If d_float is non-null and its value is greater than or equal to the provided value, it returns true; otherwise, it returns false.
         * If d_float is null, an exception is thrown indicating that no float value has been set.
         * @warning This operator only checks the float value; if the object is in complex mode and has multiple values, it does not consider those other values in the comparison.
         */
        bool operator>=(float value) const
        {
            if (d_float != nullptr)
            {
                if (*d_float >= value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No float value have been set");
        }

        bool operator>=(double value) const
        {
            if (d_double != nullptr)
            {
                if (*d_double >= value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No double value have been set");
        }

        bool operator<(char c) const
        {
            if (d_char != nullptr)
            {
                if (*d_char < c)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No char value have been set");
        }

        bool operator<(int value) const
        {
            if (d_int != nullptr)
            {
                if (*d_int < value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No int value have been set");
        }

        bool operator<(float value) const
        {
            if (d_float != nullptr)
            {
                if (*d_float < value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No float value have been set");
        }

        bool operator<(double value) const
        {
            if (d_double != nullptr)
            {
                if (*d_double < value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No double value have been set");
        }

        bool operator<=(char c) const
        {
            if (d_char != nullptr)
            {
                if (*d_char <= c)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No char value have been set");
        }

        bool operator<=(int value) const
        {
            if (d_int != nullptr)
            {
                if (*d_int <= value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No int value have been set");
        }

        bool operator<=(float value) const
        {
            if (d_float != nullptr)
            {
                if (*d_float <= value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No float value have been set");
        }

        bool operator<=(double value) const
        {
            if (d_double != nullptr)
            {
                if (*d_double <= value)
                    return true;
                else
                    return false;
            }
            else
                throw std::invalid_argument("No double value have been set");
        }

        dynamic_r operator+(dynamic_r &val)
        {
            if (val.type() == "bool")
                throw std::invalid_argument("A bool value does not support the summation operator");
            dynamic_r temp;
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

        void operator+=(dynamic_r &val)
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

        char operator+(char val)
        {
            if (d_char != nullptr)
                return *d_char + val;
            else if (d_int != nullptr)
                return static_cast<char>(*d_int) + val;
            else if (d_float != nullptr)
                return static_cast<char>(*d_float) + val;
            else if (d_double != nullptr)
                return static_cast<char>(*d_double) + val;
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        void operator+=(char val)
        {
            if (d_char != nullptr)
                *d_char += val;
            else if (d_int != nullptr)
                *d_int += static_cast<int>(val);
            else if (d_float != nullptr)
                *d_float += static_cast<float>(val);
            else if (d_double != nullptr)
                *d_double += static_cast<double>(val);
            else
                throw std::invalid_argument("this operator is not allow in boolean types");
        }

        dynamic_r operator-(dynamic_r &val)
        {
            dynamic_r temp;
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

        void operator-=(dynamic_r &val)
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

        dynamic_r operator*(dynamic_r &val)
        {
            dynamic_r temp;
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

        void operator*=(dynamic_r &val)
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
        void operator/(dynamic_r &val)
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
        void operator/=(dynamic_r &&val)
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
        int operator%(int val)
        {
            if (d_int != nullptr)
                return *d_int % val;
            else
                throw std::invalid_argument("Modulus not allowed in to different types");
        }
        void operator%=(int val)
        {
            if (d_int != nullptr)
                *d_int %= val;
            else
                throw std::invalid_argument("Modulus not allowed in to different types");
        }
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
        bool operator&&(bool val)
        {
            if (d_bool != nullptr)
                return *d_bool && val;
            else
                throw std::invalid_argument("The boolean value is null ptr");
        }
        bool operator||(bool val)
        {
            if (d_bool != nullptr)
                return *d_bool || val;
            else
                throw std::invalid_argument("The boolean value is null ptr");
        }
        ~dynamic_r()
        {
            delete[] d_int;
            delete[] d_float;
            delete[] d_double;
            delete[] d_char;
            delete[] d_bool;
        };
    };
}

#endif // OPENUDT___UDT_DYNAMIC__DYANMIC_R__HPP