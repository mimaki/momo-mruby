#
# STDOUT
#

assert('STDOUT class') do
  assert_kind_of(Class, STDOUT.class)
  assert_equal(Object, STDOUT.superclass)
end

assert('STDOUT._putc') do
  assert_nothing_raised {STDOUT._putc(0)}
  assert_raise(ArgumentError) {STDOUT._putc}
  assert_raise(ArgumentError) {STDOUT._putc(1, 2)}
end


#
# STDIN
#

# class STDINstub < STDIN
#   @@buffer = []
#   def self._getc
#     c = @@buffer.shift
#   end
#   def self.buffer=(str)
#     @@buffer = str.chars.map {|c| c.ord}
#   end
# end

assert('STDIN class') do
  assert_kind_of(Class, STDIN.class)
  assert_equal(Object, STDIN.superclass)
  assert_equal(STDIN, $stdin)
end

assert('STDIN._getc') do
  assert_kind_of(Fixnum, STDIN._getc)
end

# assert('STDIN.getc') do
#   $stdin = STDINstub
#   $stdin.buffer = "A"
#   assert_equal('A', $stdin.getc)
#   assert_nil($stdin.getc)
#   $stdin = STDIN
# end
