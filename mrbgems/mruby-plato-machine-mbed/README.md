# mruby-plato-machine-mbed   [![Build Status](https://travis-ci.org/mruby-plato/mruby-plato-machine-mbed.svg?branch=master)](https://travis-ci.org/mruby-plato/mruby-plato-machine-mbed)
PlatoMbed::Machine class for mbed board
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

  # ... (snip) ...

  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-machine'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-machine-mbed'
end
```

## example
```ruby
Plato::Machine.delay(100)
puts Plato::Machine.millis
```

## License
under the MIT License:
- see LICENSE file
