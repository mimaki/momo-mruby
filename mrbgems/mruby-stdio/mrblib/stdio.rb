$/ = "\n" unless $/

#
# STDOUT
#

class STDOUT
  class << self
    def _putc(c)
      raise "STDOUT._putc not implemented."
    end

    def putc(c)
      c = c.ord if c.is_a?(String)
      _putc(c)
    end

    def puts(*args)
      unless args
        putc $/
      else
        args.each {|o|
          o = o.to_s unless o.is_a?(String)
          o << $/ unless o[-1] == $/
          o.each_char {|c| putc(c)}
        }
      end
      nil
    end
  end
end


#
# STDIN
#

class STDIN
  class << self
    def _getc
      raise "STDIN._getc not implemented."
    end

    def getc
      c = _getc
      c && c >= 0 ? c.chr : nil
    end

    def gets(*args)
      rs = $/
      limit = -1
      case args.size
      when 0
      when 1
        if args[0].is_a?(String)
          rs = args[0]
        elsif args[0].is_a?(Fixnum)
          limit = args[0]
        else
          raise TypeError.new
        end
      when 2
        rs, limit = args
      else
        raise ArgumentError.new
      end

      str = ''
      while c = getc
        str << c
        break if c == rs
        break if limit > 0 && str.length >= limit
      end
      $_ = str.length > 0 ? str : nil
    end

    def readline(*args)
      str = gets(args)
      raise EOFError.new unless str
      str
    end
  end
end

$stdin = STDIN
$stdout = STDOUT

module Kernel
  def getc
    $stdin.getc if $stdin
  end

  def gets(*args)
    $stdin.gets(*args) if $stdin
  end

  def putc(c)
    $stdout.putc(c) if $stdout
  end
end
