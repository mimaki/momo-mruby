# momo-mruby (mruby on GR-PEACH)

**momo-mruby**は、ルネサスエレクトロニクス製のマイコンボード [GR-PEACH](http://gadget.renesas.com/ja/product/peach.html) で動作する「[mruby](http://mruby.org/)」実行環境です。  
mrubyは、人気の開発言語「[Ruby](https://www.ruby-lang.org/)」を軽量化したプログラミング言語で、組込みシステムや様々なソフトウェアに組み込むことができる高機能なプログラミング言語です。  
momo-mrubyは、GR-PEACHマイコンボード上にmruby 1.3.0を動作せることで、以下の機能を提供します。

1. mrubyによる組込みアプリケーションの実行  
microSDに書き込んだmrubyアプリケーションを実行できます。  
mrubyコンパイラ(mrbc)でコンパイルしたmrubyバイナリ(mrbファイル)が実行できます。(mrubyスクリプトの実行もサポート予定)  
また、複数のアプリケーションを連続で実行することも可能です。

3. 対話型mruby(mirb)  
momo-mrubyでは、Rubyのirbに相当する対話型mruby(mirb)を動作させることができます。  
mirbでは対話形式でmrubyスクリプトを動作させることができるため、mrubyスクリプトの簡易実行やmrubyライブラリの動作確認等に利用できます。

3. mruby IoT フレームワーク Plato 対応  
momo-mrubyは、mruby IoT フレームワーク「[Plato](http://plato.click)」に対応しています。Platoで作成したIoTアプリケーションはmomo-mrubyで動作させることができます。

# momo-mruby環境構築

## mrubyビルド環境のセットアップ
momo-mrubyでは、開発環境にmrubyのビルド環境を設定する必要があります。  
mrubyをビルドするためには以下をセットアップする必要があります。

- C言語開発環境 (gcc等)
- Ruby
- GNU Bison

## C言語開発環境

### Windowsの場合
Windows環境でのmrubyのビルドには、Microsoft Visual Studio(VC++)、MinGW(gcc)、Cygwin(gcc)等が利用可能ですが、ここでは[MinGW](http://www.mingw.org/)を使用する前提で説明していきます。  
[MinGWのダウンロードサイト](https://sourceforge.net/projects/mingw/files/Installer/)から**mingw-get-setup.exe**をダウンロードして実行します。（インストール時の設定はデフォルトのままでOKです）

**MinGW Installation Manager**の画面が表示されたら
- mingw32-base
- mingw32-gcc-g++
- msys-base

の3項目を選択して、**Installation**メニューの**Apply Changes**を実行して下さい。  
インストール完了後、以下のファイルのショートカットをデスクトップに作成します。
```
C:¥MinGW¥msys¥1.0¥msys.bat
```
**注意**  
以下、Windows環境でのコマンド実行は、このmsys.batを実行して表示されるコマンド画面から実行するものとします。


### Macの場合  
XcodeのCommand Line Toolsをインストールして下さい。


## Ruby

mrubyをビルドするためには、本家Rubyが必要です。  

### Windowsの場合
[RubyInstaller](https://rubyinstaller.org/)より、2.0.0以降のバージョンのインストーラをダウンロードして、Rubyをインストールして下さい。  

### Macの場合
プリインストールされているRuby、またはrbenvなどでインストールされたRubyがそのまま利用できます。


## GNU Bison

### Windowsの場合  
[Bison for Windows](http://gnuwin32.sourceforge.net/packages/bison.htm)より、**Complete package, except sources**の**Setup**をダウンロードして、Bisonをインストールして下さい。  
インストール先のフォルダ名は **C:¥GnuWin32** に指定するものとします。  
インストール実行後、環境変数 **PATH** に以下を追加して下さい。
```
C:¥GnuWin32¥bin
```

### Macの場合  
**Homebrew**を使用して、以下のコマンドでBisonをインストールします。
```
$ brew install bison
```

以下のコマンドを実行し、上記それぞれにパスが通っていることを確認します。


## mbed CLIのセットアップ

**momo-mruby** では mbed (GR-PEACH) 用にクロスコンパイルするために [mbed CLI](https://github.com/ARMmbed/mbed-cli) を使用します。  
mbed CLIのセットアップ手順を以下に示します。

1. Python 2.7  
mbed CLI を利用するためには Python 2.7 が必要です。(Python 3は利用できません)  
[Python 2.7](https://www.python.org/downloads/release/python-2712/) をセットアップしてください。  
※ momo-mruby上ではPythonは動作しません。

2. Git  
[Git](https://git-scm.com/) 1.9.5 以降をインストールしてください。

3. Mercurial
[Mercurial](https://www.mercurial-scm.org/) 2.2.2 以降をインストールして下さい。

4. GNU ARM Embedded Toolchain  
[GNU ARM Embedded Toolchain 5.4](https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update) をインストールしてください。

以下のコマンドを実行し、上記それぞれにパスが通っていることを確認します。

**Python**
```
$ python --version
Python 2.7.xx
```
**Git**
```
$ git --version
git version 2.x.xxxxxx
```
**Mercurial**
```
$ hg --version
Mercurial - 分散構成管理ツール(バージョン 4.1.2)
(詳細は https://mercurial-scm.org を参照)

Copyright (C) 2005-2017 Matt Mackall and others
本製品はフリーソフトウェアです。
頒布条件に関しては同梱されるライセンス条項をお読みください。
市場適合性や特定用途への可否を含め、 本製品は無保証です。
```
**GNU ARM Toolchain**
```
$ arm-none-eabi-gcc --version
arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors) 5.4.1 20160609 
...
```

パスが通っていない場合はパスを追加して下さい。

### Windowsの場合  
システムのプロパティ - 詳細設定 - 環境変数から、環境変数 **PATH** に以下を追加します。
- C:¥Python27
- C:¥Program Files¥Git¥cmd
- C:¥Program Files (x86)¥GNU Tools ARM Embedded¥5.4 2016q2¥bin  
※ 32bit版Windowsの場合は C:¥Program Files¥GNU Tools ARM Embedded¥5.4 2016q2¥bin

### Macの場合  
```
$ export PATH=$PATH:$INSTALL_DIR/gcc-arm-none-eabi-5_4-2016q2/bin
```

※ **$INSTALL_DIR**には、GNU ARM Toolchainsをインストールしたディレクトリを指定して下さい。


5. mbed CLI  
mbed CLIをインストールします。
```
$ pip install mbed-cli
```


## ソースコードの取得とビルド

以下のコマンドを実行して、 **momo-mruby** のソースコードを取得します。
```
$ cd $WORKING_DIR
$ git clone https://github.com/mimaki/momo-mruby.git --recursive
```

* **$WORKIND_DIR**には、任意のディレクトリを指定して下さい。

```
$ cd momo-mruby
$ make clean
$ make
```
<font color="IndianRed">

### 注意！！  
git clone直後、make clean後、およびmrbgems追加／削除後の make では、コンパイルエラーとなってしまいます。  
この場合は、再度 make (cleanを付けずに) を実行することで、2回目以降は正しく make できるようになります。  
この問題は、今のところ回避手段が見つかっていません。

</font>


# momo-mrubyのGR-PEACHへの書き込み

GR-PEACHをPCにUSB接続します。

MBEDドライブがマウントされるので、以下のファイルをMBEDドライブにコピーします。  
./BUILD/RZ\_A1H/GCC\_ARM/momo-mruby.bin

しばらくすると（数秒以上かかります）MBEDドライブが再度マウントされ、momo-mrubyが起動します。


# mrubyアプリケーションの実行

momo-mruby起動時にmicroSDカードが装着されている場合は、ルートディレクトリにある**autorun.mrb**を実行します。  
mrubyアプリケーションのコンパイルには、mrubyコンパイラ(mrbc)を使用します。app.rbをコンパイルする場合にはmruby/binディレクトリ内のmrbcコマンドを実行します。

```
mrbc -o <出力ファイル名> <mrubyスクリプトファイル名>
```

**例: sample/led.rbをコンパイル**
```
$ cd sample
$ ../mruby/bin/mrbc -o autorun.mrb led.rb
```

コンパイル結果(autorun.mrb)をmicroSDカードのルートディレクトリにコピーして、GR-PEACHのmicroSDスロットに装着します。  
microSD装着後、GR-PEACHをUSB接続して電源投入すると、momo-mrubyが起動し、mrubyアプリケーション(autorun.mrb)が実行されます。  
(led.rbを実行した場合はLEDがカラフルに点滅すれば動作していることが確認できます)


# momo-mrubyの対話モード(mirb)の起動

momo-mruby書き込み後のGR-PEACHをmicroSDを抜いた状態でPCにUSB接続します。  
ターミナルソフト(CoolTerm推奨)を起動して、GR-PEACHに接続します。

### Windowsの場合  
シリアルポートドライバをインストールする必要があります。  
[こちら](https://developer.mbed.org/handbook/Windows-serial-configuration)のページの**Download latest driver**のリンクからインストーラをダウンロードし、インストーラを実行して下さい。  
シリアルポートドライバのインストール後に、GR-PEACHをPCに接続すると、COMx に割り当てられます。

### Macの場合  
usbmodemXXXX に割り当てられます。

ターミナルソフトの設定は下記の通りです。

**Serial Port**

|設定項目|設定値|
|:--|:-:|
|Baudrate|9600|
|Data bits|8|
|Parity|none|
|Stop bits|1|

**Terminal**

|設定項目|設定値|
|:--|:-:|
|Terminal Mode|Line Mode|
|Enter Key Emulation|LF|
|Local Echo|ON|

**Connect**をクリックして、GR-PEACHに接続すると、mirbが開始されます。

**mribの実行例**
```
No disk, or could not put SD card in to SPI idle state
Fail to initialize card
mirb - Embeddable Interactive Ruby Shell

> MRUBY_VERSION
 => "1.3.0"
> p 'Hello, momo-mruby!'
"Hello, momo-mruby!"
 => "Hello, momo-mruby!"
> 
```

<font color="RoyalBlue">

### ポイント  
mrubyアプリケーションの終了後もmirbが実行されます。  

</font>


# ライセンス

本ソフトウェアはMITライセンスのもとで公開しています。[LICENSE](LICENSE) を参照してください。
