因[原版ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)作者長期不更新（202203~202212），本人將此分支發佈到Arduino公開庫，改名為Cpp_Standard_Library以示區分。

本函式庫試圖在Arduino上實作C++11~17標準函式庫（STL）的大部分功能。除了ArduinoSTL以外，本函式庫部分功能實作也參考了MSVC、LLVM和boost。因為是依照STL做的接口，所以不需要另外寫文檔，你可以參考任何一個權威的STL文檔。除非另有說明，否則本函式庫的使用方法應該是一樣的，如果不一樣那應該就是個bug，歡迎提交Issue。

如果你需要某些標準函式庫中應有而本函式庫中尚未提供的功能，也歡迎提交Issue，作者將會優先為你實作。

目前支援AVR和SAM架構。暫時沒有支援ESP32的計劃，因為ESP32官方已經提供了標準庫，同時使用兩套標準庫將產生許多難以處理的問題。

自從[原始ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)沒有更新或時間較長（202203~202212），我將這個分支發佈到Arduino公共庫，並重命名為Cpp_Standard_Library以區別。

該函式庫嘗試在 Arduino 上實作 C++11~17 標準函式庫（STL）的大部分功能。除了ArduinoSTL之外，這個函式庫的一些功能實作也參考了MSVC、LLVM和boost。因為介面是根據STL來做的，所以不需要額外寫文檔，可以參考任何權威的STL文檔。除非另有說明，該庫的使用和行為應該是相同的；如果不同，則應該是一個錯誤，歡迎提交問題。

如果你需要一些標準庫中提供但本庫中尚未提供的功能，也歡迎你提交issue，作者會優先為你實現。

目前支援 AVR 和 SAM 架構。目前還沒有計劃支援 ESP32，因為 ESP32 已經官方提供了標準庫。並行使用兩個標準函式庫會產生很多棘手的問題。

# 招牌功能（不限於此） Signature features (not limited to this)

-   `<algorithm> fill_n shuffle`
-   `<chrono> chrono::duration`
-   `<iostream> cin cout`使用串口作為標準輸入輸出流
-   `<map>`
-   `<memory> unique_ptr`
-   `<random> mt19937, ArduinoUrng`：`mt19937`佔記憶體較多（約5K），謹慎使用。`ArduinoUrng`是Arduino平台特定的`UniformRandomNumberGenerator`，可用於`shuffle`。
-   `<ratio>`
-   `<set>`
-   `<type_traits>`
-   `<vector>`
-   `<xutility> std::begin std::end`

# 原版README（僅供參考，部分內容已過時）

這是封裝為 Arduino 函式庫的 C++ 標準函式庫的實作。該庫透過將關鍵的 C++ 功能添加到 Arduino 環境中來支援我的 CS-11M 課程的教學。

該函式庫是從 uClibc++ 移植的：

<http://git.uclibc.org/uClibc++>

使用 Andy Brown 的 Arduino 庫的串流實現：

<http://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/>

## 使用 printf() 和 scanf()

ArduinoSTL 頭檔包含將您選擇的序列埠綁定到的程式碼
stdio 原語。這會自動發生，但用戶仍然必須調用
串行.begin()

```c++
#include <ArduinoSTL.h>

void setup() {
  Serial.begin(9600); 
  printf("Hello World\n");
}
```

## 使用`cin`一個`cout`

當您包含此頭檔時，您將自動獲得 cin 和 cout 基於`Serial`。請參閱下文以了解如何指定您自己的設備。這是一個使用範例草圖`cin`和`cout`.

```c++
#include <ArduinoSTL.h>

using namespace std;

void setup() {
  Serial.begin(9600);
  cout << "Feed me an integers." << endl;
}

void loop() {
  int foo;
  if (cin >> foo) { 
    cout << "You fed me " << foo << endl;
  }else{
    cin.clear();
    cin.ignore();
  }
}
```

## 更改串口

您可以變更串口`cin`,`cout`和`printf()`使用。您可以使用內建序列埠（例如`Serial1`在 Leonardo 上）或者您可以使用軟體序列埠來實現`Stream`.

### 使用內建連接埠

在`src/ArduinoSTL.cpp`改變的值`ARDUINOSTL_DEFAULT_SERIAL`。保留其他預設值不註釋。

### 使用軟體序列埠。

放`ARDUINO_DEFAULT_SERAL` to `NULL`。註解掉其他預設值。

以下是使用 SofwareSerial 的範例草圖：

```c++
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1);

namespace std { 
  ohserialstream cout(mySerial);
  ihserialstream cin(mySerial);
}

void setup() {
  mySerial.begin(9600);
  ArduinoSTL_Serial.connect(mySerial);
}
```

## 避免實例化`cin`和`cout`

註解掉`ARDUINOSTL_DEFAULT_CIN_COUT`並且什麼都不會被實例化。如果您打算選擇非預設串列端口，則必須註解掉該標誌。使用時沒有明顯的開銷`printf()`所以你目前無法避免初始化它。

## Known Issues

使用列印浮點數和雙精度數`cout`忽略格式說明符。

uClibc 似乎相當完整。即使 Arduino 可用的堆數量有限，字串和向量都可以工作。 uClibc++ 狀態頁面可以在這裡找到：

<https://cxx.uclibc.org/status.html>

始終使用最新的 Arduino IDE。本函式庫使用 Arduino IDE 函式庫規格 rev.2.1，其功能僅在 Arduino 1.6.10 及更高版本上可用。該規範可以在這裡找到：

<https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification>

## 執照

uClibc++ 函式庫根據 LGPL 取得許可。該專案採用 LGPL 與其使用的大部分程式碼相容。除非另有說明，否則所有程式碼均根據 LGPL 獲得許可。有一個例外：

-   根據 Andy Brown 的意願，src/serstream 在 BSD 許可證下獲得許可：<http://andybrown.me.uk/terms-and-conditions/>