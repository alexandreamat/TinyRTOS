#ifndef __TIMER_COUNTER_H__
#define __TIMER_COUNTER_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define TIMER_COUNTER_0_TCNT_MAX (UINT8_MAX)
#define TIMER_COUNTER_1_TCNT_MAX (UINT16_MAX)
#define TIMER_COUNTER_2_TCNT_MAX (UINT8_MAX)

/* ====== Type Definitions ====== */

typedef enum {
  TIMER_COUNTER_OUTPUT_MODE_NORMAL = 0,
} timer_counter_output_mode_t;

typedef enum {
  TIMER_COUNTER_0_WGM_NORMAL = 0,
  TIMER_COUNTER_0_WGM_CTC = 2,
} timer_counter_0_wgm_t;

typedef enum {
  TIMER_COUNTER_1_WGM_NORMAL = 0,
  TIMER_COUNTER_1_WGM_CTC_OCR = 4,
} timer_counter_1_wgm_t;

typedef enum {
  TIMER_COUNTER_2_WGM_NORMAL = 0,
  TIMER_COUNTER_2_WGM_CTC = 2,
} timer_counter_2_wgm_t;

typedef void (*timer_counter_func_t)(void);

typedef struct {
  uint8_t val;
  timer_counter_output_mode_t mode;
  timer_counter_func_t cb;
} timer_counter_8_bit_output_t;

typedef struct {
  uint16_t val;
  timer_counter_output_mode_t mode;
  timer_counter_func_t cb;
} timer_counter_16_bit_output_t;

typedef struct {
  bool edge_select;
  bool noise_cancel;
  timer_counter_func_t cb;
} timer_counter_input_t;

void timer_counter_0_set_attrs(timer_counter_0_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_8_bit_output_t* output_a,
                               timer_counter_8_bit_output_t* output_b);

void timer_counter_1_set_attrs(timer_counter_1_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_16_bit_output_t* output_a,
                               timer_counter_16_bit_output_t* output_b,
                               timer_counter_input_t* input);

void timer_counter_2_set_attrs(timer_counter_2_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_8_bit_output_t* output_a,
                               timer_counter_8_bit_output_t* output_b);

uint8_t timer_counter_0_get_count(void);

uint16_t timer_counter_1_get_count(void);

uint8_t timer_counter_2_get_count(void);

#endif  // __TIMER_COUNTER_H__
