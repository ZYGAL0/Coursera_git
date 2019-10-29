#include "node.h"

#include <utility>

bool EmptyNode::Evaluate(const std::string &date, const std::string &event) const {
    return true;
}

EventComparisonNode::EventComparisonNode(Comparison cmp, std::string event) : cmp_(cmp), event_(std::move(event)) {}

bool EventComparisonNode::Evaluate(const std::string &date, const std::string &event) const {
    return Compare(event, event_, cmp_);
}

DateComparisonNode::DateComparisonNode(Comparison cmp, std::string date) : cmp_(cmp), date_(std::move(date)) {}

bool DateComparisonNode::Evaluate(const std::string &date, const std::string &event) const {
    return Compare(date, date_, cmp_);
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, const std::shared_ptr<Node> &left,
                                           const std::shared_ptr<Node> &right) : op_(op), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const std::string &date, const std::string &event) const {
    if (LogicalOperation::Or == op_) {
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    } else {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
}