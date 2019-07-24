package cordova.plugin.uamobilekeys;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CallbackContext;

import com.assaabloy.mobilekeys.api.ApiConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeysApi;
import com.assaabloy.mobilekeys.api.ble.*;
import com.assaabloy.mobilekeys.api.hce.NfcConfiguration;

import android.content.Context;
import android.os.Build;

public class UaMobileKeysSetup extends CordovaPlugin {
    public UaMobileKeysSetup() {}

    private MobileKeysApi mobileKeysFactory;
    int androidVersionCurrentlyRunning = Build.VERSION.SDK_INT;
    //Context context = this.cordova.getActivity().getApplicationContext();

    //Context context = (androidVersionCurrentlyRunning >= 21) ? cordova.getActivity().getWindow().getContext() : cordova.getActivity().getApplicationContext();

    public void initializeMobileKeysApi(Context context)
    {
        OpeningTrigger[] openingTriggers = {new TapOpeningTrigger(context)};
        ScanConfiguration scanConfiguration = new ScanConfiguration.Builder(openingTriggers, 1)
                .setBluetoothModeIfSupported(BluetoothMode.DUAL)
                .setScanMode(ScanMode.OPTIMIZE_PERFORMANCE)
                .setRssiSensitivity(RssiSensitivity.HIGH)
                .build();

        ApiConfiguration apiConfiguration = new ApiConfiguration.Builder()
                .setApplicationId("uamobkeys")
                .setApplicationDescription("Sample app for testing")
                .setNfcParameters(new NfcConfiguration.Builder()
                        .unsafe_setAttemptNfcWithScreenOff(false)
                        .build())
                .build();
        mobileKeysFactory = MobileKeysApi.getInstance();
        mobileKeysFactory.initialize(context, apiConfiguration, scanConfiguration);
        if(mobileKeysFactory.isInitialized() == false) {
            throw new IllegalStateException();
        }

        MobileKeysApi.getInstance().getReaderConnectionController().enableHce();
    }

    public boolean isMobileKeysInitialized() {
        return MobileKeysApi.getInstance().isInitialized();
    }
}
