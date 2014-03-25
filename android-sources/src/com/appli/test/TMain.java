package com.appli.test;

import org.qtproject.qt5.android.bindings.QtApplication;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.os.Bundle;
import android.content.Intent;
import android.util.Log;

public class TMain extends QtActivity
{
    private static native void qtDebug(String s);
    private static native void qtFacebookLogin( String s ); // s - access_token

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
        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
