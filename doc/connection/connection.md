# 接続手順書
- [接続手順書](#接続手順書)
  - [ビルド用PCへ接続し、プログラムや設計書を編集する](#ビルド用pcへ接続しプログラムや設計書を編集する)
  - [ビルド用PC以外からプログラムや設計書を参照する(読み取り専用)](#ビルド用pc以外からプログラムや設計書を参照する読み取り専用)

## ビルド用PCへ接続し、プログラムや設計書を編集する
1. スタートメニューを開き、「リモートデスクトップ接続」と検索して開く。  
  ![リモートデスクトップ接続](img/remote.png)

  * Macの人は、App Storeを開いて、「microsoft remote desktop」で検索してください。  
    2つ表示されるので、どちらかを「インストール」してください。  
  ![Macリモートデスクトップ接続](img/mac_remote.png)

1. チームごとに、決められたコンピュータに対して接続する。  
  ![リモートデスクトップ接続2](img/remote2.png)  
  __※接続先アドレスはZoomのチャットで連絡します。__
    |チーム|コンピューター(PC name)|
    |-|-|
    |1|xx.xx.xx.xx|
    |2|xx.xx.xx.xx|
    |3|xx.xx.xx.xx|
    |4|xx.xx.xx.xx|
    |5|xx.xx.xx.xx|
1. 以下ユーザー名とパスワードでログインする。  
  ![リモートデスクトップ接続3](img/remote3.png)
    |チーム|ユーザー名|パスワード|
    |-|-|-|
    |1|intern1\intern1|intern1#####|
    |2|intern2\intern2|intern2#####|
    |3|intern3\intern3|intern3#####|
    |4|intern4\intern4|intern4#####|
    |5|intern5\intern5|intern5#####|
1. ここからはチームメンバに画面共有して進めましょう。
1. Slackを起動する。  
  Zoomのブレークアウトルームに移動後の、社員との連絡手段として使用します。  
  アカウント・ワークスペース設定済みとなっているはずです。
1. デスクトップにある「Z」のリンクを開く。  
    |格納ファイルフォルダ名|内容|
    |-|-|
    |Z:\Internship_program|マイクロマウス用プログラム|
    |Z:\unit_test|単体テスト用プログラム|
    |Z:\設計書\MicroMouse.iproj|マイクロマウス用プログラムの設計書|
    |Z:\マイクロマウス開発手順書.pdf|プログラムのビルド手順書|
    |Z:\マイクロマウス単体テスト手順書.pdf|単体テストの手順書|
    |Z:\接続手順書|本資料へのショートカット|
1. 「マイクロマウス開発手順書.pdf」を開く
1. 手順書を参考に、プログラムがビルドできる(p7まで実施できる)ことを確認し、プログラム開発に入る。
* (参考)PCには以下ツールが入っています。
  * マイクロマウス用コンパイラ(CS+)・・・マイクロマウス用プログラムのコンパイラ
  * 次世代設計ツール NextDesign (デンソークリエイト製ツール！)・・・設計書のエディタ

## ビルド用PC以外からプログラムや設計書を参照する(読み取り専用)
* 開発手順書
  * https://github.com/dcinc-edu2020/intern2021/blob/master/doc/build/マイクロマウス開発手順書.pdf
* 設計書
  * https://dcinc-edu2020.github.io/intern2021/doc/design/index.html
* マイクロマウス用プログラム
  * https://github.com/dcinc-edu2020/intern2021/tree/master/program/Internship_program
* 単体テスト手順書
  * https://github.com/dcinc-edu2020/intern2021/blob/master/doc/build/マイクロマウス単体テスト手順書.pdf
* 単体テスト用プログラム
  * https://github.com/dcinc-edu2020/intern2021/tree/master/program/unit_test

* 走行デモ動画
  * https://github.com/dcinc-edu2020/intern2021/tree/master/doc/movie

## 機能開発向け資料
    |格納ファイルフォルダ名|内容|
    |-|-|
    |Z:\Internship_program2|迷路走行用プログラム|
    |Z:\設計書(迷路走行)\MicroMouse.iproj|迷路走行用プログラムの設計書|
    |Z:\迷路走行プログラムの手引き.pdf|迷路走行の参考資料|

* 迷路走行用プログラム
  * https://github.com/dcinc-edu2020/intern2021/tree/master/program/Internship_program2
* 迷路走行用プログラム設計書
  * https://dcinc-edu2020.github.io/intern2021/doc/design2/index.html
* 迷路走行プログラムの手引き
  * https://github.com/dcinc-edu2020/intern2021/blob/master/doc/build/迷路走行プログラムの手引き.pdf
