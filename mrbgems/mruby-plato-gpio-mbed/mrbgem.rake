MRuby::Gem::Specification.new('mruby-plato-gpio-mbed') do |spec|
  spec.license = 'MIT'
  spec.author = 'SCSK KYUSHU CORPORATION'
  spec.description = 'Plato::GPIO class for mbed board'

  spec.add_dependency('mruby-plato-gpio')

  spec.cc.include_paths << [
    '~/git/mimaki/mbed-mruby',
    '~/git/mimaki/mbed-mruby/mbed-os'
  ]
  spec.cc.defines << ['MBED']
end
