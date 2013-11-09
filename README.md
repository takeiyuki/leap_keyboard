leap_keyboard
=============

leapmotionでものエアキーボード実装（適当）です。

ソースが読めたようなものではない気がしますので、ザクッと説明（コメントアウトもないし）。
1.samplelistnerクラスでキャリブレーション、取得したての値をグローバル変数へ移動
2.この中でジェスチャ（指で押したかどうか）も認識、押された場合押したキーボードの位置をtap_positioinに入れる。
  位置はわかりづらいかもしれないが、x,z軸でキーボードの左上を(0,0)にして、キーボードの大きさで除算、整数のみから判断。
  これにより順番に左上から1,2,3...とキーの位置が割り振られる。
3.mainloopの方では、描画と「一度押したら連続しては押されない」というのをやっています。
　これはジェスチャが連続して認識されるためです。
　また押したかおされてないかはtap_list[]に入れてあります。tapped_time[]はどのくらい前に押されたかを保持しています。
　（なんでこの辺りクラスにまとまってないんだろう）
　
　
ほとんどサンプルソースの改変です。
かなり適当にやっているので、もっと効率のいい方法があるかと思います。
