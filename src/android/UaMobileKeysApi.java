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
                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.ACCESS_FINE_LOCATION} :
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

        // Generates and returns stauts payload as JSON if successfull and "false" if error
        String jsonResponse = GenerateJsonResponse(openingResult.getStatusPayload());

        PluginResult result = new PluginResult(PluginResult.Status.OK, jsonResponse);
        _callbackContext.sendPluginResult(result);
    }

    @Override
    public void onReaderConnectionFailed(Reader reader, OpeningType openingType, OpeningStatus openingStatus)
    {
        PluginResult result = new PluginResult(PluginResult.Status.OK, "false");
        _callbackContext.sendPluginResult(result);
    }

    private static String GenerateJsonResponse(byte[] payload) {
        LockFeedbackObject lockFeedback = new LockFeedbackObject();
        if (containsData(payload)) {
            lockFeedback.DoorId = DoorId(payload);
            lockFeedback.DidUnlock = Boolean.toString(didUnlock(payload));
            lockFeedback.BatteryStatus = ReaderBatteryStatus(payload);

            // Maybe add try/parse
            String results = new Gson().toJson(lockFeedback);
            return results;
        } 
        
        return "false";
    }

    // Door feedback implementation
    public static Boolean containsData(byte[] payload) {
        return payload.length>0;
    }

    public static Boolean didUnlock(byte[] payload) {
        if (!containsData(payload)) {
            return false;
        }

        String result = partialResult(payload, 1, 1);
        int unlockStatus = Integer.parseInt(result);
        if (unlockStatus > 0) {
            return true;
        } else {
            return false;
        }
    }

    private static String partialResult(byte[] payload, int location, int length) {
        String dataAsString = openingStatusPayloadAsString(payload);

        int formatStart = 0;
        int formatLength = 2;

        int useLocation = location * 2;
        int useLength = length * 2;

        ReaderResultDataFormat dataFormat = ReaderResultDataFormat.Unknown;
        String result = "";

        if (dataAsString.length() >= useLocation + useLength) {
            String dataFormatString = dataAsString.substring(formatStart, formatStart+formatLength);

            if (dataFormatString.length() > 0) {
                int resultAsValue = Integer.parseInt(dataFormatString);
                 dataFormat= ReaderResultDataFormat.fromInt(resultAsValue);
            }
            if (dataFormat == ReaderResultDataFormat.Standard) {
                result = dataAsString.substring(useLocation, useLocation + useLength);
            }
        }
        return result;
    }

    private static String openingStatusPayloadAsString(byte[] payload) {
        String result = "";
        for (int i =0;i<payload.length;i++) {
            String thisThing = String.format("%02x", payload[i]);
            result = result.concat(thisThing);
        }
        return result;
    }

    public static Boolean didUnlock(byte[] payload) {
        if (!containsData(payload)) {
            return false;
        }

        String result = partialResult(payload, 1, 1);
        int unlockStatus = Integer.parseInt(result);
        if (unlockStatus > 0) {
            return true;
        } else {
            return false;
        }
    }

    public static String DoorId(byte[] payload) {

        String resultString = partialResult(payload, 3, 4);
        String doorIdResult = "";
        if (resultString.length()>0) {
            int resultAsValue = Integer.parseInt(resultString, 16);
            doorIdResult = String.format("%d", resultAsValue);
        }
        return doorIdResult;
    }

    public static ReaderBatteryStatus ReaderBatteryStatus(byte[] payload) {
        ReaderBatteryStatus result = ReaderBatteryStatus.NotApplicable;
        String resultString = partialResult(payload, 7, 1);
        if(resultString.length() > 0) {
            int resultAsValue = Integer.parseInt(resultString, 16);
            result = ReaderBatteryStatus.fromInt(resultAsValue);
        }
        return result;
    }
}

public enum ReaderBatteryStatus {
    Good (0x00),
    Warning (0x01),
    Critical (0x02),
    NotApplicable (-1);

    private final int value;
    private ReaderBatteryStatus(int value) {
        this.value = value;
    }

    public static ReaderBatteryStatus fromInt(int id) {
        ReaderBatteryStatus foundValue = NotApplicable;
        for (ReaderBatteryStatus type : ReaderBatteryStatus.values()) {
            if (type.value == id ) {
                foundValue = type;
                break;
            }
        }
        return foundValue;
    }
}

public class LockFeedbackObject {
    String DoorId;
    String DidUnlock;
    String BatteryStatus;

    public String getDoorId() {
        return DoorId;
    }

    public void setDoorId(String doorId) {
        this.DoorId = doorId;
    }

    public String getDidUnlock() {
        return this.DidUnlock;
    }

    public void setDidUnlock(String didUnlock) {
        this.DidUnlock = didUnlock;
    }

    public String getBatteryStatus() {
        return this.BatteryStatus;
    }

    public void setBatteryStatus(String batteryStatus) {
        this.BatteryStatus = batteryStatus;
    }
}

