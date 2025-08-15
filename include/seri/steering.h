//! @file
//! @brief 足回りモジュール

#pragma once

#include <seri/control.h>
#include <seri/pid.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// 足回りパラメーター
typedef struct {
    /// 最高タイヤ回転速度 [rad/s]
    SL_FP_T max_rot_speed;
    /// 速度に占める並進速度の割合(残りは回転速度が占める)
    SL_FP_T trans_ratio;
    /// タイヤ半径 [m] (未使用)
    SL_FP_T tire_r;
    /// ロボットの中心からタイヤまでの距離 [m] (未使用)
    SL_FP_T tire_d;
} steering_param_t;

/// クローラー足回りの操縦方法
typedef enum {
    /// 左スティックのX軸を旋回、Y軸を前後に割り当てる
    CRAWLER_LEFT_STICK,
    /// 左スティックのY軸を左モーター前後、右スティックのY軸を右モーター前後に割り当てる
    CRAWLER_BOTH_STICK
} crawler_ctrl_type_t;

/// @brief 足回りパラメーター型を作成する。
///
/// @param[in] max_rot_speed @ref steering_param_t::max_rot_speed
/// @param[in] trans_ratio   @ref steering_param_t::trans_ratio
steering_param_t create_steering_param(SL_FP_T max_rot_speed, SL_FP_T trans_ratio);

/// @brief クローラー足回りのモーター速度を計算する。
/// @details 結果は右・左の順に格納される。
/// @details スティック入力の扱いはctrl_typeの値によって変わる。
///
/// @param[out]    result         計算結果の配列
/// @param[in,out] pid_data       PID制御データ
/// @param[in]     steering_param 足回りのパラメーター
/// @param[in]     sticks         正規化済みスティック入力
/// @param[in]     ctrl_type      操縦方法
void calc_speed_crawler(int16_t result[2], pid_data_t *pid_data[2], steering_param_t steering_param, sticks_nor_t sticks, crawler_ctrl_type_t ctrl_type);

/// @brief メカナムホイール足回りのモーター速度を計算する。
/// @details 結果は右前から反時計回りに格納される。
/// @details スティック入力は左が水平移動入力、右のX軸が旋回入力に使用される。
///
/// @param[out]    result         計算結果の配列
/// @param[in,out] pid_data       PID制御データ
/// @param[in]     steering_param 足回りのパラメーター
/// @param[in]     sticks         正規化済みスティック入力
void calc_speed_mechanum(int16_t result[4], pid_data_t *pid_data[4], steering_param_t steering_param, sticks_nor_t sticks);

/// @brief n輪オムニホイール足回りのモーター速度を計算する。
/// @details 結果は0番のモーターから反時計回りに格納される。
/// @details
/// 0番のモーターはモーター位置の基準となるモーターであり、任意のものを指定できる。
/// @details スティック入力は左が水平移動入力、右のX軸が旋回入力に使用される。
///
/// @param[out]    result         計算結果の配列
/// @param[in,out] pid_data       PID制御データ
/// @param[in]     steering_param 足回りのパラメーター
/// @param[in]     sticks         正規化済みスティック入力
/// @param[in]     n              モーターの個数
/// @param[in]     initial_angle  0番のモーターの角度(右0・反時計回り) [rad]
void calc_speed_omni(int16_t *result, pid_data_t **pid_data, steering_param_t steering_param, sticks_nor_t sticks, size_t n, SL_FP_T initial_angle);

#ifdef __cplusplus
}
#endif
