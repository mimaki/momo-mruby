# Plato::DigitalIO module

assert('DigitalIO', 'class') do
  assert_equal(Plato::DigitalIO.class, Class)
end

assert('DigitalIO', 'superclass') do
  assert_equal(Plato::DigitalIO.superclass, Plato::GPIO)
end

assert('DigitalIO', 'new') do
  dio = Plato::DigitalIO.new(1);
  assert_equal(dio.instance_variable_get(:@pin), 1)
  assert_raise(ArgumentError) {Plato::DigitalIO.new}
  assert_raise(ArgumentError) {Plato::DigitalIO.new(0, 1)}
end

assert('DigitalIO', 'read') do
  v = Plato::DigitalIO.new(0).read
  assert_equal(v.class, Fixnum)
end

assert('DigitalIO', 'write') do
  dio = Plato::DigitalIO.new(0)
  assert_nothing_raised {
    dio.write(1)
  }
  assert_raise(ArgumentError) {dio.write}
  assert_raise(ArgumentError) {dio.write(0, 1)}
end
