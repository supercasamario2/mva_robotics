#include <Eigen/Dense>
#include "drake/solvers/mathematical_program.h"
#include "drake/solvers/mosek_solver.h"
#include "drake/solvers/solve.h"
#include "drake/common/symbolic/expression.h"
#include "drake/geometry/optimization/graph_of_convex_sets.h"
#include "drake/geometry/optimization/hpolyhedron.h"
#include "drake/geometry/optimization/point.h"
#include <iostream>
#include <vector>

using drake::solvers::MathematicalProgram;
using drake::solvers::MosekSolver;
using drake::solvers::MosekSolverDetails;
using drake::geometry::optimization::HPolyhedron;
using drake::geometry::optimization::GraphOfConvexSets;
using drake::geometry::optimization::GraphOfConvexSetsOptions;
using drake::geometry::optimization::Point;

/*
    les régions Q_i sont des hpolyhedron (dans drake/geometry/optimization/hpolyhedron.h)
    --> donc la liste des régions = std vector de hpolyedron

    source / target = des vecteurs (avec eigen du coup)

*/
class baseGCS {
    
    public:
        std::vector<HPolyhedron> regions; // Q_i de l'article
        GraphOfConvexSets gcs;
        GraphOfConvexSetsOptions options;
        GraphOfConvexSets::Vertex* source = nullptr; // point de départ
        GraphOfConvexSets::Vertex* target = nullptr; // point d'arrivée

        baseGCS(std::vector<HPolyhedron> regions){
            std::copy(regions.begin(), regions.end(), std::back_inserter(this->regions));
        }
        baseGCS(){std::cout << "bonjour je suis le gcs" << std::endl;};

        void addSourceTarget(Eigen::VectorXd source, Eigen::VectorXd target){
            // j'ai séparé la condition en 2 cas jsp trop ce qu'il se passe si 
            // on donne nullptr à RemoveVertex et j'ai la flemme d'essayer

            // le paramètre "edges" n'est pas utilisé dans les programmes d'exemples sur le 
            // github de l'article, donc on peut le dégager je pense

            if(this->source != nullptr){
                this->gcs.RemoveVertex(this->source);
            }
            if(this->target != nullptr){
                this->gcs.RemoveVertex(this->target);
            }
            this->source = this->gcs.AddVertex(Point(source));
            std::cout << this->source->name() << std::endl;
        }

        void findStartGoalEdges(){
            
        }

};
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

    baseGCS gcs;
    Eigen::Vector3d jaaj(1, 2, 3);
    gcs.addSourceTarget(jaaj, jaaj);
    return 0;
}
