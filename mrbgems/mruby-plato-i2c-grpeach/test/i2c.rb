# PlatoPeach::I2C class

assert('I2C - class') do
  assert_kind_of(Class, PlatoPeach::I2C)
  assert_equal(Object, PlatoPeach::I2C.superclass)
end

assert('I2C#new') do
  assert_nothing_raised {
    PlatoPeach::I2C.new(1)
    PlatoPeach::I2C.new(2, 3)
  }
  assert_raise(ArgumentError) {PlatoPeach::I2C.new}
  assert_raise(ArgumentError) {PlatoPeach::I2C.new(0, 1, 2)}
end

assert('I2C.oepn - Plato::I2C') do
  assert_raise(RuntimeError) {
    Plato::I2C.register_device(nil)
    Plato::I2C.open(0)
  }
  assert_nothing_raised {
    Plato::I2C.register_device(PlatoPeach::I2C)
    Plato::I2C.open(0)
  }
end

assert('I2C#read') do
  i2c = Plato::I2C.open(0)
  assert_equal([0], i2c.read(0, 1))
  assert_equal([0, 0, 0, 0], i2c.read(0, 4, :as_array))
  assert_equal("\0\0\0", i2c.read(0, 3, :as_string))

  assert_raise(ArgumentError) {i2c.read}
  assert_raise(ArgumentError) {i2c.read(1)}
  assert_raise(ArgumentError) {i2c.read(1, 2, :as_string, 4)}
end

assert('I2C#write') do
  i2c = Plato::I2C.open(0)
  assert_nothing_raised {
    i2c.write(0, 0)
    i2c.write(0, [0, 1, 2, 3])
    i2c.write(0, 'abc')
    i2c.write(0, :off)
    i2c.write(0, 0, false)
    i2c.write(0, 0, true)
  }

  assert_raise(ArgumentError) {i2c.write}
  assert_raise(ArgumentError) {i2c.write(0)}
  assert_raise(ArgumentError) {i2c.write(0, 1, 2, 3)}
end

assert('I2C#_start/_end') do
  assert_nothing_raised {
    i2c = Plato::I2C.open(0)
    i2c._start
    i2c._end
  }
end
