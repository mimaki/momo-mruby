MRuby::Gem::Specification.new('mruby-plato-i2c-mbed') do |spec|
  spec.license = 'MIT'
  spec.authors = 'SCSK KYUSHU CORPORATION'
  spec.description = 'PlatoMbed::I2C class'

  spec.add_dependency('mruby-plato-i2c')
  spec.add_test_dependency('mruby-string-ext')
end
