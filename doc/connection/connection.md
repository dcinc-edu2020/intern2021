# 接続手順書
- [接続手順書](#接続手順書)
  - [開発用PCへ接続する](#開発用pcへ接続する)
  - [開発を始める](#開発を始める)
  - [開発用PC以外からプログラムや設計書を参照する(読み取り専用)](#開発用pc以外からプログラムや設計書を参照する読み取り専用)

## 開発用PCへ接続する
<details>
<summary>Windowsの人</summary>

1. スタートメニューを開き、「リモートデスクトップ接続」と検索して開いてください。  
  ![リモートデスクトップ接続](img/remote.png)

1. チームごとに、決められたコンピュータに対して接続します。  
  「コンピューター」に以下アドレスを記入して「接続」を押します。  
  ![リモートデスクトップ接続2](img/remote2.png)  
  __※接続先アドレスはZoomのチャットで連絡します。__
    |チーム|コンピューター|
    |-|-|
    |1|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |2|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |3|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |4|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |5|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|

1. 以下ユーザー名とパスワードを入力してOKします。  
   自分のアカウント名がすでに入っている場合は、下のほうにある「その他」→「別のアカウントを使用する」を押してください。
  ![リモートデスクトップ接続3](img/remote3.png)
    |チーム|ユーザー名|パスワード|
    |-|-|-|
    |共通|~\intern|intern#1|

1. これで開発用PCにログインできました。  
   ログイン出来たら、チームメンバに開発用PCの画面を共有して進めて行きましょう。
2. 接続の練習はここまでです。  
   リモートデスクトップを切断し、次の人に開発用PCに接続してもらいましょう。 
   ![リモートデスクトップ接続4](img/remote4.png) 
</details>
<details>
<summary>Macの人</summary>

1. App Storeを開いて、「Microsoft Remote Desktop」で検索します。  
    出てきたアプリを「インストール」して、インストールが終わったら「開く」を押してください。  
  ![Macリモートデスクトップ接続](img/mac_remote.png)

1. 最初に聞かれる内容は「Not now」を選択します。  
  ![Macリモートデスクトップ接続2](img/mac_remote2.png)

1. 「Add PC」を押します。  
  ![Macリモートデスクトップ接続3](img/mac_remote3.png)

1. チームごとに、決められたコンピュータに対して接続します。  
  出てきた画面の「PC name」に以下を入れて、「Add」を押します。  
  __※接続先アドレスはZoomのチャットで連絡します。__
    |チーム|PC name|
    |-|-|
    |1|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |2|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |3|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |4|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|
    |5|ml-lab-XXX-XXX-XXX.japaneast.cloudapp.azure.com:XXX|

    ![Macリモートデスクトップ接続4](img/mac_remote4.png)

1. 作成されたボタンをダブルクリックします。  
  ![Macリモートデスクトップ接続5](img/mac_remote5.png)

1. ユーザー名とパスワードに以下を入れて「Continue」を押します。
    |チーム|Username|Password|
    |-|-|-|
    |共通|intern|intern#1|

    ![Macリモートデスクトップ接続6](img/mac_remote6.png)

1. 以下のようなメッセージが出た場合、「Continue」を押します。  
  ![Macリモートデスクトップ接続7](img/mac_remote7.png)

1. これで開発用PCにログインできました。  
   ログイン出来たら、チームメンバに開発用PCの画面を共有して進めて行きましょう。
2. 接続の練習はここまでです。  
   リモートデスクトップを切断(スタートメニュー→電源→切断)し、次の人に開発用PCに接続してもらいましょう。 
   ![Macリモートデスクトップ接続8](img/mac_remote8.png) 
</details>

## 開発を始める

1. チームメンバに開発用PCの画面を共有して進めましょう。

1. 開発用PCでSlackを起動する。  
  Zoomのブレークアウトルームに移動後の、社員との連絡手段として使用します。  
  アカウント・ワークスペース設定済みとなっています。

1. 開発用PCのデスクトップにある「Z」のリンクを開き、  
   「マイクロマウス開発手順書.pdf」を開きます。  

1. 手順書を参考に、プログラムがビルドできる(p7まで実施できる)ことを確認し、プログラム開発に入りましょう。

* その他の格納されているファイルは以下です。
    |格納ファイルフォルダ名|内容|
    |-|-|
    |Z:\Internship_program|マイクロマウス用プログラム|
    |Z:\unit_test|単体テスト用プログラム|
    |Z:\設計書\MicroMouse.iproj|マイクロマウス用プログラムの設計書|
    |Z:\マイクロマウス開発手順書.pdf|プログラムのビルド手順書|
    |Z:\マイクロマウス単体テスト手順書.pdf|単体テストの手順書|
    |Z:\接続手順書|本資料へのショートカット|

* (参考)PCには以下ツールが入っています。
  * マイクロマウス用コンパイラ(CS+)・・・マイクロマウス用プログラムのコンパイラ
  * 次世代設計ツール NextDesign (デンソークリエイト製ツール)・・・設計書のエディタ

## 開発用PC以外からプログラムや設計書を参照する(読み取り専用)
以下のリンクは、開発用PC以外(各自のPC)からでも開くことができます。

* 開発手順書
  * https://github.com/dcincedu/intern/blob/master/doc/build/マイクロマウス開発手順書.pdf
* 設計書
  * https://dcincedu.github.io/intern/doc/design/index.html
* マイクロマウス用プログラム
  * https://github.com/dcincedu/intern/tree/master/program/Internship_program
* 単体テスト手順書
  * https://github.com/dcincedu/intern/blob/master/doc/build/マイクロマウス単体テスト手順書.pdf
* 単体テスト用プログラム
  * https://github.com/dcincedu/intern/tree/master/program/unit_test

* 走行デモ動画
  * https://github.com/dcincedu/intern/tree/master/doc/movie
