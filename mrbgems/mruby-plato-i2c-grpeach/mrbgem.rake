MRuby::Gem::Specification.new('mruby-plato-i2c-grpeach') do |spec|
  spec.license = 'MIT'
  spec.author = 'Hiroshi Mimaki'
  spec.description = 'PlatoPeach::I2C class'

  spec.add_dependency('mruby-plato-i2c')
  spec.add_test_dependency('mruby-string-ext')
end
