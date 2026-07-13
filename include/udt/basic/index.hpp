#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include "cfrost/structure.h"

#pragma once
#ifndef OPENUDT___BASIC___indHPP
#define OPENUDT___BASIC___indHPP

namespace udt
{
    /**
     * @brief Represents a size-based index with an explicit validity state.
     *
     * This type is intended to model an index that may be temporarily invalid
     * before it is initialized or assigned. The validity flag allows callers to
     * detect an unusable index without relying on sentinel values or external
     * state.
     */
    class index
    {
    private:
        /// Stores the underlying numeric value of the index.
        size_t ind = size_t();

        /// Indicates whether the index is currently usable.
        bool is_valid = true;

    public:
        /**
         * @brief Constructs an index in its default state.
         *
         * The resulting object uses the default-initialized value and remains
         * valid by default.
         */
        index() = default;

        /**
         * @brief Destroys the index object.
         */
        ~index() = default;

        /**
         * @brief Constructs an index from a raw size value.
         *
         * @param index The initial numeric value to store.
         */
        index(size_t index) : ind(index), is_valid(true) {}

        /**
         * @brief Copies another index object.
         *
         * @param other The index to copy from.
         */
        index(const index &other) = default;

        /**
         * @brief Copies the state of another index object.
         *
         * @param other The index to assign from.
         * @return Reference to this object.
         */
        index &operator=(const index &other) = default;

        /**
         * @brief Marks the index as valid and assigns a new numeric value.
         *
         * @param index The new value to store.
         */
        void make_valid(size_t index) noexcept
        {
            this->ind = index;
            is_valid = true;
        }

        /**
         * @brief Marks the index as invalid and clears its stored value.
         */
        procedure(unvalidate) noexcept
        {
            is_valid = false;
            ind = size_t();
        }

        /**
         * @brief Checks whether the index is currently valid.
         *
         * @return true if the index can be used, false otherwise.
         */
        bool is_valid() const noexcept
        {
            return is_valid;
        }

        /**
         * @brief Assigns a new value to the index.
         *
         * @param index The new numeric value to store.
         * @throws std::runtime_error if the index is invalid.
         */
        void set(size_t index)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot set index: index is invalid");
            }
            this->ind = index;
        }

        /**
         * @brief Returns the stored numeric value.
         *
         * @return The stored index value.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t get() const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Invalid index");
            }
            return ind;
        }

        /**
         * @brief Checks whether the current index is valid for a string context.
         *
         * @param context The string being checked.
         * @return true if the index is within the string bounds, false otherwise.
         */
        bool validFor(const std::string &context) const noexcept
        {
            if (context.length() < ind)
                return false;
            return true;
        }

        /**
         * @brief Checks whether the current index is valid for a container context.
         *
         * @tparam Y The element type stored in the container.
         * @param context The container being checked.
         * @return true if the index is within the container bounds, false otherwise.
         */
        template <typename Y>
        bool validFor(const std::vector<Y> &context) const noexcept
        {
            if (context.size() < ind)
                return false;
            return true;
        }

        /**
         * @brief Assigns a raw size value to this index.
         *
         * @param index The new numeric value to store.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator=(size_t index)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot assign index: index is invalid");
            }
            this->ind = index;
        }

        /**
         * @brief Compares this index with a raw size value.
         *
         * @param index The value to compare against.
         * @return true if the values differ, false otherwise.
         * @throws std::runtime_error if the index is invalid.
         */
        bool operator!=(size_t index) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot compare index: index is invalid");
            }
            return this->ind != index;
        }

        /**
         * @brief Compares this index with a raw size value.
         *
         * @param index The value to compare against.
         * @return true if the values are equal, false otherwise.
         * @throws std::runtime_error if the index is invalid.
         */
        bool operator==(size_t index) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot compare index: index is invalid");
            }
            return this->ind == index;
        }

        /**
         * @brief Compares this index with another index object.
         *
         * @param other The other index to compare with.
         * @return true if the values differ, false otherwise.
         * @throws std::runtime_error if either index is invalid.
         */
        bool operator!=(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot compare indices: one or both indices are invalid");
            }
            return this->ind != other.ind;
        }

        /**
         * @brief Compares this index with another index object.
         *
         * @param other The other index to compare with.
         * @return true if the values are equal, false otherwise.
         * @throws std::runtime_error if either index is invalid.
         */
        bool operator==(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot compare indices: one or both indices are invalid");
            }
            return this->ind == other.ind;
        }

        /**
         * @brief Increments the index using the postfix form.
         *
         * @param unused Unused placeholder for postfix semantics.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator++(int)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot increment index: index is invalid");
            }
            ind++;
        }

        /**
         * @brief Decrements the index using the postfix form.
         *
         * @param unused Unused placeholder for postfix semantics.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator--(int)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot decrement index: index is invalid");
            }
            ind--;
        }

        /**
         * @brief Increments the index using the prefix form.
         *
         * @throws std::runtime_error if the index is invalid.
         */
        procedure(operator++)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot increment index: index is invalid");
            }
            ++ind;
        }

        /**
         * @brief Decrements the index using the prefix form.
         *
         * @throws std::runtime_error if the index is invalid.
         */
        procedure(operator--)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot decrement index: index is invalid");
            }
            --ind;
        }

        /**
         * @brief Adds an offset to the index.
         *
         * @param offset The offset value to add.
         * @return The resulting numeric value.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator+(size_t offset) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot add to index: index is invalid");
            }
            return ind + offset;
        }

        /**
         * @brief Adds another index value to this index.
         *
         * @param other The other index to add.
         * @return A new index containing the summed value.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator+(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot add indices: one or both indices are invalid");
            }
            return index(this->ind + other.ind);
        }

        /**
         * @brief Subtracts an offset from the index.
         *
         * @param offset The offset value to subtract.
         * @return The resulting numeric value.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator-(size_t offset) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot subtract from index: index is invalid");
            }
            return ind - offset;
        }

        /**
         * @brief Subtracts another index value from this index.
         *
         * @param other The other index to subtract.
         * @return A new index containing the difference.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator-(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot subtract indices: one or both indices are invalid");
            }
            return index(this->ind - other.ind);
        }

        /**
         * @brief Multiplies the index by a scalar factor.
         *
         * @param factor The multiplication factor.
         * @return The resulting numeric value.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator*(size_t factor) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot multiply index: index is invalid");
            }
            return ind * factor;
        }

        /**
         * @brief Multiplies this index by another index.
         *
         * @param other The other index to multiply with.
         * @return A new index containing the product.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator*(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot multiply indices: one or both indices are invalid");
            }
            return index(this->ind * other.ind);
        }

        /**
         * @brief Divides the index by a scalar divisor.
         *
         * @param divisor The divisor value.
         * @return The resulting numeric value.
         * @throws std::runtime_error if the index is invalid or the divisor is zero.
         */
        size_t operator/(size_t divisor) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot divide index: index is invalid");
            }
            if (divisor == 0)
            {
                throw std::runtime_error("Cannot divide index by zero");
            }
            return ind / divisor;
        }

        /**
         * @brief Divides this index by another index.
         *
         * @param other The other index to divide by.
         * @return A new index containing the quotient.
         * @throws std::runtime_error if either index is invalid or the divisor is zero.
         */
        index operator/(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot divide indices: one or both indices are invalid");
            }
            if (other.ind == 0)
            {
                throw std::runtime_error("Cannot divide index by zero");
            }
            return index(this->ind / other.ind);
        }

        /**
         * @brief Adds an offset to the current index in place.
         *
         * @param offset The offset value to add.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator+=(size_t offset)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot add to index: index is invalid");
            }
            ind += offset;
        }

        /**
         * @brief Adds another index to this index in place.
         *
         * @param other The other index to add.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator+=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot add indices: one or both indices are invalid");
            }
            this->ind += other.ind;
        }

        /**
         * @brief Subtracts an offset from the current index in place.
         *
         * @param offset The offset value to subtract.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator-=(size_t offset)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot subtract from index: index is invalid");
            }
            ind -= offset;
        }

        /**
         * @brief Subtracts another index from this index in place.
         *
         * @param other The other index to subtract.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator-=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot subtract indices: one or both indices are invalid");
            }
            this->ind -= other.ind;
        }

        /**
         * @brief Multiplies the current index by a scalar factor in place.
         *
         * @param factor The multiplication factor.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator*=(size_t factor)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot multiply index: index is invalid");
            }
            ind *= factor;
        }

        /**
         * @brief Multiplies this index by another index in place.
         *
         * @param other The other index to multiply with.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator*=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot multiply indices: one or both indices are invalid");
            }
            this->ind *= other.ind;
        }

        /**
         * @brief Divides the current index by a scalar divisor in place.
         *
         * @param divisor The divisor value.
         * @throws std::runtime_error if the index is invalid or the divisor is zero.
         */
        void operator/=(size_t divisor)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot divide index: index is invalid");
            }
            if (divisor == 0)
            {
                throw std::runtime_error("Cannot divide index by zero");
            }
            ind /= divisor;
        }

        /**
         * @brief Divides this index by another index in place.
         *
         * @param other The other index to divide by.
         * @throws std::runtime_error if either index is invalid or the divisor is zero.
         */
        void operator/=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot divide indices: one or both indices are invalid");
            }
            if (other.ind == 0)
            {
                throw std::runtime_error("Cannot divide index by zero");
            }
            this->ind /= other.ind;
        }

        /**
         * @brief Computes the modulo of the index by a scalar divisor.
         *
         * @param divisor The divisor value.
         * @return The remainder after division.
         * @throws std::runtime_error if the index is invalid or the divisor is zero.
         */
        size_t operator%(size_t divisor) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot modulo index: index is invalid");
            }
            if (divisor == 0)
            {
                throw std::runtime_error("Cannot modulo index by zero");
            }
            return ind % divisor;
        }

        /**
         * @brief Computes the modulo of this index by another index.
         *
         * @param other The other index to use as the divisor.
         * @return A new index containing the remainder.
         * @throws std::runtime_error if either index is invalid or the divisor is zero.
         */
        index operator%(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot modulo indices: one or both indices are invalid");
            }
            if (other.ind == 0)
            {
                throw std::runtime_error("Cannot modulo index by zero");
            }
            return index(this->ind % other.ind);
        }

        /**
         * @brief Applies a logical AND operation with a scalar mask.
         *
         * @param mask The mask value.
         * @return The result of the operation.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator&&(size_t mask) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot logical AND index: index is invalid");
            }
            return ind && mask;
        }

        /**
         * @brief Applies a logical AND operation with another index.
         *
         * @param other The other index to combine with.
         * @return A new index containing the result.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator&&(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot logical AND indices: one or both indices are invalid");
            }
            return index(this->ind && other.ind);
        }

        /**
         * @brief Applies a logical OR operation with a scalar mask.
         *
         * @param mask The mask value.
         * @return The result of the operation.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator||(size_t mask) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot logical OR index: index is invalid");
            }
            return ind || mask;
        }

        /**
         * @brief Applies a logical OR operation with another index.
         *
         * @param other The other index to combine with.
         * @return A new index containing the result.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator||(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot logical OR indices: one or both indices are invalid");
            }
            return index(this->ind || other.ind);
        }

        /**
         * @brief Applies a bitwise XOR operation with a scalar mask.
         *
         * @param mask The mask value.
         * @return The result of the operation.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator^(size_t mask) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR index: index is invalid");
            }
            return ind ^ mask;
        }

        /**
         * @brief Applies a bitwise XOR operation with another index.
         *
         * @param other The other index to combine with.
         * @return A new index containing the result.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator^(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR indices: one or both indices are invalid");
            }
            return index(this->ind ^ other.ind);
        }

        /**
         * @brief Applies a bitwise AND update with a scalar mask.
         *
         * @param mask The mask value.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator&=(size_t mask)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise AND index: index is invalid");
            }
            ind &= mask;
        }

        /**
         * @brief Applies a bitwise AND update with another index.
         *
         * @param other The other index to combine with.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator&=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise AND indices: one or both indices are invalid");
            }
            this->ind &= other.ind;
        }

        /**
         * @brief Applies a bitwise OR update with a scalar mask.
         *
         * @param mask The mask value.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator|=(size_t mask)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise OR index: index is invalid");
            }
            ind |= mask;
        }

        /**
         * @brief Applies a bitwise OR update with another index.
         *
         * @param other The other index to combine with.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator|=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise OR indices: one or both indices are invalid");
            }
            this->ind |= other.ind;
        }

        /**
         * @brief Applies a bitwise XOR update with a scalar mask.
         *
         * @param mask The mask value.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator^=(size_t mask)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR index: index is invalid");
            }
            ind ^= mask;
        }

        /**
         * @brief Applies a bitwise XOR update with another index.
         *
         * @param other The other index to combine with.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator^=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR indices: one or both indices are invalid");
            }
            this->ind ^= other.ind;
        }

        /**
         * @brief Shifts the index left by a scalar amount.
         *
         * @param shift The number of bit positions to shift.
         * @return The shifted result.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator<<(size_t shift) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot left shift index: index is invalid");
            }
            return ind << shift;
        }

        /**
         * @brief Shifts this index left by another index.
         *
         * @param other The shift amount.
         * @return A new index containing the shifted value.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator<<(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot left shift indices: one or both indices are invalid");
            }
            return index(this->ind << other.ind);
        }

        /**
         * @brief Shifts the index right by a scalar amount.
         *
         * @param shift The number of bit positions to shift.
         * @return The shifted result.
         * @throws std::runtime_error if the index is invalid.
         */
        size_t operator>>(size_t shift) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot right shift index: index is invalid");
            }
            return ind >> shift;
        }

        /**
         * @brief Shifts this index right by another index.
         *
         * @param other The shift amount.
         * @return A new index containing the shifted value.
         * @throws std::runtime_error if either index is invalid.
         */
        index operator>>(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot right shift indices: one or both indices are invalid");
            }
            return this->ind >> other.ind;
        }

        /**
         * @brief Shifts the index left by a scalar amount in place.
         *
         * @param shift The number of bit positions to shift.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator<<=(size_t shift)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot left shift index: index is invalid");
            }
            ind <<= shift;
        }

        /**
         * @brief Shifts this index left by another index in place.
         *
         * @param other The shift amount.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator<<=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot left shift indices: one or both indices are invalid");
            }
            this->ind <<= other.ind;
        }

        /**
         * @brief Shifts the index right by a scalar amount in place.
         *
         * @param shift The number of bit positions to shift.
         * @throws std::runtime_error if the index is invalid.
         */
        void operator>>=(size_t shift)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot right shift index: index is invalid");
            }
            ind >>= shift;
        }

        /**
         * @brief Shifts this index right by another index in place.
         *
         * @param other The shift amount.
         * @throws std::runtime_error if either index is invalid.
         */
        void operator>>=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot right shift indices: one or both indices are invalid");
            }
            this->ind >>= other.ind;
        }

        /**
         * @brief Toggles the validity state of the index.
         */
        void operator~() noexcept { is_valid = !is_valid; }

        /**
         * @brief Converts the index to a raw size_t value.
         *
         * @return The stored numerical value.
         * @throws std::runtime_error if the index is invalid.
         */
        operator size_t() const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot convert to size_t: index is invalid");
            }
            return ind;
        }
    };

    /**
     * @brief Creates an index object from a value of any arithmetic type.
     *
     * @tparam T The source value type.
     * @param value The value to convert.
     * @return An index containing the converted value.
     */
    template <typename T>
    index cast2index(const T &value) { return index(static_cast<size_t>(value)); }
}

#endif // OPENUDT___BASIC___indHPP