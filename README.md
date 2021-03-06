这适用于esp8266 nodeMCU初学者培训使用，另外附待补全的ino代码

# 电脑部分

1电脑安装文件中的arduino-1.8.13-windows，弹出什么都同意。

2安装8266_package_2.7.4，这样arduino中就有8266库了。

3下载blinker-library-master，将下载好的blinker库解压到 ***\*我的电脑>文档>Arduino>libraries\**** 文件夹中，完成arduino的blink库安装。

4下载文件中的car.ino，放到一个无中文路径的文件夹里面。用arduino打开它，然后

1 认真看注释

2 填写密钥、WiFi名称和密码，这个密钥得在blinker里面申请。例如：![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps525D.tmp.jpg)

3 补全后退和右转的代码

4 检查代码中的引脚是不是和现实焊接的引脚相同，不同则改代码，也可以最后在手机端改，也可以先看小车的情况再改

5 代码写好后连接ESP8266，就是最大的有USB口的那个芯片

6 工具-端口，选择数据线插入的那个端口

7 工具-开发板，选择ESP8266 Boards中的NodeMCU1.0

8 觉得万事具备了，点击左上角“文件”下方的“√”![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps526E.tmp.jpg)，进行验证。存储路径不能出现中文 

9 验证成功后点击√右边的右箭头![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps531B.tmp.jpg)，上传到芯片。验证失败的话就检查下哪里有问题

10 等待芯片连上WiFi，blinker里设定好按键，就可以操控了

 

 

 

 

 


 

# 手机部分

1 下载安装点灯blinker，注册登录。安卓手机用户可以用群文件的安装包。

2 右上角加号-独立设备-网络接入-阿里云-复制key-返回我的设备

3 把key给敲代码的同学，填第一个空

4 顺便把热点名称和密码也给代码同学

5 回到界面后发现出现了一台arduino，点进去，点载入示例。

6 点右上角便签样的东西，进行编辑。

7 底栏“按键”点四下，表示创建四个按键，一个个点进去改数据键名、显示文本和图标样式设置。8 例如前进按键：数据键名：btn-a ，显示文本：前进 ； 样式设计自己选个前进的图标，改好保存。这个btn-啥啥的需要看代码来改，如下图左转是btn-l,右转是btn-r，后退是btn-b.

![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps532B.tmp.jpg) 

9 四个方向都改好之后，点右上角的锁，保存布局。

10 如果操控的时候发现例如左转变成右转的现象，直接把文本和图标换一下就行了

能改软件就不要改硬件

![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps532C.tmp.png) 

 

 

 

# 硬件部分

 
![image](https://user-images.githubusercontent.com/57294382/159697406-ccd9132f-47ce-41ed-8396-8dc83c248e5c.png)

 

## Tips：

1 电池那里不能焊反，会冒烟。为了避免这种情况发生，检查无误再给电池。没有电池也可以先用USB来供电。

2 下方的电源管理芯片BAT接红色线正极，GND黑色线负极。OUT-5V接Vin。

3 马达不用管正负

4 亚克力板贴纸可以撕掉

5 连接线用杜邦线剪掉一半剥线，线公头插面包板，不适合拿去焊接，用剪出来的焊接到马达或芯片上

6 电源管理芯片的GND和VIN是给电池充电用的，暂时不用焊接上去

7 根据电磁感应，8266没有通电的时候，手动旋转电机也可以给8266供电


 ![image](https://user-images.githubusercontent.com/57294382/159697604-c288c86d-2e9f-4468-8a26-cdcf3790ba3e.png)


 

 

 

 

 

 

 

# 理论知识

 

1. ### 直流电机的基本模型

下图为最简单的直流电机，也就是今天我们用的电机，它的固定部分（定子）为两个静止的磁极N、S；旋转部分（转子）为电枢线圈abcd，线圈的首端和末端分别接到两个相互绝缘的圆弧形的换向片上。换向片与一对静止的电刷B1、B2接触，B1接电源正极，B2接电源负极。电枢旋转时，电枢线圈通过换向片和电刷与外电路接通。

![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps535F.tmp.png) 

在直流电动机中，电流并非直接接入线圈，而是通过电刷B1、B2和换向器再接入线圈。因为电刷B1、B2静止不动，电流总是从正极性电刷B1流入，经过旋转的换向片流入位于N极下的导体，再经过位于S极下的导体，由负极性电刷B2流出。故当导体旋转而交替地处于N极和S极下时，导体中的电流将随其所处磁极极性的改变而同时改变其方向，从而使电磁转矩始终保持不变，使电枢向同一个方向旋转，这就是直流电动机的工作原理。

 

 

2. ###  这次使用到的基础语法：

 

写代码的地方主要是在 Arduino IDE 平台进行编写，语法和 C 语言的语法基本没有差别，因此学过 C语言，再来写 Arduino 代码就会轻松很多

 

1. IDE里面有两个函数，分别是

![img](https://gitee.com/jeremyue/image-hosting-service/raw/master/wps5370.tmp.jpg) 

 

从函数的名字中可以看得出来，他们的基本功能，

1.1 setup() 函数

setup()函数，为准备工作的含义，及 arduino 开发板通电一次就会执行的代码。因此里面的所有代码只会执行一次

1.2 loop() 函数

loop() 函数，代表循环函数，也就是说里面的语句会不断的执行



2 arduino 基本函数

2.1 pinMode(pin,mode) 配置引脚

描述：将指定引脚设置为输入 或者 输出

语法：pinMode(pin,mode)

参数：Pin：要设置的引脚

Mode：OUTPUT , INPUT

2.2 digitialWrite(pin,value) 

描述：获取引脚pin的信息value

语法：digitialWrite(pin,value)

参数：Pin：针脚编号 （如 1,5,10,A0,A3）

Value：引脚的高电平或低电平，如 HIGH,LOW

模拟针脚也可以当数字使用

2.3 delay(s) 延时函数

“s”的单位为 毫秒，我们可以直接在 loop() 函数中，使用 delay() 函数

 

3. ### 波特率

在电子通信领域，波特（Baud）即调制速率，指的是有效数据讯号调制载波的速率，即单位时间内载波调制状态变化的次数。

波特率表示每秒钟传送的码元符号的个数，它是对符号传输速率的一种度量，它用单位时间内载波调制状态改变的次数来表示，1波特率即指每秒传输1个符号。波特（Baud，单位符号：Bd）这一单位是以法国电讯工程师埃米尔·博多（英语：Émile Baudot）（1845-1903）的姓氏来命名的，他是数位通讯的先驱之一，是电传与博多式电报机的发明人。

 

 

 

 

## 作品缺陷：

接到云服务器，延迟比较高。登录也比较慢。

代码和思路简单，没有对异常操作做预案，容易出现bug

轮胎抓地力差

不走直线
