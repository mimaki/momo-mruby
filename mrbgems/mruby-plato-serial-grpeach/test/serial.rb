# PlatoPeach::Serial class

assert('Serial - class') do
  assert_kind_of(Class, PlatoPeach::Serial)
  assert_equal(Object, PlatoPeach::Serial.superclass)
end

assert('Serial#new') do
  assert_nothing_raised {
    PlatoPeach::Serial.new(1200)
    PlatoPeach::Serial.new(2400, 7)
    PlatoPeach::Serial.new(4800, 8, 1)
    PlatoPeach::Serial.new(9600, 8, 1, 1)
    PlatoPeach::Serial.new(19200, 8, 1, 1, :odd)
    PlatoPeach::Serial.new(38400, 8, 1, 1, :even)
    PlatoPeach::Serial.new(115200, 8, 1, 1, :none)
    PlatoPeach::Serial.new(115200, 8, 1, 1, :xxx)
  }
  assert_raise(ArgumentError) {PlatoPeach::Serial.new}
  assert_raise(ArgumentError) {PlatoPeach::Serial.new(9600, 8, 1, 1, :none, 0)}
end

assert('Serial.oepn - Plato::Serial') do
  assert_nothing_raised {
    Plato::Serial.register_device(PlatoPeach::Serial)
    Plato::Serial.open(9600)
  }
end

assert('Serial#_read') do
  ser = Plato::Serial.open(9600)
  assert_equal(-1, ser._read)
end

assert('Serial#_write') do
  ser = Plato::Serial.open(9600)
  assert_nothing_raised {
    ser._write(1)
  }
  assert_raise(ArgumentError) {ser.write}
  assert_raise(ArgumentError) {ser.write(0, 1)}
end

assert('Serial#available') do
  ser = Plato::Serial.open(9600)
  assert_equal(0, ser.available)
end

assert('Serial#flush') do
  assert_nothing_raised {
    ser = Plato::Serial.open(9600)
    ser.flush
  }
end

assert('Serial#close') do
  assert_nothing_raised {
    ser = Plato::Serial.open(9600)
    ser.close
  }
end
