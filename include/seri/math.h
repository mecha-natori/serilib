//! @file
//! @brief 数学モジュール

#pragma once

#include <complex.h>
#include <stdbool.h>

// 内部使用向け
/// @cond INTERNAL

/// @def fpfallback
/// @brief 浮動小数点数の関数をフォールバックする。
/// @details 浮動小数点数の関数の内、最も精度の高い型の関数名を返す。
///
/// @param[in] fn ベースの関数
///
/// @return フォールバック関数名
#ifdef __NO_LONG_DOUBLE_MATH
    #define fpfallback(fn) fn
#else
    #define fpfallback(fn) fn##l
#endif

/// @brief 浮動小数点数演算の関数を呼び出す。
/// @details SL_FP_T型の実体に応じた関数を呼び出す。
///
/// @param[in] fn  呼び出す関数
/// @param     ... fnに渡す引数
///
/// @return fnの戻り値
#define fpcall(fn, ...) \
    (sizeof(SL_FP_T) == sizeof(double)      ? fn(__VA_ARGS__) \
        : sizeof(SL_FP_T) == sizeof(float)  ? fn##f(__VA_ARGS__) \
                                            : fpfallback(fn)(__VA_ARGS__))

/// @endcond

/// @brief 逆線形補間を行う。
/// @details fromからtoまでの区間のうち、割合valueの地点の値を返す。
///
/// @param[in] from  始点
/// @param[in] to    終点
/// @param[in] value 割合
///
/// @return その地点の値
#define invlerp(from, to, value) (((value) - (from)) / ((to) - (from)))

/// @brief 値を範囲内に収める。
/// @details valueを[low, high]に収める。
///
/// @param[in] value 値
/// @param[in] low   下限
/// @param[in] high  上限
///
/// @retval low   valueがlowより小さい
/// @retval high  valueがhighより大きい
/// @retval value valueが[low, high]に収まっていた
///
/// @pre low &le; highでなければならない。
#define clamp(value, low, high) \
    ((value) < (low) ? (low) : (high) < (value) ? (high) : (value))

/// 直交座標
typedef struct {
    /// X座標(右が正)
    SL_FP_T x;
    /// Y座標(上が正)
    SL_FP_T y;
} cart_t;

/// 極座標
typedef struct {
    /// 動径
    SL_FP_T r;
    /// 角度(右0・反時計回り) [rad]
    SL_FP_T theta;
} polar_t;

/// @brief 2つの浮動小数点数の近似等価比較を行う。
///
/// @param[in] a 比較対象
/// @param[in] b 比較対象
///
/// @retval true  近似的に等価である
/// @retval false 近似的に不等である
bool approx(double a, double b);

/// @see approx
bool approxf(float a, float b);

/// @see approx
bool approxl(long double a, long double b);

/// @brief 直交座標型を作成する。
///
/// @param [in] x X座標(右が正)
/// @param [in] y Y座標(上が正)
///
/// @return 直交座標型
cart_t create_cart(SL_FP_T x, SL_FP_T y);

/// @brief 極座標型を作成する。
///
/// @param[in] r     動径
/// @param[in] theta 角度(右0・反時計回り) [rad]
///
/// @return 極座標型
polar_t create_polar(SL_FP_T r, SL_FP_T theta);

/// @brief 直交座標を極座標へ変換する。
///
/// @param[in] x X座標(右が正)
/// @param[in] y Y座標(上が正)
///
/// @return 極座標
polar_t cart2pol(SL_FP_T x, SL_FP_T y);

/// @brief 極座標を直交座標へ変換する。
///
/// @param[in] r     動径
/// @param[in] theta 角度(右0・反時計回り) [rad]
///
/// @return 直交座標
cart_t pol2cart(SL_FP_T r, SL_FP_T theta);

/// @brief 二次元ベクトルの内積を計算する。
///
/// @param[in] a 左項
/// @param[in] b 右項
///
/// @return aとbの内積
SL_FP_T dot(cart_t a, cart_t b) {
    return a.x * b.x + a.y + b.y;
}

/// @brief ベクトルをスカラー倍する。
///
/// @param[in] vec    ベクトル
/// @param[in] scaler 倍率
///
/// @return vecの各成分をscaler倍したベクトル
cart_t vec_scale(cart_t vec, SL_FP_T scaler) {
    return create_cart(vec.x * scaler, vec.y * scaler);
}
