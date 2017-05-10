#
# PlatoMbed::Serial class
#
module PlatoPeach
  class Serial
    include Plato::Serial
  end
end

# register GR-PEACH device
Plato::Serial.register_device(PlatoPeach::Serial)
