#
# PlatoPeach::SPI class
#

# register GR-PEACH device
Plato::SPI.register_device(PlatoPeach::SPI)

# for SPI test
module PlatoDevice
  class W5200
    def initialize(mode, ss)
      @spi = Plato::SPI.open(mode, nil, :msbfirst, ss)
    end

    def mac
      addr = []
      6.times {|i|
        addr << _read(0x0009 + i)
      }
      addr
    end

    # private
    def _read(reg)
      @spi._start
      @spi.transfer((reg & 0xff00) >> 8)
      @spi.transfer(reg & 0xff)
      @spi.transfer(0x00) # read
      @spi.transfer(0x01) # 1byte
      v = @spi.transfer(0)
      @spi._end
      v
    end
  end
end
