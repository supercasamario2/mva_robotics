
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <Eigen/Dense>

namespace py = pybind11;

Eigen::Matrix3d identity() {
    return Eigen::Matrix3d::Identity();
}

PYBIND11_MODULE(mva_robotics, m) {
    m.def("identity", &identity);
}
