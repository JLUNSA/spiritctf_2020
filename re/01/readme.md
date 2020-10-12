## Secure App
本题大致逻辑就是把Flag反过来存到了内存里，输出的时候取flag的前半部分反转过来。

你需要做的就是用IDA定位程序取到的地址，然后转到HEX View，把flag复制出来，写个程序~~或者手动~~把flag翻转过来就好了。
![01](imgs/01.png)

最终Flag为 `Spirit{2aa57287-603a-4c2e-b7a8-978dae5fdd1f}`