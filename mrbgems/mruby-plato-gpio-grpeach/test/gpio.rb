assert('GPIO - class') do
  assert_kind_of(Class, Plato::GPIO)
  assert_equal(Object, Plato::GPIO.superclass)
end

assert('GPIO::D0-D15') do
  assert_equal(0, Plato::GPIO::D0)
  assert_equal(1, Plato::GPIO::D1)
  assert_equal(2, Plato::GPIO::D2)
  assert_equal(3, Plato::GPIO::D3)
  assert_equal(4, Plato::GPIO::D4)
  assert_equal(5, Plato::GPIO::D5)
  assert_equal(6, Plato::GPIO::D6)
  assert_equal(7, Plato::GPIO::D7)
  assert_equal(8, Plato::GPIO::D8)
  assert_equal(9, Plato::GPIO::D9)
  assert_equal(10, Plato::GPIO::D10)
  assert_equal(11, Plato::GPIO::D11)
  assert_equal(12, Plato::GPIO::D12)
  assert_equal(13, Plato::GPIO::D13)
  assert_equal(14, Plato::GPIO::D14)
  assert_equal(15, Plato::GPIO::D15)
end

assert('GPIO::A0-A5') do
  assert_equal(16, Plato::GPIO::A0)
  assert_equal(17, Plato::GPIO::A1)
  assert_equal(18, Plato::GPIO::A2)
  assert_equal(19, Plato::GPIO::A3)
  assert_equal(20, Plato::GPIO::A4)
  assert_equal(21, Plato::GPIO::A5)
end

assert('GPIO::LED1-LED4') do
  assert_equal(22, Plato::GPIO::LED1)
  assert_equal(23, Plato::GPIO::LED2)
  assert_equal(24, Plato::GPIO::LED3)
  assert_equal(25, Plato::GPIO::LED4)
end

assert('GPIO::BUTTON1') do
  assert_equal(26, Plato::GPIO::BUTTON1)
end
