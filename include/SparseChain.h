#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

class SparseChain {
public:
    SparseChain() = default;

    void push_back(bool value)
    {
        if (value) {
            indices_.push_back(size_);
        }

        ++size_;
    }

    std::size_t size() const noexcept
    { return size_; }

    bool contains(std::size_t index) const noexcept
    { return std::binary_search(indices_.begin(), indices_.end(), index); }

    SparseChain conjunctWith(const SparseChain& other) const
    {
        if (size_ != other.size_) {
            throw std::invalid_argument("SparseChain sizes must be equal for conjunction");
        }

        SparseChain result;
        result.size_ = size_;

        std::size_t left = 0;
        std::size_t right = 0;
        while (left < indices_.size() && right < other.indices_.size()) {
            if (indices_[left] == other.indices_[right]) {
                result.indices_.push_back(indices_[left]);
                ++left;
                ++right;
            } else if (indices_[left] < other.indices_[right]) {
                ++left;
            } else {
                ++right;
            }
        }

        return result;
    }

    double sum(const std::vector<float>& weights) const
    {
        if (weights.size() != size_) {
            throw std::invalid_argument("Weights size must match SparseChain size");
        }

        double total = 0.0;
        for (std::size_t index : indices_) {
            total += weights[index];
        }

        return total;
    }

private:
    std::size_t size_ = 0;
    std::vector<std::size_t> indices_;
};
