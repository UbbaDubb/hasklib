// bindings/milstein_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/Milstein.hpp"

void init_milstein(py::module &m)
{
    py::class_<Milstein>(m, "Milstein")
        .def(py::init<>())
        .def("step", &Milstein::step,
             py::arg("process"), py::arg("t"), py::arg("x"),
             py::arg("dt"), py::arg("z"))
        .def("simulate_terminal", &Milstein::simulate_terminal,
             py::arg("process"), py::arg("x0"), py::arg("T"),
             py::arg("N"), py::arg("rng"));
}
