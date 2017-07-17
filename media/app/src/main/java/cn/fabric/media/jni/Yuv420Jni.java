package cn.fabric.media.jni;

import io.vov.vitamio.utils.Log;

import static android.R.attr.width;

/**
 * Created by chendingqiang on 2017/7/18.
 * yuv420sp工具类
 */

public class Yuv420Jni {
    private static String TAG = "Yuv420Jni";
    static{
        try
        {
            System.loadLibrary("yuv-lib");
        }catch (Exception e)
        {
            Log.e(TAG,e);
        }
    }

    /**
     * 将Nv21数据转换为Yuv420SP数据
     * @param data Nv21数据
     * @param dstData Yuv420sp数据
     * @param w 宽度
     * @param h 高度
     */
    public native static void Nv21ToYuv420SP(byte[] data, byte[] dstData, int w, int h);


    /**
     * 将Nv21数据转换为I420数据
     * @param data Nv21数据
     * @param dstData Yuv420sp数据
     * @param w 宽度
     * @param h 高度
     */
    public native static void Nv21ToI420(byte[] data, byte[] dstData, int w, int h);

    /**
     * yuv420sp旋转90度
     * @param data
     * @param dstData
     * @param w
     * @param h
     */
    public native static void Yuv420SPRotate90(byte[] data, byte[] dstData, int w, int h);


    /**
     * yuv420sp旋转270度
     * @param data
     * @param dstData
     * @param w
     * @param h
     */
    public native static void Yuv420SPRotate270(byte[] data, byte[] dstData, int w, int h);

    /**
     * nv21转yuv420sp,
     * 旋转90，裁剪
     * @param src 原来的字节
     * @param dst 要得到的字节
     * @param nWidth 新的宽度
     * @param nHight 新的高度
     * @param width  旧的宽度
     * @param height 旧的高度
     */
    public native static void nv21ToYuv420spRotate90(byte[] src,byte[] dst ,int nWidth,int nHight,int width,int height);


    /**
     * nv21转yuv420sp,
     * 旋转270，裁剪
     * @param src 原来的字节
     * @param dst 要得到的字节
     * @param nWidth 新的宽度
     * @param nHight 新的高度
     * @param width  旧的宽度
     * @param height 旧的高度
     */
    public native static void nv21ToYuv420spRotate270(byte[] src,byte[] dst ,int nWidth,int nHight,int width,int height);


    /**
     * 镜像，裁剪
     * @param src 要转换的
     * @param nWidth 新的宽度
     * @param nHight 新的高度
     * @param width  旧的宽度
     * @param height 旧的高度
     */
    public native static void mirror(byte[] src,int width,int height);

}
