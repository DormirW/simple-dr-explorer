#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(drawSignal()),this,SLOT(draw()));
    ui->select_2->setDisabled(1);
    ui->return_2->setDisabled(1);
    ui->pushButton->setDisabled(1);
}

void MainWindow::openRaw()//raw文件的读取
{
    //文件对象
    FILE* fp;
    long width,height;
    //用于暂存数据的指针
    long* dptr=new long[1];
    //打开raw文件默认窗口为[0, 4096]
    lowerbound=0;
    upperbound=4096;
    angle=0;
    hrate=1.0;
    wrate=1.0;
    srate=1.0;
    mirrortype=0;
    iss=0;
    isr=0;
    ish=0;
    isw=0;
    isi=0;
    ise=0;

    //打开文件夹中的图片文件
    fname = QFileDialog::getOpenFileName(this,"Choose an raw file please","","RAW Files(*.raw);;All(*.*)");
    //打开文件
    fp=fopen(fname.toLocal8Bit(),"rb");

    //读取前八个字节得到高宽
    fread(dptr,1,4,fp);
    width=*dptr;
    fread(dptr,1,4,fp);
    height=*dptr;

    uchar* data = new uchar[width*height];
    ushort pixels;
    for(long i=0;i<height;i++){
        for (long j=0;j<width;j++) {
            //每次读取两个字节
            fread(dptr,1,2,fp);
            pixels=*dptr;
            //左移四位舍去无效数据，右移四位将像素值归位
            pixels<<=4;
            pixels>>=4;
            //按窗口映射像素值
            pixels=window(pixels);
            data[i*width+j]=pixels;
        }
    }
    fclose(fp);
    //深拷贝防止内存访问冲突
    im=QImage(data,width,height,width,QImage::Format_Grayscale8).copy();
    State st;
    setState(st);
    sta.push(st);
    delete fp;
    delete[] dptr;
    delete[] data;
}

uchar MainWindow::window(ushort p)//实现灰度映射
{
    long l,h;
    if(p>=4096) p=4095;
    //如果窗宽大于窗位，则反色
    if(lowerbound>upperbound){
        h=lowerbound;
        l=upperbound;
        p=4095-p;
    }
    else{
        l=lowerbound;
        h=upperbound;
    }
    //判断像素值是否在窗内，并进行线性映射
    if(p<=l) return 0;
    else if(p>=h) return 255;
    else {
        double a=(((double)(p-l))/((double)(h-l)))*255;
        return (uchar)round(a);
    }
}

uchar MainWindow::windowg(int p)
{
    int l=0;
    int h=255;
    //判断像素值是否在窗内，并进行线性映射
    if(p<=l) return 0;
    else if(p>=h) return 255;
    else {
        double a=(((double)(p-l))/((double)(h-l)))*255;
        return (uchar)round(a);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()//显示图像
{
    QPixmap* map=new QPixmap(QPixmap::fromImage(im));
    ui->imlabel->setPixmap(*map);
}


//按用户输入的窗位与窗宽进行图像映射
//如果选择了锐化，则先锐化再映射
void MainWindow::set()
{
    FILE* fp;
    long* size=new long[1];
    long width,height;
    long* dptr=new long[1];
    fp=fopen(fname.toLocal8Bit(),"rb");
    fread(size,1,4,fp);
    width=*size;
    fread(size,1,4,fp);
    height=*size;
    ushort* src=new ushort[width*height];
    uchar* data = new uchar[width*height];
    ushort pixels;
    for(long i=0;i<height;i++){
        for (long j=0;j<width;j++) {
            fread(dptr,1,2,fp);
            pixels=*dptr;
            pixels<<=4;
            pixels>>=4;
            src[i*width+j]=pixels;
        }
    }
    if(iss) data=laplacian(src,srate,width,height);
    else{
        for(long i=0;i<height;i++){
            for (long j=0;j<width;j++) {
                pixels=window(src[i*width+j]);
                data[i*width+j]=pixels;
            }
        }
    }
    fclose(fp);
    im=QImage(data,width,height,width,QImage::Format_Grayscale8).copy();
    delete fp;
    delete[] size;
    delete[] dptr;
    delete[] data;
}

//获取设置的参数
void MainWindow::get()
{
    lowerbound=ui->low->text().toUShort();
    upperbound=ui->high->text().toUShort();
    hrate = ui->scale_h->text().toDouble();
    wrate = ui->scale_w->text().toDouble();
    angle = ui->rotation->text().toDouble();
    mirrortype = ui->mirror->currentIndex();
    srate=ui->sharp->text().toDouble();
    isr=ui->isr->isChecked();
    isw=ui->isws->isChecked();
    ish=ui->ishs->isChecked();
    iss=ui->iss->isChecked();
    isi=ui->isi->isChecked();
    ise=ui->ise->isChecked();
}

//双线性插值
//参数分别为映射后的坐标，原始图像的像素值，原始图像的宽
uchar MainWindow::binterp(double src_x, double src_y, QImage ima, int ori_w, int ori_h)
{
    //周边四个点的坐标
    int x1,x2,y1,y2;
    uchar p11,p12,p21,p22;
    double w11,w12,w21,w22;
    x1=floor(src_x);
    y1=floor(src_y);
    x2=x1+1;
    y2=y1+1;

    //周边点的像素值
    p11=ima.pixel(y1,x1);
    p12=inImage(ori_w,ori_h,x1,y2)?ima.pixel(y2,x1):0;
    p21=inImage(ori_w,ori_h,x2,y1)?ima.pixel(y1,x2):0;
    p22=inImage(ori_w,ori_h,x2,y2)?ima.pixel(y2,x2):0;


    //权重计算
    w11=(x2-src_x)*(y2-src_y);
    w12=(x2-src_x)*(-y1+src_y);
    w21=(-x1+src_x)*(y2-src_y);
    w22=(-x1+src_x)*(-y1+src_y);

    //插值计算
    return round(p11*w11+p12*w12+p21*w21+p22*w22);
}

QImage MainWindow::laplacian(QImage im, double rate)
{
    int kernel[9]={-1,-1,-1,-1,8,-1,-1,-1,-1};
    int w=im.width();
    int h=im.height();

    //初始化需要返回的图像
    QImage temp=QImage(w,h,QImage::Format_Grayscale8);
    double pixel=0;
    uchar a,data;
    int x,y;
    double p,t;

    for (int i=0;i<h;++i) {
        for (int j=0;j<w;++j) {
            pixel=0;
            for (int k=0;k<9;k++) {
                x=i+k/3-1;
                y=j+k%3-1;
                if(inImage(w,h,x,y)){
                    a=im.pixel(y,x);
                    p=(double)a;
                    t=kernel[k]*p;
                    pixel+=t;
                }
            }
            a=im.pixel(j,i);
            p=(double)a;
            data=windowg((int)round(pixel*rate)+p);
            temp.setPixel(j,i,qRgb(data,data,data));
        }
    }
    return temp.copy();
}

//图像锐化
uchar* MainWindow::laplacian(ushort* src, double rate, int w, int h)
{
    //卷积核
    int kernel[9]={-1,-1,-1,-1,8,-1,-1,-1,-1};

    //存放变换后的数据
    uchar* dst=new uchar[w*h];
    uchar data;

    double pixel=0;
    int x,y;
    double p,t;

    for (int i=0;i<h;++i) {
        for (int j=0;j<w;++j) {
            pixel=0;
            //卷积
            for (int k=0;k<9;k++) {
                x=i+k/3-1;
                y=j+k%3-1;
                if(inImage(w,h,x,y)){
                    p=src[x*w+y];
                    t=kernel[k]*p;
                    pixel+=t;
                }
            }
            p=src[i*w+j];
            if(pixel*rate+p<0) pixel=0;
            p=(ushort)round(pixel*rate+p);
            //映射
            data=window(p);
            dst[i*w+j]=data;
        }
    }
    return dst;
}

//保存参数和图像数据
void MainWindow::setState(State &st)
{
    st.im=im.copy();
    st.angle=angle;
    st.hrate=hrate;
    st.wrate=wrate;
    st.srate=srate;
    st.mirrortype=mirrortype;
    st.iss=iss;
    st.isr=isr;
    st.ish=ish;
    st.isw=isw;
    st.isi=isi;
    st.ise=ise;
    st.upperbound=upperbound;
    st.lowerbound=lowerbound;
    st.fname=fname;
}

//将参数和图像数据读出
void MainWindow::getState(State &st)
{
    im=st.im.copy();
    angle=st.angle;
    hrate=st.hrate;
    wrate=st.wrate;
    srate=st.srate;
    mirrortype=st.mirrortype;
    iss=st.iss;
    isr=st.isr;
    ish=st.ish;
    isw=st.isw;
    isi=st.isi;
    ise=st.ise;
    lowerbound=st.lowerbound;
    upperbound=st.upperbound;
    fname=st.fname;
}

//将设置的参数填入窗口
void MainWindow::init()
{
    ui->low->setText(QString::number(lowerbound));
    ui->high->setText(QString::number(upperbound));
    ui->scale_h->setText(QString::number(hrate));
    ui->scale_w->setText(QString::number(wrate));
    ui->rotation->setText(QString::number(angle));
    ui->mirror->setCurrentIndex(mirrortype);
    ui->sharp->setText(QString::number(srate));
    ui->isr->setChecked(isr);
    ui->isws->setChecked(isw);
    ui->ishs->setChecked(ish);
    ui->iss->setChecked(iss);
    ui->sharp->setText(QString::number(srate));
    ui->isi->setChecked(isi);
    ui->ise->setChecked(ise);
}

QImage MainWindow::invert(QImage im)
{
    int w,h;
    w=im.width();
    h=im.height();
    uchar p;
    QImage temp=QImage(w,h,QImage::Format_Grayscale8);
    for(int i=0;i<h;++i){
        for(int j=0;j<w;++j){
            p=im.pixel(j,i);
            p=255-p;
            temp.setPixel(j,i,qRgb(p,p,p));
        }
    }
    return temp.copy();
}

QImage MainWindow::rgb2gray(QImage rgbim)
{
    return rgbim.convertToFormat(QImage::Format_Grayscale8,Qt::AutoColor);
}

//越界判断函数
bool MainWindow::inImage(int w, int h, double x, double y){
    //用于检查目标点是否在原图像中
    if(x>=0&&x<h&&y>=0&&y<w) return 1;
    else return 0;
}

//旋转
QImage MainWindow::rotation(QImage im, double angle)
{
    im=rgb2gray(im);

    //角度转弧度
    double a=angle/180*PI;
    int cx,cy,tcx,tcy;
    int w,h,tw,th;
    w=im.width();
    h=im.height();

    //计算中心点
    cx=h/2;
    cy=w/2;

    //为了完全显示图像，计算旋转后图像应该的长宽
    tw=abs(w*cos(a))+abs(h*sin(a));
    th=abs(h*cos(a))+abs(w*sin(a));

    //初始化需要返回的图像
    QImage temp=QImage(tw,th,QImage::Format_Grayscale8);

    //旋转后图像的中心点
    tcx=th/2;
    tcy=tw/2;

    //记录插值后的像素值
    uchar pixel;
    int x,y;
    double ox,oy;
    for (int i=0;i<th;++i) {
        for (int j=0;j<tw;++j) {
            //将原点移动到图像中心
            x=i-tcx;
            y=j-tcy;

            //将目标图像位置映射至原始图像
            ox=x*cos(a)+y*sin(a);
            oy=y*cos(a)-x*sin(a);

            //双线性插值赋值
            pixel=inImage(w,h,ox+cx,oy+cy)?binterp(ox+cx,oy+cy,im,w,h):0;
            temp.setPixel(j,i,qRgb(pixel,pixel,pixel));
        }
    }
    return temp.copy();//深拷贝防止内存访问冲突
}

//缩放
QImage MainWindow::scale(QImage im, double wrate, double hrate)
{
    //获取原始长宽
    int ori_w,ori_h;
    ori_w=im.width();
    ori_h=im.height();

    //取整处理
    int tar_w=(int)round(ori_w*wrate);
    int tar_h=(int)round(ori_h*hrate);

    //初始化需要返回的图像
    QImage temp=QImage(tar_w,tar_h,QImage::Format_Grayscale8);

    //记录插值后的像素值
    uchar pixel;

    //获取取整后的比例系数
    double wr,hr;
    wr=(double)(ori_w-1)/(double)(tar_w-1);
    hr=(double)(ori_h-1)/(double)(tar_h-1);

    //赋值
    double src_x,src_y;
    for (int i = 0; i < tar_h; ++i) {
        for (int j = 0; j < tar_w ; ++j) {
            //坐标映射
            src_x=i*hr;
            src_y=j*wr;

            //双线性插值估计像素值
            pixel=binterp(src_x,src_y,im,ori_w,ori_h);
            temp.setPixel(j,i,qRgb(pixel,pixel,pixel));
        }
    }
    return temp.copy();
}

//翻转
QImage MainWindow::mirror(QImage im, int mirror)
{
    //mirror是标识符，1代表水平翻转，2代表竖直翻转，0代表不翻转
    int w,h;
    w=im.width();
    h=im.height();
    QImage temp=QImage(w,h,QImage::Format_Grayscale8);
    uchar pixel;
    if(mirror==1){
        for (int i=0;i<h;++i) {
            for (int j=0;j<w;++j) {
                pixel=im.pixel((w-1-j),i);
                temp.setPixel(j,i,qRgb(pixel,pixel,pixel));//水平翻转
            }
        }
        return temp.copy();
    }
    else if (mirror==2) {
        for (int i=0;i<h;++i) {
            for (int j=0;j<w;++j) {
                pixel=im.pixel(j,(h-1-i));
                temp.setPixel(j,i,qRgb(pixel,pixel,pixel));//竖直
            }
        }
        return temp.copy();
    }
    else{
        return im.copy();
    }
}

QImage MainWindow::equalize(QImage im)
{
    //获取长宽和尺寸
    int row,col;
    row=im.height();
    col=im.width();
    long size=row*col;

    //获取直方图
    unsigned char* grayData = im.bits();
    //    long number[8]={0};
    //    double value[8]={0};
    long number[256]={0};
    double value[256]={0};

    //将灰度值进行统计
    for(int i=0;i<size;i++){
        //        number[(grayData[i]-1)/32]++;
        number[grayData[i]]++;
    }

    //计算概率密度函数
    value[0]=(double)number[0]/(double)size;
    for(int i=1;i<256;i++){
        value[i]=value[i-1]+(double)number[i]/(double)size;
    }

    //均衡化
    for(int i=0;i<size;i++){
        grayData[i]=255*value[grayData[i]];
    }

    //显示图像
    QImage eqim=QImage(grayData,col,row,QImage::Format_Grayscale8);
    return eqim.copy();
}

void MainWindow::on_select_2_clicked()
{
    //获取设置参数
    get();

    //获取当前图的参数
    State st;
    st=sta.top();

    //判断是否需要重新进行灰度映射和锐化或者旋转
    //如果不需要则可以直接获取之前的图像，省去许多重绘的时间
    if(upperbound==st.upperbound&&lowerbound==st.lowerbound&&iss==st.iss&&srate==st.srate&&angle==st.angle&&isr==st.isr&&ise==st.ise){
        im=st.im.copy();
        //缩放
        if(isw&&ish&&wrate!=st.wrate&&hrate!=st.hrate) im = scale(im,wrate/st.wrate,hrate/st.hrate);
        else if((isw&&wrate!=st.wrate)||(isw&&isw!=st.isw)) im = scale(im,wrate/st.wrate,1);
        else if((ish&&hrate!=st.hrate)||(ish&&ish!=st.ish)) im = scale(im,1,hrate/st.hrate);

        //镜像
        if(mirrortype!=st.mirrortype){
            im = mirror(im,st.mirrortype);
            im = mirror(im,mirrortype);
        }

        //灰度反转
        if(isi!=st.isi) im=invert(im);
    }
    else{
        //灰度映射&锐化
        set();

        //缩放
        if(isw&&ish) im = scale(im,wrate,hrate);
        else if(isw) im = scale(im,wrate,1);
        else if(ish) im = scale(im,1,hrate);

        //旋转
        if(isr) im = rotation(im,angle);

        //镜像
        im = mirror(im,mirrortype);

        //灰度反转
        if(isi) im=invert(im);

        //直方图均衡化
        if(ise) im=equalize(im);
    }

    //压栈
    State stt;
    setState(stt);
    sta.push(stt);


    //绘图
    emit drawSignal();

    if(sta.size()<2) ui->return_2->setEnabled(0);
    else ui->return_2->setDisabled(0);
}

void MainWindow::on_select_clicked()
{
    //打开raw文件
    openRaw();

    //初始化参数窗口
    init();

    //发送信号,调用函数显示图片
    emit drawSignal();

    ui->select_2->setEnabled(1);
    ui->pushButton->setEnabled(1);
}

void MainWindow::on_pushButton_clicked()
{
    QString filename1 = QFileDialog::getSaveFileName(this,tr("保存图片"),"",tr("图片(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)"));
    im.save(filename1);
}

void MainWindow::on_return_2_clicked()
{
    sta.pop();
    State st=sta.top();
    getState(st);
    init();
    emit drawSignal();
    if(sta.size()<2) ui->return_2->setEnabled(0);
    else ui->return_2->setDisabled(0);
}
