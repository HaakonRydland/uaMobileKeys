//#region Seupt information
var exec = require('cordova/exec');

function UaMobileKeys() {}

UaMobileKeys.prototype.PluginName = "UaMobileKeys";

UaMobileKeys.prototype.pInvoke = function(method, data, callback, callbackError) {
    console.log('Inside pInvoke');

    if (data == null || data == undefined) {
        data = [];
    } else if (!Array.isArray(data)) {
        data = [data];
    }
    exec(callback, function(err) {
        callback(method + ' returned an error in ' + this.PluginName);
    }, this.PluginName, method, data);
}

UaMobileKeys.install = function() {
    console.log('Inside install');

    if (!window.plugins) {
        window.plugins = {};
    }

    window.plugins.UaMobileKeys = new UaMobileKeys();

    return window.plugins.UaMobileKeys;
};

cordova.addConstructor(UaMobileKeys.install);

//#endregion

//#region MobileKeys implementation
UaMobileKeys.prototype.startup = function(arg0, success, error) {
    this.pInvoke("startup", arg0, success, error);
};

UaMobileKeys.prototype.isEndpointSetup = function(arg0, success, error) {
    this.pInvoke("isEndpointSetup", arg0, success, error);
};

UaMobileKeys.prototype.setupEndpoint = function(arg0, success, error) {
    this.pInvoke("setupEndpoint", arg0, success, error);
};

UaMobileKeys.prototype.updateEndpoint = function(arg0, success, error) {
    this.pInvoke("updateEndpoint", arg0, success, error);
};

UaMobileKeys.prototype.listMobileKeys = function(arg0, success, error) {
    this.pInvoke("listMobileKeys", arg0, success, error);
};

UaMobileKeys.prototype.endpointInfo = function(arg0, success, error) {
    this.pInvoke("endpointInfo", arg0, success, error);
};


//#endregion

//#region interface for native code test methods
UaMobileKeys.prototype.coolMethod = function(arg0, success, error) {
    this.pInvoke("coolMethod", arg0, success, error);
};

UaMobileKeys.prototype.externalClassMethod = function(arg0, success, error) {
    this.pInvoke("externalClassMethod", arg0, success, error);
};

UaMobileKeys.prototype.echoMethod = function(arg0, success, error) {
    this.pInvoke("echoMethod", arg0, success, error);
};

//#endregion