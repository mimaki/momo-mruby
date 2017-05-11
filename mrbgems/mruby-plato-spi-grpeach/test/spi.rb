# PlatoPeach::SPI class

=begin
assert('SPI', 'class') do
  assert_equal(PlatoPeach::SPI.class, Class)
end

assert('SPI', 'superclass') do
  assert_equal(PlatoPeach::SPI.superclass, Object)
end

assert('SPI', 'register_device') do
  assert_nothing_raised {
    Plato::SPI.register_device(PlatoPeach::SPI)
  }
end

assert('SPI', 'new') do
  spi0 = PlatoPeach::SPI.new(0)
  spi1 = PlatoPeach::SPI.new(1, 1)
  spi2 = PlatoPeach::SPI.new(2, 2, :msbfirst)
  spi3 = PlatoPeach::SPI.new(3, 3, :lsbfirst, 1)
  assert_true(spi0 && spi1 && spi2 && spi3)

  assert_raise(ArgumentError) {PlatoPeach::SPI.new}
  assert_raise(ArgumentError) {PlatoPeach::SPI.new(0, 1, :msbfirst, 2, 3)}
  assert_raise(RangeError) {PlatoPeach::SPI.new(-1)}
  assert_raise(RangeError) {PlatoPeach::SPI.new(4)}
  assert_raise(TypeError) {PlatoPeach::SPI.new(0, 1, 0)}
end

assert('SPI', 'open') do
  spi0 = Plato::SPI.open(0)
  spi1 = Plato::SPI.open(1, 1)
  spi2 = Plato::SPI.open(2, 2, :msbfirst)
  spi3 = Plato::SPI.open(3, 3, :lsbfirst, 1)
  assert_true(spi0 && spi1 && spi2 && spi3)

  assert_raise(ArgumentError) {Plato::SPI.open}
  assert_raise(ArgumentError) {Plato::SPI.open(0, 1, :msbfirst, 2, 3)}
  assert_raise(RangeError) {Plato::SPI.open(-1)}
  assert_raise(RangeError) {Plato::SPI.open(4)}
  assert_raise(TypeError) {Plato::SPI.open(0, 1, 0)}
end

assert('SPI', 'transfer') do
  # transfer(data)
  spi = Plato::SPI.open(0)
  v = spi.transfer(0)
  assert_equal(v.class, Array)
  assert_equal(v.size, 1)
  assert_equal(v[0].class, Fixnum)
  v = spi.transfer([1,2,3])
  assert_equal(v.class, Array)
  assert_equal(v.size, 1)
  assert_equal(v[0].class, Fixnum)
  v = spi.transfer('ABCDE')
  assert_equal(v.class, Array)
  assert_equal(v.size, 1)
  assert_equal(v[0].class, Fixnum)

  # transfer(data, rcvlen)
  v = spi.transfer(1, 2)
  assert_equal(v.class, Array)
  assert_equal(v.size, 2)
  assert_equal(v[0].class, Fixnum)
  assert_equal(v[1].class, Fixnum)
  v = spi.transfer([1,2], 3)
  assert_equal(v.class, Array)
  assert_equal(v.size, 3)
  assert_equal(v[0].class, Fixnum)
  assert_equal(v[1].class, Fixnum)
  assert_equal(v[2].class, Fixnum)
  v = spi.transfer('A', 4)
  assert_equal(v.class, Array)
  assert_equal(v.size, 4)
  assert_equal(v[0].class, Fixnum)
  assert_equal(v[1].class, Fixnum)
  assert_equal(v[2].class, Fixnum)
  assert_equal(v[3].class, Fixnum)

  # transfer(data, rcvlen, rcvtype)
  v = spi.transfer(255, 2, :as_array)
  assert_equal(v.class, Array)
  assert_equal(v.size, 2)
  assert_equal(v[0].class, Fixnum)
  assert_equal(v[1].class, Fixnum)
  v = spi.transfer('123', 3, :as_string)
  assert_equal(v.class, String)
  assert_equal(v.size, 3)

  # ArgumentError
  assert_raise(ArgumentError) {spi.transfer}
  assert_raise(ArgumentError) {spi.transfer(1, 1, :as_array, 1)}
end
=end
