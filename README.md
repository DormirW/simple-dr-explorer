# 这是东南大学2020级计算机数字图像处理课程实验项目

项目所有代码及相应的raw图像放在了文件夹中，以下是本系统的总体设计、算法设计以及部分代码实现

# 医用X光透视图像（DR）简易浏览器

### 功能需求

#### 灰度窗宽窗位调整

标准读取图像的像素位深为12bit，而显示出的图像位深为8bit，这就要求在读取到显示的过程中完成像素灰度值的映射，即按设置的窗宽窗位进行像素映射

#### 灰度反转

对于不同的医学影像，背景颜色不同有着不同的观察效果。所以提供灰度反转功能，即将灰度图像每一个像素值大小反转

#### 图像放大和缩小

按照需求，放大缩小目标图像，便于医生观察诊断

#### 图像左右翻转

提供镜像翻转图像的功能，便于医生观察诊断

#### 图像锐化

有的情况下成片较为模糊，图像边界并不明显，所以需要进行一定程度的锐化，使得图像边界与一些细节更加明显，便于观察

### 人机交互需求

为方便医生读片，需要有较为良好的人机交互见面

#### 多次调整灰度窗

灰度窗要求方便调整，且显示及时，方便选择最佳的灰度窗

#### 多次灰度反转

需要多次反复反转灰度，以对比效果、观察图片

#### 撤销操作

如果进行设置之后觉得效果不好，可以使用撤销功能撤销本次操作

#### 保存图像

提供保存图像的功能，可以导出处理后的便于观察的图片，用于打印检查报告

## 系统总体设计

基本的设计原则，要尽可能便于设置参数，同时要能够一目了然当前图像的相关参数（如放大了多少倍，旋转了多少度，窗宽窗位是多少），一切以实用性为主，同时尽可能保证系统的稳定性，减少bug的发生。

基本的设计思路则是根据设计原则，除了选择图片与保存图片需要弹窗外，其余操作只使用一级界面，将所有的参数设置与图片显示放在一个界面。设置对应参数后点击“设置图片”，系统从对应的文本框等读出参数，依次调用相应函数对图像进行处理，最后显示处理后的图像。

## 算法设计与实现

##### 算法选择

###### 双线性插值

双线性插值是选择和缩放操作的基础。基本思路是，将映射后的坐标向下取整得到x1, y1，并以此得到x2, y2, 获取这四个点的像素值，通过双线性插值完成对目标点像素值的估计。

所用公式

$$
P(x,y)=(x_2-x)(y_2-y)P_{11}+(x_2-x)(y-y_1)P12\\
+(x-x_1)(y_2-y)P21+(x-x_1)(y-y_1)P22
$$

同时，值得注意的是，进行坐标映射后，计算出的$x_2, y_2$可能会出现越界的情况，赋值时加入越界检测，如果越界则赋值为0。

代码如下：

```cpp
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
```

###### 图像缩放

通过输入的比例系数完成对坐标点的映射，将目标图像的点映射到原始图像中，并通过双线性插值完成像素值估计。

代码如下：

```cpp
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
    //深拷贝防止内存访问冲突
    return temp.copy();
}
```

###### 图像旋转

默认使用逆时针旋转，旋转角度$\alpha$，单位为角度，转换为弧度制，用a表示。

在坐标映射的时候，如果将原始图像旋转计算其坐标，将像素值直接赋给目标图像，思路较为简单，但是映射后的坐标可能是非整数，需要取整，最终会导致有部分点没有被赋值。

所以本实验采用逆向映射，先计算旋转后图像的长宽

$$
targetW=|wcos(a)+hsin(a)|\\
targetH=|wsin(a)+hcos(a)|
$$


以此长宽开辟数组空间，然后遍历数组。

对于每个点，先将其映射到以图像中心为原点的坐标上，然后计算其旋转前的位置

$$
originx=x*cos(a)+y*sin(a)\\
originy=y*cos(a)-x*sin(a)
$$

其中originx, originy即是旋转后的点在原始图像中对应的位置。

当然，目标图像中并非所有点都是由原始图像旋转而来（目标图像经过扩展以使得图像能够完整显示），所以对逆向映射后的坐标进行边界检查，如果不属于原始图像上的点则赋值为0

如果逆向映射后的点属于原始图像，则通过双线性插值，以其周围四个点的像素值估计该点像素值，并赋给目标图像，完成图像的旋转任务。

代码如下：

```cpp
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
```

###### 图像翻转

图像翻转较为简单，主要是坐标映射的任务，原坐标(x, y)以下述公式映射为目标坐标(targetx, targety)：

$$
targety=width-y-1\\
targetx=height-x-1
$$

代码如下：

```cpp
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
```

###### 读取raw文件

使用FILE类型的指针打开文件，然后按字节读取，先读出高宽，再依次读出每个像素值并将像素值存入提前开辟的数组空间

因为每个像素值占两个字节，但是只有低12位有效，所以在存储数据前需要先将读出的16比特数据左移四位，舍弃高四位的数据，再右移四位，恢复像素值的大小

在未设置窗宽窗位之前，默认将[0,4095]的像素值线性映射至[0,255]间。

代码如下：

```cpp
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
```

###### 灰度窗映射及锐化

因为要求锐化操作在灰度窗映射之前，所以将锐化与灰度窗映射结合。

对于灰度窗映射，先判断窗宽是否小于窗位，如果是的话就将颜色取反，并交换窗宽和窗位。

完成判断后进行映射：如果像素值小于等于窗宽，则该像素值映射为0；如果像素值大于等于窗位，则像素值映射为255；如果处于窗内，则进行线性映射

对于锐化操作，使用laplacian算子对图像进行卷积，计算图像水平、竖直以及对角线三个方向的梯度。

卷积核如下

$$
\left[\begin{matrix}
-1 & -1 & -1\\

-1 &  8 & -1\\

-1 & -1 & -1
\end{matrix}\right]
$$

卷积得到的图像即是图像的边缘成分，当然也不可避免的包含了噪声的内容。

将提取出的图像边缘乘以一个比例系数后加到原图，即可完成图像锐化

$$
dst\_image=ori\_image+\alpha*edge\_image
$$

此外，为了有较大的动态范围表现，本次实验对图像的锐化在灰度映射之前，在读取raw文件之后，去除无效的最高四位得到12bit深度的图像数据，对每个像素点进行锐化处理，再经过设置好的窗宽窗位映射之后得到增强后的图像。

代码实现：

```cpp
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
```

###### 撤销操作

撤销操作使用栈来实现，每次读取、设置图像后都会申请一个State对象，用来保存当前的图片数据及其对应的参数，然后压入栈中。当撤销时，将先弹出当前栈顶元素（因为当前栈顶元素为目前显示的图像），然后显示此时的栈顶图像。

```cpp
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
```

###### 直方图均衡化

首先将rgb图像转为灰度图像，统计各个灰度值的数量，并计算概率密度函数，最后将每个像素的灰度值乘以其对应区间的概率密度函数即可。

```cpp
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
    return eqim.copy();//深拷贝防止内存访问冲突
}
```

###### 鲁棒性增强

主要在于按键的处理上。比如未读出图片时如果点击“设置图片”，将会出现意想不到的情况。又如未设置图片的时候，栈内没有历史图像，点击“回退操作”也并不合适。所以引入一些判断条件，在按钮不允许被点击的情况下，将会锁定按钮，禁止该功能。

###### 性能优化

考虑到一些操作需要较大的时间开销，所以系统在实现的时候引入了判定机制，对于改变的参数进行判断。如果改变的参数是例如灰度窗的设置、锐化、直方图均衡化等涉及到截断像素值的操作，那么需要从保存的文件路径重新读取图像；如果改变的参数是例如放大缩小等不会截断像素的操作，则在当前图像上进行操作，无需进行重绘，减少时间开销
