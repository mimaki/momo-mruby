#! /usr/bin/env ruby
require 'fileutils'

# remame 'mruby/string.h' to 'mruby/_string.h'
inc = File.join('mruby', 'include', 'mruby')
string_h = File.join(inc, 'string.h')
_string_h = File.join(inc, '_string.h')
if File.exist? string_h
  FileUtils.mv string_h, _string_h
end

bak = case RUBY_PLATFORM.downcase
when /darwin/ # macOS
  "''"
else  # Linux and other
  ''
end

# modify #inlucde path
`find mruby -type f | grep '\.[ch]$'`.each_line {|f|
  if f =~ /\.[ch]$/
    `sed -i #{bak} 's!mruby/string.h!mruby/_string.h!g' #{f}`
  end
}

# Enable MRB_ENABLE_DEBUG_HOOK
`sed -i #{bak} 's!^//#define MRB_ENABLE_DEBUG_HOOK!#define MRB_ENABLE_DEBUG_HOOK 1!g' mruby/include/mrbconf.h`
