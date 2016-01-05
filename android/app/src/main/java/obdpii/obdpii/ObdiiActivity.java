package obdpii.obdpii;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class ObdiiActivity extends AppCompatActivity {

    private WebView webView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle("OBDPII");
        setContentView(R.layout.activity_obdii);
        webView = (WebView) findViewById(R.id.activity_obdii_webview);
        if (webView == null) {
            System.out.println("WEB VIEW WAS NULL. WHY??");
            return;
        }
        webView.getSettings().setJavaScriptEnabled(true);
        webView.loadUrl("http://192.168.10.1");
        webView.setWebViewClient(new WebViewClient());

    }
}
