// bindings/ou_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/OU.hpp"

void init_ou(py::module &m)
{
    py::class_<OU, StochasticProcess>(m, "OU")
        .def(py::init<>())
        .def(py::init<double, double, double>(),
             py::arg("kappa"), py::arg("theta"), py::arg("sigma"))
        .def("drift", &OU::drift, py::arg("t"), py::arg("x"))
        .def("diffusion", &OU::diffusion, py::arg("t"), py::arg("x"))
        .def("diffusion_derivative", &OU::diffusion_derivative,
             py::arg("t"), py::arg("x"))
        .def("sample_terminal", &OU::sample_terminal,
             py::arg("X0"), py::arg("T"), py::arg("rng"))
        .def("reversion_speed",
             static_cast<void (OU::*)(double)>(&OU::reversion_speed), py::arg("kappa"))
        .def("reversion_speed",
             static_cast<double (OU::*)() const>(&OU::reversion_speed))
        .def("mean_level",
             static_cast<void (OU::*)(double)>(&OU::mean_level), py::arg("theta"))
        .def("mean_level",
             static_cast<double (OU::*)() const>(&OU::mean_level))
        .def("vol_param",
             static_cast<void (OU::*)(double)>(&OU::vol_param), py::arg("sigma"))
        .def("vol_param",
             static_cast<double (OU::*)() const>(&OU::vol_param));
}
