#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

class BitChain {
public:
    BitChain() = default;

    void push_back(bool value)
    {
        if (size_ % bits_per_word_ == 0) {
            words_.push_back(0);
        }

        if (value) {
            words_.back() |= word_type{1} << (size_ % bits_per_word_);
        }

        ++size_;
    }

    std::size_t size() const noexcept
    { return size_; }

    bool contains(std::size_t index) const noexcept
    {
        return index < size_
            && (words_[index / bits_per_word_]
                & (word_type{1} << (index % bits_per_word_))) != 0;
    }

    BitChain conjunctWith(const BitChain& other) const
    {
        if (size_ != other.size_) {
            throw std::invalid_argument("BitChain sizes must be equal for conjunction");
        }

        BitChain result;
        result.size_ = size_;
        result.words_.reserve(words_.size());
        for (std::size_t index = 0; index < words_.size(); ++index) {
            result.words_.push_back(words_[index] & other.words_[index]);
        }

        return result;
    }

    double sum(const std::vector<float>& weights) const
    {
        if (weights.size() != size_) {
            throw std::invalid_argument("Weights size must match BitChain size");
        }

        double total = 0.0;
        size_t word_index = 0;
        size_t bit_index = 0;
        for (size_t index = 0; index < size_; ++index) {
            if (bit_index == bits_per_word_) {
                ++word_index;
                bit_index = 0;
            }

            if ((words_[word_index] & (word_type{1} << bit_index)) != 0) {
                total += weights[index];
            }

            ++bit_index;
        }

        return total;
    }

private:
    using word_type = std::uint64_t;
    static constexpr std::size_t bits_per_word_ = sizeof(word_type) * 8;

    std::size_t size_ = 0;
    std::vector<word_type> words_;
};