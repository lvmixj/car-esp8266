/*注意啦：
 * 写代码的同学需要做的：
 * 1 认真看注释
 * 2 填写密钥、WiFi名称和密码，这个密钥得在blinker里面申请
 * 3 补全后退和右转的代码
 * 4 检查代码中的引脚是不是和现实焊接的引脚相同，不同则改代码
 * 5 代码写好后连接ESP8266
 * 6 工具-端口，选择数据线插入的那个端口
 * 7 工具-开发板，选择ESP8266 Boards中的NodeMCU1.0
 * 8 觉得万事具备了，点击左上角“文件”下方的“√”，进行验证。存储路径不能出现中文 
 * 9 验证成功后点击√右边的又箭头，上传到芯片。验证失败的话就检查下哪里有问题。
 * 10 等待芯片连上WiFi，blinker里设定好按键，就可以操控了
*/


#define BLINKER_WIFI
#include <Blinker.h>

char auth[] = "";  //申请服务器的密钥
char ssid[] = "";  //WiFi名称，建议自己手机开热点，名字和密码简单点
char pswd[] = "";  //WiFi密码

// 新建组件对象。5个按钮。按键名就是blink里面的数据键名
BlinkerButton Button1("btn-a");//前进
BlinkerButton Button2("btn-l");//左转(逆时针)
BlinkerButton Button3("btn-r");//右转(顺时针)
BlinkerButton Button4("btn-b");//后退
BlinkerNumber Number1("num-abc");//计数
BlinkerButton Button5("btn-abc");//点灯

int counter = 0;//初始化计数

//定义引脚名称，如果焊接错了这里可以改

//下面两个分别是左电机的两个引脚
#define L_DIR_PIN       D5
#define L_PWM_PIN       D6

//分别是右电机的两个引脚
#define R_DIR_PIN       D8
#define R_PWM_PIN       D7
//两个引脚电平一高一低才能动，如果本该前进却做出了其他动作
//那就回到这检查下代码是否和实际焊接硬件对上了

#define TIME_TAP       100 //操作间隔


void blinker_car_init()
{
    //初始化输出端引脚
    pinMode(L_DIR_PIN, OUTPUT);
    pinMode(L_PWM_PIN, OUTPUT);
    pinMode(R_DIR_PIN, OUTPUT);
    pinMode(R_PWM_PIN, OUTPUT);
    
    //初始化引脚为低电平，不让电机动
    digitalWrite(L_DIR_PIN, LOW);
    digitalWrite(L_PWM_PIN, LOW);
    digitalWrite(R_DIR_PIN, LOW);
    digitalWrite(R_PWM_PIN, LOW);
}

//按下按键即会执行该函数
//按键1——前进功能的设置
void button1_callback(const String & state) {
  
    //让blinker获取按钮状态
    BLINKER_LOG("get button state: ", state);
    
    //按一下
    if(state=="tap"){
      digitalWrite(L_DIR_PIN,HIGH);//使L_DIR_PIN为高电平
      digitalWrite(R_DIR_PIN,HIGH);//使R_DIR_PIN为高电平
      delay(TIME_TAP);
      digitalWrite(L_DIR_PIN,LOW);//使L_DIR_PIN为低电平
      digitalWrite(R_DIR_PIN,LOW);//使R_DIR_PIN为低电平
    }
    
    //一直按着
    if(state=="press"){
      digitalWrite(L_DIR_PIN,HIGH);
      digitalWrite(R_DIR_PIN,HIGH);
    }
    
    //松开
    if(state=="pressup"){
      digitalWrite(L_DIR_PIN,LOW);
      digitalWrite(R_DIR_PIN,LOW);//最终都要回归低电平，免得乱跑
    }   
}

//按键2——左转(逆时针旋转)的设置
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state=="tap"){
      digitalWrite(L_PWM_PIN,HIGH);//左边电机向后转
      digitalWrite(R_DIR_PIN,HIGH);//右边电机向前转才能左转
      delay(TIME_TAP);
      digitalWrite(L_PWM_PIN,LOW);
      digitalWrite(R_DIR_PIN,LOW);
    }
    if(state=="press"){
      digitalWrite(L_PWM_PIN,HIGH);
      digitalWrite(R_DIR_PIN,HIGH);
    }
    if(state=="pressup"){
      digitalWrite(L_PWM_PIN,LOW);
      digitalWrite(R_DIR_PIN,LOW);
    }   
}

//接下里几个方向同理
//按键3——右转(顺时针旋转)的设置
void button3_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state=="tap"){
      digitalWrite(L_DIR_PIN,HIGH);
      digitalWrite(R_PWM_PIN,HIGH);
      delay(TIME_TAP);
      digitalWrite(L_DIR_PIN,LOW);
      digitalWrite(R_PWM_PIN,LOW);
    }
    
    //---------------------可以点按，但是长按的代码自己写，可以参考左转-------------------------------------
}

//按键4——后退的设置
void button4_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    //-------------------------这里自己写，可以参考前进---------------------------------
}



//下面是灯的设置和设备初始化，不需要改动
void button5_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}
// 初始化串口
void setup() {
    //初始化波特率
    Serial.begin(115200);

    BLINKER_DEBUG.stream(Serial);

    // 初始化有LED的IO
    blinker_car_init();
    pinMode(LED_BUILTIN, OUTPUT);

    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Button4.attach(button4_callback);
    Button5.attach(button5_callback);
}

void loop() {
    Blinker.run();
}
