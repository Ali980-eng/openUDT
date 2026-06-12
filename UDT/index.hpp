#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once
#ifndef OPENUDT___UDT_INDEX_HPP
#define OPENUDT___UDT_INDEX_HPP

namespace udt
{

    class index
    {
    private:
        size_t index_ = size_t();
        bool is_valid = true;

    public:
        index() = default;

        ~index() = default;

        index(size_t index) : index_(index), is_valid(true) {}

        index(const index &other) = default;

        index &operator=(const index &other) = default;

        void make_valid(size_t index) noexcept
        {
            this->index_ = index;
            is_valid = true;
        }

        void unvalidate() noexcept
        {
            is_valid = false;
            index_ = size_t();
        }

        bool is_valid() const noexcept
        {
            return is_valid;
        }

        void set(size_t index)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot set index: index is invalid");
            }
            this->index_ = index;
        }

        size_t get() const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Invalid index");
            }
            return index_;
        }

        bool validFor(const std::string &context) const noexcept
        {
            if (context.length() < index_)
                return false;
            return true;
        }

        template <typename Y>
        bool validFor(const std::vector<Y> &context) const noexcept
        {
            if (context.size() < index_)
                return false;
            return true;
        }

        void operator=(size_t index)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot assign index: index is invalid");
            }
            this->index_ = index;
        }

        bool operator!=(size_t index) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot compare index: index is invalid");
            }
            return this->index_ != index;
        }

        bool operator==(size_t index) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot compare index: index is invalid");
            }
            return this->index_ == index;
        }

        bool operator!=(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot compare indices: one or both indices are invalid");
            }
            return this->index_ != other.index_;
        }

        bool operator==(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot compare indices: one or both indices are invalid");
            }
            return this->index_ == other.index_;
        }

        void operator++(int)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot increment index: index is invalid");
            }
            index_++;
        }

        void operator--(int)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot decrement index: index is invalid");
            }
            index_--;
        }

        void operator++()
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot increment index: index is invalid");
            }
            ++index_;
        }

        void operator--()
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot decrement index: index is invalid");
            }
            --index_;
        }

        size_t operator+(size_t offset) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot add to index: index is invalid");
            }
            return index_ + offset;
        }

        index operator+(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot add indices: one or both indices are invalid");
            }
            return index(this->index_ + other.index_);
        }

        size_t operator-(size_t offset) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot subtract from index: index is invalid");
            }
            return index_ - offset;
        }

        index operator-(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot subtract indices: one or both indices are invalid");
            }
            return index(this->index_ - other.index_);
        }

        size_t operator*(size_t factor) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot multiply index: index is invalid");
            }
            return index_ * factor;
        }

        index operator*(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot multiply indices: one or both indices are invalid");
            }
            return index(this->index_ * other.index_);
        }

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
            return index_ / divisor;
        }

        index operator/(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot divide indices: one or both indices are invalid");
            }
            if (other.index_ == 0)
            {
                throw std::runtime_error("Cannot divide index by zero");
            }
            return index(this->index_ / other.index_);
        }

        void operator+=(size_t offset)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot add to index: index is invalid");
            }
            index_ += offset;
        }

        void operator+=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot add indices: one or both indices are invalid");
            }
            this->index_ += other.index_;
        }

        void operator-=(size_t offset)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot subtract from index: index is invalid");
            }
            index_ -= offset;
        }

        void operator-=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot subtract indices: one or both indices are invalid");
            }
            this->index_ -= other.index_;
        }

        void operator*=(size_t factor)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot multiply index: index is invalid");
            }
            index_ *= factor;
        }

        void operator*=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot multiply indices: one or both indices are invalid");
            }
            this->index_ *= other.index_;
        }

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
            index_ /= divisor;
        }

        void operator/=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot divide indices: one or both indices are invalid");
            }
            if (other.index_ == 0)
            {
                throw std::runtime_error("Cannot divide index by zero");
            }
            this->index_ /= other.index_;
        }

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
            return index_ % divisor;
        }

        index operator%(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot modulo indices: one or both indices are invalid");
            }
            if (other.index_ == 0)
            {
                throw std::runtime_error("Cannot modulo index by zero");
            }
            return index(this->index_ % other.index_);
        }

        size_t operator&&(size_t mask) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot logical AND index: index is invalid");
            }
            return index_ && mask;
        }

        index operator&&(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot logical AND indices: one or both indices are invalid");
            }
            return index(this->index_ && other.index_);
        }

        size_t operator||(size_t mask) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot logical OR index: index is invalid");
            }
            return index_ || mask;
        }

        index operator||(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot logical OR indices: one or both indices are invalid");
            }
            return index(this->index_ || other.index_);
        }

        size_t operator^(size_t mask) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR index: index is invalid");
            }
            return index_ ^ mask;
        }

        index operator^(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR indices: one or both indices are invalid");
            }
            return index(this->index_ ^ other.index_);
        }

        void operator&=(size_t mask)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise AND index: index is invalid");
            }
            index_ &= mask;
        }

        void operator&=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise AND indices: one or both indices are invalid");
            }
            this->index_ &= other.index_;
        }

        void operator|=(size_t mask)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise OR index: index is invalid");
            }
            index_ |= mask;
        }

        void operator|=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise OR indices: one or both indices are invalid");
            }
            this->index_ |= other.index_;
        }

        void operator^=(size_t mask)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR index: index is invalid");
            }
            index_ ^= mask;
        }

        void operator^=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot bitwise XOR indices: one or both indices are invalid");
            }
            this->index_ ^= other.index_;
        }

        size_t operator<<(size_t shift) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot left shift index: index is invalid");
            }
            return index_ << shift;
        }

        index operator<<(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot left shift indices: one or both indices are invalid");
            }
            return index(this->index_ << other.index_);
        }

        size_t operator>>(size_t shift) const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot right shift index: index is invalid");
            }
            return index_ >> shift;
        }

        index operator>>(const index &other) const
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot right shift indices: one or both indices are invalid");
            }
            return this->index_ >> other.index_;
        }

        void operator<<=(size_t shift)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot left shift index: index is invalid");
            }
            index_ <<= shift;
        }

        void operator<<=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot left shift indices: one or both indices are invalid");
            }
            this->index_ <<= other.index_;
        }

        void operator>>=(size_t shift)
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot right shift index: index is invalid");
            }
            index_ >>= shift;
        }

        void operator>>=(const index &other)
        {
            if (!this->is_valid || !other.is_valid)
            {
                throw std::runtime_error("Cannot right shift indices: one or both indices are invalid");
            }
            this->index_ >>= other.index_;
        }

        void operator~() noexcept { is_valid = !is_valid; }

        operator size_t() const
        {
            if (!is_valid)
            {
                throw std::runtime_error("Cannot convert to size_t: index is invalid");
            }
            return index_;
        }
    };

    template <typename T>
    index cast2index(const T &value) { return index(static_cast<size_t>(value)); }

}

#endif // OPENUDT___UDT_INDEX_HPP