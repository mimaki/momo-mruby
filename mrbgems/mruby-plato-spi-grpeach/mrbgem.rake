MRuby::Gem::Specification.new('mruby-plato-spi-grpeach') do |spec|
  spec.license = 'MIT'
  spec.author = 'SCSK KYUSHU CORPORATION'
  spec.description = 'PlatoPeach::SPI class'

  spec.add_dependency('mruby-plato-gpio')
  spec.add_dependency('mruby-plato-digitalio-grpeach')
  spec.add_dependency('mruby-plato-spi')
end
