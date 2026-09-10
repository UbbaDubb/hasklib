// bindings/cir_bindings.cpp
#include "bindings.hpp"
#include "hasklib/stochastic/CIR.hpp"

// Note: CIR has no sample_terminal — unlike GBM/OU/ABM, it has no closed-form
// exact sampler implemented yet, so there is nothing to bind for it here.
void init_cir(py::module &m)
{
    py::class_<CIR, StochasticProcess>(m, "CIR")
        .def(py::init<>())
        .def(py::init<double, double, double>(),
             py::arg("kappa"), py::arg("theta"), py::arg("sigma"))
        .def("drift", &CIR::drift, py::arg("t"), py::arg("x"))
        .def("diffusion", &CIR::diffusion, py::arg("t"), py::arg("x"))
        .def("diffusion_derivative", &CIR::diffusion_derivative,
             py::arg("t"), py::arg("x"))
        .def("reversion_speed",
             static_cast<void (CIR::*)(double)>(&CIR::reversion_speed), py::arg("kappa"))
        .def("reversion_speed",
             static_cast<double (CIR::*)() const>(&CIR::reversion_speed))
        .def("mean_level",
             static_cast<void (CIR::*)(double)>(&CIR::mean_level), py::arg("theta"))
        .def("mean_level",
             static_cast<double (CIR::*)() const>(&CIR::mean_level))
        .def("vol_param",
             static_cast<void (CIR::*)(double)>(&CIR::vol_param), py::arg("sigma"))
        .def("vol_param",
             static_cast<double (CIR::*)() const>(&CIR::vol_param));
}
