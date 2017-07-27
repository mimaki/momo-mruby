# Plato::DigitalIO module

assert('DigitalIO - class') do
  assert_kind_of(Class, Plato::DigitalIO)
  assert_equal(Plato::GPIO, Plato::DigitalIO.superclass)
end

assert('DigitalIO#new') do
  dio = Plato::DigitalIO.new(1);
  assert_equal(1, dio.instance_variable_get(:@pin))
  assert_raise(ArgumentError) {Plato::DigitalIO.new}
  # assert_raise(ArgumentError) {Plato::DigitalIO.new(0, 1)}
end

assert('DigitalIO#read') do
  v = Plato::DigitalIO.new(0).read
  assert_kind_of(Fixnum, v)
end

assert('DigitalIO#write') do
  dio = Plato::DigitalIO.new(0)
  assert_nothing_raised {
    dio.write(1)
  }
  assert_raise(ArgumentError) {dio.write}
  assert_raise(ArgumentError) {dio.write(0, 1)}
end
