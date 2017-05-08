# PlatoMbed::I2C class

assert('I2C', 'class') do
  assert_equal(PlatoMbed::I2C.class, Class)
end

assert('I2C', 'superclass') do
  assert_equal(PlatoMbed::I2C.superclass, Object)
end

assert('I2C', 'new') do
  i1 = PlatoMbed::I2C.new(1)
  i2 = PlatoMbed::I2C.new(2, 3)
  assert_true(i1 && i2)
  assert_equal(i1.instance_variable_get("@addr"), 1 << 1)
  assert_equal(i1.instance_variable_get("@wait"), 1000)
  assert_equal(i2.instance_variable_get("@addr"), 2 << 1)
  assert_equal(i2.instance_variable_get("@wait"), 3)
end

assert('I2C', 'new - argument error') do
  assert_raise(ArgumentError) {PlatoMbed::I2C.new}
  assert_raise(ArgumentError) {PlatoMbed::I2C.new(0, 1, 2)}
end

assert('I2C', 'oepn - Plato::I2C') do
  Plato::I2C.register_device(PlatoMbed::I2C)
  Plato::I2C.open(0)
end

assert('I2C', 'read') do
  i2c = Plato::I2C.open(0)
  assert_equal(i2c.read(0, 1), [0])
  assert_equal(i2c.read(0, 4, :as_array), [0, 0, 0, 0])
  assert_equal(i2c.read(0, 3, :as_string), "\0\0\0")
end

assert('I2C', 'read - argument error') do
  i2c = Plato::I2C.open(0)
  assert_raise(ArgumentError) {i2c.read}
  assert_raise(ArgumentError) {i2c.read(1)}
  assert_raise(ArgumentError) {i2c.read(1, 2, :as_string, 4)}
end

assert('I2C', 'write') do
  assert_nothing_raised {
    i2c = Plato::I2C.open(0)
    i2c.write(0, 0)
    i2c.write(0, [0, 1, 2, 3])
    i2c.write(0, 'abc')
    i2c.write(0, :off)
    i2c.write(0, 0, false)
    i2c.write(0, 0, true)
  }
end

assert('I2C', 'write - argument error') do
  i2c = Plato::I2C.open(0)
  assert_raise(ArgumentError) {i2c.write}
  assert_raise(ArgumentError) {i2c.write(0)}
  assert_raise(ArgumentError) {i2c.write(0, 1, 2, 3)}
end

assert('I2C', '_start/_end') do
  assert_nothing_raised {
    i2c = Plato::I2C.open(0)
    i2c._start
    i2c._end
  }
end
