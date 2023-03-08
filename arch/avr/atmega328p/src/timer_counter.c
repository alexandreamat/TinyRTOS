#include "timer_counter.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* ====== Preprocessor Definitions ====== */

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
  TCCR0B = 0;  // stop the timer
  TIMSK0 = 0;  // disable interrupts
  TCNT0 = 0;   // reset counter

  // set wave generation mode
  TCCR0A = (((wave_gen_mode >> 0) & 1u) << WGM00) |
           (((wave_gen_mode >> 1) & 1u) << WGM01);
  TCCR0B = ((wave_gen_mode >> 2) & 1u) << WGM02;

  // selectively enable interrupts, set callbacks, set output compare value
  if (output_a) {
    timer_counter_0_compa_func = output_a->cb;
    TCCR0A |= output_a->mode << COM0A0;
    OCR0A = output_a->val;
    TIMSK0 |= 1 << OCIE0A;
  } else {
    timer_counter_0_compa_func = NULL;
  }
  if (output_b) {
    timer_counter_0_compb_func = output_b->cb;
    TCCR0A |= output_b->mode << COM0B0;
    OCR0B = output_b->val;
    TIMSK0 |= 1 << OCIE0B;
  } else {
    timer_counter_0_compb_func = NULL;
  }
  if (overflow_cb) {
    timer_counter_0_ovf_func = overflow_cb;
    TIMSK0 |= 1 << TOIE0;
  } else {
    timer_counter_0_ovf_func = NULL;
  }

  // start the timer
  TCCR0B |= timer_counter_0_prescaler_to_clock_select(prescaler) << CS00;
}

void timer_counter_1_set_attrs(timer_counter_1_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_16_bit_output_t* output_a,
                               timer_counter_16_bit_output_t* output_b,
                               timer_counter_input_t* input) {
  TCCR1B = 0;  // stop the timer
  TIMSK1 = 0;  // disable interrupts
  TCNT1 = 0;   // reset the counter

  // set wave generation mode
  TCCR1A = (((wave_gen_mode >> 0) & 1u) << WGM10) |
           (((wave_gen_mode >> 1) & 1u) << WGM11);
  TCCR1B = (((wave_gen_mode >> 2) & 1u) << WGM12) |
           (((wave_gen_mode >> 3) & 1u) << WGM13);

  // selectively enable interrupts, set callbacks, set output compare value
  if (output_a) {
    timer_counter_1_compa_func = output_a->cb;
    TCCR1A |= output_a->mode << COM1A0;
    OCR1A = output_a->val;
    TIMSK1 |= 1 << OCIE1A;
  } else {
    timer_counter_1_compa_func = NULL;
    TIMSK1 &= ~(1 << OCIE1A);
  }
  if (output_b) {
    timer_counter_1_compb_func = output_b->cb;
    TCCR1A |= output_b->mode << COM1B0;
    OCR1B = output_b->val;
  } else {
    timer_counter_1_compb_func = NULL;
  }
  if (input) {
    timer_counter_1_capt_func = input->cb;
    TCCR1B |= (input->edge_select << ICES1) | (input->noise_cancel << ICNC1);
    TIMSK1 |= 1 << ICIE1;
  } else {
    timer_counter_1_capt_func = NULL;
  }
  if (overflow_cb) {
    timer_counter_1_ovf_func = overflow_cb;
    TIMSK1 |= 1 << TOIE1;
  } else {
    timer_counter_1_ovf_func = NULL;
  }

  // start the timer
  TCCR1B |= timer_counter_1_prescaler_to_clock_select(prescaler) << CS10;
}

void timer_counter_2_set_attrs(timer_counter_2_wgm_t wave_gen_mode,
                               unsigned prescaler,
                               timer_counter_func_t overflow_cb,
                               timer_counter_8_bit_output_t* output_a,
                               timer_counter_8_bit_output_t* output_b) {
  TCCR2B = 0;    // stop the timer
  TIMSK2 = 0;    // disable interrupts
  TIFR2 = 0xFF;  // clear any pending interrupt flags
  TCNT2 = 0;     // reset the counter

  // set wave generation mode
  TCCR2A |= (((wave_gen_mode >> 0) & 1u) << WGM20) |
            (((wave_gen_mode >> 1) & 1u) << WGM21);
  TCCR2B |= ((wave_gen_mode >> 2) & 1u) << WGM22;

  // selectively enable interrupts, set callbacks, set output compare value
  if (output_a) {
    timer_counter_2_compa_func = output_a->cb;
    TCCR2A |= output_a->mode << COM2A0;
    OCR2A = output_a->val;
    TIMSK2 |= 1 << OCIE2A;
  } else {
    timer_counter_2_compa_func = NULL;
  }
  if (output_b) {
    timer_counter_2_compb_func = output_b->cb;
    TCCR2A |= output_b->mode << COM2B0;
    OCR2B = output_b->val;
    TIMSK2 |= 1 << OCIE2B;
  } else {
    timer_counter_2_compb_func = NULL;
  }
  if (overflow_cb) {
    timer_counter_2_ovf_func = overflow_cb;
    TIMSK2 |= 1 << TOIE2;
  } else {
    timer_counter_2_ovf_func = NULL;
  }

  // start the timer
  TCCR2B |= timer_counter_2_prescaler_to_clock_select(prescaler) << CS20;
}

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

ISR(TIMER0_COMPA_vect) {
  timer_counter_0_compa_func();
  TIFR0 = 1 << OCF0A;
}

ISR(TIMER0_COMPB_vect) {
  timer_counter_0_compb_func();
  TIFR0 = 1 << OCF0B;
}

ISR(TIMER0_OVF_vect) {
  timer_counter_0_ovf_func();
  TIFR0 = 1 << TOIE0;
}

ISR(TIMER1_COMPA_vect) {
  timer_counter_1_compa_func();
  TIFR1 = 1 << OCF1A;
}

ISR(TIMER1_COMPB_vect) {
  timer_counter_1_compb_func();
  TIFR1 = 1 << OCF1B;
}

ISR(TIMER1_OVF_vect) {
  timer_counter_1_ovf_func();
  TIFR1 = 1 << TOIE1;
}

ISR(TIMER1_CAPT_vect) {
  timer_counter_1_capt_func();
  TIFR1 = 1 << ICIE1;
}

ISR(TIMER2_COMPA_vect) {
  timer_counter_2_compa_func();
  TIFR2 = 1 << OCF2A;
}

ISR(TIMER2_COMPB_vect) {
  timer_counter_2_compb_func();
  TIFR2 = 1 << OCF2B;
}

ISR(TIMER2_OVF_vect) {
  timer_counter_2_ovf_func();
  TIFR2 = 1 << TOIE2;
}
