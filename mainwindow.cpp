// xed /usr/i686-w64-mingw32/include/winuser.rh  /usr/include/X11/keysymdef.h
// for i in $(seq $((0x20)) $((0x7e))); do echo -ne "\x$(printf '%02x' $i)"; done; echo
#include "mainwindow.h"
#include "ui_mainwindow.h"

extern "C" {
#if defined(__linux) || defined(__linux__) || defined(linux)
 #include <X11/Xlib.h>
 #include <X11/keysym.h>
 #include <X11/extensions/XTest.h>
#elif defined(_WIN32) || defined(WIN32) || defined(WINDOWS)
 #include <windows.h>
#endif
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    QString data = ui->plainTextEdit->toPlainText();
    ui->plainTextEdit->setPlainText("");
    ui->plainTextEdit->setEnabled(false);
    QThread::sleep(ui->spinBox->value());
    for(int i = 0; i < data.size(); i++){
        this->keyevent(data[i]);
    }
    ui->plainTextEdit->setEnabled(true);
}

void MainWindow::on_actionExit_triggered(){
    qApp->quit();
}

void MainWindow::on_actionAbout_triggered(){
    QMessageBox::information(this, tr("Paste Anyway"), tr("Paste Anyway v1.0\nCreated By Fugu"), QMessageBox::Ok);
}

void MainWindow::keyevent(QChar x){
    //unsigned char b = x.toLatin1();
    unsigned short b = x.unicode();
qDebug() << b << " -> " << x << " => " << x.unicode();
#if defined(__linux) || defined(__linux__) || defined(linux)
    if(b < 0x20 || b > 0x7e){
        if(b == 0x0a || b == 0x0d){
            this->norm(XK_KP_Enter);
        }else if(b == 8220 || b == 8221){
            this->shift(XK_quotedbl);
        }else if(b == 8216 || b == 8217){
            this->norm(XK_quotedbl);
        }
    }else{
        if(
                (b >= 0x21 && b <= 0x26) ||
                (b >= 0x28 && b <= 0x2b) ||
                (b == 0x3a ) ||
                (b >= 0x3e && b <= 0x5a) ||
                (b >= 0x5e && b <= 0x5f) ||
                (b >= 0x7b && b <= 0x7e)
                ){
            this->shift(b);
        }else if(b == 0x3c){
            this->shift(XK_comma);
        }else{
            this->norm(b);
        }
    }
#elif defined(_WIN32) || defined(WIN32) || defined(WINDOWS)
    if(b == 0x0a || b == 0x0d){
      this->norm(VK_RETURN);
    }else if(b == ' '){
      this->norm(VK_SPACE);
    }else if(b == '!'){
      this->shift('1');
    }else if(b == '"'){
      this->shift(VK_OEM_7);
    }else if(b >= '#' && b <= '%'){
      b += 0x10;
      this->shift(b);
    }else if(b == '&'){
      this->shift('7');
    }else if(b == '\''){
      this->norm(VK_OEM_7);
    }else if(b == '('){
      this->shift('9');
    }else if(b == ')'){
      this->shift('0');
    }else if(b == '*'){
      this->shift('8');
    }else if(b == '+'){
      this->shift(VK_OEM_PLUS);
    }else if(b == ','){
      this->norm(VK_OEM_COMMA);
    }else if(b == '-'){
      this->norm(VK_OEM_MINUS);
    }else if(b == '.'){
      this->norm(VK_OEM_PERIOD);
    }else if(b == '/'){
      this->norm(VK_OEM_2);
    }else if(b >= '0' && b <= '9'){
      this->norm(b);
    }else if(b == ':'){
      this->shift(VK_OEM_1);
    }else if(b == ';'){
      this->norm(VK_OEM_1);
    }else if(b == '<'){
      this->shift(VK_OEM_COMMA);
    }else if(b == '='){
      this->norm(VK_OEM_PLUS);
    }else if(b == '>'){
      this->shift(VK_OEM_PERIOD);
    }else if(b == '?'){
      this->shift(VK_OEM_2);
    }else if(b == '@'){
      this->shift('2');
    }else if(b >= 'A' && b <= 'Z'){
      this->shift(b);
    }else if(b == '['){
      this->norm(VK_OEM_4);
    }else if(b == '\\'){
      this->norm(VK_OEM_5);
    }else if(b == ']'){
      this->norm(VK_OEM_6);
    }else if(b == '^'){
      this->shift('6');
    }else if(b == '_'){
      this->shift(VK_OEM_MINUS);
    }else if(b == '`'){
      this->norm(VK_OEM_3);
    }else if(b >= 'a' && b <= 'z'){
      b -= 0x20;
      this->norm(b);
    }else if(b == '{'){
      this->shift(VK_OEM_4);
    }else if(b == '|'){
      this->shift(VK_OEM_5);
    }else if(b == '}'){
      this->shift(VK_OEM_6);
    }else if(b == '~'){
      this->shift(VK_OEM_3);
    }
#endif
}

void MainWindow::norm(unsigned short x){
#if defined(__linux) || defined(__linux__) || defined(linux)
    Display *display;
    display = XOpenDisplay(NULL);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, x), True, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, x), False, 0);
    XFlush(display);
    XCloseDisplay(display);
#elif defined(_WIN32) || defined(WIN32) || defined(WINDOWS)
    unsigned char key = (unsigned char)(x&0xff);
    keybd_event(key, MapVirtualKey(key, 0), 0, 0);
    keybd_event(key, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0);
#endif
}

void MainWindow::shift(unsigned short x){
#if defined(__linux) || defined(__linux__) || defined(linux)
    Display *display;
    display = XOpenDisplay(NULL);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), True, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, x), True, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, x), False, 0);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, XK_Shift_L), False, 0);
    XFlush(display);
    XCloseDisplay(display);
#elif defined(_WIN32) || defined(WIN32) || defined(WINDOWS)
    unsigned char key = (unsigned char)(x&0xff);
    keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
    keybd_event(key, MapVirtualKey(key, 0), 0, 0);
    keybd_event(key, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
#endif
}
