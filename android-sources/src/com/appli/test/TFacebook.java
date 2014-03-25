package com.appli.test;
 
import org.qtproject.qt5.android.QtNative;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.os.Bundle;
import android.content.Intent;
import android.app.Activity;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.graphics.Bitmap;

import java.util.HashMap;
import java.util.Map;
import android.webkit.URLUtil;

public class TFacebook extends Activity
{
    private static native void qtDebug(String s);

    public static Map<String, String> getParametersFromUrl(String url)
    {
        Map<String, String> map = new HashMap<String, String>();

        if(url!=null && URLUtil.isValidUrl(url))
        {
            String[] params = url.split("[#,&,?]");
            for (String param : params)
            {
                try {
                String name = param.split("=")[0];
                String value = param.split("=")[1];
                map.put(name, value);
            } catch (Exception e)
            {
            }
            }
        }
        return map;
    }

    private class MyWebViewClient extends WebViewClient {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            view.loadUrl(url);
            return true;
        }

        @Override
        public  void onPageStarted (WebView view, String url, Bitmap favicon)
        {
             super.onPageStarted(view, url, favicon);

             qtDebug( "onPageStarted" );
             qtDebug( url );
        }

        @Override
        public void onPageFinished (WebView view, String url)
        {
            super.onPageFinished(view, url);

            qtDebug( "onPageFinished" );
            qtDebug( url );

            String[] urlToken = url.split("[#,&,?]");
            if( urlToken[0].equals("https://www.facebook.com/connect/login_success.html") )
            {
                Map<String, String>keyToken = getParametersFromUrl(url);
                String sAccessToken = (String)keyToken.get("access_token");
                qtDebug( "access_token : " + sAccessToken );

                Intent data = new Intent();
                data.putExtra("access_token", sAccessToken);
                // Activity finished ok, return the data
                setResult(RESULT_OK, data);
                finish();
            }
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        qtDebug( "TFACEBOOK::: onCreate()" );

        setContentView(R.layout.activity);
        WebView myWebView = (WebView) findViewById(R.id.webview);
        myWebView.setWebViewClient(new MyWebViewClient());
       // myWebView.loadUrl("https://www.facebook.com/dialog/oauth?client_id=360091654097401&redirect_uri=https://www.facebook.com/connect/login_success.html");

        myWebView.loadUrl("https://graph.facebook.com/oauth/authorize?type=user_agent&client_id=360091654097401&redirect_uri=https://www.facebook.com/connect/login_success.html&scope=read_stream,offline_access");
   }
}
