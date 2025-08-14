#include <math.h>
#include <seri/control.h>
#include <seri/math.h>
#include <seri/pid.h>
#include <seri/steering.h>
#include <string.h>

SL_FP_T _calc_speed_crawler_tire(int i, steering_param_t steering_param, cart_t l, cart_t r, crawler_ctrl_type_t ctrl_type);

SL_FP_T
_calc_speed_crawler_tire_type_left(int i, steering_param_t steering_param, cart_t l);

SL_FP_T
_calc_speed_crawler_tire_type_both(int i, steering_param_t steering_param, cart_t l, cart_t r);

void calc_speed_crawler(int16_t *const result, pid_data_t **const pid_data, const steering_param_t steering_param, const sticks_nor_t sticks, const crawler_ctrl_type_t ctrl_type) {
    int16_t buf[2];
    const cart_t l = create_cart(sticks.lx, sticks.ly);
    const cart_t r = create_cart(sticks.rx, sticks.ry);
    for(int i = 0; i < 2; i++) {
        buf[i] = _calc_speed_crawler_tire(i, steering_param, l, r, ctrl_type);
        // PID
        if(pid_data != NULL && pid_data[i] != NULL) {
            buf[i] = process_pid(pid_data[i], buf[i]);
        }
    }
    memcpy(result, buf, 4);
}

SL_FP_T _calc_speed_crawler_tire(const int i, const steering_param_t steering_param, const cart_t l, const cart_t r, const crawler_ctrl_type_t ctrl_type) {
    switch(ctrl_type) {
        case CRAWLER_LEFT_STICK:
            return _calc_speed_crawler_tire_type_left(i, steering_param, l);
        case CRAWLER_BOTH_STICK:
            return _calc_speed_crawler_tire_type_both(i, steering_param, l, r);
    }
}

SL_FP_T _calc_speed_crawler_tire_type_left(const int i, const steering_param_t steering_param, const cart_t l) {
    // i=0(右): 正転方向が-y方向 -y * (-1)^0 = -y
    // i=1(左): 正転方向が+y方向 -y * (-1)^1 = +y
    return steering_param.trans_ratio * -l.y * pow(-1, i)
        + (1.0 - steering_param.trans_ratio) * l.x;
}

SL_FP_T _calc_speed_crawler_tire_type_both(const int i, const steering_param_t steering_param, const cart_t l, const cart_t r) {
    switch(i) {
        // 右
        case 0:
            return -r.y;
        // 左
        case 1:
            return l.y;
    }
    return NAN;
}
