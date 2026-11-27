#include <Eigen/Dense>
#include "drake/solvers/mathematical_program.h"
#include "drake/solvers/mosek_solver.h"
#include "drake/solvers/solve.h"
#include "drake/common/symbolic/expression.h"
#include "drake/geometry/optimization/graph_of_convex_sets.h"
#include <iostream>

using drake::solvers::MathematicalProgram;
using drake::solvers::MosekSolver;
using drake::solvers::MosekSolverDetails;

int main(){
    MathematicalProgram leProgramme;
    const auto x = leProgramme.NewContinuousVariables<2>("x");
    leProgramme.AddConstraint(x(0) >= 5.);
    leProgramme.AddQuadraticCost(Eigen::Matrix2d::Identity(), Eigen::Vector2d::Zero(), x);

    MosekSolver solver;
    std::cout << "test mosek " << solver.is_available() << std::endl;
    std::cout << "test mosek " << solver.is_enabled() << std::endl;
    auto sol = solver.Solve(leProgramme);
    std::cout << sol.is_success() << std::endl;
    std::cout << sol.GetSolution(x) << std::endl;

    return 0;
}
