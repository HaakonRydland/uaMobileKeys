Pod::Spec.new do |s|
  s.name             = "SeosMobileKeysSDK-Debug"
  s.version          = "7.6.7"
  s.summary          = "Open readers with your iOS device"
  s.homepage         = "http://www.assaabloy.com/seos"
  s.license      = {
     :type => 'Copyright',
     :text => <<-LICENSE
       Copyright (c) 2021 ASSA ABLOY Mobile Services. Version 7.6.7. All rights reserved.
       LICENSE
   }

  s.author           = { "ASSA ABLOY Mobile Services" => "mobilekeys@assaabloy.com" }
  s.source = { :path => '.' }

  s.requires_arc = true

  s.ios.deployment_target = '11.0'
  s.ios.frameworks = 'Foundation', 'CoreTelephony', 'Security', 'CoreLocation', 'CoreBluetooth', 'CoreMotion', 'UIKit', 'SystemConfiguration', 'LocalAuthentication'

  s.watchos.deployment_target = '4.0'
  s.watchos.frameworks = 'Foundation', 'Security', 'CoreLocation', 'CoreBluetooth', 'CoreMotion', 'UIKit'

  s.module_name = 'SeosMobileKeysSDK'

  s.dependency 'JSONModel'
  s.dependency 'CocoaLumberjack'
  s.dependency 'Mixpanel'
  s.dependency 'BerTlv'
  s.vendored_frameworks = 'SeosMobileKeysSDK.framework'
end

