// bindings/normal_rng_bindings.cpp
#include "bindings.hpp"
#include "hasklib/random/NormalRng.hpp"

void init_normal_rng(py::module &m)
{
    py::class_<NormalRng>(m, "NormalRng")
        .def(py::init<>())
        .def(py::init<unsigned int>(), py::arg("seed"))
        .def("draw", &NormalRng::draw);
}