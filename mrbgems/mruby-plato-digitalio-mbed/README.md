# mruby-plato-digitalio-mbed   [![Build Status](https://travis-ci.org/mruby-plato/mruby-plato-digitalio-mbed.svg?branch=master)](https://travis-ci.org/mruby-plato/mruby-plato-digitalio-mbed)
Plato::DigitalIO class for mbed board
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

  # ... (snip) ...

  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-gpio'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-digitalio-mbed'
end
```

## example
```ruby
io1 = Plato::DigitalIO.new(0)
io2 = Plato::DigitalIO.new(1)
io2.write(io1.low? ? 0 : 1)
```

## License
under the MIT License:
- see LICENSE file
