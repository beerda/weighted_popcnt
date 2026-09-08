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
        if (size_ % bitsPerWord == 0) {
            words_.push_back(0);
        }

        if (value) {
            words_.back() |= wordType{1} << (size_ % bitsPerWord);
        }

        ++size_;
    }

    std::size_t size() const noexcept
    { return size_; }

    bool contains(std::size_t index) const noexcept
    {
        return index < size_
            && (words_[index / bitsPerWord]
                & (wordType{1} << (index % bitsPerWord))) != 0;
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
            if (bit_index == bitsPerWord) {
                ++word_index;
                bit_index = 0;
            }

            if ((words_[word_index] & (wordType{1} << bit_index)) != 0) {
                total += weights[index];
            }

            ++bit_index;
        }

        return total;
    }

    double sum(const std::vector<float>& partialSums,
               const size_t querySize) const
    {
        size_t maxQuery = (1 << querySize) - 1;
        size_t nBlocks = size_ / querySize;

        if (size_ % querySize != 0) {
            throw std::invalid_argument("BitChain size must be a multiple of query size");
        }
        if (partialSums.size() != maxQuery * nBlocks) {
            throw std::invalid_argument("Partial sums size must match BitChain size and query size");
        }

        double total = 0.0;
        for (size_t block = 0; block < nBlocks; ++block) {
            size_t bitIndex = block * querySize;
            size_t pos = bitIndex / bitsPerWord;
            size_t offset = bitIndex % bitsPerWord;
            size_t query = (words_[pos] >> offset) & maxQuery;
            if (query > 0) {
                total += partialSums[block * maxQuery + query - 1];
            }
        }

        return total;
    }

    static std::vector<float> createPartialSums(const std::vector<float>& weights,
                                                const size_t querySize)
    {
        if (weights.size() % querySize != 0) {
            throw std::invalid_argument("Weights size must be a multiple of query size");
        }

        size_t maxQuery = (1 << querySize) - 1;
        size_t nBlocks = weights.size() / querySize;
        std::vector<float> result(maxQuery * nBlocks, 0.0F);
        for (size_t q = 1; q <= maxQuery; ++q) {
            for (size_t bit = 0; bit < querySize; ++bit) {
                if ((q & (1 << bit)) != 0) {
                    for (size_t block = 0; block < nBlocks; ++block) {
                        result[block * maxQuery + q - 1] += weights[block * querySize + bit];
                    }
                }
            }
        }

        return result;
    }

private:
    using wordType = std::uint64_t;
    static constexpr std::size_t bitsPerWord = sizeof(wordType) * 8;

    std::size_t size_ = 0;
    std::vector<wordType> words_;
};