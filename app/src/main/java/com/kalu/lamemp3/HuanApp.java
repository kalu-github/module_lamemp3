package com.kalu.lamemp3;

import android.app.Application;
import android.content.Context;

import androidx.multidex.MultiDex;

public final class HuanApp extends Application {

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        MultiDex.install(this);
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }
}
