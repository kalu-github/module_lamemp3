package com.kalu.lamemp3;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import lib.kalu.lamemp3.LameUtil;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String version = LameUtil.getVersion();
        Toast.makeText(getApplicationContext(), "lame = " + version, Toast.LENGTH_SHORT).show();

        findViewById(R.id.main_button_pcm2mp3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                pcm2mp3();
            }
        });
    }

    private void pcm2mp3() {
        try {
            // step1
            String pcmName = "test.pcm";
            String pcmPath = getApplicationContext().getFilesDir().getAbsolutePath() + "/" + pcmName;
            File pcmFile = new File(pcmPath);
            if (pcmFile.exists()) {
                pcmFile.delete();
            }
            pcmFile.createNewFile();
            InputStream is = getApplicationContext().getAssets().open(pcmName);
            FileOutputStream fos = new FileOutputStream(pcmPath);
            byte[] buffer = new byte[1024];
            int byteCount = 0;
            while ((byteCount = is.read(buffer)) != -1) {// 循环从输入流读取
                // buffer字节
                fos.write(buffer, 0, byteCount);// 将读取的输入流写入到输出流
            }
            fos.flush();// 刷新缓冲区
            is.close();
            fos.close();
            // step2
            String mp3Path = getApplicationContext().getFilesDir().getAbsolutePath() + "/test.mp3";
            File mp3File = new File(mp3Path);
            if (mp3File.exists()) {
                mp3File.delete();
            }
            mp3File.createNewFile();
            // step3
            LameUtil.pcm2mp3(pcmPath, mp3Path, 16000, 1, 16000 * 16, 5);
        } catch (Exception e) {
        }
    }
}
