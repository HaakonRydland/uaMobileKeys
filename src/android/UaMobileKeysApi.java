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
        MobileKeys mobileKeys = MobileKeysApi.getInstance().getMobileKeys();
        mobileKeys.applicationStartup(this);

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

        callbackContext.success("Reached setupEndpoint()");
    }

    // endpointUpdate
    public void updateEndpoint(CallbackContext callbackContext) {
        callbackContext.success("Reached updateEndpoint()");
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
            public void handleMobileKeysTransactionCompleted()
            {
                // does something if unregisterEndpoint was successful
            }

            @Override
            public void handleMobileKeysTransactionFailed(MobileKeysException mobileKeysException)
            {
                // does something if unregisterEndpoint was unsuccessful
            }
        });
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
}

