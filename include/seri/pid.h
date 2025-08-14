//! @file
//! @brief PID制御モジュール

#pragma once

/// PIDパラメーター
typedef struct {
    /// Pゲイン
    SL_FP_T kp;
    /// Iゲイン
    SL_FP_T ki;
    /// Dゲイン
    SL_FP_T kd;
} pid_params_t;

/// PID制御データ
typedef struct {
    /// PIDパラメーター
    pid_params_t params;
    /// 前回処理時の差分
    SL_FP_T prev_p;
    /// 前回処理時の積算差分
    SL_FP_T prev_i;
    /// 現在の実際の値
    SL_FP_T actual_value;
} pid_data_t;

/// @brief PIDパラメーター型を作成する。
///
/// @param[in] kp @ref pid_params_t::kp
/// @param[in] ki @ref pid_params_t::ki
/// @param[in] kd @ref pid_params_t::kd
///
/// @return PIDパラメーター型
pid_params_t create_pid_params(SL_FP_T kp, SL_FP_T ki, SL_FP_T kd);

/// @brief PID制御データ型を作成する。
///
/// @param[in] params @ref pid_data_t::params
///
/// @return PID制御データ型
pid_data_t create_pid_data(pid_params_t params);

/// @brief PID制御データを基に値を計算する。
///
/// @param[in,out] pid_data PID制御データ
/// @param[in]     target   目標値
///
/// @return 値
SL_FP_T process_pid(pid_data_t *pid_data, SL_FP_T target);
