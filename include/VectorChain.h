#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

class VectorChain {
public:
    VectorChain() = default;

    void push_back(bool value)
    { values_.push_back(value); }

    std::size_t size() const noexcept
    { return values_.size(); }

    bool contains(std::size_t index) const noexcept
    { return index < values_.size() && values_[index]; }

    VectorChain conjunctWith(const VectorChain& other) const
    {
        if (size() != other.size()) {
            throw std::invalid_argument("VectorChain sizes must be equal for conjunction");
        }

        VectorChain result;
        result.values_.reserve(size());
        for (std::size_t index = 0; index < size(); ++index) {
            result.values_.push_back(values_[index] && other.values_[index]);
        }

        return result;
    }

    double sum(const std::vector<float>& weights) const
    {
        if (weights.size() != size()) {
            throw std::invalid_argument("Weights size must match VectorChain size");
        }

        double total = 0.0;
        for (std::size_t index = 0; index < size(); ++index) {
            if (values_[index]) {
                total += weights[index];
            }
        }

        return total;
    }

private:
    std::vector<bool> values_;
};