
#include <jni.h>
#include<string.h>
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
        (JNIEnv *env, jclass cl, jbyteArray src, jbyteArray dst, jint width, jint height)
{

    jbyte *srcFrame = env->GetByteArrayElements(src, NULL);
    jbyte *dstFrame = env->GetByteArrayElements(dst, NULL);

    int size =width*height;
    int i,j;
    int uWidth = width/2;
    int uHeight = width/2;
    //y
    memcpy(dstFrame,srcFrame,size);
    int tempindex = 0 ;
    int srcindex= 0;
    //u
    for(i= 0 ;i <uHeight;i++)
    {


        for(j = 0;j <uWidth ;j++ )
        {
            dstFrame[size+tempindex+j]= srcFrame[size+(srcindex<<1)+1];
            srcindex++;
        }
        tempindex+= uWidth;
    }


    //v
    for (i = 0; i < uHeight;i++)
    {

        for (j = 0; j < uWidth;j++)
        {
            dstFrame[size+tempindex + j] = srcFrame[size + (srcindex << 1 )];
            srcindex++;
        }
        tempindex+= uWidth;
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