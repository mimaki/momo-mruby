# PlatoPeach::Machine module

assert('Machine', 'class') do
  assert_equal(PlatoPeach::Machine.class, Class)
end

assert('Machine', 'register_device') do
  assert_nothing_raised {
    Plato::Machine.register_device(PlatoPeach::Machine)
  }
end

assert('Machine', 'delay') do
  assert_nothing_raised {
    Plato::Machine.delay(1)
    PlatoPeach::Machine.delay(1)
  }
  assert_raise(ArgumentError) {Plato::Machine.delay}
  assert_raise(ArgumentError) {Plato::Machine.delay(0, 1)}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay(0, 1)}
end

assert('Machine', 'delay_us') do
  assert_nothing_raised {
    Plato::Machine.delay_us(1)
    PlatoPeach::Machine.delay_us(1)
  }
  assert_raise(ArgumentError) {Plato::Machine.delay_us}
  assert_raise(ArgumentError) {Plato::Machine.delay_us(0, 1)}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay_us}
  assert_raise(ArgumentError) {PlatoPeach::Machine.delay_us(0, 1)}
end

assert('Machine', 'millis') do
  ms = Plato::Machine.millis
  assert_equal(ms.class, Fixnum)
  ms = PlatoPeach::Machine.millis
  assert_equal(ms.class, Fixnum)
end

# assert('Machine', 'micros') do
#   us = Plato::Machine.millis
#   assert_equal(us.class, Fixnum)
#   us = PlatoPeach::Machine.millis
#   assert_equal(us.class, Fixnum)
# end
