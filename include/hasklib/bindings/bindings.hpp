// bindings/bindings.hpp
#pragma once
#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_normal_rng(py::module &m);

void init_stochasticprocess(py::module &m);
void init_gbm(py::module &m);
void init_ou(py::module &m);
void init_abm(py::module &m);
void init_cir(py::module &m);
void init_euler_maruyama(py::module &m);
void init_milstein(py::module &m);