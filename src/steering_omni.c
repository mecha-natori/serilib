#include <math.h>
#include <seri/control.h>
#include <seri/math.h>
#include <seri/pid.h>
#include <seri/steering.h>
#include <stdlib.h>
#include <string.h>

SL_FP_T _calc_speed_omni_tire(int i, steering_param_t steering_param, cart_t l, cart_t r, SL_FP_T initial_angle, SL_FP_T angle_per_motor);

void calc_speed_omni(int16_t *const result, pid_data_t **const pid_data, const steering_param_t steering_param, const sticks_nor_t sticks, const size_t n, const SL_FP_T initial_angle) {
    int16_t *const buf = malloc(n * 2);
    const SL_FP_T angle_per_motor = 2.0 * M_PI / (SL_FP_T)n;
    const cart_t l = create_cart(sticks.lx, sticks.ly);
    const cart_t r = create_cart(sticks.rx, sticks.ry);
    for(int i = 0; i < n; i++) {
        buf[i] = _calc_speed_omni_tire(i, steering_param, l, r, initial_angle, angle_per_motor);
        // PID
        if(pid_data != NULL && pid_data[i] != NULL) {
            buf[i] = process_pid(pid_data[i], buf[i]);
        }
    }
    memcpy(result, buf, n * 2);
    free(buf);
}

SL_FP_T _calc_speed_omni_tire(const int i, const steering_param_t steering_param, const cart_t l, const cart_t r, const SL_FP_T initial_angle, const SL_FP_T angle_per_motor) {
    // モーター正転時の進行方向の単位ベクトルの角度
    // 角度 = (位置ベクトルの角度 + 時計回りに90deg)
    // 位置ベクトルの角度 = (基準角度 + モーターの位置相対角度)
    const SL_FP_T vec_angle = initial_angle + (SL_FP_T)i * angle_per_motor - M_PI_2;
    // モーター正転時の進行方向の単位ベクトル
    const cart_t motor_vec = pol2cart(1.0, vec_angle);
    // 旋回速度のベクトル
    const polar_t rot_vec_pol = create_polar(r.x, vec_angle);
    const cart_t rot_vec = pol2cart(rot_vec_pol.r, rot_vec_pol.theta);
    // 並進速度
    const SL_FP_T v_trans = dot(motor_vec, l);
    // 旋回速度
    const SL_FP_T v_rot = dot(motor_vec, rot_vec);
    // 速度
    const SL_FP_T v =
        steering_param.trans_ratio * v_trans + (1.0 - steering_param.trans_ratio) * v_rot;
    return steering_param.max_rot_speed * v;
}
