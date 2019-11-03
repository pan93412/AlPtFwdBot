# AlPtFwdBot
一個能轉傳私訊，並允許回覆的機器人

## 編譯
請先安裝：

- Threads (編譯器可能已經內建)
- OpenSSL 函式庫
- Boost (元件：system) 函式庫
- libcurl (選用)
- zlib

之後執行：

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```

即可編譯。

## 使用
```
I: usage: ./AlPtFwd token 接收者
I: token   @BotFather 取得的機器人憑證
I: 接收者  誰要接收轉傳的訊息？設 0 則不受理轉傳訊息。
```

1. 記得把機器人先加進目的地群組
2. 先 `./AlPtFwd [憑證] 0` 後進去想要作為轉傳目的地的群組
3. 輸入 `/chatid` 取得聊天室 ID
4. 關閉機器人後 `./AlPtFwd [憑證] [聊天室 ID]`

## 使用範例
<table>
  <tr>
    <th>管理方</th>
    <th>傳送方</th>
  </tr>
  <tr>
    <td>
<pre>
  作者, [03.11.19 02:57]
  /chatid

  StarsBot, [03.11.19 02:57]
  ###已清除###

  StarsBot, [03.11.19 02:57]
  [轉傳自 作者]
  Test!

  StarsBot, [03.11.19 02:57]
  [回覆給 StarsBot]
  來源：###已清除###
  傳送者：作者 (###已清除###)
  若要回覆，請用 /reply ###已清除###-806 訊息 。

  作者, [03.11.19 02:58]
  /reply ###已清除###-806 喔嗨

  StarsBot, [03.11.19 02:58]
  [回覆給 作者]
  我們幫你轉傳出去了喔！👍
</pre>
    </td>
    <td>
<pre>
  作者, [03.11.19 02:57]
  Test!

  StarsBot, [03.11.19 02:58]
  [回覆給 作者]
  我們幫你轉傳出去了喔！👍

  StarsBot, [03.11.19 02:58]
  [回覆給 作者]
  喔嗨
</pre>
    </td>
  </tr>
</table>

## 授權條款
MIT License

## 作者
- pan93412, 2019.
