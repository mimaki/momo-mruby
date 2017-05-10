# mruby-plato-serial-grpeach   [![Build Status](https://travis-ci.org/mruby-plato/mruby-plato-serial-grpeach.svg?branch=master)](https://travis-ci.org/mruby-plato/mruby-plato-serial-grpeach)
PlatoPeach::Serial class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

  # ... (snip) ...

  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-serial'
  conf.gem :git => 'https://github.com/mruby-plato/mruby-plato-serial-grpeach'
end
```

## example
```ruby
ser = Plato::Serial.open(9600)
name = ser.gets
ser.puts "Hello, #{name.chomp}!"
```

## License
under the MIT License:
- see LICENSE file
