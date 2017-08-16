include Plato

leds = [
  [LED.new(GPIO::LED1), 3], # red
  [LED.new(GPIO::LED2), 5], # green
  [LED.new(GPIO::LED3), 7]  # blue
]

i = 0
loop {
  leds.each {|led|
    led[0].toggle if i % led[1] == 0
  }
  i += 1
  Machine.delay(100)
}
