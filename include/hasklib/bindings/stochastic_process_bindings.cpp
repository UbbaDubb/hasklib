// bindings/stochastic_process_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/StochasticProcess.hpp"

void init_stochasticprocess(py::module &m)
{
    py::class_<StochasticProcess>(m, "StochasticProcess")
        .def("drift", &StochasticProcess::drift, py::arg("t"), py::arg("x"))
        .def("diffusion", &StochasticProcess::diffusion, py::arg("t"), py::arg("x"))
        .def("diffusion_derivative", &StochasticProcess::diffusion_derivative,
             py::arg("t"), py::arg("x"));
}