package cordova.plugin.uamobilekeys;

import com.assaabloy.mobilekeys.api.ApiConfiguration;
import com.assaabloy.mobilekeys.api.MobileKeysApi;
import com.assaabloy.mobilekeys.api.ble.*;
import com.assaabloy.mobilekeys.api.hce.NfcConfiguration;
import android.content.Context;

public class UaMobileKeysSetup {
    private MobileKeysApi mobileKeysFactory;

    Context context = this.cordova.getActivity().getApplicationContext();

    private void initializeMobileKeysApi()
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
}
