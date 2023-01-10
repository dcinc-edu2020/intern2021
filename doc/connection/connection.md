# 接続手順書
- [接続手順書](#接続手順書)
  - [開発用PCへ接続する](#開発用pcへ接続する)
    - [証明書を設定する(windows)](#証明書を設定するwindows)
    - [リモートデスクトップする(windows)](#リモートデスクトップするwindows)
    - [証明書を設定する(mac)](#証明書を設定するmac)
    - [リモートデスクトップする(mac)](#リモートデスクトップするmac)
  - [開発を始める](#開発を始める)
  - [開発用PC以外からプログラムや設計書を参照する(読み取り専用)](#開発用pc以外からプログラムや設計書を参照する読み取り専用)

## 開発用PCへ接続する
<details>
<summary>Windowsの人</summary>

### 証明書を設定する(windows)
* デンソークリエイト内にある開発用PCにアクセスするための証明書を皆さんのPCに登録します。

1. 証明書をダウンロードします。  
   __※証明書のダウンロードURLはZoomのチャットで連絡します。__
1. ダウンロードしたファイルをダブルクリックして開きます。すると証明書の内容が表示されます。  
   「証明書のインストール」をクリックします。  
  ![証明書1](img/cert1.png)  
1. 「次へ」をクリックします。  
  ![証明書2](img/cert2.png)
1. 「証明書をすべて次のストアに配置する」を選択し、「参照」をクリックします。  
  ![証明書3](img/cert3.png)
1. 「信頼されたルート証明機関」を選択し、「OK」をクリックします。  
  ![証明書4](img/cert4.png)
1. 「次へ」をクリックします。  
  ![証明書5](img/cert5.png)
1. 「完了」をクリックします。  
  ![証明書6](img/cert6.png)
1. 「OK」をクリックします。  
  ![証明書7](img/cert7.png)

### リモートデスクトップする(windows)

1. 画面を共有しながら進めましょう。  
    接続に詰まった場合に画面を見せながら相談できます。

1. スタートメニューを開き、「リモートデスクトップ接続」と検索して開いてください。  
  ![リモートデスクトップ接続](img/remote.png)

1. チームごとに、決められたコンピュータに対して接続します。  
  まず、接続に必要な RD ゲートウェイ を設定します。  
  「オプションの表示」をクリックします。  
  ![リモートデスクトップ接続2](img/remote2.png)

1. 「詳細設定」の「任意の場所から接続する」の枠の「設定」をクリックします。  
   ![リモートデスクトップ接続2](img/remote3.png)

1. 「次の RD ゲートウェイサーバー設定を使用する」にチェックを付け、  
  「サーバー名」を以下の通り入力し、「OK」をクリックします。  
    |項目|入力|
    |-|-|
    |サーバー名|__※サーバー名(=ゲートウェイ名)はZoomのチャットで連絡します。__|  

    ![リモートデスクトップ接続2](img/remote4.png)

1. 「全般」に戻り、  
  「コンピューター」と「ユーザー名」を以下の通り入力し、「接続」をクリックします。  
    |項目|入力|
    |-|-|
    |コンピューター|__※コンピューター名(=開発PC名)はZoomのチャットで連絡します。__|
    |ユーザー名|__※ユーザ名はZoomのチャットで連絡します。__|  

    ![リモートデスクトップ接続2](img/remote5.png)

1. 以下ユーザー名とパスワードを入力してOKします。  
   もし自分のアカウント名がすでに入っている場合は、下のほうにある「その他」→「別のアカウントを使用する」を押してください。  
    |項目|入力|
    |-|-|
    |ユーザー名|__※ユーザ名はZoomのチャットで連絡します。__|
    |パスワード|__※パスワードはZoomのチャットで連絡します。__|  

    ![リモートデスクトップ接続3](img/remote6.png)  

2. これで開発用PCにログインできました。  
   接続の練習はここまでです。  
   リモートデスクトップを切断し、次の人に開発用PCに接続してもらいましょう。  

   ![リモートデスクトップ接続4](img/remote7.png)

</details>
<details>
<summary>Macの人</summary>

### 証明書を設定する(mac)
* デンソークリエイト内にある開発用PCにアクセスするための証明書を皆さんのPCに登録します。

1. 証明書をダウンロードします。  
   __※証明書のダウンロードURLはZoomのチャットで連絡します。__
1. ダウンロードしたファイルをダブルクリックして開きます。すると確認のダイアログが表示されるので、  
    キーチェーンを「ログイン」にして「追加」をクリックします。  
  ![証明書1](img/mac_cert1.png)  
  もし以下のようなダイアログが出た場合は、  
  各自のPCのログインユーザ名・パスワードを入力して「キーチェーンを変更」してください。  
  ![証明書2](img/mac_cert2.png)
1. 「キーチェーン」ウィンドウの「ログイン」（もしくは「システム」）内に、  
    "DCLocalRootCA" が入っていれば完了です。  
  ![証明書3](img/mac_cert3.png)

### リモートデスクトップする(mac)
1. 画面を共有しながら進めましょう。  
    接続に詰まった場合に画面を見せながら相談できます。

1. App Storeを開いて、「Microsoft Remote Desktop」で検索します。  
    出てきたアプリを「インストール」して、インストールが終わったら「開く」を押してください。  
  ![Macリモートデスクトップ接続](img/mac_remote.png)

1. 最初に聞かれる内容は「Not now」を選択します。  
  ![Macリモートデスクトップ接続2](img/mac_remote2.png)

1. チームごとに、決められたコンピュータに対して接続するための設定をしていきます。  
  最初に、「Add PC」を押します。  
  ![Macリモートデスクトップ接続3](img/mac_remote_g0.png)

1. 接続に必要な"Gateway"を設定します。  
   "Gateway"の欄を開き、「Add Gateway...」をクリックします。  
  ![Macリモートデスクトップ接続](img/mac_remote_g1.png)

1. GatewayにアクセスするUserを設定します。  
   "User account"の欄を開き、「Add User Account...」をクリックします。  
  ![Macリモートデスクトップ接続](img/mac_remote_g2.png)

1. UsernameとPassword、Friendly nameを以下の通り入力し、  
   「Add」をクリックします。  
    |項目|入力|
    |-|-|
    |Username|__※Username(=ユーザ名)はZoomのチャットで連絡します。__|
    |Password|__※Password(=パスワード)はZoomのチャットで連絡します。__|
    |Friendly name|dc intern|  

    ![Macリモートデスクトップ接続](img/mac_remote_g3.png)

1. Gatewayのダイアログに戻るので、それぞれ以下の通り入力し、  
   「Add」をクリックします。  

    |項目|入力|
    |-|-|
    |Gateway name|__※Gateway name(=ゲートウェイ名)はZoomのチャットで連絡します。__|
    |Friendly name|dc intern|
    |User account|dc intern|

    ![Macリモートデスクトップ接続](img/mac_remote_g4.png)

1. Add PCのダイアログに戻るので、それぞれ以下の通り入力し、  
   「Add」をクリックします。  

    |項目|入力|
    |-|-|
    |PC name|__※PC name(=開発PC名)はZoomのチャットで連絡します。__|
    |User account|dc intern|
    |Friendly name|dc intern|
    |Gateway|dc intern|

    ![Macリモートデスクトップ接続](img/mac_remote_g5.png)

1. 作成されたボタンをダブルクリックします。  
  ![Macリモートデスクトップ接続](img/mac_remote_g6.png)

1. 以下のようなメッセージが出た場合、「Continue」を押します。  
  ![Macリモートデスクトップ接続](img/mac_remote_g7.png)  
  ![Macリモートデスクトップ接続](img/mac_remote_g8.png)

1. これで開発用PCにログインできました。  
   接続の練習はここまでです。  
   リモートデスクトップを切断し、次の人に開発用PCに接続してもらいましょう。  
  ![Macリモートデスクトップ接続](img/mac_remote_g9.png)
</details>

## 開発を始める

1. チームメンバに開発用PCの画面を共有して進めましょう。

1. 開発用PCでSlackを起動する。  
  Zoomのブレークアウトルームに移動後の、社員との連絡手段として使用します。  
  アカウント・ワークスペース設定済みとなっています。

1. 開発用PCのデスクトップにある「Z」のリンクを開き、  
   「1_マイクロマウス開発手順書.pdf」を開きます。  

1. 手順書を参考に、プログラム開発に入りましょう。

* (参考)PCには以下ツールが入っています。
  * マイクロマウス用コンパイラ(CS+)・・・マイクロマウス用プログラムのコンパイラ
  * 次世代設計ツール NextDesign (デンソークリエイト製ツール)・・・設計書のエディタ

## 開発用PC以外からプログラムや設計書を参照する(読み取り専用)
* 開発用PCに格納されているファイルは以下です。  
  以下のリンクは、開発用PC以外(各自のPC)からでも開くことができます。

  |格納ファイルフォルダ名|用途|内容|
  |-|-|-|
  |[Z:\1-1_マイクロマウス開発手順書.pdf](https://github.com/dcincedu/intern/blob/master/doc/build/1-1_マイクロマウス開発手順書.pdf)|1 ゴール停止|プログラムの開発の流れ|
  |[Z:\1_設計書\MicroMouse1.iproj](https://dcincedu.github.io/intern/doc/design/MicroMouse1/index.html)|1 ゴール停止|マイクロマウス用プログラムの設計書|
  |[Z:\1_Internship_program](https://github.com/dcincedu/intern/tree/master/program/1_Internship_program)|1 ゴール停止|マイクロマウス用プログラム|
  |[Z:\1-2_ゴール時停止で使う主なC言語文法.pdf](https://github.com/dcincedu/intern/blob/master/doc/build/1-2_ゴール時停止で使う主なC言語文法.pdf)|1 ゴール停止|ごく簡単なC言語文法資料|
  |[Z:\1-3_設計書の読み方ガイド.pdf](https://github.com/dcincedu/intern/blob/master/doc/build/1-3_設計書の読み方ガイド.pdf)|1 ゴール停止|ゴール停止プログラムの変更完了までの設計書の読み方|
  ||||
  |[Z:\2-1_迷路走行プログラムの手引き.pdf](https://github.com/dcincedu/intern/blob/master/doc/build/2-1_迷路走行プログラムの手引き.pdf)|2 迷路走行|迷路走行プログラムの開発の流れ|
  |[Z:\2_設計書\MicroMouse2.iproj](https://dcincedu.github.io/intern/doc/design/MicroMouse2/index.html)|2 迷路走行|迷路走行プログラムの設計書|
  |[Z:\2_Internship_program](https://github.com/dcincedu/intern/tree/master/program/2_Internship_program2)|2 迷路走行|迷路走行用プログラム|
  |[Z:\2-2_迷路走行プログラムで使う主なC言語文法.pdf](https://github.com/dcincedu/intern/blob/master/doc/build/2-2_迷路走行プログラムで使う主なC言語文法.pdf)|2 迷路走行|ごく簡単なC言語文法資料|
  

* 走行デモ動画
  * https://github.com/dcincedu/intern/tree/master/doc/movie
