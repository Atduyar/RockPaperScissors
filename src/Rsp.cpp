#include "Rsp.h"

#include <iostream>

const char* ToString(RPS rps) {
    switch (rps) {
        case Rock:
            return "rock";
        case Paper:
            return "paper";
        case Scissors:
            return "scissors";
        default:
            return "[Unknown RSP_type]";
    }
}

RPS GetEnemy(RPS rps) {
    if (rps == Scissors) {
        return Rock;
    } else
        return (RPS)(rps + 1);
}
RPS GetPrey(RPS rps) {
    if (rps == Rock) {
        return Scissors;
    } else
        return (RPS)(rps - 1);
}

RPS operator>>(RPS root, RPS (*func)(RPS)) { return func(root); }
std::ostream& operator<<(std::ostream& os, const RPS& rsp) {
    os << "RSP: " << ToString(rsp);
    return os;
}
