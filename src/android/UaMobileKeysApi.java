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

public class UaMobileKeysApi extends CordovaPlugin {
    private MobileKeysApiFacade mobileKeysApiFacade;

    // Mobile Keys interface
    public void startup(CallbackContext callbackContext) {
        callbackContext.success("Reached startup()");
    }

    public void isEndpointSetup(CallbackContext callbackContext) {
        callbackContext.success("Reached isEndpointSetup()");
    }

    public void setupEndpoint(CallbackContext callbackContext) {
        callbackContext.success("Reached setupEndpoint()");
    }

    public void updateEndpoint(CallbackContext callbackContext) {
        callbackContext.success("Reached updateEndpoint()");
    }

    public void listMobileKeys(CallbackContext callbackContext) {
        callbackContext.success("Reached listMobileKeys()");
    }

    public void endpointInfo(CallbackContext callbackContext) {
        callbackContext.success("Reached endpointInfo()");
    }

}

