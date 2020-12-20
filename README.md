# リポジトリ概要
2020年度ロボットシステム学の課題1の提出ファイルです。

# 何がしたいのか？
モールス信号によってメッセージを発します。   
<dl>
  <dt>内容</dt>
  <dd>GORILLA NO UNKO</dd>
  </dl>

# 動作環境
- ubuntu 20.04.1 LTS

# 使用したもの
- Raspberry Pi 4 Model B
- 5mmLED　x1
- 抵抗器　220Ω　x1
- ブレッドボード
- ジャンパー線　
    - M-M x1
    - F-M x2

# 実行動画
<https://youtu.be/YVg5n7G2vg4>

# 実行までの流れ
- インストール方法
```
git clone https://github.com/Yyoshinuma/Rsys2020.git
cd Rsys2020/myled
make
sudo insmod myled.ko
  sudo rmmod myled  (insmodができない場合これを実行後insmodする)
sudo chmod 666 /dev/myled0
```
- 実行方法
```
echo 1 > /dev/myled0    
```

# ライセンス
GNU General Public Licence v3.0

