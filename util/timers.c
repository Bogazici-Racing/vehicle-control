#include "timers.h"
#include "main.h"
#include "sensors.h"        // To access update_mandatory_sensors
#include "maps.h"           // To access update_maps

// ===========================================================
// Static Variables
// ===========================================================

// System time counter (Incremented by SysTick interrupt)
static volatile uint32_t system_time_ms = 0;

// ===========================================================
// Task List (The "To-Do" List)
// ===========================================================

// TODO: Add or remove tasks here as the project grows
static Task task_list[] = {
    // { Function Name,             Period (ms),          Last Run (0) }
    
    // Fast Task: Read critical sensors (TPS, MAP, etc.)
    { update_mandatory_sensors,     PERIOD_FAST_TASK_MS,    0 },

    // Medium Task: Update fuel and ignition maps
    { update_maps,                  PERIOD_MEDIUM_TASK_MS,  0 },

    // Slow Task: Read advanced sensors (Oil, EGT, etc.)
    { update_advanced_sensors,      PERIOD_SLOW_TASK_MS,    0 },

    // TODO: Add Data Logger task here later
    // { update_data_logger,        PERIOD_SLOW_TASK_MS,    0 } 
};

// Calculate number of tasks automatically
#define NUM_TASKS (sizeof(task_list) / sizeof(Task))

// ===========================================================
// Interrupt Callback
// ===========================================================

/**
 * @brief Called automatically by STM32 HAL Systick Interrupt every 1ms
 * (Defined in stm32f4xx_it.c or internally in HAL)
 */
void HAL_SYSTICK_Callback(void) {
    system_time_ms++; // Increment system clock
}

// ===========================================================
// Public Functions
// ===========================================================

void timers_init(void) {
    system_time_ms = 0;
    
    // Optional: Reset last_run_ms for all tasks to 0
    for (int i = 0; i < NUM_TASKS; i++) {
        task_list[i].last_run_ms = 0;
    }
}

uint32_t get_system_time(void) {
    return system_time_ms;
}

/**
 * @brief Main Scheduler Logic
 * Checks if enough time has passed for each task.
 * If yes, executes the task.
 */
void timers_update(void) {
    uint32_t current_time = get_system_time();

    for (int i = 0; i < NUM_TASKS; i++) {
        // Calculate time elapsed since last run
        // TODO: Handle uint32_t overflow if system runs for > 49 days (Low priority)
        if ((current_time - task_list[i].last_run_ms) >= task_list[i].period_ms) {
            
            // Update the last run time
            task_list[i].last_run_ms = current_time;

            // Execute the task function
            task_list[i].task_function();
        }
    }
}