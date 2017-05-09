assert('GPIO', 'class') do
  assert_equal(Plato::GPIO.class, Class)
  assert_equal(Plato::GPIO.superclass, Object)
end

assert('GPIO', 'D0-D15') do
  assert_equal(Plato::GPIO::D0, 0)
  assert_equal(Plato::GPIO::D1, 1)
  assert_equal(Plato::GPIO::D2, 2)
  assert_equal(Plato::GPIO::D3, 3)
  assert_equal(Plato::GPIO::D4, 4)
  assert_equal(Plato::GPIO::D5, 5)
  assert_equal(Plato::GPIO::D6, 6)
  assert_equal(Plato::GPIO::D7, 7)
  assert_equal(Plato::GPIO::D8, 8)
  assert_equal(Plato::GPIO::D9, 9)
  assert_equal(Plato::GPIO::D10, 10)
  assert_equal(Plato::GPIO::D11, 11)
  assert_equal(Plato::GPIO::D12, 12)
  assert_equal(Plato::GPIO::D13, 13)
  assert_equal(Plato::GPIO::D14, 14)
  assert_equal(Plato::GPIO::D15, 15)
end

assert('GPIO', 'A0-A5') do
  assert_equal(Plato::GPIO::A0, 16)
  assert_equal(Plato::GPIO::A1, 17)
  assert_equal(Plato::GPIO::A2, 18)
  assert_equal(Plato::GPIO::A3, 19)
  assert_equal(Plato::GPIO::A4, 20)
  assert_equal(Plato::GPIO::A5, 21)
end

assert('GPIO', 'LED1-LED4') do
  assert_equal(Plato::GPIO::LED1, 22)
  assert_equal(Plato::GPIO::LED2, 23)
  assert_equal(Plato::GPIO::LED3, 24)
  assert_equal(Plato::GPIO::LED4, 25)
end

assert('GPIO', 'BUTTON1') do
  assert_equal(Plato::GPIO::BUTTON1, 26)
end
