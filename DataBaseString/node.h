#pragma once

#include "date.h"

#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:
    [[nodiscard]] virtual bool Evaluate(const std::string &date, const std::string &event) const = 0;

    template<typename T>
    [[nodiscard]] bool Compare(const T &first, const T &second, Comparison cmp) const {
        if (cmp == Comparison::Less) {
            return first < second;
        } else if (cmp == Comparison::LessOrEqual) {
            return first <= second;
        } else if (cmp == Comparison::Greater) {
            return first > second;
        } else if (cmp == Comparison::Equal) {
            return first == second;
        } else if (cmp == Comparison::GreaterOrEqual) {
            return first >= second;
        } else {
            return first != second;
        }
    }

};

class EmptyNode : public Node {
public:
    [[nodiscard]] bool Evaluate(const std::string &date, const std::string &event) const override;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, std::string event);

    [[nodiscard]] bool Evaluate(const std::string &date, const std::string &event) const override;

private:
    const std::string event_;
    const Comparison cmp_;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, std::string date);

    [[nodiscard]] bool Evaluate(const std::string &date, const std::string &event) const override;

private:
    const std::string date_;
    const Comparison cmp_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation op, const std::shared_ptr<Node> &left, const std::shared_ptr<Node> &right);

    [[nodiscard]] bool Evaluate(const std::string &date, const std::string &event) const override;

private:
    const LogicalOperation op_;
    std::shared_ptr<const Node> left_, right_;
};