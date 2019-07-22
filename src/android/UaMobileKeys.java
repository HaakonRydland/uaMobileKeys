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

/**
 * This class echoes a string called from JavaScript.
 */
public class UaMobileKeys extends CordovaPlugin {

    private UaKeyImplementation uaKey = new UaKeyImplementation();
    private UaMobileKeyImplementation uaImplementation = new UaMobileKeyImplementation();

    // Main method for selecting the correct native code, based on input from JavaScript Interface
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
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
            this.setupEndpoint(callbackContext);
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
        }

        return false;
    }

    // Mobile keys implementation
    private void startup(CallbackContext callbackContext){
        uaImplementation.startup(callbackContext);
    }

    private void isEndpointSetup(CallbackContext callbackContext){
        uaImplementation.isEndpointSetup(callbackContext);
    }

    private void setupEndpoint(CallbackContext callbackContext){
        uaImplementation.setupEndpoint(callbackContext);
    }

    private void updateEndpoint(CallbackContext callbackContext){
        uaImplementation.updateEndpoint(callbackContext);
    }

    private void listMobileKeys(CallbackContext callbackContext){
        uaImplementation.listMobileKeys(callbackContext);
    }

    private void endpointInfo(CallbackContext callbackContext){
        uaImplementation.endpointInfo(callbackContext);
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
}
