# PlatoPeach::Machine module

assert('Machine - class') do
  assert_kind_of(Class, PlatoPeach::Machine)
  assert_equal(Object, PlatoPeach::Machine.superclass)
end

assert('Machine.register_device') do
  assert_nothing_raised {
    Plato::Machine.register_device(PlatoPeach::Machine)
  }
end

assert('Machine.delay') do
  assert_nothing_raised {
    Plato::Machine.delay(1)
    PlatoPeach::Machine.delay(1)
  }
  assert_raise(ArgumentError) {Plato::Machine.delay}
  assert_raise(ArgumentError) {Plato::Machine.delay(0, 1)}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay(0, 1)}
end

assert('Machine.delay_us') do
  assert_nothing_raised {
    Plato::Machine.delay_us(1)
    PlatoPeach::Machine.delay_us(1)
  }
  assert_raise(ArgumentError) {Plato::Machine.delay_us}
  assert_raise(ArgumentError) {Plato::Machine.delay_us(0, 1)}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay_us}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay_us(0, 1)}
end

assert('Machine.millis') do
  ms = Plato::Machine.millis
  assert_kind_of(Fixnum, ms)
  ms = PlatoPeach::Machine.millis
  assert_kind_of(Fixnum, ms)
end
