# mruby-plato-GPIO-grpeach   [![Build Status](https://travis-ci.org/mruby-plato/mruby-plato-gpio-grpeach.svg?branch=master)](https://travis-ci.org/mruby-plato/mruby-plato-gpio-grpeach)
Plato::GPIO class for GR-PEACH board
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

  # ... (snip) ...

  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-gpio'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-gpio-grpeach'
end
```

## example
```ruby
io1 = Plato::GPIO.new(Plato::GPIO::LED1)
io1.high
```

## License
under the MIT License:
- see LICENSE file
