#include "hw_timer.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
  uint8_t val;
  uint8_t mode;
  hw_timer_func_t* cb;
} hw_timer_8_bit_output_t;

typedef struct {
  uint16_t val;
  uint16_t mode;
  hw_timer_func_t* cb;
} hw_timer_16_bit_output_t;

typedef struct {
  bool edge_select;
  bool noise_cancel;
  hw_timer_func_t* cb;
} hw_timer_input_t;

static hw_timer_func_t hw_timer_0_compa_func = {0};
static hw_timer_func_t hw_timer_0_compb_func = {0};
static hw_timer_func_t hw_timer_0_ovf_func = {0};

static hw_timer_func_t hw_timer_1_compa_func = {0};
static hw_timer_func_t hw_timer_1_compb_func = {0};
static hw_timer_func_t hw_timer_1_ovf_func = {0};
static hw_timer_func_t hw_timer_1_capt_func = {0};

static hw_timer_func_t hw_timer_2_compa_func = {0};
static hw_timer_func_t hw_timer_2_compb_func = {0};
static hw_timer_func_t hw_timer_2_ovf_func = {0};

static void hw_timer_0_install(uint8_t wave_gen_mode, unsigned prescaler,
                               hw_timer_func_t* overflow_cb,
                               hw_timer_8_bit_output_t* output_a,
                               hw_timer_8_bit_output_t* output_b)
    __attribute__((unused));

static void hw_timer_1_install(uint8_t wave_gen_mode, unsigned prescaler,
                               hw_timer_func_t* overflow_cb,
                               hw_timer_16_bit_output_t* output_a,
                               hw_timer_16_bit_output_t* output_b,
                               hw_timer_input_t* input) __attribute__((unused));

static void hw_timer_2_install(uint8_t wave_gen_mode, unsigned prescaler,
                               hw_timer_func_t* overflow_cb,
                               hw_timer_8_bit_output_t* output_a,
                               hw_timer_8_bit_output_t* output_b)
    __attribute__((unused));

static uint8_t hw_timer_0_prescaler_to_clock_select(unsigned prescaler);

static uint8_t (*hw_timer_1_prescaler_to_clock_select)(unsigned prescaler) =
    &hw_timer_0_prescaler_to_clock_select;

static uint8_t hw_timer_2_prescaler_to_clock_select(unsigned prescaler);

void hw_timer_create(hw_timer_func_t* func, unsigned time_ms) {
  hw_timer_1_install(
      4, 1024, NULL,
      &(hw_timer_16_bit_output_t){F_CPU / 1024 / 1000 * time_ms - 1, 0, func},
      NULL, NULL);
}

static uint8_t hw_timer_0_prescaler_to_clock_select(unsigned prescaler) {
  switch (prescaler) {
    case 1:
      return 1;
    case 8:
      return 2;
    case 64:
      return 3;
    case 256:
      return 4;
    case 1024:
      return 5;
    default:
      return 0;
  }
}

static uint8_t hw_timer_2_prescaler_to_clock_select(unsigned prescaler) {
  switch (prescaler) {
    case 1:
      return 1;
    case 8:
      return 2;
    case 32:
      return 3;
    case 64:
      return 4;
    case 128:
      return 5;
    case 256:
      return 6;
    case 1024:
      return 7;
    default:
      return 0;
  }
}

static void hw_timer_0_install(uint8_t wave_gen_mode, unsigned prescaler,
                               hw_timer_func_t* overflow_cb,
                               hw_timer_8_bit_output_t* output_a,
                               hw_timer_8_bit_output_t* output_b) {
  uint8_t clock_select = hw_timer_0_prescaler_to_clock_select(prescaler);
  TCCR0A = (((wave_gen_mode >> 0) & 1u) << WGM00) |  //
           (((wave_gen_mode >> 1) & 1u) << WGM01);   //
  TCCR0B = (clock_select << CS00) | (((wave_gen_mode >> 2) & 1u) << WGM02);
  TCNT0 = 0;
  if (output_a) {
    hw_timer_1_compa_func = *output_a->cb;
    TCCR0A |= output_a->mode << COM0A0;
    OCR0A = output_a->val;
    TIMSK0 |= 1 << OCIE0A;
  }
  if (output_b) {
    hw_timer_1_compb_func = *output_b->cb;
    TCCR0A |= output_b->mode << COM0B0;
    OCR0B = output_b->val;
    TIMSK0 |= 1 << OCIE0B;
  }
  if (overflow_cb) {
    hw_timer_1_ovf_func = *overflow_cb;
    TIMSK0 |= 1 << TOIE0;
  }
}

static void hw_timer_1_install(uint8_t wave_gen_mode, unsigned prescaler,
                               hw_timer_func_t* overflow_cb,
                               hw_timer_16_bit_output_t* output_a,
                               hw_timer_16_bit_output_t* output_b,
                               hw_timer_input_t* input) {
  uint8_t clock_select = hw_timer_1_prescaler_to_clock_select(prescaler);
  TCCR1A = (((wave_gen_mode >> 0) & 1u) << WGM10) |  //
           (((wave_gen_mode >> 1) & 1u) << WGM11);   //
  TCCR1B = (clock_select << CS10) |                  //
           (((wave_gen_mode >> 2) & 1u) << WGM12) |  //
           (((wave_gen_mode >> 3) & 1u) << WGM13);   //
  TCNT1 = 0;
  if (output_a) {
    hw_timer_1_compa_func = *output_a->cb;
    TCCR1A |= output_a->mode << COM1A0;
    OCR1A = output_a->val;
    TIMSK1 |= 1 << OCIE1A;
  }
  if (output_b) {
    hw_timer_1_compb_func = *output_b->cb;
    TCCR1A |= output_b->mode << COM1B0;
    OCR1B = output_b->val;
    TIMSK1 |= 1 << OCIE1B;
  }
  if (input) {
    hw_timer_1_capt_func = *input->cb;
    TCCR1B |= (input->edge_select << ICES1) | (input->noise_cancel << ICNC1);
    TIMSK1 |= 1 << ICIE1;
  }
  if (overflow_cb) {
    hw_timer_1_ovf_func = *overflow_cb;
    TIMSK1 |= 1 << TOIE1;
  }
}

static void hw_timer_2_install(uint8_t wave_gen_mode, unsigned prescaler,
                               hw_timer_func_t* overflow_cb,
                               hw_timer_8_bit_output_t* output_a,
                               hw_timer_8_bit_output_t* output_b) {
  uint8_t clock_select = hw_timer_2_prescaler_to_clock_select(prescaler);
  TCCR2A = (((wave_gen_mode >> 0) & 1u) << WGM20) |  //
           (((wave_gen_mode >> 1) & 1u) << WGM21);   //
  TCCR2B = (clock_select << CS20) | (((wave_gen_mode >> 2) & 1u) << WGM22);
  TCNT2 = 0;
  if (output_a) {
    hw_timer_1_compa_func = *output_a->cb;
    TCCR2A |= output_a->mode << COM2A0;
    OCR2A = output_a->val;
    TIMSK2 |= 1 << OCIE2A;
  }
  if (output_b) {
    hw_timer_1_compb_func = *output_b->cb;
    TCCR2A |= output_b->mode << COM2B0;
    OCR2B = output_b->val;
    TIMSK2 |= 1 << OCIE2B;
  }
  if (overflow_cb) {
    hw_timer_1_ovf_func = *overflow_cb;
    TIMSK2 |= 1 << TOIE2;
  }
}

ISR(TIMER0_COMPA_vect) { hw_timer_0_compa_func.ref(hw_timer_0_compa_func.arg); }

ISR(TIMER0_COMPB_vect) { hw_timer_0_compb_func.ref(hw_timer_0_compb_func.arg); }

ISR(TIMER0_OVF_vect) { hw_timer_0_ovf_func.ref(hw_timer_0_ovf_func.arg); }

ISR(TIMER1_COMPA_vect) { hw_timer_1_compa_func.ref(hw_timer_1_compa_func.arg); }

ISR(TIMER1_COMPB_vect) { hw_timer_1_compb_func.ref(hw_timer_1_compb_func.arg); }

ISR(TIMER1_OVF_vect) { hw_timer_1_ovf_func.ref(hw_timer_1_ovf_func.arg); }

ISR(TIMER1_CAPT_vect) { hw_timer_1_capt_func.ref(hw_timer_1_capt_func.arg); }

ISR(TIMER2_COMPA_vect) { hw_timer_2_compa_func.ref(hw_timer_2_compa_func.arg); }

ISR(TIMER2_COMPB_vect) { hw_timer_2_compb_func.ref(hw_timer_2_compb_func.arg); }

ISR(TIMER2_OVF_vect) { hw_timer_2_ovf_func.ref(hw_timer_2_ovf_func.arg); }