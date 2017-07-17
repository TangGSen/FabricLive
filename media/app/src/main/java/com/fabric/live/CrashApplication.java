package com.fabric.live;

/**
 * Created by chendingqiang on 2017/7/17.
 */

import android.app.Application;

import cn.fabric.media.exception.CrashHandler;

/**
 * 崩溃监控
 */
public class CrashApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        CrashHandler crashHandler = CrashHandler.getInstance();
        crashHandler.init(getApplicationContext());
    }
}
