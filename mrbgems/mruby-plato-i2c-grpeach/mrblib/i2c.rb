#
# PlatoPeach::I2C class
#
module PlatoPeach
  class I2C
    include Plato::I2C
  end
end

# register GR-PEACH device
Plato::I2C.register_device(PlatoPeach::I2C)
