Pod::Spec.new do |s|
  s.name             = "SeosMobileKeysSDK-Debug"
  s.version          = "7.3.0"
  s.summary          = "Open readers with your iOS device"
  s.homepage         = "http://www.assaabloy.com/seos"
  s.license      = {
     :type => 'Copyright',
     :text => <<-LICENSE
       Copyright (c) 2019 ASSA ABLOY Mobile Services. Version 7.3.0. All rights reserved.
       LICENSE
   }

  s.author           = { "ASSA ABLOY Mobile Services" => "mobilekeys@assaabloy.com" }
  s.source = { :path => '.' }

  s.requires_arc = true

  s.ios.deployment_target = '10.0'
  s.ios.frameworks = 'Foundation', 'CoreTelephony', 'Security', 'CoreLocation', 'CoreBluetooth', 'CoreMotion', 'UIKit', 'SystemConfiguration', 'LocalAuthentication', 'CoreML'

  s.watchos.deployment_target = '4.0'
  s.watchos.frameworks = 'Foundation', 'Security', 'CoreLocation', 'CoreBluetooth', 'CoreMotion', 'UIKit', 'CoreML'

  s.module_name = 'SeosMobileKeysSDK'

  s.dependency 'JSONModel', '~> 1.7.0'
  s.dependency 'CocoaLumberjack/Swift', '~> 3.5.3'
  s.dependency 'Mixpanel', '~> 3.4.5'
  s.dependency 'BerTlv', '~> 0.2.5'
  s.vendored_frameworks = 'SeosMobileKeysSDK.framework'

end
