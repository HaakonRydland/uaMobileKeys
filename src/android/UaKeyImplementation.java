package cordova.plugin.uamobilekeys;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

public class UaKeyImplementation extends CordovaPlugin {
    public UaKeyImplementation() {}

    public boolean GotContact() { return true; }

    public void echoMethod(CallbackContext callbackContext, boolean outputchanger) {
        if (outputchanger) {
            callbackContext.success("Got contact with external method: " + outputchanger);
        } else {
            callbackContext.error("Didn't get contact with external method: " + outputchanger);
        }
    }
}