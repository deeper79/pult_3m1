#include "video.h"

V4L2_video_class::V4L2_video_class(QObject *parent)
    : QObject(parent),rX(1600),rY(1200),num_input(0),pDevice(-1),ResizeEnable(true)
{

    img = new QImage(720,576,QImage::Format_RGB16);
    out = new QImage(1920,1080,QImage::Format_RGB888);


}
QList<QString*> V4L2_video_class::GetAviableDevice(){
    QList<QCameraInfo> info;
    QList<QString*> cameras;
    info = QCameraInfo::availableCameras();

    for (const QCameraInfo &info : info) {
        cameras << new QString(info.deviceName());
    }
    return cameras;
}

QString V4L2_video_class::CurrentFormatInput() const {
    if(!pDevice) return NULL;
    v4l2_std_id std_id;
    struct v4l2_standard standard;
    if(ioctl(pDevice, VIDIOC_G_STD, &std_id) == -1){
        qDebug() << "error VIDIOC_G_STD function: CurrentFormatInput";
        return NULL;
    }
    memset(&standard, 0, sizeof(standard));
    standard.index = 0;
    while (ioctl(pDevice, VIDIOC_ENUMSTD, &standard) == 0) {
        if (standard.id & std_id) {
            qDebug() << "Current video standard:" << QString((char *)standard.name);
            break;
        }

        standard.index++;
    }
    return QString((char *)standard.name);
}

bool V4L2_video_class::OpenDevice(const char *dev){

    struct stat st;
    struct v4l2_capability cap;

    if(stat(dev,&st)==-1){
        qDebug() << "Неизвестное устройство" << dev_name << errno << strerror(errno);
        return false;
    }

    if(!S_ISCHR(st.st_mode)){
        qDebug() << "Не устройство"<< dev_name << errno  << strerror(errno);
        return false;
    }

    pDevice = open(dev,O_RDWR|O_NONBLOCK,0);

    if(pDevice ==-1){

        qDebug() << "Cannot open " << dev_name << errno << strerror(errno);
        return false;
    }

    if(ioctl(pDevice,VIDIOC_QUERYCAP,&cap) == -1){

        if(EINVAL == errno){
            qDebug() << dev << "is no V4L2 device";
            return false;
        }else{
            qDebug() << dev << " ???????";
        }
    }
    qDebug() << "Name: " << QString((char *)cap.card) <<"Driver: " << QString((char *)cap.driver);

    if(!(cap.capabilities&V4L2_CAP_VIDEO_CAPTURE)){

        qDebug() << dev << "is no video capture device";
        return false;
    }
    return true;
}

void V4L2_video_class::SuppotedFormatInput(void) const{

    if(!pDevice) return;

    struct v4l2_input input;
    struct v4l2_standard standard;

    if (-1 == ioctl(pDevice, VIDIOC_G_INPUT, &input.index)) {
        qDebug()<<"error VIDIOC_G_INPUT ";
    }

    if (-1 == ioctl(pDevice, VIDIOC_ENUMINPUT, &input)) {
        qDebug()<<"error VIDIOC_ENUMINPUT ";
    }

    qDebug()<< "Current input  supports:"<< QString((char *)input.name);

    memset(&standard, 0, sizeof(standard));
    standard.index = 0;

    while (0 == ioctl(pDevice, VIDIOC_ENUMSTD, &standard)) {
        if (standard.id & input.std)
            qDebug()<< QString((char *)standard.name);

        standard.index++;
    }

    if (errno != EINVAL || standard.index == 0) {
        qDebug()<<"error VIDIOC_ENUMINPUT ";
    }
}
/*bool V4L2_video_class::ResetCroppingParameters(void){
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;

    memset (&cropcap, 0, sizeof (cropcap));
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == ioctl (pDevice, VIDIOC_CROPCAP, &cropcap)) {
      //  perror ("VIDIOC_CROPCAP");
        return -1;
    }

    memset (&crop, 0, sizeof (crop));
    crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    crop.c = cropcap.defrect;



    if (-1 == ioctl (pDevice, VIDIOC_S_CROP, &crop)
        && errno != EINVAL) {
       // perror ("VIDIOC_S_CROP");
        return -1;
    }
}
bool V4L2_video_class::VideoDownSampling(void){
    struct v4l2_cropcap cropcap;
    struct v4l2_format format;

    ResetCroppingParameters();

    memset (&format, 0, sizeof (format));

    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    format.fmt.pix.width = cropcap.defrect.width >> 1;
    format.fmt.pix.height = cropcap.defrect.height >> 1;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;

    if (-1 == ioctl (pDevice, VIDIOC_S_FMT, &format)) {
        perror ("VIDIOC_S_FORMAT");
        exit (EXIT_FAILURE);
    }
}*/

void V4L2_video_class::SuppotedFormatFrame(){
    struct  v4l2_frmsizeenum fmt;
    fmt.index = 0;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while (ioctl(pDevice,VIDIOC_ENUM_FRAMESIZES, &fmt) == 0) {
        fmt.index++;
    }
    return;
}
void V4L2_video_class::DeInitDevice(void){
    for(uint i=0;i<n_buffers;i++){
        if(munmap(buffers[i].start,buffers[i].length)== -1){
            qDebug()<<"Error unmap buffers" << strerror(errno);
        }
    }
    delete buffers;
    close(pDevice);
    pDevice = -1;
}

bool V4L2_video_class::SetFrameFormat(QSize size) const{

    struct v4l2_format frm;


    memset(&frm, 0, sizeof(frm));

    frm.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    frm.fmt.pix.width       = size.width();
    frm.fmt.pix.height      = size.height();
    frm.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB565;

    if(ioctl(pDevice,VIDIOC_S_FMT,&frm) == -1){
        qDebug()<<"Error setting format: "<< strerror(errno) ;
        return false;
    }
    return true;
}

bool V4L2_video_class::SelectFormatInput(v4l2_std_id std_id,uint number){

    if(!pDevice) return false;

    struct v4l2_input input;
    memset(&input, 0, sizeof(input));
    input.index = number;
    if(ioctl(pDevice, VIDIOC_G_INPUT, &input.index)==-1){
        qDebug() << "error VIDIOC_G_INPUT";
        return false;
    }
    if( ioctl(pDevice, VIDIOC_ENUMINPUT, &input)==-1){
        qDebug() << "error VIDIOC_ENUMINPUT";
    }
    if((input.std & std_id) == 0){
        qDebug() << "Format: " << QString((char *)input.std) << "not suppoted";
        return false;
    }
    if(ioctl(pDevice, VIDIOC_S_STD, &std_id) == -1){
        qDebug() << "Can`t change format: " << strerror(errno) ;
        return false;
    }
    return true;
}


int V4L2_video_class::read_frame(void){

    struct v4l2_buffer buf;

    memset(&buf,0,sizeof(buf));
    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if ((ioctl(pDevice, VIDIOC_DQBUF, &buf))==-1) return false;
    assert(buf.index < n_buffers);

    process_image(buffers[buf.index].start);

    if (ioctl(pDevice, VIDIOC_QBUF, &buf)==-1)    return false;

    return true;
}

bool V4L2_video_class::StartCapturing(void){

    enum v4l2_buf_type type;

    for(uint i =0 ; i<n_buffers;i++){
        struct v4l2_buffer buf;
        memset(&buf,0,sizeof(buf));

        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;

        if(ioctl(pDevice,VIDIOC_QBUF,&buf) == -1)  return false;

        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

        if(ioctl(pDevice,VIDIOC_STREAMON,&type) == -1) return false;
    }
    return true;
}

bool V4L2_video_class::InitDevice(){

    SelectFormatInput(V4L2_STD_PAL_D1,1);
    if(!SetFrameFormat(QSize(720,576))) return false;
    if(!InitMmap()) return false;
   // SuppotedFormatInput();
 //   SuppotedControls();
   // allControl();
     //VideoDownSampling();
    return true;
}

void V4L2_video_class::MainLoop(void){

    fd_set fds;
    struct timeval tv;
    int r;

    FD_ZERO(&fds);
    FD_SET(pDevice, &fds);
    for (;;) {
        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        r = select(pDevice + 1, &fds, NULL, NULL, &tv);

        if (r == -1) {
            if (EINTR == errno)
                continue;
        }
        if (r == 0) {
            qDebug() << "select timeout";
            return;
        }
        read_frame();
    }
    return;
}

bool V4L2_video_class::StopCapturing(void){
    enum v4l2_buf_type type;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(pDevice, VIDIOC_STREAMOFF, &type) == -1){
        return false;
    }
    return true;
}

bool V4L2_video_class::InitMmap(void){

    struct v4l2_requestbuffers req;

    memset(&req,0,sizeof(req));
    req.count  = 4;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if(ioctl(pDevice,VIDIOC_REQBUFS,&req)==-1){
        if(EINVAL == errno){
            qDebug() << "Device not suppoted memore mapping";
            return false;
        }
    }

    if(req.count < 2){
        qDebug() << "Insufficient buffer memory on device" ;
        return false;
    }

    buffers = new buffer[4];

    for(n_buffers = 0;n_buffers<req.count;n_buffers++){

        struct v4l2_buffer buf;
        memset(&buf,0,sizeof(buf));

        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = n_buffers;

        if(ioctl(pDevice,VIDIOC_QUERYBUF,&buf) == -1){
            return false;
        }

        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start  = mmap(NULL,
                                         buf.length,
                                         PROT_READ|PROT_WRITE,
                                         MAP_SHARED,
                                         pDevice,
                                         buf.m.offset);
        if(MAP_FAILED == buffers[n_buffers].start){
            return false;
        }

    }

    return true;
}

void V4L2_video_class::process_image(const void *p){
//#pragma omp parallel num_threads(MAX_NUM_THREADS)
   // {
//#pragma omp master
  //      {
            *img = QImage((uchar *)p,720,576,QImage::Format_RGB16).convertToFormat(QImage::Format_RGB888);

 //       }
 //   }

    if(ResizeEnable) {
        ResizeFrameOpenMP();
        emit haveFrame(out);
    }
    else{
        emit haveFrame(img);
        //img->save("out.jpg");
    }
//}

}
void V4L2_video_class::SuppotedControls(){
    memset(&queryctrl, 0, sizeof(queryctrl));

    queryctrl.id = V4L2_CTRL_FLAG_NEXT_CTRL;
    while (0 == ioctl(pDevice, VIDIOC_QUERYCTRL, &queryctrl)) {
        if (!(queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)) {
            qDebug() << "Control" << QString((char *)queryctrl.name);

            if (queryctrl.type == V4L2_CTRL_TYPE_MENU)
                enumerate_menu(queryctrl.id);
        }

        queryctrl.id |= V4L2_CTRL_FLAG_NEXT_CTRL;
    }
    if (errno != EINVAL) {
        perror("VIDIOC_QUERYCTRL");
        exit(EXIT_FAILURE);
    }
}
void V4L2_video_class::allControl(void){
    struct v4l2_query_ext_ctrl query_ext_ctrl;

    memset(&query_ext_ctrl, 0, sizeof(query_ext_ctrl));

    query_ext_ctrl.id = V4L2_CTRL_FLAG_NEXT_CTRL | V4L2_CTRL_FLAG_NEXT_COMPOUND;
    while (0 == ioctl(pDevice, VIDIOC_QUERY_EXT_CTRL, &query_ext_ctrl)) {
        if (!(query_ext_ctrl.flags & V4L2_CTRL_FLAG_DISABLED)) {

            qDebug() << "Control" << QString((char *)query_ext_ctrl.name);


            if (query_ext_ctrl.type == V4L2_CTRL_TYPE_MENU)
                enumerate_menu(query_ext_ctrl.id);
        }

        query_ext_ctrl.id |= V4L2_CTRL_FLAG_NEXT_CTRL | V4L2_CTRL_FLAG_NEXT_COMPOUND;
    }
    if (errno != EINVAL) {
        perror("VIDIOC_QUERY_EXT_CTRL");
        exit(EXIT_FAILURE);
    }
}
void V4L2_video_class::enumerate_menu(__u32 id){

        qDebug() << "  Menu items:\\n";

        memset(&querymenu, 0, sizeof(querymenu));
        querymenu.id = id;

        for (querymenu.index = queryctrl.minimum;
             querymenu.index <= queryctrl.maximum;
             querymenu.index++) {
            if (0 == ioctl(pDevice, VIDIOC_QUERYMENU, &querymenu)) {
                qDebug()<< querymenu.name;
            }
        }

}

V4L2_video_class::~V4L2_video_class()
{

}

bool V4L2_video_class::ResizeFrame(void){

    IppiResizeSpec_32f *pSpec;
    int                specSize     = 0;
    Ipp8u              *pBuffer     = 0;
    Ipp8u              *pInitBuf    = 0;
    Ipp32u             numChannels  = 3;
    IppiPoint          dstOffset    = {0, 0};
    IppStatus          status       = ippStsNoErr;
    IppiBorderType     border       = ippBorderRepl;
    IppiSize           srcSize      = {img->width(),img->height()};
    IppiSize           dstSize      = {rX,rY};
    Ipp8u              *pSrc       = img->bits();
    Ipp8u              *pDst       = out->bits();
    Ipp32s             srcStep      = 3*img->width();
    Ipp32s             dstStep      = 3*rX;
    int                initSize     = 0;
    int                bufSize      = 0;

    status = ippiResizeGetSize_8u(srcSize,
                                  dstSize,
                                  ippLanczos,
                                  0,
                                  &specSize,
                                  &initSize);

    if (status != ippStsNoErr) return status;

    pInitBuf = ippsMalloc_8u(initSize);
    pSpec    = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize);

    if (pInitBuf == NULL || pSpec == NULL)
    {
        ippsFree(pInitBuf);
        ippsFree(pSpec);
        return ippStsNoMemErr;
    }

    status = ippiResizeLanczosInit_8u(srcSize, dstSize, 3, pSpec, pInitBuf);
    ippsFree(pInitBuf);

    if (status != ippStsNoErr)
    {
        ippsFree(pSpec);
        return status;
    }

    /* work buffer size */
    status = ippiResizeGetBufferSize_8u(pSpec, dstSize, numChannels, &bufSize);
    if (status != ippStsNoErr)
    {
        ippsFree(pSpec);
        return status;
    }

    pBuffer = ippsMalloc_8u(bufSize);
    if (pBuffer == NULL)
    {
        ippsFree(pSpec);
        return ippStsNoMemErr;
    }
    /* Resize processing */
    status = ippiResizeLanczos_8u_C3R(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, border, 0, pSpec, pBuffer);

    ippsFree(pSpec);
    ippsFree(pBuffer);
    // out->save("/home/pult/resize.jpg");


    return true;
}

bool V4L2_video_class::ResizeFrameOpenMP(void){

    IppiResizeSpec_32f* pSpec = 0;            // Структура указатель на преобразование
    int specSize = 0, initSize = 0;           // Размер структур на преобразование
    Ipp8u* pBuffer  = 0;                      // Указатель на буффер преобразования
    Ipp8u* pInitBuf = 0;                      // Указатель на буффер нинчилаизации преобразования
    IppStatus status = ippStsNoErr;           // Статус ошибки - "нет ошибки"
    IppiBorderSize borderSize = {0, 0, 0, 0}; // Размер бордера
    IppiBorderType border = ippBorderRepl;    // Повтор бордера по краям
    int numThreads, slice, tail;              // количесво потоков, частей обработки и остаток
    int bufSize1, bufSize2;                   // размеры выходных буфферов
    IppiSize dstTileSize, dstLastTileSize;    // количество строк выходных буфферах и послденем буффере
    IppStatus pStatus[MAX_NUM_THREADS];       // массив ошибок для каждого потока

    IppiSize           srcSize      = {img->width(),img->height()}; // размер входного изображения
    IppiSize           dstSize      = {rX,rY};                      // размер выходного изображения
    Ipp8u              *pSrc        = img->bits();                  // указатель на начало данных входного изображения
    Ipp8u              *pDst        = out->bits();                  // указатель на начало данных выходного изображения
    Ipp32s             srcStep      = 3*img->width();               // количество байт в строке входного изображения
    Ipp32s             dstStep      = 3*rX;                         // количество байт в строке выходного изображения

    status = ippiResizeGetSize_8u(srcSize       ,
                                  dstSize       ,
                                  ippCubic     ,
                                  0             ,
                                  &specSize     ,
                                  &initSize    ); // определение размеров необходимых буфферов

    if (status != ippStsNoErr) return status;    // если ошибка вернуть статус ошибки и выйти
    pInitBuf = ippsMalloc_8u(initSize);          // выделяем память под буффер иницилизации
    pSpec    = (IppiResizeSpec_32f*)ippsMalloc_8u(specSize); // выделяем память под буффер работы

    if (pInitBuf == NULL || pSpec == NULL)
    {
        ippsFree(pInitBuf);
        ippsFree(pSpec);
        return ippStsNoMemErr;
    }

    status = ippiResizeLinearInit_8u(srcSize, dstSize, pSpec);
    ippsFree(pInitBuf);

    if (status != ippStsNoErr)
    {
        ippsFree(pSpec);
        return status;
    }

    status = ippiResizeGetBorderSize_8u(pSpec, &borderSize);
    if (status != ippStsNoErr)
    {
        ippsFree(pSpec);
        return status;
    }

#pragma omp parallel num_threads(MAX_NUM_THREADS)
    {
#pragma omp master
        {
            numThreads = omp_get_num_threads();
            slice = dstSize.height / numThreads;
            tail  = dstSize.height % numThreads;

            dstTileSize.width = dstLastTileSize.width = dstSize.width;
            dstTileSize.height = slice;
            dstLastTileSize.height = slice + tail;

            ippiResizeGetBufferSize_8u(pSpec, dstTileSize, ippC3, &bufSize1);
            ippiResizeGetBufferSize_8u(pSpec, dstLastTileSize, ippC3, &bufSize2);

            pBuffer = ippsMalloc_8u(bufSize1 * (numThreads - 1) + bufSize2);
        }

#pragma omp barrier
        {
            if (pBuffer)
            {
                Ipp32u  i;
                Ipp8u  *pSrcT, *pDstT;
                Ipp8u  *pOneBuf;
                IppiPoint srcOffset = {0, 0};
                IppiPoint dstOffset = {0, 0};
                IppiSize  srcSizeT = srcSize;
                IppiSize  dstSizeT = dstTileSize;

                i = omp_get_thread_num();
                dstSizeT.height = slice;
                dstOffset.y += i * slice;

                if (i == (uint)numThreads - 1) dstSizeT = dstLastTileSize;

                pStatus[i] = ippiResizeGetSrcRoi_8u(pSpec, dstOffset, dstSizeT, &srcOffset, &srcSizeT);

                if (pStatus[i] == ippStsNoErr)
                {
                    pSrcT = (Ipp8u*)((char*)pSrc + srcOffset.y * srcStep);
                    pDstT = (Ipp8u*)((char*)pDst + dstOffset.y * dstStep);
                    pOneBuf = pBuffer + i * bufSize1;
                    pStatus[i] = ippiResizeLinear_8u_C3R (pSrcT, srcStep, pDstT, dstStep, dstOffset, dstSizeT, border, 0, pSpec, pOneBuf);
                }
            }
        }
    }

    ippsFree(pSpec);

    if (pBuffer == NULL) return ippStsNoMemErr;

    ippsFree(pBuffer);

    for (Ipp32u i = 0; i < (uint)numThreads; ++i)
    {
        /* Return bad status */
        if(pStatus[i] != ippStsNoErr) return pStatus[i];
    }
    // out->save("/home/pult/resize2.jpg");

    return status;

}


