# serilib

serilibはロボット制御の計算部分を補佐することを目的とした環境非依存のライブラリです。

- [serilib](#serilib)
  - [機能](#%E6%A9%9F%E8%83%BD)
  - [使用方法](#%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95)
  - [関連ページ](#%E9%96%A2%E9%80%A3%E3%83%9A%E3%83%BC%E3%82%B8)

## 機能

- PID処理
- スティック入力を正規化(-1.0〜0.0〜1.0、√2修正)
- 数学計算
  - ベクトル
  - 逆線形補間
- 足回りのモーター速度計算
  - n輪オムニホイール
  - 2輪クローラー
  - メカナムホイール

## 使用方法

例においてはプロジェクトルート直下に`serilib`という名前で追加することを想定する。

1. プロジェクトのリポジトリにサブモジュールとしてこのリポジトリを追加する\
   例：

   ```shell
   git submodule add https://github.com/mecha-natori/serilib.git serilib
   ```

2. CMakeにserilibを認識させる\
   例：

   ```cmake
   # CMakeLists.txt

   add_subdirectory(serilib)
   ```

3. `target_link_libraries`に以下を加える

   ```cmake
   seri
   ```

   例：

   ```cmake
   # CMakeLists.txt

   target_link_libraries(firmware.elf PRIVATE seri)
   ```

## 関連ページ

- [APIドキュメント](https://mecha-natori.github.io/serilib)
- [Wiki](https://github.com/mecha-natori/serilib/wiki)
