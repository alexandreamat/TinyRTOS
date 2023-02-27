#include "timer_counter.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* ====== Preprocessor Definitions ====== */

#define TIMER_COUNTER_0_TCNT_MAX (0xFF)
#define TIMER_COUNTER_1_TCNT_MAX (0xFFFF)
#define TIMER_COUNTER_2_TCNT_MAX (0xFF)

/* ====== Static Variables ====== */

static timer_counter_func_t timer_counter_0_compa_func = NULL;
static timer_counter_func_t timer_counter_0_compb_func = NULL;
static timer_counter_func_t timer_counter_0_ovf_func = NULL;

static timer_counter_func_t timer_counter_1_compa_func = NULL;
static timer_counter_func_t timer_counter_1_compb_func = NULL;
static timer_counter_func_t timer_counter_1_ovf_func = NULL;
static timer_counter_func_t timer_counter_1_capt_func = NULL;

static timer_counter_func_t timer_counter_2_compa_func = NULL;
static timer_counter_func_t timer_counter_2_compb_func = NULL;
static timer_counter_func_t timer_counter_2_ovf_func = NULL;

/* ====== Static Function Declarations ====== */

static uint8_t timer_counter_0_prescaler_to_clock_select(unsigned prescaler);

static uint8_t (*timer_counter_1_prescaler_to_clock_select)(
    unsigned prescaler) = &timer_counter_0_prescaler_to_clock_select;

static uint8_t timer_counter_2_prescaler_to_clock_select(unsigned prescaler);

/* ====== External Function Definitions ====== */

void timer_counter_0_set_attrs(timer_counter_0_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_8_bit_output_t* output_a,
                               timer_counter_8_bit_output_t* output_b) {
  TCCR0B = 0;
  if (output_a) {
    timer_counter_0_compa_func = *output_a->cb;
    TCCR0A |= output_a->mode << COM0A0;
    OCR0A = output_a->val;
    TIMSK0 |= 1 << OCIE0A;
  } else {
    timer_counter_0_compa_func = NULL;
    TIMSK0 &= ~(1 << OCIE0A);
  }
  if (output_b) {
    timer_counter_0_compb_func = *output_b->cb;
    TCCR0A |= output_b->mode << COM0B0;
    OCR0B = output_b->val;
    TIMSK0 |= 1 << OCIE0B;
  } else {
    timer_counter_0_compb_func = NULL;
    TIMSK0 &= ~(1 << OCIE0B);
  }
  if (overflow_cb) {
    timer_counter_0_ovf_func = *overflow_cb;
    TIMSK0 |= 1 << TOIE0;
  } else {
    timer_counter_0_ovf_func = NULL;
    TIMSK0 &= ~(1 << TOIE0);
  }
  TCNT0 = 0;
  uint8_t clock_select = timer_counter_0_prescaler_to_clock_select(prescaler);
  TCCR0A = (((wave_gen_mode >> 0) & 1u) << WGM00) |  //
           (((wave_gen_mode >> 1) & 1u) << WGM01);   //
  printf("clock_select = %u\n", clock_select);
  TCCR0B = (clock_select << CS00) | (((wave_gen_mode >> 2) & 1u) << WGM02);
}

void timer_counter_1_set_attrs(timer_counter_1_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_16_bit_output_t* output_a,
                               timer_counter_16_bit_output_t* output_b,
                               timer_counter_input_t* input) {
  TCCR1B = 0;
  if (output_a) {
    timer_counter_1_compa_func = *output_a->cb;
    TCCR1A |= output_a->mode << COM1A0;
    OCR1A = output_a->val;
    TIMSK1 |= 1 << OCIE1A;
  } else {
    timer_counter_1_compa_func = NULL;
    TIMSK1 &= ~(1 << OCIE1A);
  }
  if (output_b) {
    timer_counter_1_compb_func = *output_b->cb;
    TCCR1A |= output_b->mode << COM1B0;
    OCR1B = output_b->val;
    TIMSK1 |= 1 << OCIE1B;
  } else {
    timer_counter_1_compb_func = NULL;
    TIMSK1 &= ~(1 << OCIE1B);
  }
  if (input) {
    timer_counter_1_capt_func = *input->cb;
    TCCR1B |= (input->edge_select << ICES1) | (input->noise_cancel << ICNC1);
    TIMSK1 |= 1 << ICIE1;
  } else {
    timer_counter_1_capt_func = NULL;
    TIMSK1 &= ~(1 << ICIE1);
  }
  if (overflow_cb) {
    timer_counter_1_ovf_func = *overflow_cb;
    TIMSK1 |= 1 << TOIE1;
  } else {
    timer_counter_1_ovf_func = NULL;
    TIMSK1 &= ~(1 << TOIE1);
  }
  TCNT1 = 0;
  uint8_t clock_select = timer_counter_1_prescaler_to_clock_select(prescaler);
  TCCR1A = (((wave_gen_mode >> 0) & 1u) << WGM10) |  //
           (((wave_gen_mode >> 1) & 1u) << WGM11);   //
  TCCR1B = (clock_select << CS10) |                  //
           (((wave_gen_mode >> 2) & 1u) << WGM12) |  //
           (((wave_gen_mode >> 3) & 1u) << WGM13);   //
}

void timer_counter_2_set_attrs(timer_counter_2_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_8_bit_output_t* output_a,
                               timer_counter_8_bit_output_t* output_b) {
  TCCR2B = 0;  // stop timer counter while configuring
  if (output_a) {
    timer_counter_2_compa_func = *output_a->cb;
    TCCR2A |= output_a->mode << COM2A0;
    OCR2A = output_a->val;
    TIMSK2 |= 1 << OCIE2A;
  } else {
    timer_counter_2_compa_func = NULL;
    TIMSK2 &= ~(1 << OCIE2A);
  }
  if (output_b) {
    timer_counter_2_compb_func = *output_b->cb;
    TCCR2A |= output_b->mode << COM2B0;
    OCR2B = output_b->val;
    TIMSK2 |= 1 << OCIE2B;
  } else {
    timer_counter_2_compb_func = NULL;
    TIMSK2 &= ~(1 << OCIE2B);
  }
  if (overflow_cb) {
    timer_counter_2_ovf_func = *overflow_cb;
    TIMSK2 |= 1 << TOIE2;
  } else {
    timer_counter_2_ovf_func = NULL;
    TIMSK2 &= ~(1 << TOIE2);
  }
  TCNT2 = 0;  // reset timer counter
  uint8_t clock_select = timer_counter_2_prescaler_to_clock_select(prescaler);
  TCCR2A = (((wave_gen_mode >> 0) & 1u) << WGM20) |  //
           (((wave_gen_mode >> 1) & 1u) << WGM21);   //
  // start timer coutner
  TCCR2B = (clock_select << CS20) | (((wave_gen_mode >> 2) & 1u) << WGM22);
}

uint8_t timer_counter_0_get_count(void) { return TCNT0; }

uint16_t timer_counter_1_get_count(void) { return TCNT1; }

uint8_t timer_counter_2_get_count(void) { return TCNT2; }

/* ====== Static Function Definitions ====== */

static uint8_t timer_counter_0_prescaler_to_clock_select(unsigned prescaler) {
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

static uint8_t timer_counter_2_prescaler_to_clock_select(unsigned prescaler) {
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

ISR(TIMER0_COMPA_vect) { timer_counter_0_compa_func(); }

ISR(TIMER0_COMPB_vect) { timer_counter_0_compb_func(); }

ISR(TIMER0_OVF_vect) { timer_counter_0_ovf_func(); }

ISR(TIMER1_COMPA_vect) { timer_counter_1_compa_func(); }

ISR(TIMER1_COMPB_vect) { timer_counter_1_compb_func(); }

ISR(TIMER1_OVF_vect) { timer_counter_1_ovf_func(); }

ISR(TIMER1_CAPT_vect) { timer_counter_1_capt_func(); }

ISR(TIMER2_COMPA_vect) { timer_counter_2_compa_func(); }

ISR(TIMER2_COMPB_vect) { timer_counter_2_compb_func(); }

ISR(TIMER2_OVF_vect) { timer_counter_2_ovf_func(); }
