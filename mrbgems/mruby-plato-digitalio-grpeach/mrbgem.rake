MRuby::Gem::Specification.new('mruby-plato-digitalio-grpeach') do |spec|
  spec.license = 'MIT'
  spec.author = 'Hiroshi Mimaki'
  spec.description = 'Plato::DigitalIO class for GR-PEACH board'

  spec.add_dependency('mruby-plato-gpio')
  spec.add_dependency('mruby-plato-gpio-grpeach')
  spec.add_dependency('mruby-plato-digitalio')
end
