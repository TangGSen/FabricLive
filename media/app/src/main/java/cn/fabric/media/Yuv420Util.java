package cn.fabric.media;

/**
 * Created by blueberry on 1/5/2017.
 */

public class Yuv420Util {
    /**
     * Nv21:
     * YYYYYYYY
     * YYYYYYYY
     * YYYYYYYY
     * YYYYYYYY
     * VUVU
     * VUVU
     * VUVU
     * VUVU
     * <p>
     * I420:
     * YYYYYYYY
     * YYYYYYYY
     * YYYYYYYY
     * YYYYYYYY
     * UUUU
     * UUUU
     * VVVV
     * VVVV
     *
     * @param data Nv21数据
     * @param dstData I420(YUV420)数据
     * @param w 宽度
     * @param h 长度
     */
    public static void Nv21ToI420(byte[] data, byte[] dstData, int w, int h) {

        int size = w * h;
        // Y
        System.arraycopy(data, 0, dstData, 0, size);
        for (int i = 0; i < size / 4; i++) {
            dstData[size + i] = data[size + i * 2 + 1]; //U
            dstData[size + size / 4 + i] = data[size + i * 2]; //V
        }
    }

    /**
     * 将Nv21数据转换为Yuv420SP数据
     * @param data Nv21数据
     * @param dstData Yuv420sp数据
     * @param w 宽度
     * @param h 高度
     */
    public static void Nv21ToYuv420SP(byte[] data, byte[] dstData, int w, int h) {
        int size = w * h;
        // Y
        System.arraycopy(data, 0, dstData, 0, size);

        for (int i = 0; i < size / 4; i++) {
            dstData[size + i * 2] = data[size + i * 2 + 1]; //U
            dstData[size + i * 2 + 1] = data[size + i * 2]; //V
        }
    }

    public static void Nv21ToYuv420SPAnd_Rotate(byte[] data, byte[] dstData, int w, int h,int nw,int nh) {
        int deleteW = (nw - w) / 2;
        int deleteH = (nh - h) / 2;
        //处理y 旋转加裁剪
        int i, j;
        int index = w * h;
        for (j = deleteH; j < nh- deleteH; j++) {
            for (i = deleteW; i < nw- deleteW; i++)
                dstData[--index]= data[j * nw + i];
        }

        //处理u
        index= w * h * 5 / 4;

        for (i = nh + deleteH / 2;i < nh / 2 * 3 - deleteH / 2; i++)
            for (j = deleteW + 1; j< nw - deleteW; j += 2)
                dstData[--index]= data[i * nw + j];

        //处理v 旋转裁剪加格式转换
        index= w * h * 3 / 2;
        for (i = nh + deleteH / 2;i < nh / 2 * 3 - deleteH / 2; i++)
            for (j = deleteW; j < nw- deleteW; j += 2)
                dstData[--index]= data[i * nw + j];
    }

    /**
     * 翻转90度
     * @param src
     * @param dst
     * @param width
     * @param height
     */
    public static void Yuv420SPRotate_90(byte[] src, byte[] dst,int width,int height)
    {
        int nWidth = 0, nHeight = 0;
        int wh = 0;
        int uvHeight = 0;
        if(width != nWidth || height != nHeight)
        {
            nWidth = width;
            nHeight = height;
            wh = width * height;
            uvHeight = height >> 1;//uvHeight = height / 2
        }

        //旋转Y
        int k = 0;
        for(int i = 0; i < width; i++){
            int nPos = width - 1;
            for(int j = 0; j < height; j++)
            {
                dst[k] = src[nPos - i];
                k++;
                nPos += width;
            }
        }

        for(int i = 0; i < width; i+=2){
            int nPos = wh + width - 1;
            for(int j = 0; j < uvHeight; j++) {
                dst[k] = src[nPos - i - 1];
                dst[k + 1] = src[nPos - i];
                k += 2;
                nPos += width;
            }
        }


    }


    /**
     * 逆时针旋转90度
     * @param src
     * @param dst
     * @param srcWidth
     * @param srcHeight
     */
    public static void YUV420spRotateNegative90(byte[] src, byte[] dst,int srcWidth,int srcHeight)
    {


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


    }

}
