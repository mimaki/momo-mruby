MRuby::Gem::Specification.new('mruby-stdio') do |spec|
  spec.license = 'MIT'
  spec.author = 'SCSK KYUSHU CORPORATION'
  spec.description = 'STDOUT and STDIN for embedded system'

  spec.add_test_dependency('mruby-string-ext')
end
