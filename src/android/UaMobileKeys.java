package cordova.plugin.uamobilekeys;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.assaabloy.mobilekeys.api.ApiConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeys;
import com.assaabloy.mobilekeys.api.MobileKeysApi;
import com.assaabloy.mobilekeys.api.ReaderConnectionController;
import com.assaabloy.mobilekeys.api.ble.*;
import com.assaabloy.mobilekeys.api.hce.NfcConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeysException;

import android.content.Context;
import android.os.Build;
import android.app.Activity;


/**
 * This class echoes a string called from JavaScript.
 */
public class UaMobileKeys extends CordovaPlugin {

    private UaKeyImplementation uaKey = new UaKeyImplementation();
    private UaMobileKeysApi uaKeyApi = new UaMobileKeysApi();
    private UaMobileKeysSetup uaSetup = new UaMobileKeysSetup();

    // Main method for selecting the correct native code, based on input from JavaScript Interface
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if (!uaSetup.isMobileKeysInitialized()) {
            this.initializeMobileKeysApi();
        }

        if (action.equals("coolMethod")) {
            String message = args.getString(0);
            this.coolMethod(message, callbackContext);
            return true;
        } else if (action.equals("echoMethod")) {
            String arguments = args.getString(0);
            boolean argumentResults = Boolean.valueOf(arguments);
            this.echoMethod(callbackContext, argumentResults);
            return true;
        } else if (action.equals("externalClassMethod")) {
            this.externalClassMethod(callbackContext);
            return true;
        } else if (action.equals("startup")) {
            this.startup(callbackContext);
            return true;
        } else if (action.equals("isEndpointSetup")) {
            this.isEndpointSetup(callbackContext);
            return true;
        } else if (action.equals("setupEndpoint")) {
            String invitationCode = args.getString(0);
            this.setupEndpoint(callbackContext, invitationCode);
            return true;
        } else if (action.equals("updateEndpoint")) {
            this.updateEndpoint(callbackContext);
            return true;
        } else if (action.equals("listMobileKeys")) {
            this.listMobileKeys(callbackContext);
            return true;
        } else if (action.equals("endpointInfo")) {
            this.endpointInfo(callbackContext);
            return true;
        } else if (action.equals("unregisterEndpoint")) {
            this.unregisterEndpoint(callbackContext);
            return true;
        } else if (action.equals("initializeMobileKeysApi")) {
            this.initializeMobileKeysApi();
            return true;
        } else if (action.equals("startScanning")) {
            this.startScanning(callbackContext);
            return true;
        } else if (action.equals("startForegroundScanning")) {
            this.startForegroundScanning(callbackContext);
            return true;
        } else if (action.equals("stopScanning")) {
            this.stopScanning(callbackContext);
            return true;
        } else if (action.equals("pluginResult")) {
            this.pluginResult(callbackContext);
            return true;
        }

        return false;
    }

    // Initialize Mobile Keys Api - should only be called once
    private void initializeMobileKeysApi() {
        int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
        Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();
        uaSetup.initializeMobileKeysApi(context);
    }

    // Mobile keys implementation
    private void startup(CallbackContext callbackContext){
        try {
            uaKeyApi.startup(callbackContext);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in startup()");
        }
    }

    private void isEndpointSetup(CallbackContext callbackContext){
        try {
            uaKeyApi.isEndpointSetup(callbackContext);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in isEndpointSetup()");
        }
    }

    private void setupEndpoint(CallbackContext callbackContext, String invitationCode){
        try {
            uaKeyApi.setupEndpoint(callbackContext, invitationCode);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in setupEndpoint()");
        }
    }

    private void updateEndpoint(CallbackContext callbackContext){
        try {
            uaKeyApi.updateEndpoint(callbackContext);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in updateEndpoint()");
        }
    }

    private void listMobileKeys(CallbackContext callbackContext){
        uaKeyApi.listMobileKeys(callbackContext);
    }

    private void endpointInfo(CallbackContext callbackContext){
        uaKeyApi.endpointInfo(callbackContext);
    }

    private void unregisterEndpoint(CallbackContext callbackContext) {
            uaKeyApi.unregisterEndpoint(callbackContext);
    }

    private void startScanning(CallbackContext callbackContext) {
        int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
        Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();
        Activity acc = cordova.getActivity();

        uaKeyApi.startScanning(callbackContext, context, acc);
    }

    private void startForegroundScanning(CallbackContext callbackContext) {
        int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
        Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();
        Activity acc = cordova.getActivity();

        uaKeyApi.startForegroundScanning(callbackContext, context, acc);
    }

    private void stopScanning(CallbackContext callbackContext) {
        uaKeyApi.stopScanning(callbackContext);
    }

    // Simple test-methods to ensure that contact has been made with the plugin
    private void coolMethod(String message, CallbackContext callbackContext) {
        if (message != null && message.length() > 0) {
            callbackContext.success(message);
        } else {
            callbackContext.error("Expected one non-empty string argument.");
        }
    }

    private void externalClassMethod(CallbackContext callbackContext) {
        if (uaKey.GotContact()) {
            callbackContext.success("Got contact with external class");
        }
        callbackContext.error("Didn't get in touch with external class");
    }

    private void echoMethod(CallbackContext callbackContext, boolean outputchanger) {
        uaKey.echoMethod(callbackContext, outputchanger);
    }

    private void pluginResult(CallbackContext callbackContext) throws JSONException {
        try {
            uaKeyApi.pluginResult(callbackContext);
        } catch (JSONException ex) {
            callbackContext.error(ex.toString());
        }

    }
}
