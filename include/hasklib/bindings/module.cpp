// bindings/module.cpp
#include "bindings.hpp"

PYBIND11_MODULE(hasklib_py, m) {
    m.doc() = "hasklib stochastic module Python bindings";

    init_normal_rng(m);   // register NormalRng first — GBM/OU/ABM/CIR take it as a param type
    init_stochasticprocess(m);      // register StochasticProcess — base class GBM/OU/ABM/CIR inherit from
    init_gbm(m);           
    init_ou(m);            
    init_abm(m);           
    init_cir(m);            
    init_euler_maruyama(m); 
    init_milstein(m);       
}