package cordova.plugin.uamobilekeys;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import android.content.pm.PackageManager;
import android.Manifest;
import android.app.Notification;
import android.app.Activity;
import android.content.Context;
import android.support.v4.content.ContextCompat;
import android.support.v4.app.ActivityCompat;
import android.support.design.widget.Snackbar;
import android.view.View;
import java.util.List;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import com.assaabloy.mobilekeys.api.*;
import com.assaabloy.mobilekeys.api.ApiConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeys;
import com.assaabloy.mobilekeys.api.MobileKeysApi;
import com.assaabloy.mobilekeys.api.ReaderConnectionController;
import com.assaabloy.mobilekeys.api.ble.*;
import com.assaabloy.mobilekeys.api.hce.NfcConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeysCallback;
import com.assaabloy.mobilekeys.api.MobileKeysException;
import com.assaabloy.mobilekeys.api.EndpointSetupConfiguration;
import com.assaabloy.mobilekeys.api.EndpointInfo;

public class UaMobileKeysApi extends CordovaPlugin implements MobileKeysCallback {

    public UaMobileKeysApi () {}
    private UaMobileKeysSetup keySetup = new UaMobileKeysSetup();
    private View containerView;
    private int REQUEST_LOCATION_PERMISSION = 1;

    // Mobile Keys interface
    // applicationStartup
    public void startup(CallbackContext callbackContext) throws MobileKeysException {
        MobileKeysApi.getInstance().getMobileKeys().applicationStartup(this);

        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        callbackContext.sendPluginResult(result);
    }

    // isEndpointSetupComplete
    public void isEndpointSetup(CallbackContext callbackContext) throws MobileKeysException {
        MobileKeys mobileKeys = MobileKeysApi.getInstance().getMobileKeys();

        boolean isEndpointSetup = false;
        try
        {
            isEndpointSetup = mobileKeys.isEndpointSetupComplete();
        }
        catch (MobileKeysException e)
        {
            callbackContext.error("ERROR");
        }

        callbackContext.success(Boolean.toString(isEndpointSetup));
    }

    // endpointSetup
    public void setupEndpoint(CallbackContext callbackContext, String invitationCode) throws MobileKeysException {
        MobileKeysApi.getInstance().getMobileKeys().endpointSetup(this, invitationCode, new EndpointSetupConfiguration.Builder().build());

        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        callbackContext.sendPluginResult(result);
    }

    // endpointUpdate
    public void updateEndpoint(CallbackContext callbackContext) throws MobileKeysException {
        MobileKeysApi.getInstance().getMobileKeys().endpointUpdate(this);

        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        callbackContext.sendPluginResult(result);
    }

    // listMobileKeys
    public void listMobileKeys(CallbackContext callbackContext) {
        List<MobileKey> data = null;
        try
        {
            data = MobileKeysApi.getInstance().getMobileKeys().listMobileKeys();
        }
        catch (MobileKeysException e)
        {
            System.out.println(e);
            callbackContext.error("ERROR");
        }

        String json = new Gson().toJson(data);

        PluginResult result = new PluginResult(PluginResult.Status.OK, json);
        callbackContext.sendPluginResult(result);
    }

    // getEnpointInfo
    public void endpointInfo(CallbackContext callbackContext) {
        EndpointInfo data = null;
        try {
            data = MobileKeysApi.getInstance().getMobileKeys().getEndpointInfo();
        } catch (MobileKeysException e) {
            System.out.println(e);
            callbackContext.error("ERROR");
        }

        String json = new Gson().toJson(data);
        PluginResult result = new PluginResult(PluginResult.Status.OK, json);
        callbackContext.sendPluginResult(result);
    }

    // unregisterEndpoint
    public void unregisterEndpoint(CallbackContext callbackContext) {
        MobileKeysApi.getInstance().getMobileKeys().unregisterEndpoint(new MobileKeysCallback() {
                @Override
                public void handleMobileKeysTransactionCompleted ()
                {
                    // does something if unregisterEndpoint was successful
                    callbackContext.success("true");
                }

                @Override
                public void handleMobileKeysTransactionFailed (MobileKeysException
                mobileKeysException)
                {
                    // does something if unregisterEndpoint was unsuccessful
                    callbackContext.error("ERROR");
                }
            });
        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        callbackContext.sendPluginResult(result);
    }

    // BLE scanning for doors - disabled by default because it's a background process
    public void startScanning(CallbackContext callbackContext, Context context, Activity activity) {
        ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
        controller.enableHce();

        Notification notification = UaUnlockNotification.create(context);

        controller.startForegroundScanning(notification);
    }

    // startForegroundScanning
    public void startForegroundScanning(CallbackContext callbackContext, Context context, Activity activity) {
        if (hasLocationPermissions(context)) {
            ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
            controller.enableHce();

            Notification notification = UaUnlockNotification.create(context);
            controller.startForegroundScanning(notification);

            PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
            callbackContext.sendPluginResult(result);
        } else {
            requestLocationPermission(context, activity);
        }
    }

    public void stopScanning(CallbackContext callbackContext) {
        try {
            ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
            controller.stopScanning();
        }
        catch (Exception ex)
        {
            PluginResult result = new PluginResult(PluginResult.Status.ERROR, "ERROR");
            callbackContext.sendPluginResult(result);
        }

        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        callbackContext.sendPluginResult(result);
    }

    // Checking if the app has access to bluetooth
    private boolean hasLocationPermissions(Context context)
    {
        return (ContextCompat.checkSelfPermission(context,
                Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED ||
                ContextCompat.checkSelfPermission(context,
                        Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED);
    }

    // Prompts the user to enable access to bluetooth for the app if it's not already enabled
    private void requestLocationPermission(Context context, Activity activity) {
        if (!hasLocationPermissions(context)) {
            ActivityCompat.requestPermissions(activity,
                    new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                    REQUEST_LOCATION_PERMISSION);
        }
    }

    // MobileKeysCallback interface implementation
    @Override
    public void handleMobileKeysTransactionCompleted()
    {
        // does something if transaction was successful
    }

    @Override
    public void handleMobileKeysTransactionFailed(MobileKeysException mobileKeysException)
    {
        // does something if transaction was unsuccessful
    }
}

