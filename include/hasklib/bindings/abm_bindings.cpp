// bindings/abm_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/ABM.hpp"

void init_abm(py::module &m)
{
    py::class_<ABM, StochasticProcess>(m, "ABM")
        .def(py::init<>())
        .def(py::init<double, double>(), py::arg("mu"), py::arg("sigma"))
        .def("drift", &ABM::drift, py::arg("t"), py::arg("x"))
        .def("diffusion", &ABM::diffusion, py::arg("t"), py::arg("x"))
        .def("diffusion_derivative", &ABM::diffusion_derivative,
             py::arg("t"), py::arg("x"))
        .def("sample_terminal", &ABM::sample_terminal,
             py::arg("X0"), py::arg("T"), py::arg("rng"))
        .def("drift_param",
             static_cast<void (ABM::*)(double)>(&ABM::drift_param), py::arg("mu"))
        .def("drift_param",
             static_cast<double (ABM::*)() const>(&ABM::drift_param))
        .def("vol_param",
             static_cast<void (ABM::*)(double)>(&ABM::vol_param), py::arg("sigma"))
        .def("vol_param",
             static_cast<double (ABM::*)() const>(&ABM::vol_param));
}
