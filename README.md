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

プロジェクトがGitリポジトリである場合、Gitサブモジュールとして登録すると最新版への追従をGit操作に統合することが出来ます。 また、GitHub
Releaseに使いたいアーキテクチャ向けのビルド済みファイルが存在する場合、これを使用することでビルド時間を短縮することが出来ます。

以下、使用方法ではプロジェクト直下に`serilib`という名前で設置し、その配下に`include`や`lib`が配置されているものとします。また、プロジェクトの出力ファイル(ターゲット)の名前を`firmware.elf`とします。これらの名前は各自で読み替えて下さい。

### ビルド済みファイルをダウンロードして使う場合

1. [GitHub Release](https://github.com/mecha-natori/serilib/releases/latest)から最新版をダウンロードする。

2. プロジェクト内の適当な場所に展開する。

3. CMakeにserilibを認識させる。\
   例：

   ```cmake
   # CMakeLists.txt

   target_include_directories(firmware.elf PUBLIC serilib/include)
   target_link_directories(firmware.elf PRIVATE serilib/lib)
   ```

4. `target_link_libraries`に`seri`を加える。\
   例：

   ```cmake
   # CMakeLists.txt

   target_link_libraries(firmware.elf PRIVATE seri)
   ```

### Gitサブモジュールとして使う場合

1. このリポジトリをGitサブモジュールとして登録する。\
   例：

   ```shell
   git submodule add https://github.com/mecha-natori/serilib.git serilib
   ```

2. CMakeにserilibを認識させる。\
   例：

   ```cmake
   # CMakeLists.txt

   add_subdirectory(serilib)
   ```

3. `target_link_libraries`に`seri`を加える。\
   例：

   ```cmake
   # CMakeLists.txt

   target_link_libraries(firmware.elf PRIVATE seri)
   ```

### ソースコードをダウンロードして使う場合

1. このリポジトリをダウンロードする。(右上の「Code」ボタンや`git clone`など)

2. プロジェクト内の適当な場所に展開する。

3. CMakeにserilibを認識させる。\
   例：

   ```cmake
   # CMakeLists.txt

   add_subdirectory(serilib)
   ```

4. `target_link_libraries`に`seri`を加える。\
   例：

   ```cmake
   # CMakeLists.txt

   target_link_libraries(firmware.elf PRIVATE seri)
   ```

## 関連ページ

- [APIドキュメント](https://mecha-natori.github.io/serilib)
