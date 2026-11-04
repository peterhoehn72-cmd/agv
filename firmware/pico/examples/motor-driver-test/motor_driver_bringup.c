/*
 * Open-loop bring-up experiment for the Pico, two L298N modules, and four motors.
 *
 * Purpose: exercise the wiring, power supply, and motor drivers before developing
 * feedback control. At approximately 1.5-2 kHz PWM, equal duty commands produced
 * visually similar motor responses and straight travel on the tested level
 * surface. Response to small duty changes also improved. These observations
 * establish the current baseline; wheel speed and torque were not measured.
 *
 * The straight-line trial applies one common duty command to all motors.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "hardware/pwm.h"
#include "pico/stdlib.h"

enum {
    PWM_TOP = UINT8_MAX,
    DUTY_COMMAND_MAX = UINT8_MAX,
    STRAIGHT_LINE_BASE_DUTY = 45,
    STARTUP_BURST_MS = 5,
    TRIAL_HOLD_MS = 10 * 60 * 1000,
    SWEEP_MIN_DUTY = 40,
    SWEEP_MAX_DUTY = 150,
    SWEEP_STEP_MS = 80,
};

/*
 * In normal free-running mode:
 * f_pwm = f_sys / (divider * (TOP + 1)).
 * See the README for motor-response observations at the tested frequencies.
 */

static const float PWM_CLOCK_DIVIDER = 250.0f;

typedef enum {
    STRAIGHT_LINE_TRIAL,
    INDIVIDUAL_DUTY_SWEEP,
} test_mode_t;

/* Select a test here */
static const test_mode_t TEST_MODE = STRAIGHT_LINE_TRIAL;

typedef struct {
    const char *name;
    uint8_t dir_pin_1;
    uint8_t dir_pin_2;
    uint8_t pwm_pin;
    uint slice_num;
    uint channel;
} motor_t;

static void motor_set_duty(const motor_t *motor, uint8_t duty)
{
    pwm_set_chan_level(motor->slice_num, motor->channel, duty);
}

static void motor_set_forward(const motor_t *motor)
{
    /* "Forward" follows the motor wiring and mounting used for this experiment. */
    gpio_put(motor->dir_pin_1, 1);
    gpio_put(motor->dir_pin_2, 0);
}

static void motor_stop(const motor_t *motor)
{
    /* Disable the bridge through its PWM enable input and clear direction pins. */
    motor_set_duty(motor, 0);
    gpio_put(motor->dir_pin_1, 0);
    gpio_put(motor->dir_pin_2, 0);
}

static void motor_init(motor_t *motor)
{
    const uint8_t direction_pins[] = {motor->dir_pin_1, motor->dir_pin_2};
    for (size_t i = 0; i < sizeof(direction_pins) / sizeof(direction_pins[0]); ++i) {
        gpio_init(direction_pins[i]);
        gpio_put(direction_pins[i], 0);
        gpio_set_dir(direction_pins[i], GPIO_OUT);
    }

    motor->slice_num = pwm_gpio_to_slice_num(motor->pwm_pin);
    motor->channel = pwm_gpio_to_channel(motor->pwm_pin);
    pwm_set_clkdiv(motor->slice_num, PWM_CLOCK_DIVIDER);
    pwm_set_wrap(motor->slice_num, PWM_TOP);
    motor_set_duty(motor, 0);
    gpio_set_function(motor->pwm_pin, GPIO_FUNC_PWM);
    pwm_set_enabled(motor->slice_num, true);
}

static void run_straight_line_trial(const motor_t motors[], size_t count)
{
    /* Trials showed that a brief burst is necessary 
    to start the loaded robot at low duty. */
    for (size_t i = 0; i < count; ++i) {
        motor_set_forward(&motors[i]);
        motor_set_duty(&motors[i], DUTY_COMMAND_MAX);
    }
    sleep_ms(STARTUP_BURST_MS);

    for (size_t i = 0; i < count; ++i) {
        motor_set_duty(&motors[i], STRAIGHT_LINE_BASE_DUTY);
    }
}

static void run_individual_duty_sweep(const motor_t motors[], size_t count)
{
    /* Apply the same command sequence to each motor for visual comparison.
     * The rising branch applies a maximum-level pulse before EVERY step,
     * so this is a boosted sweep, not a pure acceleration ramp. */
    for (size_t i = 0; i < count; ++i) {
        const motor_t *motor = &motors[i];
        motor_set_forward(motor);

        for (int duty = SWEEP_MIN_DUTY; duty < SWEEP_MAX_DUTY; ++duty) {
            motor_set_duty(motor, DUTY_COMMAND_MAX);
            sleep_ms(STARTUP_BURST_MS);
            motor_set_duty(motor, (uint8_t)duty);
            sleep_ms(SWEEP_STEP_MS);
            printf("%s: rising duty=%d\n", motor->name, duty);
        }

        for (int duty = SWEEP_MAX_DUTY; duty >= SWEEP_MIN_DUTY; --duty) {
            motor_set_duty(motor, (uint8_t)duty);
            sleep_ms(SWEEP_STEP_MS);
            printf("%s: falling duty=%d\n", motor->name, duty);
        }

        /* Clear the duty as well as the direction pins between motors. */
        motor_stop(motor);
    }
}

int main(void)
{
    stdio_init_all();

    /* GP numbers, not header pin numbers. These four PWM pins use distinct
     * slices. Slice/channel fields are populated during initialization.
     */
    motor_t motors[] = {
        {.name = "front-left", .dir_pin_1 = 11, .dir_pin_2 = 12,
         .pwm_pin = 10},
        {.name = "front-right", .dir_pin_1 = 14, .dir_pin_2 = 15,
         .pwm_pin = 13},
        {.name = "rear-right", .dir_pin_1 = 6, .dir_pin_2 = 7,
         .pwm_pin = 8},
        {.name = "rear-left", .dir_pin_1 = 3, .dir_pin_2 = 4,
         .pwm_pin = 2},
    };
    const size_t motor_count = sizeof(motors) / sizeof(motors[0]);

    for (size_t i = 0; i < motor_count; ++i) {
        motor_init(&motors[i]);
    }

    while (true) {
        switch (TEST_MODE) {
        case STRAIGHT_LINE_TRIAL:
            run_straight_line_trial(motors, motor_count);
            break;
        case INDIVIDUAL_DUTY_SWEEP:
            run_individual_duty_sweep(motors, motor_count);
            break;
        }

        /* In the straight-line trial, outputs remain active during this wait;
         * The individual sweep has already stopped each motor before this wait.
         */
        sleep_ms(TRIAL_HOLD_MS);
    }
}
