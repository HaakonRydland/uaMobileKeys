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

//#region interface for native code
UaMobileKeys.prototype.coolMethod = function(arg0, success, error) {
    this.pInvoke("coolMethod", arg0, success, error);
};

UaMobileKeys.prototype.coolMethod = function(arg0, success, error) {
    this.pInvoke("externalClassMethod", arg0, success, error);
};

UaMobileKeys.prototype.coolMethod = function(arg0, success, error) {
    this.pInvoke("echoMethod", arg0, success, error);
};

//#endregion