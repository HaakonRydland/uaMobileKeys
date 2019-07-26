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
import android.content.Context;

import com.assaabloy.mobilekeys.api.ApiConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeys;
import com.assaabloy.mobilekeys.api.MobileKeysApi;
import com.assaabloy.mobilekeys.api.ReaderConnectionController;
import com.assaabloy.mobilekeys.api.ble.*;
import com.assaabloy.mobilekeys.api.hce.NfcConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeysCallback;
import com.assaabloy.mobilekeys.api.MobileKeysException;
import com.assaabloy.mobilekeys.api.EndpointSetupConfiguration;

public class UaMobileKeysApi extends CordovaPlugin implements MobileKeysCallback {

    public UaMobileKeysApi () {}
    private MobileKeysApiFacade mobileKeysApiFacade;
    private UaMobileKeysSetup keySetup = new UaMobileKeysSetup();

    // Mobile Keys interface
    // applicationStartup
    public void startup(CallbackContext callbackContext) throws MobileKeysException {
        MobileKeysApi.getInstance().getMobileKeys().applicationStartup(this);

        callbackContext.success("Reached startup()");
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
            callbackContext.error("Something went wrong in isEndpointSetup()");
        }

        callbackContext.success(Boolean.toString(isEndpointSetup));
    }

    // endpointSetup
    public void setupEndpoint(CallbackContext callbackContext, String invitationCode) throws MobileKeysException {
        MobileKeysApi.getInstance().getMobileKeys().endpointSetup(this, invitationCode, new EndpointSetupConfiguration.Builder().build());

        callbackContext.success("Finished setting up endpoint. Run isEndpointSetup() to verify.");
    }

    // endpointUpdate
    public void updateEndpoint(CallbackContext callbackContext) throws MobileKeysException {
        MobileKeysApi.getInstance().getMobileKeys().endpointUpdate(this);

        callbackContext.success("Updated endpoint");
    }

    // listMobileKeys - not void: java.util.List<MobileKey>
    public void listMobileKeys(CallbackContext callbackContext) {
        callbackContext.success("Reached listMobileKeys()");
    }

    // getEnpointInfo
    public void endpointInfo(CallbackContext callbackContext) {

        callbackContext.success("Reached endpointInfo()");
    }

    public void unregisterEndpoint(CallbackContext callbackContext) {
        MobileKeysApi.getInstance().getMobileKeys().unregisterEndpoint(new MobileKeysCallback() {
                @Override
                public void handleMobileKeysTransactionCompleted ()
                {
                    // does something if unregisterEndpoint was successful
                    callbackContext.success("Managed to unregister endpoint. Run isEndpointSetup() to verify.");
                }

                @Override
                public void handleMobileKeysTransactionFailed (MobileKeysException
                mobileKeysException)
                {
                    // does something if unregisterEndpoint was unsuccessful
                    callbackContext.error("Was unable to unregister endpoint");
                }
            });
        callbackContext.success("Tried to unregister endpoint. Run isEndpointSetup() to verify.");
    }

    // BLE scanning for doors
    public void startScanning(CallbackContext callbackContext) {
        ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
        controller.enableHce();
        controller.startScanning();
    }

    public void startForegroundScanning(CallbackContext callbackContext) {
        // check if app has locationPermissions
        ReaderConnectionController controller = MobileKeysApi.getInstance().getReaderConnectionController();
        controller.enableHce();

        Notification notification = UnlockNotification.create(requireContext());
        controller.startForegroundScanning(notification);
    }

    // Interface implementations
    @Override
    public void handleMobileKeysTransactionCompleted()
    {
        // does something if applicationStartup was successful
    }

    @Override
    public void handleMobileKeysTransactionFailed(MobileKeysException mobileKeysException)
    {
        // does something if applicationStartup was unsuccessful
    }

    public void pluginResult(CallbackContext callbackContext) throws JSONException {
        try {
            JSONObject json = new JSONObject();
            json.put("testkey", "testvalue");

            PluginResult result = new PluginResult(PluginResult.Status.OK, json);

            callbackContext.sendPluginResult(result);
        } catch (JSONException ex) {
            callbackContext.error(ex.toString());
        }
    }

    /*
    private boolean hasLocationPermissions()
    {
        return (ContextCompat.checkSelfPermission(requireContext(),
                Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED ||
                ContextCompat.checkSelfPermission(requireContext(),
                        Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED);
    }*/
}

