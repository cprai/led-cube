#pragma once

#include <cstdint>

namespace displayer {

struct pru_module_t;
extern "C" pru_module_t* pru_module_new(uint32_t num_leds);
extern "C" void pru_module_update(pru_module_t* pru_module, uint32_t* new_data);
extern "C" void pru_module_shutdown(pru_module_t* pru_module);

}
