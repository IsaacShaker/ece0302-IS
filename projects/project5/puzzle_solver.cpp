#include "puzzle_solver.hpp"

#include <functional>
#include <unordered_set>

#include "frontier_queue.hpp"
#include "puzzle.hpp"
#include "state.hpp"

// specialize the std::hash function for Puzzles
// reference here: https://en.cppreference.com/w/cpp/language/extending_std
namespace std {
template <>
struct hash<Puzzle> {
    typedef Puzzle argument_type;
    typedef uint64_t result_type;

    result_type operator()(const argument_type &x) const { return x.hash(); }
};
}  // namespace std

PuzzleSolver::PuzzleSolver(const Puzzle &initialPuzzle,
                           const Puzzle &goalPuzzle)
    : initial(initialPuzzle), goal(goalPuzzle) {}

std::pair<bool, std::size_t> PuzzleSolver::search() {
    std::size_t solution_cost;

    frontier_queue<Puzzle> frontier;
    // TODO: instantiate explored as an unordered_set
    std::unordered_set<Puzzle> explored;

    frontier.push(initial, 0, initial.heuristic(goal));

    bool found = false;
    while (true) {
        if (frontier.empty()) {
            found = false;
            break;
        }

        auto node = frontier.pop();
        Puzzle value = node.getValue();
        // TODO: add state to explored
        explored.insert(value);

        std::size_t cost = node.getPathCost();

        if (value.heuristic(goal) == 0) {
            found = true;
            solution_cost = node.getPathCost();
            break;
        }

        for (int a = Puzzle::LEFT; a <= Puzzle::DOWN; ++a) {
            bool ok;
            Puzzle result;
            std::tie(ok, result) = value.apply(static_cast<Puzzle::Action>(a));

            if (ok) {
                // TODO: define in_explored as whether the result is in explored
                bool in_explored = explored.count(result);
                bool in_frontier = frontier.contains(result);
                if (!(in_explored || in_frontier)) {
                    frontier.push(result, cost + 1, result.heuristic(goal));
                } else if (in_frontier) {
                    frontier.replaceif(result, cost + 1);
                }
            }
        }
    }

    return std::make_pair(found, solution_cost);
}
