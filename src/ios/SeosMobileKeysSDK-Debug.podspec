Pod::Spec.new do |s|
  s.name             = "SeosMobileKeysSDK-Debug"
  s.version          = "7.5.2"
  s.summary          = "Open readers with your iOS device"
  s.homepage         = "http://www.assaabloy.com/seos"
  s.license      = {
     :type => 'Copyright',
     :text => <<-LICENSE
       Copyright (c) 2019 ASSA ABLOY Mobile Services. Version 7.5.2. All rights reserved.
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

  s.dependency 'JSONModel', '~> 1.8.0'
  s.dependency 'CocoaLumberjack/Swift', '~> 3.5.3'
  s.dependency 'Mixpanel', '~> 3.4.9'
  s.dependency 'BerTlv', '~> 0.2.5'
  s.vendored_frameworks = 'SeosMobileKeysSDK.framework'

end
