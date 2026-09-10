// bindings/euler_maruyama_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/EulerMaruyama.hpp"

void init_euler_maruyama(py::module &m)
{
    py::class_<EulerMaruyama>(m, "EulerMaruyama")
        .def(py::init<>())
        .def("step", &EulerMaruyama::step,
             py::arg("process"), py::arg("t"), py::arg("x"),
             py::arg("dt"), py::arg("z"))
        .def("simulate_terminal", &EulerMaruyama::simulate_terminal,
             py::arg("process"), py::arg("x0"), py::arg("T"),
             py::arg("N"), py::arg("rng"));
}
