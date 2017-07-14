#
# STDOUT
#

assert('STDOUT class') do
  assert_kind_of(Class, STDOUT.class)
  assert_equal(Object, STDOUT.superclass)
end

# assert('STDOUT._putc') do
#   assert_nothing_raised {STDOUT._putc(0)}
#   assert_raise(ArgumentError) {STDOUT._putc}
#   assert_raise(ArgumentError) {STDOUT._putc(1, 2)}
# end


#
# STDIN
#

class STDINstub < STDIN
  @@buffer = []
  def self._getc
    c = @@buffer.shift
  end
  def self.buffer=(str)
    @@buffer = str.chars.map {|c| c.ord}
  end
end

assert('STDIN class') do
  assert_kind_of(Class, STDIN.class)
  assert_equal(Object, STDIN.superclass)
  assert_equal(STDIN, $stdin)
end

assert('STDIN.getc') do
  $stdin = STDINstub
  $stdin.buffer = "A"
  assert_equal('A', $stdin.getc)
  assert_nil($stdin.getc)
  $stdin = STDIN
end

assert('STDIN.gets()') do
  $stdin = STDINstub

  $stdin.buffer = "ABC\n123\t45\nabcde\n"
  assert_equal("ABC\n",   $stdin.gets)
  assert_equal("123\t45\n", $stdin.gets)
  assert_equal("abcde\n", $stdin.gets)
  assert_nil($stdin.gets)

  $stdin = STDIN
end

assert('STDIN.gets(rs)') do
  $stdin = STDINstub

  $stdin.buffer = "ABC\n123\t45\nabcde\n"
  assert_equal("ABC\n123",      $stdin.gets('3'))
  assert_equal("\t45\nabcde\n", $stdin.gets('3'))
  assert_nil($stdin.gets)

  $stdin = STDIN
end

assert('STDIN.gets(limit)') do
  $stdin = STDINstub

  $stdin.buffer = "ABC\n123\t45\nabcde\n"
  assert_equal("ABC\n", $stdin.gets(4))
  assert_equal("123\t", $stdin.gets(4))
  assert_equal("45\n",  $stdin.gets(4))
  assert_equal("abcd",  $stdin.gets(4))
  assert_equal("e\n",   $stdin.gets(4))
  assert_nil($stdin.gets)

  $stdin = STDIN
end

assert('STDIN.gets(rs, limit)') do
  $stdin = STDINstub

  $stdin.buffer = "ABC\n123\t45\nabcde\n"
  assert_equal("ABC\n1",  $stdin.gets("\t", 5))
  assert_equal("23\t",    $stdin.gets("\t", 5))
  assert_equal("45\nab",  $stdin.gets("\t", 5))
  assert_equal("cde\n",   $stdin.gets("\t", 5))
  assert_nil($stdin.gets)

  $stdin = STDIN
end
