# mruby-plato-digitalio-grpeach   [![Build Status](https://travis-ci.org/mruby-plato/mruby-plato-digitalio-grpeach.svg?branch=master)](https://travis-ci.org/mruby-plato/mruby-plato-digitalio-grpeach)
PlatoPeach::SPI class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

  # ... (snip) ...

  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-digitalio'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-digitalio-grpeach'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-spi'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-spi-grpeach'
end
```

## example
```ruby
spi = Plato::SPI.open(1)
puts spi.transfer(0)
```

## License
under the MIT License:
- see LICENSE file
