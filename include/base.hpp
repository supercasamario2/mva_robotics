#ifndef BASE_GCS_HPP
#define BASE_GCS_HPP

#include <Eigen/Dense>
#include <vector>

#include "drake/geometry/optimization/graph_of_convex_sets.h"
#include "drake/geometry/optimization/hpolyhedron.h"
#include "drake/geometry/optimization/point.h"

using drake::geometry::optimization::HPolyhedron;
using drake::geometry::optimization::GraphOfConvexSets;
using drake::geometry::optimization::GraphOfConvexSetsOptions;
using drake::geometry::optimization::Point;

class baseGCS {
public:

    // Attributs
    std::vector<HPolyhedron> regions;
    GraphOfConvexSets gcs;
    GraphOfConvexSetsOptions options;

    GraphOfConvexSets::Vertex* source = nullptr;
    GraphOfConvexSets::Vertex* target = nullptr;

    // Constructeurs
    baseGCS(std::vector<HPolyhedron> regions);
    baseGCS();

    // Méthodes
    void addSourceTarget(Eigen::VectorXd source, Eigen::VectorXd target);
    void findStartGoalEdges();
};

#endif