#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

// ===========================================================
// Scheduler Configuration (Placeholders)
// ===========================================================

// Task periods in milliseconds (TODO: Tune these values for real engine needs)
#define PERIOD_FAST_TASK_MS     10   // 100 Hz (Sensors)
#define PERIOD_MEDIUM_TASK_MS   20   // 50 Hz (Maps)
#define PERIOD_SLOW_TASK_MS     100  // 10 Hz (Logging/Display)

// ===========================================================
// Task Structure Definition
// ===========================================================

/**
 * @brief Structure to represent a scheduled task
 */
typedef struct {
    void (*task_function)(void); // Pointer to the function to execute
    uint32_t period_ms;          // How often to run the task (in ms)
    uint32_t last_run_ms;        // Timestamp of the last execution (init to 0)
} Task;

// ===========================================================
// Public Function Prototypes
// ===========================================================

void timers_init(void);          // Reset system time and tasks
void timers_update(void);        // Main scheduler loop (call in while(1))
uint32_t get_system_time(void);  // Get current system time in ms

#endif // TIMERS_H