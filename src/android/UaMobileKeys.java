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

public class UaMobileKeys extends CordovaPlugin {
    private UaMobileKeysApi uaKeyApi = new UaMobileKeysApi();
    private UaMobileKeysSetup uaSetup = new UaMobileKeysSetup();

    public UaMobileKeys() {};

    // Main method for selecting the correct native code, based on input from JavaScript Interface
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

        if (!uaSetup.isMobileKeysInitialized()) {
            int lockCodeInt;
            String lockCode = args.getString(0);
            try {
                lockCodeInt = Integer.parseInt(lockCode);
            } catch (NumberFormatException e) {
                lockCodeInt = 0;
            }

            this.initializeMobileKeysApi(lockCodeInt);
        }

        if (action.equals("startup")) {
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
        } else if (action.equals("getUsefulEndpointInfo")) {
            this.getUsefulEndpointInfo(callbackContext);
            return true;
        } else if (action.equals("unregisterEndpoint")) {
            this.unregisterEndpoint(callbackContext);
            return true;
        } else if (action.equals("initializeMobileKeysApi")) {
            int lockCodeInt;
            String lockCode = args.getString(0);
            try {
                lockCodeInt = Integer.parseInt(lockCode);
            } catch (NumberFormatException e) {
                lockCodeInt = 0;
            }

            this.initializeMobileKeysApi(lockCodeInt);
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
        } else if (action.equals("checkBluetoothPermission")) {
            this.checkBluetoothPermission(callbackContext);
            return true;
        } else if (action.equals("androidCheckBtPermissionStatus")) {
            this.checkBtPermissionStatus(callbackContext);
            return true;
        }

        return false;
    }

    // Initialize Mobile Keys Api - should only be called once
    private void initializeMobileKeysApi(int lockCode) {
        int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
        Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();

        uaSetup.initializeMobileKeysApi(context, lockCode);
    }

    // Mobile keys implementation
    private void startup(CallbackContext callbackContext) {
        try {
            int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
            Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();
            uaKeyApi.startup(callbackContext, context);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in startup()");
        }
    }

    private void isEndpointSetup(CallbackContext callbackContext) {
        try {
            uaKeyApi.isEndpointSetup(callbackContext);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in isEndpointSetup()");
        }
    }

    private void setupEndpoint(CallbackContext callbackContext, String invitationCode) {
        try {
            uaKeyApi.setupEndpoint(callbackContext, invitationCode);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in setupEndpoint()");
        }
    }

    private void updateEndpoint(CallbackContext callbackContext) {
        try {
            uaKeyApi.updateEndpoint(callbackContext);
        } catch (MobileKeysException ex) {
            System.out.println(ex);
            callbackContext.error("Something went horribly wrong in updateEndpoint()");
        }
    }

    private void listMobileKeys(CallbackContext callbackContext) {
        uaKeyApi.listMobileKeys(callbackContext);
    }

    private void endpointInfo(CallbackContext callbackContext) {
        uaKeyApi.endpointInfo(callbackContext);
    }

    private void getUsefulEndpointInfo(CallbackContext callbackContext) {
        uaKeyApi.getUsefulEndpointInfo(callbackContext);
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

    private void checkBluetoothPermission(CallbackContext callbackContext) {
        int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
        Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();
        Activity acc = cordova.getActivity();

        uaKeyApi.checkBluetoothPermission(callbackContext, context, acc);
    }

    private void checkBtPermissionStatus(CallbackContext callbackContext) {
        int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
        Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();

        uaKeyApi.checkBtPermissionStatus(callbackContext, context);
    }

    private void stopScanning(CallbackContext callbackContext) {
        uaKeyApi.stopScanning(callbackContext);
    }
}
