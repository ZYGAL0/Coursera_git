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
    [[nodiscard]] virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};

class EmptyNode : public Node {
public:
    [[nodiscard]] bool Evaluate(const Date &date, const std::string &event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &cmp, const Date &date);

    [[nodiscard]] bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const Date date_;
    const Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &cmp, std::string event);

    [[nodiscard]] bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const std::string event_;
    const Comparison cmp_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &op, const std::shared_ptr<Node> &left, const std::shared_ptr<Node> &right);

    [[nodiscard]] bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const LogicalOperation op_;
    std::shared_ptr<const Node> left_, right_;
};