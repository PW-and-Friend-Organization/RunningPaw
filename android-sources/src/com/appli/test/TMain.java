package com.appli.test;

import org.qtproject.qt5.android.bindings.QtApplication;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.os.Bundle;
import android.content.Intent;
import android.content.Context;
import android.util.Log;
import android.media.MediaPlayer;

public class TMain extends QtActivity
{
    private static native void qtDebug(String s);
    private static native void qtFacebookLogin( String s ); // s - access_token

    public static MediaPlayer mPlayer;
    private static Context context;

    public static void android_play_sound( int res_id ) {
        switch( res_id )
        {
        case 0:
            mPlayer = MediaPlayer.create(context,R.raw.cat_meow);
            mPlayer.start();
            break;
        case 1:
            mPlayer = MediaPlayer.create(context,R.raw.cat_meow_002);
            mPlayer.start();
            break;
        case 2:
            mPlayer = MediaPlayer.create(context,R.raw.cat_meow_003);
            mPlayer.start();
            break;
        case 3:
            mPlayer = MediaPlayer.create(context,R.raw.dog_walking);
            mPlayer.start();
            break;
        case 4:
            mPlayer = MediaPlayer.create(context,R.raw.dogs_barking);
            mPlayer.start();
            break;
        case 5:
            mPlayer = MediaPlayer.create(context,R.raw.dog_german_shepherd_dog_barking_inside_kennel);
            mPlayer.start();
            break;
        case 6:
            mPlayer = MediaPlayer.create(context,R.raw.tiger_siberian_tiger_single_growl_and_snarl);
            mPlayer.start();
            break;
        case 7:
            mPlayer = MediaPlayer.create(context,R.raw.wild_cat_hissing_with_single_swat);
            mPlayer.start();
            break;
        case 8:
            mPlayer = MediaPlayer.create(context,R.raw.casino_slot_machine_bell_or_alarm_ring_win_jackpot_loops_);
            mPlayer.start();
            break;
        }
//        // TODO Auto-generated method stub
//        mPlayer = MediaPlayer.create(getApplicationContext(),R.raw.hosannahindi);//Create MediaPlayer object with MP3 file under res/raw folder
//        mPlayer.start();//Start playing the music
    }

    public static void startFacebook()
    {
        // Called from JNI
        qtDebug("TMAIN:::: START FACEBOOK");
        getInstance().startFacebookObject();
    }

    public static TMain g_instance;
    public TMain()
    {
    }
    public static TMain getInstance()
    {
        return g_instance;
    }
    public void startFacebookObject()
    {
        try
        {
            Intent s = new Intent(this, TFacebook.class);
            startActivityForResult(s, 10);
        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        qtDebug("TMAIN:::: onActivityResult");
        if (resultCode == RESULT_OK && requestCode == 10) {
            if (data.hasExtra("access_token")) {
                String result = data.getExtras().getString("access_token");
                //qtDebug("onActivityResult access_token " + result);
                qtFacebookLogin(result);
            }
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        try
        {
            super.onCreate(savedInstanceState);
            g_instance = this;
            context = getApplicationContext();
        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
