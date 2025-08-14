#include <seri/pid.h>

pid_params_t create_pid_params(const SL_FP_T kp, const SL_FP_T ki, const SL_FP_T kd) {
    return (pid_params_t){.kp = kp, .ki = ki, .kd = kd};
}

pid_data_t create_pid_data(const pid_params_t params) {
    return (pid_data_t){.params = params, .prev_p = 0.0, .prev_i = 0.0, .actual_value = 0.0};
}

SL_FP_T process_pid(pid_data_t *const pid_data, const SL_FP_T target) {
    const SL_FP_T p = target - pid_data->actual_value;
    const SL_FP_T i = pid_data->prev_i + p;
    const SL_FP_T d = p - pid_data->prev_p;
    pid_data->prev_p = p;
    pid_data->prev_i = i;
    return pid_data->params.kp * p + pid_data->params.ki * i + pid_data->params.kd * d;
}
