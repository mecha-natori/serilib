#include <math.h>
#include <seri/control.h>
#include <seri/math.h>
#include <seri/pid.h>
#include <seri/steering.h>
#include <string.h>

SL_FP_T _calc_speed_mechanum_tire(int i, steering_param_t steering_param, cart_t l, cart_t r);

void calc_speed_mechanum(int16_t *const result, pid_data_t **const pid_data, const steering_param_t steering_param, const sticks_nor_t sticks) {
    int16_t buf[8];
    const cart_t l = create_cart(sticks.lx, sticks.ly);
    const cart_t r = create_cart(sticks.rx, sticks.ry);
    for(int i = 0; i < 4; i++) {
        buf[i] = _calc_speed_mechanum_tire(i, steering_param, l, r);
        // PID
        if(pid_data != NULL && pid_data[i] != NULL) {
            buf[i] = process_pid(pid_data[i], buf[i]);
        }
    }
    memcpy(result, buf, 8);
}

SL_FP_T _calc_speed_mechanum_tire(const int i, const steering_param_t steering_param, const cart_t l, const cart_t r) {
    // モーター正転時の進行方向の単位ベクトルの角度
    // 角度 = (位置ベクトルの角度 + 時計回りに90deg)
    // 位置ベクトルの角度 = (45deg + モーターの位置相対角度)
    const SL_FP_T vec_angle = M_PI / 4.0 + (SL_FP_T)i * M_PI / 2.0 - M_PI_2;
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
