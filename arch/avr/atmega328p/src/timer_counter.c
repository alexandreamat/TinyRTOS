#include "timer_counter.h"

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "libc/time.h"
#include "utils/debug.h"
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

const unsigned TIMER_COUNTER_0_PRESCALERS[] = {0, 1, 8, 64, 256, 1024};
const unsigned TIMER_COUNTER_1_PRESCALERS[] = {0, 1, 8, 64, 256, 1024};
const unsigned TIMER_COUNTER_2_PRESCALERS[] = {0, 1, 8, 32, 64, 128, 256, 1024};

const size_t TIMER_COUNTER_0_PRESCALERS_SIZE =
    sizeof(TIMER_COUNTER_0_PRESCALERS) / sizeof(TIMER_COUNTER_0_PRESCALERS[0]);
const size_t TIMER_COUNTER_1_PRESCALERS_SIZE =
    sizeof(TIMER_COUNTER_1_PRESCALERS) / sizeof(TIMER_COUNTER_1_PRESCALERS[0]);
const size_t TIMER_COUNTER_2_PRESCALERS_SIZE =
    sizeof(TIMER_COUNTER_2_PRESCALERS) / sizeof(TIMER_COUNTER_2_PRESCALERS[0]);

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
  TCCR0B = 0;    // stop the timer
  TIMSK0 = 0;    // disable interrupts
  TIFR0 = 0xFF;  // clear pending interrupts
  TCNT0 = 0;     // reset counter

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
  TCCR1B = 0;    // stop the timer
  TIMSK1 = 0;    // disable interrupts
  TIFR1 = 0xFF;  // clear pending interrupts
  TCNT1 = 0;     // reset the counter

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
    OCR1A = 0;
    timer_counter_1_compa_func = NULL;
  }
  if (output_b) {
    timer_counter_1_compb_func = output_b->cb;
    TCCR1A |= output_b->mode << COM1B0;
    OCR1B = output_b->val;
  } else {
    OCR1B = 0;
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
  TIFR2 = 0xFF;  // clear pending interrupts
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
    OCR2A = 0;
    timer_counter_2_compa_func = NULL;
  }
  if (output_b) {
    timer_counter_2_compb_func = output_b->cb;
    TCCR2A |= output_b->mode << COM2B0;
    OCR2B = output_b->val;
    TIMSK2 |= 1 << OCIE2B;
  } else {
    OCR2B = 0;
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
  for (size_t i = 0; i < TIMER_COUNTER_0_PRESCALERS_SIZE; i++)
    if (prescaler == TIMER_COUNTER_0_PRESCALERS[i]) return i;
  return 0;
}

static uint8_t timer_counter_2_prescaler_to_clock_select(unsigned prescaler) {
  for (size_t i = 0; i < TIMER_COUNTER_2_PRESCALERS_SIZE; i++)
    if (prescaler == TIMER_COUNTER_2_PRESCALERS[i]) return i;
  return 0;
}

ISR(TIMER0_COMPA_vect) {
  TIFR0 = 1 << OCF0A;
  timer_counter_0_compa_func();
}

ISR(TIMER0_COMPB_vect) {
  TIFR0 = 1 << OCF0B;
  timer_counter_0_compb_func();
}

ISR(TIMER0_OVF_vect) {
  TIFR0 = 1 << TOIE0;
  timer_counter_0_ovf_func();
}

ISR(TIMER1_COMPA_vect) {
  TIFR1 = 1 << OCF1A;
  timer_counter_1_compa_func();
}

ISR(TIMER1_COMPB_vect) {
  TIFR1 = 1 << OCF1B;
  timer_counter_1_compb_func();
}

ISR(TIMER1_OVF_vect) {
  TIFR1 = 1 << TOIE1;
  timer_counter_1_ovf_func();
}

ISR(TIMER1_CAPT_vect) {
  TIFR1 = 1 << ICIE1;
  timer_counter_1_capt_func();
}

ISR(TIMER2_COMPA_vect) {
  TIFR2 = 1 << OCF2A;
  timer_counter_2_compa_func();
}

ISR(TIMER2_COMPB_vect) {
  TIFR2 = 1 << OCF2B;
  timer_counter_2_compb_func();
}

ISR(TIMER2_OVF_vect) {
  TIFR2 = 1 << TOIE2;
  timer_counter_2_ovf_func();
}
