#include "node.h"

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &op, const std::shared_ptr<Node> &left,
                                           const std::shared_ptr<Node> &right) : op_(op), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    if (LogicalOperation::Or == op_) {
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    } else {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp, std::string event) : cmp_(cmp), event_(std::move(event)) {}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    if (cmp_ == Comparison::Equal) {
        return event == event_;
    } else {
        return event != event_;
    }
}

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date) : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    if (cmp_ == Comparison::Less) {
        return date < date_;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return date <= date_;
    } else if (cmp_ == Comparison::Greater) {
        return date > date_;
    } else if (cmp_ == Comparison::Equal) {
        return date == date_;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return date >= date_;
    } else {
        return date != date_;
    }
}

bool EmptyNode::Evaluate(const Date &date, const std::string &event) const {
    return true;
}
