MRuby::Gem::Specification.new('mruby-plato-spi-grpeach') do |spec|
  spec.license = 'MIT'
  spec.author = 'Hiroshi Mimaki'
  spec.description = 'PlatoPeach::SPI class'

  spec.add_dependency('mruby-plato-gpio')
  spec.add_dependency('mruby-plato-gpio-grpeach')
  spec.add_dependency('mruby-plato-digitalio')
  spec.add_dependency('mruby-plato-digitalio-grpeach')
  spec.add_dependency('mruby-plato-spi')
end
