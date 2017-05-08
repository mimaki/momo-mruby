#
# PlatoMbed::I2C class
#
module PlatoMbed
  class I2C
    include Plato::I2C
  end
end

# register mbed device
Plato::I2C.register_device(PlatoMbed::I2C)
