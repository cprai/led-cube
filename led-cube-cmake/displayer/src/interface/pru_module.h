#pragma once

#include <cstdint>

namespace displayer {

struct pruss_t;
extern "C" pruss_t* pruss_new();

struct pru_module_t;
extern "C" pru_module_t* pru_module_new(pruss_t* pruss);
extern "C" void pru_module_update(pru_module_t* pru_module,pruss_t* pruss, uint32_t* new_data);
extern "C" void pru_module_shutdown(pru_module_t* pru_module,pruss_t* pruss);

}
