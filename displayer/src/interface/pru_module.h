typedef struct pru_module_t;
extern pru_module_t* pru_module_new(uint32_t num_leds);
extern void pru_module_update(pru_module_t* pru_module, uint32_t* new_data);
extern void pru_module_shutdown(pru_module_t* pru_module)