#pragma once

#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include "displayer/color.h"
#include "ledscape.h"

namespace displayer {

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} __attribute__((__packed__)) buffer_pixel_t;

typedef struct {
  int8_t r;
  int8_t g;
  int8_t b;

  int8_t last_effect_frame_r;
  int8_t last_effect_frame_g;
  int8_t last_effect_frame_b;
} __attribute__((__packed__)) pixel_delta_t;

typedef struct {
  char output_mode_name[512];
  char output_mapping_name[512];

  uint32_t leds_per_strip;
  uint32_t used_strip_count;

  color_channel_order_t color_channel_order;

  struct {
    float red;
    float green;
    float blue;
  } white_point;

  float lum_power;

  pthread_mutex_t mutex;
  char json[4096];
} server_config_t;

typedef struct
{
  buffer_pixel_t* previous_frame_data;
  buffer_pixel_t* current_frame_data;
  buffer_pixel_t* next_frame_data;

  uint8_t has_prev_frame;
  uint8_t has_current_frame;
  uint8_t has_next_frame;

  uint32_t frame_size;
  uint32_t leds_per_strip;

  volatile uint32_t frame_counter;

  struct timeval previous_frame_tv;
  struct timeval current_frame_tv;
  struct timeval next_frame_tv;

  struct timeval prev_current_delta_tv;

  ledscape_t * leds;

  char pru0_program_filename[4096];
  char pru1_program_filename[4096];

  uint32_t red_lookup[257];
  uint32_t green_lookup[257];
  uint32_t blue_lookup[257];

  struct timeval last_remote_data_tv;

  pthread_mutex_t mutex;
} g_runtime_state_t;

template<int LEDCount>
class Displayer {
public:
  Displayer() {
    printf("[main] Setting up global runtime data...");
    g_runtime_state = (g_runtime_state_t){
            .previous_frame_data = (buffer_pixel_t*)nullptr,
            .current_frame_data = (buffer_pixel_t*)nullptr,
            .next_frame_data = (buffer_pixel_t*)nullptr,
            .has_prev_frame = false,
            .has_current_frame = false,
            .has_next_frame = false,
            .frame_size = 0,
            .leds_per_strip = 0,
            .leds = nullptr,
            .last_remote_data_tv = {
                    .tv_sec = 0,
                    .tv_usec = 0
            },
            .mutex = PTHREAD_MUTEX_INITIALIZER
    };

    g_server_config = (server_config_t){
            "ws281x",
            "original-ledscape",

            LEDCount,
            LEDSCAPE_NUM_STRIPS,
            COLOR_ORDER_BRG,

            {.9, 1, 1},
            2,
            PTHREAD_MUTEX_INITIALIZER
    };


    printf("[main] Starting LEDscape...");
    g_runtime_state.leds = ledscape_init_with_programs(
            g_server_config.leds_per_strip,
            build_pruN_program_name(
                    g_server_config.output_mode_name,
                    g_server_config.output_mapping_name,
                    0,
                    g_runtime_state.pru0_program_filename,
                    sizeof(g_runtime_state.pru0_program_filename)
            ),

            build_pruN_program_name(
                    g_server_config.output_mode_name,
                    g_server_config.output_mapping_name,
                    1,
                    g_runtime_state.pru1_program_filename,
                    sizeof(g_runtime_state.pru1_program_filename)
            )
    );

    curr_strip = 0;


  }

  ~Displayer() {
//    pru_module_shutdown(pru_module);
  }

  void display(Color outputBuffer[LEDCount]) {
    //std::cout << "Call to display module" << std::endl;

    //std::cout << "Recieved output buffer:" << std::endl;

//    uint32_t interfaceBuffer[LEDCount];

//    for (int i = 0; i < LEDCount; i++) {
//      interfaceBuffer[i] = outputBuffer[i].asU32();
//
////      std::cout << std::hex << interfaceBuffer[i] << std::endl;
//    }

    // Setup LEDscape for this frame
    uint8_t buffer_index = 0;

    buffer_index = (buffer_index+1)% 2;

    ledscape_frame_t *const frame = ledscape_frame(g_runtime_state.leds, buffer_index);

    // Build the render frame
    uint32_t strip_count = g_server_config.used_strip_count;
//    uint32_t leds_per_strip = g_runtime_state.leds_per_strip;

    color_channel_order_t color_channel_order = g_server_config.color_channel_order;

    //printf("Current strip: %d\n", curr_strip);
    for (uint32_t led_index = 0; led_index < LEDCount; ++led_index) {
      ledscape_pixel_t *const pixel_out = &frame[led_index].strip[26];

      uint8_t current_r = outputBuffer[led_index].r * 255;
      uint8_t current_b = outputBuffer[led_index].b * 255;
      uint8_t current_g = outputBuffer[led_index].g * 255;
//      printf("RGB: %d, %d, %d\n", current_r, current_g, current_b);

      uint8_t r = (uint8_t) current_r < 255 ? current_r : 255;
      uint8_t g = (uint8_t) current_g < 255 ? current_g : 255;
      uint8_t b = (uint8_t) current_b < 255 ? current_b : 255;

      ledscape_pixel_set_color(
              pixel_out,
              color_channel_order,
              r,
              g,
              b
      );
    }
    curr_strip = (curr_strip+1) % strip_count;
    // Wait for previous send to complete if still in progress
    ledscape_wait(g_runtime_state.leds);
    // Send the frame to the PRU
    ledscape_draw(g_runtime_state.leds, buffer_index);

  }

private:

  const char* build_pruN_program_name(
          const char* output_mode_name,
          const char* output_mapping_name,
          uint8_t pruNum,
          char* out_pru_filename,
          int filename_len) {
    snprintf(
            out_pru_filename,
            filename_len,
            "pru/bin/%s-%s-pru%d.bin",
            output_mode_name,
            output_mapping_name,
            (int) pruNum
    );

    return out_pru_filename;
  }

  g_runtime_state_t g_runtime_state;

  server_config_t g_server_config;

  uint32_t curr_strip;

};


}
