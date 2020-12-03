# Robot-System2020 課題1
ロボットシステム学の課題1置き場です。

# 使用環境・道具
- Raspberry Pi 4 Model B
- ubuntu 20.04
- 5mmLED　x1
- 抵抗器　220Ω　x1
- ブレッドボード
- ジャンパー線　
    - M-M x1
    - F-M x2

# 何がしたいのか？
モールス信号によってメッセージを発します。   
<dl>
  <dt>内容</dt>
  <dd>GORILLA NO UNKO</dd>
  </dl>

# 実行までの流れ
```
git clone https://github.com/Yyoshinuma/Rsys2020.git
cd Rsys2020/myled   
make    
sudo insmod myled.ko    
  sudo rmmod myled  (insmodができない場合)
sudo chmod 666 /dev/myled0    
echo 1 > /dev/myled0    
```

# 実行イメージビデオ
<https://youtu.be/YVg5n7G2vg4>
