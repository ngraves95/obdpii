package obdpii.obdpii;

import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import java.util.List;

public class ConnectActivity extends AppCompatActivity {

    private WifiManager wifi;

    private String targetSsid = "obdpii";
    private String targetPassword = "hackmycar";

    private ProgressDialog connectingDialog;
    private boolean shouldConnect = true;

    private WebView webView;

    private final BroadcastReceiver wifiScanReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context c, Intent intent) {
            System.out.println("Receiving...");

            if (intent.getAction().equals(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION)
                    && shouldConnect) {
                System.out.println("Results available.");

                List<ScanResult> scanResults = wifi.getScanResults();
                for (ScanResult sr : scanResults) {
                    System.out.println("SSID: " + sr.SSID);
                    if (targetSsid.equals(sr.SSID)) {
                        System.out.println("Found matching SSID: " + sr.SSID);
                        // Connect to our target network after we find it.
                        WifiConfiguration conf = new WifiConfiguration();
                        conf.SSID = quote(targetSsid);   // Please note the quotes. String should contain ssid in quotes
                        conf.preSharedKey = quote(targetPassword);

                        WifiManager wifiManager = (WifiManager)getSystemService(Context.WIFI_SERVICE);
                        int netId = wifiManager.addNetwork(conf);
                        wifiManager.enableNetwork(netId, true);
                        wifiManager.reconnect();

                        new Thread() {
                            @Override
                            public void run() {
                                try {
                                    Thread.sleep(5000);
                                } catch (Exception e) {
                                    // Swallow.
                                }
                                connectingDialog.dismiss();
                                shouldConnect = false;
                                Intent i = new Intent(getApplicationContext(), ObdiiActivity.class);
                                startActivity(i);
                            }
                        }.start();

                        return;
                    }
                }
            }
        }
    };


    private String quote(String src) {
        return "\"" + src + "\"";
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTitle("OBDPII");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        Button connectButton = (Button) findViewById(R.id.connectButton);
        connectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                shouldConnect = true;
                connectingDialog = ProgressDialog.show(ConnectActivity.this, "",
                        "Connecting. Please wait...", true);

                // Scan wifi networks and register our receiver.
                wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);
                registerReceiver(wifiScanReceiver, new IntentFilter(
                        WifiManager.SCAN_RESULTS_AVAILABLE_ACTION));

                if (!wifi.isWifiEnabled()) {
                    wifi.setWifiEnabled(true);
                }
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_connect, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
