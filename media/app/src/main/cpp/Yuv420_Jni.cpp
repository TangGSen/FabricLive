
#include <jni.h>
#include<string.h>
#include "libyuv.h"
#include <android/log.h>
#define LIBENC_LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "libyuv", __VA_ARGS__))
#define LIBENC_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO , "libyuv", __VA_ARGS__))
#define LIBENC_LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN , "libyuv", __VA_ARGS__))
#define LIBENC_LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "libyuv", __VA_ARGS__))
#ifndef _Included_cn_fabric_media_jni_Yuv420Jni
#define _Included_cn_fabric_media_jni_Yuv420Jni
#ifdef __cplusplus
extern "C" {
#endif

int VideoStreamProcess(unsigned char *Src_data, unsigned char *Dst_data,
                       int src_width, int src_height,
                       bool EnableRotate, bool EnableMirror,
                       unsigned char *Dst_data_mirror, unsigned char *Dst_data_rotate,
                       int rotatemodel) {
    if(EnableRotate && Dst_data_rotate==NULL)
    {
        LIBENC_LOGE("需要翻转，但是没有传目标数组");
        return -1;
    }

    if(EnableMirror && Dst_data_mirror==NULL)
    {
        LIBENC_LOGE("需要镜像，但是没有传目标数组");
        return -1;
    }
    //src:NV12 video size
    int NV12_Size = src_width * src_height * 3 / 2;
    int NV12_Y_Size = src_width * src_height;

    //dst:YUV420 video size
    int I420_Size = src_width * src_height * 3 / 2;
    int I420_Y_Size = src_width * src_height;
    int I420_U_Size = (src_width >> 1) * (src_height >> 1);
    int I420_V_Size = I420_U_Size;

    // video format transformation process
    unsigned char *Y_data_Src = Src_data;
    unsigned char *UV_data_Src = Src_data + NV12_Y_Size;
    int src_stride_y = src_width;
    int src_stride_uv = src_width;

    unsigned char *Y_data_Dst = Dst_data;
    unsigned char *U_data_Dst = Dst_data + I420_Y_Size;
    unsigned char *V_data_Dst = Dst_data + I420_Y_Size + I420_U_Size;

    int Dst_Stride_Y = src_width;
    int Dst_Stride_U = src_width >> 1;
    int Dst_Stride_V = Dst_Stride_U;
    //NV12ToI420
    libyuv::NV21ToI420(Y_data_Src, src_stride_y,
                       UV_data_Src, src_stride_uv,
                       Y_data_Dst, Dst_Stride_Y,
                       U_data_Dst, Dst_Stride_U,
                       V_data_Dst, Dst_Stride_V,
                       src_width, src_height);


    // video mirror process


    if (EnableMirror) {
        unsigned char *Y_data_Dst_mirror = Dst_data_mirror;
        unsigned char *U_data_Dst_mirror = Dst_data_mirror + I420_Y_Size;
        unsigned char *V_data_Dst_mirror = Dst_data_mirror + I420_Y_Size + I420_U_Size;
        int Dst_Stride_Y_mirror = src_width;
        int Dst_Stride_U_mirror = src_width >> 1;
        int Dst_Stride_V_mirror = Dst_Stride_U_mirror;
        libyuv::I420Mirror(Y_data_Dst, Dst_Stride_Y,
                           U_data_Dst, Dst_Stride_U,
                           V_data_Dst, Dst_Stride_V,
                           Y_data_Dst_mirror, Dst_Stride_Y_mirror,
                           U_data_Dst_mirror, Dst_Stride_U_mirror,
                           V_data_Dst_mirror, Dst_Stride_V_mirror,
                           src_width, src_height);
    }

    //video rotate process
    if (EnableRotate) {
        int Dst_Stride_Y_rotate;
        int Dst_Stride_U_rotate;
        int Dst_Stride_V_rotate;
        unsigned char *Y_data_Dst_rotate = Dst_data_rotate;
        unsigned char *U_data_Dst_rotate = Dst_data_rotate + I420_Y_Size;
        unsigned char *V_data_Dst_rotate = Dst_data_rotate + I420_Y_Size + I420_U_Size;

        if (rotatemodel == libyuv::kRotate90 || rotatemodel == libyuv::kRotate270) {
            Dst_Stride_Y_rotate = src_height;
            Dst_Stride_U_rotate = src_height >> 1;
            Dst_Stride_V_rotate = Dst_Stride_U_rotate;
        }
        else {
            Dst_Stride_Y_rotate = src_width;
            Dst_Stride_U_rotate = src_width >> 1;
            Dst_Stride_V_rotate = Dst_Stride_U_rotate;
        }

        if (EnableMirror) {
            unsigned char *Y_data_Dst_mirror = Dst_data_mirror;
            unsigned char *U_data_Dst_mirror = Dst_data_mirror + I420_Y_Size;
            unsigned char *V_data_Dst_mirror = Dst_data_mirror + I420_Y_Size + I420_U_Size;
            int Dst_Stride_Y_mirror = src_width;
            int Dst_Stride_U_mirror = src_width >> 1;
            int Dst_Stride_V_mirror = Dst_Stride_U_mirror;

            libyuv::I420Rotate(Y_data_Dst_mirror, Dst_Stride_Y_mirror,
                               U_data_Dst_mirror, Dst_Stride_U_mirror,
                               V_data_Dst_mirror, Dst_Stride_V_mirror,
                               Y_data_Dst_rotate, Dst_Stride_Y_rotate,
                               U_data_Dst_rotate, Dst_Stride_U_rotate,
                               V_data_Dst_rotate, Dst_Stride_V_rotate,
                               src_width, src_height,
                               (libyuv::RotationMode) rotatemodel);
        }
        else {
            libyuv::I420Rotate(Y_data_Dst, Dst_Stride_Y,
                               U_data_Dst, Dst_Stride_U,
                               V_data_Dst, Dst_Stride_V,
                               Y_data_Dst_rotate, Dst_Stride_Y_rotate,
                               U_data_Dst_rotate, Dst_Stride_U_rotate,
                               V_data_Dst_rotate, Dst_Stride_V_rotate,
                               src_width, src_height,
                               (libyuv::RotationMode) rotatemodel);
        }
    }
    return 0;
}

JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_Nv21ToYuv420SP
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint width, jint height)
{
    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);

    int size = width * height;
    // Y
    memcpy(dstFrame,srcFrame,size);

    for (int i = 0; i < size / 4; i++) {
        dstFrame[size + i * 2] = srcFrame[size + i * 2 + 1]; //U
        dstFrame[size + i * 2 + 1] = srcFrame[size + i * 2]; //V
    }
    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(dst, dstFrame, JNI_OK);
}

JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_Nv21ToI420
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint src_width, jint src_height)
{

    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);

    int ret = VideoStreamProcess((uint8_t *)srcFrame,(uint8_t *)dstFrame,src_width, src_height,false, false,
                       NULL,NULL,NULL);
    if(ret==-1)
    {
        LIBENC_LOGE("Nv21ToI420转换失败");
        return;
    }

    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(dst, dstFrame, JNI_OK);
}


JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_Yuv420SPRotate90
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint width, jint height)
{
    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);
    int nWidth = 0, nHeight = 0;
    int wh = 0;
    int uvHeight = 0;
    if(width != nWidth || height != nHeight)
    {
        wh = width * height;
        uvHeight = height >> 1;//uvHeight = height / 2
    }

    //旋转Y
    int k = 0;
    for(int i = 0; i < width; i++){
        int nPos = width - 1;
        for(int j = 0; j < height; j++)
        {
            dstFrame[k] = srcFrame[nPos - i];
            k++;
            nPos += width;
        }
    }

    for(int i = 0; i < width; i+=2){
        int nPos = wh + width - 1;
        for(int j = 0; j < uvHeight; j++) {
            dstFrame[k] = srcFrame[nPos - i - 1];
            dstFrame[k + 1] = srcFrame[nPos - i];
            k += 2;
            nPos += width;
        }
    }
    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(dst, dstFrame, JNI_OK);
}


JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_YUV420spRotateNegative90
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint srcWidth, jint srcHeight) {

    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);

    int nWidth = 0, nHeight = 0;
    int wh = 0;
    int uvHeight = 0;
    if(srcWidth != nWidth || srcHeight != nHeight)
    {
        nWidth = srcWidth;
        nHeight = srcHeight;
        wh = srcWidth * srcHeight;
        uvHeight = srcHeight >> 1;//uvHeight = height / 2
    }

    //旋转Y
    int k = 0;
    for(int i = 0; i < srcWidth; i++) {
        int nPos = 0;
        for(int j = 0; j < srcHeight; j++) {
            dst[k] = src[nPos + i];
            k++;
            nPos += srcWidth;
        }
    }

    for(int i = 0; i < srcWidth; i+=2){
        int nPos = wh;
        for(int j = 0; j < uvHeight; j++) {
            dst[k] = src[nPos + i];
            dst[k + 1] = src[nPos + i + 1];
            k += 2;
            nPos += srcWidth;
        }
    }

    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(dst, dstFrame, JNI_OK);
}

/*
 * Class:     cn_fabric_media_jni_Yuv420Jni
 * Method:    nv21ToYuv420spRotate90
 * Signature: ([B[BIIII)V
 */
JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_nv21ToYuv420spRotate90
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint nWidth, jint nHeight, jint width, jint height)
{
    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);

    int deleteW = (nWidth - height) / 2;
    int deleteH = (nHeight - width) / 2;

    int i, j;

    for (i = 0; i < height; i++){
    for (j = 0; j < width; j++){
        dstFrame[(height- i) * width - 1 - j] = srcFrame[nWidth * (deleteH + j) + nWidth - deleteW -i];
    }
    }

    int index = width * height;
    for (i = deleteW + 1; i< nWidth - deleteW; i += 2)
    for (j = nHeight / 2 * 3 -deleteH / 2; j > nHeight + deleteH / 2; j--)
        dstFrame[index++]= srcFrame[(j - 1) * nWidth + i];

    for (i = deleteW; i < nWidth- deleteW; i += 2)
        for (j = nHeight / 2 * 3 -deleteH / 2; j > nHeight + deleteH / 2; j--)
        dstFrame[index++]= srcFrame[(j - 1) * nWidth + i];


    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(dst, dstFrame, JNI_OK);
}

/*
 * Class:     cn_fabric_media_jni_Yuv420Jni
 * Method:    nv21ToYuv420spRotate270
 * Signature: ([B[BIIII)V
 */
JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_nv21ToYuv420spRotate270
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint nWidth, jint nHeight, jint width, jint height)
{

    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);

    int deleteW = (nWidth - height) / 2;
    int deleteH = (nHeight - width) / 2;
    int i, j;
    //处理y 旋转加裁剪
    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            dstFrame[i* width + j] = srcFrame[nWidth * (deleteH + j) + nWidth - deleteW - i];
        }
    }

    //处理u 旋转裁剪加格式转换
    int index = width * height;
    for (i = nWidth - deleteW - 1;i > deleteW; i -= 2)
        for (j = nHeight + deleteH / 2;j < nHeight / 2 * 3 - deleteH / 2; j++)
            dstFrame[index++]= srcFrame[(j) * nWidth + i];

    //处理v 旋转裁剪加格式转换

    for (i = nWidth - deleteW - 2;i >= deleteW; i -= 2)
        for (j = nHeight + deleteH / 2;j < nHeight / 2 * 3 - deleteH / 2; j++)
            dstFrame[index++]= srcFrame[(j) * nWidth + i];

    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(dst, dstFrame, JNI_OK);
}

/*
 * Class:     cn_fabric_media_jni_Yuv420Jni
 * Method:    mirror
 * Signature: ([BIIII)V
 */
JNIEXPORT void JNICALL Java_cn_fabric_media_jni_Yuv420Jni_mirror
        (JNIEnv *env, jclass cl, jbyteArray src, jint width, jint height)
{
    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    int i, j;

    int a, b;
    uint8_t temp;
    //mirror y
    for (i = 0; i < height; i++){
        a= i * width;
        b= (i + 1) * width - 1;
        while (a < b) {
            temp= srcFrame[a];
            srcFrame[a]= srcFrame[b];
            srcFrame[b]= temp;
            a++;
            b--;
        }
    }
    //mirror u
    int uindex = width * height;
    for (i = 0; i < height / 2;i++) {
        a = i * width / 2;
        b= (i + 1) * width / 2 - 1;
        while (a < b) {
            temp= srcFrame[a + uindex];
            srcFrame[a+ uindex] = srcFrame[b + uindex];
            srcFrame[b+ uindex] = temp;
            a++;
            b--;
        }
    }
    //mirror v
    uindex= width * height / 4 * 5;
    for (i = 0; i < height / 2;i++) {
        a= i * width / 2;
        b= (i + 1) * width / 2 - 1;
        while (a < b) {
            temp= srcFrame[a + uindex];
            srcFrame[a+ uindex] = srcFrame[b + uindex];
            srcFrame[b+ uindex] = temp;
            a++;
            b--;
        }
    }

    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);
    env->ReleaseByteArrayElements(src, srcFrame, JNI_OK);

}

#ifdef __cplusplus
}
#endif
#endif