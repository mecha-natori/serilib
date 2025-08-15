//! @file
//! @brief 操作モジュール

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// 生のスティックデータ
typedef struct {
    /// 左スティック左右軸(右が正)
    int16_t lx;
    /// 左スティック上下軸(上が正)
    int16_t ly;
    /// 右スティック左右軸(右が正)
    int16_t rx;
    /// 右スティック上下軸(上が正)
    int16_t ry;
    /// デッドゾーン(0-100) [%]
    uint8_t dead_zone;
} sticks_t;

/// 正規化済みスティックデータ
typedef struct {
    /// 左スティック左右軸(右が正)
    SL_FP_T lx;
    /// 左スティック上下軸(上が正)
    SL_FP_T ly;
    /// 右スティック左右軸(右が正)
    SL_FP_T rx;
    /// 右スティック上下軸(上が正)
    SL_FP_T ry;
} sticks_nor_t;

/// @brief スティックデータを正規化する。
///
/// @param[in] sticks 生のスティックデータ
///
/// @return 正規化されたスティックデータ
sticks_nor_t normalize_sticks(sticks_t sticks);

#ifdef __cplusplus
}
#endif
