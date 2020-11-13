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
import android.os.Vibrator;
import android.os.VibrationEffect;
import android.os.Build;
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

public class UaMobileKeysApi extends CordovaPlugin implements MobileKeysCallback, ReaderConnectionListener {

    public UaMobileKeysApi () {}
    private UaMobileKeysSetup keySetup = new UaMobileKeysSetup();
    private View containerView;
    private int REQUEST_LOCATION_PERMISSION = 10;
    private CallbackContext _callbackContext;
    private ReaderConnectionCallback readerConnectionCallback;
    private Context _context;
    private boolean startupHasRun;

    // Mobile Keys interface
    // applicationStartup
    public void startup(CallbackContext callbackContext, Context context) throws MobileKeysException {
        _callbackContext = callbackContext;
        _context = context;

        if (!startupHasRun) {
            MobileKeysApi.getInstance().getMobileKeys().applicationStartup(this);
            startupHasRun = true;
            readerConnectionCallback = new ReaderConnectionCallback(context);
            readerConnectionCallback.registerReceiver(this);
        } else {
            // Startup has already been called.
            PluginResult result = new PluginResult(PluginResult.Status.OK, "already_done");
            _callbackContext.sendPluginResult(result);
        }
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
        _callbackContext = callbackContext;
        MobileKeysApi.getInstance().getMobileKeys().endpointSetup(this, invitationCode, new EndpointSetupConfiguration.Builder().build());
    }

    // endpointUpdate
    public void updateEndpoint(CallbackContext callbackContext) throws MobileKeysException {
        _callbackContext = callbackContext;
        MobileKeysApi.getInstance().getMobileKeys().endpointUpdate(this);
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

    public void getUsefulEndpointInfo(CallbackContext callbackContext) {
        EndpointInfo data = null;

        try {
            data = MobileKeysApi.getInstance().getMobileKeys().getEndpointInfo();

            String json = new Gson().toJson(data);
            PluginResult result = new PluginResult(PluginResult.Status.OK, json);
            callbackContext.sendPluginResult(result);
        } catch (MobileKeysException e) {
            System.out.println(e);
            callbackContext.error("ERROR");
        }
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
        _callbackContext = callbackContext;
        if (hasLocationPermissions(context)) {
            ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
            controller.enableHce();

            Notification notification = UaUnlockNotification.create(context);
            controller.startForegroundScanning(notification);
        } else {
            requestLocationPermission(context, activity);
        }
    }

    public void checkBluetoothPermission(CallbackContext callbackContext, Context context, Activity activity) {
        if (!hasLocationPermissions(context)) {
            requestLocationPermission(context, activity);
        }

        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        callbackContext.sendPluginResult(result);
    }

    public void checkBtPermissionStatus(CallbackContext callbackContext, Context context) {
        if (hasLocationPermissions(context)) {
            PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
            callbackContext.sendPluginResult(result);
        } else {
            PluginResult result = new PluginResult(PluginResult.Status.OK, "false");
            callbackContext.sendPluginResult(result);
        }
    }

    public void stopScanning(CallbackContext callbackContext) {
        try {
            ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
            if (controller.isScanning()) {
                controller.stopScanning();
            }
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
        boolean permissionGranted = true;
        permissionGranted &= ContextCompat.checkSelfPermission(context,
                Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED || ContextCompat.checkSelfPermission(context,
                Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            permissionGranted &= ContextCompat.checkSelfPermission(context,
                    Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED;
        }

        return permissionGranted;
    }

    // Prompts the user to enable access to bluetooth for the app if it's not already enabled
    private void requestLocationPermission(Context context, Activity activity) {
        if (!hasLocationPermissions(context)) {
            ActivityCompat.requestPermissions(activity, getPermissions(),
                    REQUEST_LOCATION_PERMISSION);
        }
    }

    public static String[] getPermissions(){
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q ?
                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_BACKGROUND_LOCATION} :
                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION};
    }

    // MobileKeysCallback interface implementation
    @Override
    public void handleMobileKeysTransactionCompleted()
    {
        // does something if transaction was successful
        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        _callbackContext.sendPluginResult(result);
    }

    @Override
    public void handleMobileKeysTransactionFailed(MobileKeysException mobileKeysException)
    {
        String errorResult = "false";

        switch (mobileKeysException.getErrorCode())
        {
            case INTERNAL_ERROR:
                errorResult = "internal_error";
                break;
            case SERVER_UNREACHABLE:
                errorResult = "server_unreachable";
                break;
            case SDK_BUSY:
                errorResult = "sdk_busy";
                break;
            case INVALID_INVITATION_CODE:
                errorResult = "invalid_invitation_code";
                break;
            case DEVICE_SETUP_FAILED:
                errorResult = "device_setup_failed";
                break;
            case SDK_INCOMPATIBLE:
                errorResult = "sdk_incompatible";
                break;
            case DEVICE_NOT_ELIGIBLE:
                errorResult = "device_not_eligible";
                break;
            case ENDPOINT_NOT_SETUP:
                errorResult = "endpoint_not_setup";
                break;
            default:
                errorResult = "false";
                break;
        }

        PluginResult result = new PluginResult(PluginResult.Status.OK, errorResult);
        _callbackContext.sendPluginResult(result);
    }

    @Override
    public void onReaderConnectionOpened(Reader reader, OpeningType openingType)
    {
        Vibrator vibrator = (Vibrator) _context.getSystemService(_context.VIBRATOR_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            vibrator.vibrate(VibrationEffect.createOneShot(30, VibrationEffect.DEFAULT_AMPLITUDE));
        } else {
            vibrator.vibrate(30);
        }
    }

    @Override
    public void onReaderConnectionClosed(Reader reader, OpeningResult openingResult)
    {
        Vibrator vibrator = (Vibrator) _context.getSystemService(_context.VIBRATOR_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            vibrator.vibrate(VibrationEffect.createOneShot(150, VibrationEffect.DEFAULT_AMPLITUDE));
        } else {
            vibrator.vibrate(150);
        }

        PluginResult result = new PluginResult(PluginResult.Status.OK, "true");
        _callbackContext.sendPluginResult(result);
    }

    @Override
    public void onReaderConnectionFailed(Reader reader, OpeningType openingType, OpeningStatus openingStatus)
    {
        PluginResult result = new PluginResult(PluginResult.Status.OK, "false");
        _callbackContext.sendPluginResult(result);
    }
}

