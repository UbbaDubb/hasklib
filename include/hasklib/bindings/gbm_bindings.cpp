// bindings/gbm_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/GBM.hpp"

void init_gbm(py::module &m)
{
    py::class_<GBM, StochasticProcess>(m, "GBM")
        .def(py::init<>())
        .def(py::init<double, double>(), py::arg("mu"), py::arg("sigma"))
        .def("drift", &GBM::drift, py::arg("t"), py::arg("x"))
        .def("diffusion", &GBM::diffusion, py::arg("t"), py::arg("x"))
        .def("diffusion_derivative", &GBM::diffusion_derivative,
             py::arg("t"), py::arg("x"))
        .def("sample_terminal", &GBM::sample_terminal,
             py::arg("S0"), py::arg("T"), py::arg("rng"))
        .def("drift_param",
             static_cast<void (GBM::*)(double)>(&GBM::drift_param), py::arg("mu"))
        .def("drift_param",
             static_cast<double (GBM::*)() const>(&GBM::drift_param))
        .def("vol_param",
             static_cast<void (GBM::*)(double)>(&GBM::vol_param), py::arg("sigma"))
        .def("vol_param",
             static_cast<double (GBM::*)() const>(&GBM::vol_param));
}
