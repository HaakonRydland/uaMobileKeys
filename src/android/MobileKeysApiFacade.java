package cordova.plugin.uamobilekeys;

/**
 *
 * Interface to access the mobile keys api
 */
public interface MobileKeysApiFacade extends MobileKeysApiFactory
{
    /**
     * Callback to the api that setup/registration is complete
     */
    void onStartUpComplete();

    /**
     * Callback to the api that setup/registration is complete
     */
    void onEndpointSetUpComplete();

    /**
     * Endpoint is not personalized callback
     */
    void endpointNotPersonalized();

    /**
     * Check to see if endoint is setup
     * @return
     */
    boolean isEndpointSetUpComplete();
}
